// gameof1d.cpp
//
// This code computes the evolution of a one-dimensional variant of Conway's Game of Life, as conceived by Jonathan K. Millen and published in BYTE magazine in December, 1978.
//
// This system is a linear set of cells that are either "alive" or "dead".
// Time in this system progresses in discrete steps.
//
// Usage: ./gameof1d <total_number_of_cells> <total_number_of_time_steps> <initial_fraction_of_alive_cells>
// Default values: num_cells = 70, num_steps = 120, target_fraction = 0.35
//
// Without command line arguments, the program takes 70 cells computes the time evolution for 120 steps, and for each step, prints out a line with
// a representation of the state and fraction of alive cells.
//
// The state of each cell at the next time step depends on its present state and that of its neighbors, in the following way:
//   - First, count the number of alive neighbors at most 2 cells away
//   - An alive cell stays alive if that count is 2 or 4, else it dies
//   - A dead cell becomes alive if that count is 2 or 3, else it stays dead.
//
// Since the first two and the last two cells would not have enough neighbours to apply
// this rule, we use cells on the other side as neighbours, i.e., 'periodic boundaries'.
//
// The initial state of this system is constructed with a given fraction of alive
// cells which are (nearly) equally spaced among dead cells.
//
//
// This code is part of assignment 2 of the 2025 Winter PHY1610 course.
// Modified by Rojin Anbarafshan from original script written by Ramses van Zon, 2023-2025, University of Toronto
// Date: January 2025

#include <iostream>
#include <rarray> 
#include "initialization.h"
#include "calculate_next_alive_status.h"
#include "output_single_timestep.h"



int main(int argc, char* argv[])
{

    //------------------------------- HANDLING INPUT --------------------------------------//

    // Set default simulation parameters then accept command line arguments
    int num_cells = 70;
    int num_steps = 120;
    double target_fraction = 0.35;
    try {
        if (argc > 1)
            num_cells = std::stoi(argv[1]);
        if (argc > 2)
            num_steps = std::stoi(argv[2]);
        if (argc > 3)
            target_fraction = std::stod(argv[3]);
    } catch(...) {
        std::cout <<
            "Computes a 1d version of Conway's game of life\n\n"
            "Usage:\n"
            "  gameof1d [-h | --help] | [NUMCELLS [NUMSTEPS [FRACTION]]]\n\n";
        
        // Ensuring that the user is not asking for help -> there is an error in arguments
        if (std::string(argv[1]) != "-h" and std::string(argv[1]) != "--help") {
            std::cerr << "Error in arguments!\n";
            return 1;
        } else
            return 0; // for the case tgat tge user requests help
    }


    //------------------------------- INITIALIZATION --------------------------------------//
    // Simulation system is just the alive status of each cell

    rvector<bool> alive_status = initialize_alive_status(num_cells, target_fraction);


    // Define charachters used to display alive/dead cells in the output (when printed to terminal)
    char alive_char = 'O';
    char dead_char  = ' ';

    // Create the output for the first timestep:
    output_single_timestep(0, alive_status, alive_char, dead_char);


    //------------------------------- TIME EVOLUTION --------------------------------------//
    
    // Time loop
    for (int step = 1; step <= num_steps; step++) {

        alive_status = calculate_next_alive_status(alive_status);
        
        // Create the output for each timestep:
        output_single_timestep(step, alive_status, alive_char, dead_char);
    }
}


