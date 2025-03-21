/// @file init.h
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module for initializing the simulation parameters for solving the percolation model for a 2D lattice.

#ifndef INIT
#define INIT

#include <iostream>
#include <stdexcept> // to handle exceptions


/// @brief Structure to store the simulation parameters obtained from command-line input.
struct SimParameters
{

    int M;                  // Number of columns (lattice is M cells wide).
    int N;                  // Number of rows (lattice is N cells high).
    double p;               // Probability of each cell being empty.
    double g;               // Downwards tendency (positive constant).
    int K;                  // Number of repetitions (#walkers per each empty cell).
    int S;                  // Parameter used in max number of steps for each walker.
    int seed;               // Initial seed for random generator.

    int max_steps;          // Maximum number of allowed steps for each walker.
};

/// @brief Function to store the command-line arguments into simulation parameters.
SimParameters store_commandline_args(int argc, char *argv[]);

/// @brief Print the parameters (for debugging and confirmation)
void print_sim_parameters(const SimParameters &sim_params);

#endif