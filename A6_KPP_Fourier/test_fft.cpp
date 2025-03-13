/// @file test_fft.cpp
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief For testing the FFT functions defined in diffusion_substep module with a simple sine function.

#include "init.h"
#include "diffusion_substep.h"

#include <iostream>
#include <stdexcept> // to handle exceptions
#include <cmath>
#include <complex>

#include <rarray>
#include <fftw3.h>

using complex = std::complex<double>;

int main(int argc, char *argv[])
{
    // Obtain the simulation parameters from command-line inputs
    SimParameters sim_params = store_commandline_args(argc, argv);

    // Print the simulation parameters for confirmation
    print_sim_parameters(sim_params);

    // Store the useful simulation parameters to local variables
    int N = sim_params.N;    // Number of spatial grid points
    double L = sim_params.L; // Length of spatial domain
    double dx = sim_params.dx; // Spatial grid size

    int complex_size = N / 2 + 1;

    // Define vectors
    rvector<double> f_in(N), f_out(N);
    rvector<complex> f_hat(complex_size);

    f_out.fill(0.0);
    f_hat.fill(0.0);

    // Create simple sine function
    for (int j = 0; j < N; j++)
    {
        f_in[j] = sin(2* M_PI * j * dx / L);
    }
    std::cout << "f_in" << f_in << "\n";

    // forward FT
    fft_fast(f_in, f_hat, 0);
    
    //std::cout << f_hat << "\n";

    // inverse FT
    fft_fast(f_out, f_hat, 1);
    std::cout << "f_out" << f_out << "\n";
}
