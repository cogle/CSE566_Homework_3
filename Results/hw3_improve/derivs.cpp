//////////////////////////////////////////////////////////
// GalaxSee (version MPI 0.9)
// Copyright 1997 - 2002
// David A. Joiner and the Shodor Education Foundation
//////////////////////////////////////////////////////////

#include <math.h>
#include "modeldata.h"
#include "mpidata.h"
#include "mpi.h"

#include <stdio.h>

extern modeldata g_dynamic;
extern mpidata g_mpi;

void derivs(int n,double time,double * x, double * der){
    extern int max(int,int);

// For ease of use, create cart3d variables, associate them
// with locations in the given arrays, and write equations in
// terms of points rather than x and der.

    cart3d pos;
    cart3d vel;
    cart3d xder;
    cart3d vder;
    mapPoints(n,3,x,der,&pos,&vel,&xder,&vder);

// BEGIN DEFINING ACCELERATIONS HERE, FOOLOWED BY DEFINITION
// OF XDER AS CURRENT VELOCITY.

    int i;    
    double * shield_rad;

    // precondition problem before force calculation,
    // set up sheild radii, build trees, meshes.
    shield_rad = new double[g_dynamic.npoints+1];
    #pragma omp parallel shared(shield_rad, g_dynamic, vder) private(i)
    {
      #pragma omp for 
      for(i=0;i<g_dynamic.npoints;i++) {
        shield_rad[i]=g_dynamic.comp_s_rad((g_dynamic.gnorm*
            g_dynamic.mass[i]),g_dynamic.time_step);
        vder.x[i]=0.0;
        vder.y[i]=0.0;
        vder.z[i]=0.0;
      }
    }
    //For MPI Version, need to pass once to each processor
    // - g_dynamic.npoints
    // - g_dynamic.gnorm
    // - g_dynamic.mass
    // - shield_rad
    // - x
        
    MPI_Request * message_request = new MPI_Request[g_mpi.size];
    MPI_Request * number_request = new MPI_Request[g_mpi.size];
    MPI_Request * numberper_request = new MPI_Request[g_mpi.size];
    MPI_Request * gnorm_request = new MPI_Request[g_mpi.size];
    MPI_Request * mass_request = new MPI_Request[g_mpi.size];
    MPI_Request * srad_request = new MPI_Request[g_mpi.size];
    MPI_Request * x_request = new MPI_Request[g_mpi.size];
    
    // decide how to split up problem
    int * number_per_cpu = new int[g_mpi.size];
    int block = (g_dynamic.npoints)/(g_mpi.size);
    for (int i=0;i<g_mpi.size;i++) {
        number_per_cpu[i] = block;
        if (i==g_mpi.size-1) {
            //last client gets overflow
            number_per_cpu[i]+=g_dynamic.npoints-g_mpi.size*block;
        }
    }
    
    // tell clients to get ready for data and send it
    for (int i=1;i<g_mpi.size;i++) {
        MPI_Isend(0,0,MPI_INT,i,MPIDATA_DODERIVS,
            MPI_COMM_WORLD,&message_request[i]);
        MPI_Isend(&g_dynamic.npoints,1,MPI_INT,i,MPIDATA_PASSNUMBER,
            MPI_COMM_WORLD,&number_request[i]);             
        MPI_Isend(&number_per_cpu[i],1,MPI_INT,i,MPIDATA_PASSNUMBERPER,
            MPI_COMM_WORLD,&numberper_request[i]);
        MPI_Isend(&g_dynamic.gnorm,1,MPI_DOUBLE,i,MPIDATA_PASSGNORM,
            MPI_COMM_WORLD,&gnorm_request[i]);
        MPI_Isend(g_dynamic.mass,g_dynamic.npoints,MPI_DOUBLE,i,
            MPIDATA_PASSMASS,MPI_COMM_WORLD,&mass_request[i]);
        MPI_Isend(shield_rad,g_dynamic.npoints,MPI_DOUBLE,i,
            MPIDATA_PASSSHIELD,MPI_COMM_WORLD,&srad_request[i]);
        MPI_Isend(x,g_dynamic.npoints*6,MPI_DOUBLE,i,
            MPIDATA_PASSX,MPI_COMM_WORLD,&x_request[i]);
        // have it wait here for a message that the work has been
        // completed.
    }
    
    // determine number of processes, decide
    // on which processes will solve which
    // parts of problem


    // For each body, compute accelerations.
    int num =number_per_cpu[0];
    #pragma omp parallel shared(num,shield_rad,vder,xder) private(i)
    {
      double rad2,rad,diff,diffx,diffy,diffz,dcon;
      #pragma omp for
      for(i=0;i<num;i++){
        for(int j=0;j<g_dynamic.npoints;j++){
          if (i!=j) {
            rad2=pow((pos.x[i]-pos.x[j]),2)+
                pow((pos.y[i]-pos.y[j]),2)+
                pow((pos.z[i]-pos.z[j]),2);
            rad=sqrt(rad2);
            dcon=g_dynamic.gnorm/(rad*rad2);
            diffx=(pos.x[j]-pos.x[i])*dcon;
            diffy=(pos.y[j]-pos.y[i])*dcon;
            diffz=(pos.z[j]-pos.z[i])*dcon;

            if (rad>shield_rad[j]) {
                vder.x[i]+=diffx*g_dynamic.mass[j];
                vder.y[i]+=diffy*g_dynamic.mass[j];
                vder.z[i]+=diffz*g_dynamic.mass[j];
            }
           // if (rad>shield_rad[i]) {
           //     vder.x[j]-=diffx*g_dynamic.mass[i];
           //     vder.y[j]-=diffy*g_dynamic.mass[i];
           //     vder.z[j]-=diffz*g_dynamic.mass[i];
           // }
           }
        }
        xder.x[i]=vel.x[i];
        xder.y[i]=vel.y[i];
        xder.z[i]=vel.z[i];
      }
    }
    
    
    for (int i=1;i<g_mpi.size;i++) {
    
        //wait for processes to complete sending
        MPI_Wait(&message_request[i], &g_mpi.status );
        MPI_Wait(&number_request[i], &g_mpi.status );
        MPI_Wait(&numberper_request[i], &g_mpi.status );
        MPI_Wait(&gnorm_request[i], &g_mpi.status );
        MPI_Wait(&mass_request[i], &g_mpi.status );
        MPI_Wait(&srad_request[i], &g_mpi.status );
        MPI_Wait(&x_request[i], &g_mpi.status );

    }
    
    for (int i=1;i<g_mpi.size;i++) {
    
        // get replies
        double * retval = new double[number_per_cpu[i]*6];
        MPI_Recv(retval,number_per_cpu[i]*6,
            MPI_DOUBLE,i,MPIDATA_DONEDERIVS,MPI_COMM_WORLD,
            &g_mpi.status);
        
        
        //compare replies
        int num_per_cpu = number_per_cpu[i];
        #pragma omp parallel shared(xder, vder, num_per_cpu, block)
        {
          #pragma omp for
          for (int ireturn=0;ireturn<num_per_cpu;ireturn++) {
            int ireal = block*i + ireturn;
            xder.x[ireal]=retval[ireturn];
            xder.y[ireal]=retval[num_per_cpu+ireturn];
            xder.z[ireal]=retval[2*num_per_cpu+ireturn];
            vder.x[ireal]=retval[3*num_per_cpu+ireturn];
            vder.y[ireal]=retval[4*num_per_cpu+ireturn];
            vder.z[ireal]=retval[5*num_per_cpu+ireturn];
          }   
        }
        delete retval;

    }
    

    // Clean up dynamically allocated arrays
    delete shield_rad;
    delete message_request;
    delete number_request;
    delete numberper_request;
    delete gnorm_request;
    delete mass_request;
    delete srad_request;
    delete x_request;
    delete number_per_cpu;
}


int max(int input1,int input2) {
    if (input1>input2)
        return input1;
    else
        return input2;
}
