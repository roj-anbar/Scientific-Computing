// output_single_timestep.cpp

#include "output_single_timestep.h"

// To create and print the output for one single timestep
// Inputs: timestep (int), current allive status (boolean rvector), assigned charachters for displaying alive and dead cells
// Outputs: a single string line containing current time step, current status of cells, and fraction of alive cells

void output_single_timestep(const int &time, const rvector<bool> &alive_status, const char &alive_char, const char &dead_char){

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

    std::cout << time << "\t" << string_represention << " " << fraction << "\n";
}