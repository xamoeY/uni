#!/bin/sh

# Time limit is one minute.
# See "man sbatch" for other time formats.
#SBATCH --time=0:05 --time-min=0:04
# Run 10 tasks on 2 nodes.
#SBATCH -N 2 -n 10
# Output goes to job.out, error messages to job.err.
#SBATCH --error=job.err --output=job.out

mpiexec ./timempi

