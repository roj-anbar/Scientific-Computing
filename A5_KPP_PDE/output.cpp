/// @file output.cpp
/// @author Rojin Anbarafshan
/// @date March 07, 2025
/// @brief Module for outputing the solution of the 1D heat diffusion PDE.

#include "output.h"
#include <iostream>
#include <fstream>
#include <rarray>


/// @brief Outputs the solution vector to both a file and the screen.
/// @param filename Name of the output file where the results will be stored.
/// @param N Number of spatial grid points.
/// @param time Current time step in the simulation.
/// @param dx Spatial grid size (distance between grid points).
/// @param u Solution vector containing values of `u` at each spatial grid point.
void output_solution(const std::string &filename, int N, double time, double dx, const rvector<double> &u)
{
    std::ofstream file(filename, std::ios::app);
    
    for (int i = 0; i < N; ++i)
    {
        double position = i * dx;

        // Write to a file
        file << "t = " << time << " , x = " << position << ", u = " << u[i] << "\n";

        // Print to screen
        std::cout << "t = " << time << " , x = " << position << ", u = " << u[i] << "\n"; 
    }

    file.close();
}

