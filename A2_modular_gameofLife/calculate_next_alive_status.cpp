// calculate_next_alive_status.cpp

#include "calculate_next_alive_status.h"


// Local function used only in this module
// Takes the current status 'cell_alive' vector and the 'index' of the cell of interest
// and determines whether or not it should remain alive for next step based on the alive status of its neighboring cells.
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

// Public function (used in main)
// Loop over all elements and call 'is_cell_alive_next' on each
rvector<bool> calculate_next_alive_status(const rvector<bool> &alive_status)
{
    // Update cells (create a boolean rvector to hold the alive status at next timestep)
    rvector<bool> next_alive_status(alive_status.size());

    // Loop over elements of 'alive_status'
    for (int i = 0; i < alive_status.size(); i++)
        next_alive_status[i] = is_cell_alive_next(alive_status, i);

    // Update the 'alive_status': Make next status the current one using swap, which avoids a copy
    //std::swap(alive_status, next_alive_status);
    return next_alive_status;
}






