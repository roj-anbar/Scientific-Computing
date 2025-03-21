/// @file percolation_model.cpp
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Main driver script to simulate the percolation model through a 2D lattice.
/// In the simulation, walkers are launched from every empty cell in the top row.
/// Each walker moves randomly (left, right, up, or down) with probabilities based on a bias parameter g and continues for a maximum number of steps.
/// The simulation repeats K times for each empty top cell.
/// The final output is the fraction of walkers that successfully passed through the lattice and reached the bottom row.
/// The simulation parameters (lattice dimensions, probability of an empty cell, bias parameter, number of walkers per cell, etc.) are read from the command-line.
 
#include "init.h"
#include "setup_lattice.h"
#include "single_walker.h"

#include <rarray>
#include <cmath>
#include <stdexcept>

/// @brief Main function that simulates the percolation model with random walkers.
/// This function obtains simulation parameters from the command line, sets up a boolean lattice, and then for each empty cell
/// in the top row launches K walkers. Each walker is simulated for a maximum number of steps
/// and the simulation determines the fraction of walkers that reach the bottom.
/// @param argc Number of command-line arguments.
/// @param argv Array of command-line argument strings.
/// @return Fraction of walkers that passed the lattice successfully.

int main(int argc, char *argv[])
{
    //------------------ INITIALIZE --------------------------//

    // Obtain the simulation parameters from command-line inputs
    SimParameters sim_params = store_commandline_args(argc, argv);

    // Print the simulation parameters for confirmation
    print_sim_parameters(sim_params);

    // Store the useful simulation parameters to local variables
    int M = sim_params.M;                 // Number of columns (lattice is M cells wide).
    int N = sim_params.N;                 // Number of rows (lattice is N cells high).
    double p = sim_params.p;              // Probability of each cell being empty.
    double g = sim_params.g;              // Downwards tendency (positive constant).
    int K = sim_params.K;                 // Number of repetitions (#walkers per each empty cell).
    //int S = sim_params.S;                 // Parameter used in max number of steps for each walker.
    int seed = sim_params.seed;           // Initial seed for random generator.
    int max_steps = sim_params.max_steps; // Maximum number of allowed steps for each walker.


    // Set up the lattice where false = empty and true = filled
    rmatrix<int> lattice(N,M);
    setup_lattice(M, N, p, lattice, seed);



    //------------------------- SIMULATION ----------------------------//
    
    // Initialize variables used for counting
    int total_walkers = 0;  // total number of walkers
    int walkers_passed = 0; // number of walkers passed the lattice
    
    
    // Loop over each cell in the top row
    for (int j = 0; j < M; j++)
    { 
        // Launch a walker if cell is empty
        if (lattice[0][j] == 0) 
        {
            // Repeat simulation for K walkers
            for (int k = 0; k < K; k++)
            {
                bool passed = simulate_walker(lattice, M, N, g, max_steps, seed, j);

                // If the walker passed -> add 1 to number of passed walkers
                if (passed)
                    walkers_passed++;

                // Add one to total number of walkers
                total_walkers++;
            }
        }
    }
    

    // Calculate fraction of walkers that passed the lattice
    double fraction_passed = static_cast<double>(walkers_passed) / total_walkers;

    // Print the fraction to display
    std::cout << "Total number of walkers: " << total_walkers << std::endl;
    std::cout << "Number of walkers successfully passing the lattice: " << walkers_passed << std::endl;
    std::cout << "Fraction of walkers successfully passing the lattice: " << fraction_passed << std::endl;

    return 0;
}