//output_single_timestep.h

#ifndef SINGLE_TIMESTEP_H
#define SINGLE_TIMESTEP_H

#include <iostream>
#include <rarray>

// To create and print the output for one single timestep
// Inputs: timestep (int), current allive status (boolean rvector), assigned charachters for displaying alive and dead cells
// Outputs: a single string line containing current time step, current status of cells, and fraction of alive cells

// Declaration of the function
void output_single_timestep(const int &time, const rvector<bool> &alive_status, const char &alive_char, const char &dead_char);

#endif