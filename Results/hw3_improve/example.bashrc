# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
        . /etc/bashrc
fi

# User specific aliases and functions
MPI=/cluster/engine/mpich-3.1.2
export MPI
PATH=/cluster/engine/mpich-3.1.2/bin:$PATH
PATH=$PATH:/cluster/engine/scorep-1.2.3/bin/:/cluster/engine/scalasca-2.0/bin/:/home/warehouse/dshook
LD_LIBRARY_PATH=/cluster/engine/mpich-3.1.2/lib:LD_LIBRARY_PATH
export PATH

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/cluster/engine/mpich-3.1.2/lib
export LD_LIBRARY_PATH
