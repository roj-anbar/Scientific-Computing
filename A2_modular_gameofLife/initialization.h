//initialization.h

#ifndef INIT_H
#define INIT_H

#include <rarray>

// Declaration of initialization function
// To initialize the cell at the first timestep
rvector<bool> initialize_alive_status(const int& num_cells, const double& target_fraction);

#endif