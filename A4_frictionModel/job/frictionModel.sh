#!/bin/bash
#SBATCH --job-name=frictionModel         # Name of the job
#SBATCH --ntasks=1                       # Number of tasks
#SBATCH --time=01:00:00                  # Time limit

# Load necessary modules
module load gcc rarray boost


# Run the analysis of a friction model time-series data in the parent directory
make -C $HOME/assignment4 analysis
make -C $HOME/assignment4 doc
#make -C $HOME/assignment4 clean
