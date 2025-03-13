// initialization.cpp

#include "initialization.h"

// To initialize the cell at the first timestep
// Initialize 'alive_status' based on the 'target_fraction' (Fill cells such that the fraction of alive cells is roughly target_fraction)
// This approach avoids clustering alive cells together by spreading them approximately evenly throughout the vector
rvector<bool> initialize_alive_status(const int &num_cells, const double &target_fraction)
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
