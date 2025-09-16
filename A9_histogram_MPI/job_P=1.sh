#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --time=1:00:00
#SBATCH --output=output_P=1.txt

module load gcc/13 openmpi/5 rarray

make clean
make

# Run first version
mpirun -n 1 ./parallel_histogram_MPI 1.1 morestepnumbers_1.7GB.dat 100000

# Run second version
mpirun -n 1 ./parallel_histogram_MPI_v2 1.1 morestepnumbers_1.7GB.dat 100000