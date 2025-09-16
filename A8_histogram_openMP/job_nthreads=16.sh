#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=16
#SBATCH --time=1:00:00
#SBATCH --output=output_16threads.txt

module load gcc/13 rarray
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

make clean
make

./parallel_hist 1.3 stepnumbers.dat