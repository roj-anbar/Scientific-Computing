/// @file init.h
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module for initializing the simulation parameters for solving the PDE for 1D heat diffusion.

#ifndef INIT
#define INIT

#include <iostream>
#include <stdexcept> // to handle exceptions


/// @brief Structure to store the simulation parameters for the solver obtained from command-line input.
struct SimParameters
{

    double L;                  // Length of domain -> sim domain: [0 L)
    int N;                     // Number of spatial grid points
    double dx;                 // Size of spatial spacing (grid size) 
    double A;                  // Amplitude of boundary condition at x = 0

    double T;                  // Total time of simulation
    double dt;                 // Size of timestep
    int Nt;                    // Total number of timesteps
    double P;                  // Number of snapshots to output
    int output_interval;       // Number of timesteps between each two output
};



/// @brief Function to store the command-line arguments into simulation parameters.
SimParameters store_commandline_args(int argc, char *argv[]);

/// @brief Print the parameters (for debugging and confirmation)
void print_sim_parameters(const SimParameters &sim_params);

#endif