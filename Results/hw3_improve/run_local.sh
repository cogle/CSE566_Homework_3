#!/bin/sh
#
#  Sample openmpi job executed locally
#
#make -n    <- will show compile command without running it
#make       #<- will actually make a.out
#
#  Use mpiexec to run on local machine.
#
#number after -n is number of nodes
#parameters are: numstars starmass t_final display (display may be 1 for local run)
make 
module add cse566
export OMP_NUM_THREADS=2
mpiexec -n 4 ./a.out 20000 200.0 6000 0
rm -rf a.out

exit 0
