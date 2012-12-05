#!/bin/sh

#SBATCH --time=0:05 --time-min=0:04
#SBATCH -N 2 -n 2
#SBATCH --error=job.err --output=job.out

mpiexec ./testprog
