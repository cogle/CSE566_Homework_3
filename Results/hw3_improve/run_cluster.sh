#!/bin/sh
#
#  Sample openmpi job
#  Change this script to refer to your path below.
#  Compile the program with tau_cc.sh.
#
#make -n    <- will show compile command without running it
#make       <- will actually make a.out

#$ -q all.q
#$ -N JOB_NAME
#$ -pe mpi 16
#$ -cwd 


#parameters are: numstars starmass t_final display (display must be 0 for cluster run)
#change the line below to refer to your path.
module add cse566
mpiexec --mca btl ^openib /path/to/executable/a.out 1024 200.0 1000 0

exit 0
