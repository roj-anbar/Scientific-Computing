/// @file init.cpp
/// @author Rojin Anbarafshan
/// @date March 07, 2025
/// @brief Module for initializing the simulation parameters for solving the PDE for 1D heat diffusion.

#include "init.h"
#include <iostream>
#include <stdexcept> // to handle exceptions


/// @brief Function to store the command-line arguments into simulation parameters.
/// @param argc Number on input command-line arguments.
/// @param argv String containing all the input command-line arguments.
/// @return Outputs a 'SimParameters' structure containing all the simulation parameters.
SimParameters store_commandline_args(int argc, char* argv[])
{
    // Check if the correct number of arguments was entered by user
    if (argc != 7)
    {
        std::cerr << "Missing arguments: You must input values for (P, L, A, N, T, Solver_Type)! \n";
        throw std::runtime_error("Not enough input arguments."); // terminates program if inputs are wrong
    }

    // Create the output structure
    SimParameters sim_params;

    // Set some default or fixed number of time steps
    sim_params.Nt = 10000;

    // Store commandline arguments
    sim_params.P = std::stod(argv[1]);
    sim_params.L = std::stod(argv[2]);
    sim_params.A = std::stod(argv[3]);
    sim_params.N = std::stoi(argv[4]);
    sim_params.T = std::stod(argv[5]);
    sim_params.solver_type = argv[6];

    // Calculate secondary parameters
    sim_params.dx = sim_params.L / (sim_params.N-1);
    sim_params.dt = sim_params.T / sim_params.Nt;
    sim_params.output_interval = sim_params.Nt / static_cast<int>(sim_params.P); // output each (Nt/P) timesteps
    sim_params.alfa = sim_params.dt / (sim_params.dx * sim_params.dx);


    // Check the stability condition
    if (sim_params.alfa > 0.5)
    {
        throw std::runtime_error("Stability condition not met! Please decrease timestep size!");
    }

    return sim_params;
}




/// @brief Function to print the simulation parameters to the command-line (for sanity check).
// Parse command line arguments into our SimParameters struct
void print_sim_parameters(const SimParameters& sim_params)
{
    std::cout << "----------------------------------------\n"
              << "Simulation Parameters:\n"
              << "P               = " << sim_params.P << "\n"
              << "L               = " << sim_params.L << "\n"
              << "A               = " << sim_params.A << "\n"
              << "N               = " << sim_params.N << "\n"
              << "T               = " << sim_params.T << "\n"
              << "solver_type     = " << sim_params.solver_type << "\n"
              << "dx              = " << sim_params.dx << "\n"
              << "Nt              = " << sim_params.Nt << "\n"
              << "dt              = " << sim_params.dt << "\n"
              << "output_interval = " << sim_params.output_interval << "\n"
              << "alfa            = " << sim_params.alfa << "\n"
              << "----------------------------------------\n";
}