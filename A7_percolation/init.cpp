/// @file init.cpp
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module for initializing the simulation parameters for solving the percolation model for a 2D lattice.

#include "init.h"
#include <iostream>
#include <stdexcept> // to handle exceptions


/// @brief Function to store the command-line arguments into simulation parameters.
/// @param argc Number on input command-line arguments.
/// @param argv String containing all the input command-line arguments.
/// @return Outputs a 'SimParameters' structure containing all the simulation parameters.
SimParameters store_commandline_args(int argc, char* argv[])
{
    // Check if the correct number of arguments was entered by user (argc is one more than actual input arguments)
    if (argc != 8)
    {
        std::cerr << "Missing arguments: You must input values for (M, N, p, g, K, S, seed)! \n";
        throw std::runtime_error("Not enough input arguments."); // terminates program if inputs are wrong
    }

    // Create the output structure
    SimParameters sim_params;


    // Store commandline arguments
    sim_params.M = std::stoi(argv[1]);
    sim_params.N = std::stoi(argv[2]);
    sim_params.p = std::stod(argv[3]);
    sim_params.g = std::stod(argv[4]);
    sim_params.K = std::stoi(argv[5]);
    sim_params.S = std::stoi(argv[6]);
    sim_params.seed = std::stoi(argv[7]);

    // Calculate secondary parameters
    // Maximum number of allowed steps for each walker S*(M^2+N^2)
    sim_params.max_steps = sim_params.S * (sim_params.M * sim_params.M + sim_params.N * sim_params.N);


    return sim_params;
}




/// @brief Function to print the simulation parameters to the command-line (for sanity check).
// Parse command line arguments into our SimParameters struct
void print_sim_parameters(const SimParameters& sim_params)
{
    std::cout << "----------------------------------------\n"
              << "Simulation Parameters:\n"
              << "M               = " << sim_params.M << "\n"
              << "N               = " << sim_params.N << "\n"
              << "p               = " << sim_params.p << "\n"
              << "g               = " << sim_params.g << "\n"
              << "K               = " << sim_params.K << "\n"
              << "S               = " << sim_params.S << "\n"
              << "seed            = " << sim_params.seed << "\n"
              << "max_steps       = " << sim_params.max_steps << "\n"
              << "----------------------------------------\n";
}