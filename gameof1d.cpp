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
#include <rarray> //installed in /usr/local/include

// Determine the next alive status of the cell at location 'index' within the linear set of cells 'cell_alive',
// based on the alive status of its neighboring cells.
// 'cell_alive' is a boolean rvector

// Function: Takes the current status 'cell_alive' vector and the 'index' of the cell of interest and determines whether or not it should remain alive for next step
bool is_cell_alive_next(const rvector<bool> &cell_alive, int index)
{
    int num_cells = cell_alive.size();                                            // total number of cells
    int alive_neighbours = 0;                                                     // declare a variable for the number of alive neighbors
    for (int offset = -2; offset <= 2; offset++)                                  // loop over the neighbors starting from (i-2) to (i+2)
        if (offset != 0 and cell_alive[(index + offset + num_cells) % num_cells]) // modulus (%) enforces periodic boundary conditions
            alive_neighbours++;

    // Decide the next alive status based on the alive neighbors
    if (cell_alive[index] and
        (alive_neighbours == 2 or alive_neighbours == 4))
        return true;

    else if (not cell_alive[index] and
             (alive_neighbours == 2 or alive_neighbours == 3))
        return true;

    else
        return false;
}

// Function: To initialize the cell at the first timestep
// Initialize 'alive_status' based on the 'target_fraction' (Fill cells such that the fraction of alive cells is roughly target_fraction)
// This approach avoids clustering alive cells together by spreading them approximately evenly throughout the vector
auto initialize_alive_status(const int &num_cells, const double &target_fraction)
{

    // Initialize 'alive_status' as a boolean rvector where all cells are dead (default sets each element to FALSE)
    rvector<bool> initial_alive_status(num_cells);

    // Iterate over each element of 'alive_status' -> 'alive' is a reference to each element
    // Modifications to 'alive' will directly update the corresponding element in 'alive_status'
    double fill = 0.0;
    for (bool &alive : initial_alive_status)
    {
        fill += target_fraction;
        if (fill >= 1.0)
        {
            alive = true;
            fill -= 1.0;
        }
        else
        {
            alive = false;
        }
    }

    return initial_alive_status;
}

int main(int argc, char *argv[])
{

    //------------------------------- HANDLING INPUT --------------------------------------//

    // Set default simulation parameters then accept command line arguments
    int num_cells = 70;
    int num_steps = 120;
    double target_fraction = 0.35;
    try
    {
        if (argc > 1)
            num_cells = std::stoi(argv[1]);
        if (argc > 2)
            num_steps = std::stoi(argv[2]);
        if (argc > 3)
            target_fraction = std::stod(argv[3]);
    }
    catch (...)
    {
        std::cout << "Computes a 1d version of Conway's game of life\n\n"
                     "Usage:\n"
                     "  gameof1d [-h | --help] | [NUMCELLS [NUMSTEPS [FRACTION]]]\n\n";

        // Ensuring that the user is not asking for help -> there is an error in arguments
        if (std::string(argv[1]) != "-h" and std::string(argv[1]) != "--help")
        {
            std::cerr << "Error in arguments!\n";
            return 1;
        }
        else
            return 0; // for the case tgat tge user requests help
    }

    //------------------------------- INITIALIZATION --------------------------------------//
    // Simulation system is just the alive status of each cell

    rvector<bool> alive_status = initialize_alive_status(num_cells, target_fraction);

    //------------------------------- HANDLING OUTPUT --------------------------------------//

    // Output time step, alive of cells, and fraction of alive cells

    // Define charachters used to display alive/dead cells in the output (when printed to terminal)
    char alive_char = 'O';
    char dead_char = ' ';

    // Create the output for the first timestep:

    // Calculate the fraction of alive cells
    double fraction = std::count(alive_status.begin(), alive_status.end(), true) / double(alive_status.size());

    // Decalring a variable for the string to be printed on display
    std::string string_represention(alive_status.size(), ' ');

    // Looping over each elemnt of 'alive_status' and print the desired stuff to output (only for the first timestep)
    for (int i = 0; i < alive_status.size(); i++)
        if (alive_status[i])
            string_represention[i] = alive_char;
        else
            string_represention[i] = dead_char;

    std::cout << 0 << "\t" << string_represention << " " << fraction << "\n";

    //------------------------------- TIME LOOP --------------------------------------//
    // Time evolution loop
    for (int step = 1; step <= num_steps; step++)
    {

        // Update cells (create a boolean rvector to hold the alive status at next timestep)
        rvector<bool> next_alive_status(alive_status.size());

        // Loop over elements of 'alive_status'
        for (int i = 0; i < alive_status.size(); i++)
            next_alive_status[i] = is_cell_alive_next(alive_status, i);

        // Update the 'alive_status': Make next status the current one using swap, which avoids a copy
        std::swap(alive_status, next_alive_status);

        // Output time step, life status of cells, and fraction of alive cells
        fraction = std::count(alive_status.begin(), alive_status.end(), true) / double(alive_status.size());

        for (int i = 0; i < num_cells; i++)
            if (alive_status[i])
                string_represention[i] = alive_char;
            else
                string_represention[i] = dead_char;
        std::cout << step << "\t" << string_represention << " " << fraction << "\n";
    }
}
