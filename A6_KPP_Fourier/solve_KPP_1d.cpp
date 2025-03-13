/// @file solve_KPP_1d.cpp
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Main script for solving the 1D non-linear heat diffusion equation (KPP-Fisher's PDE).

/// Boundary conditions are periodic as:
/// BCs: u(x=0,t) = u(x=L,t); initial condition: u(x,0) = A * (sin(pi*x/L))^100
///
/// The solution at each timestep can be obtained from the previous timestep by dividing each timestep into 2 substeps:
/// (We split the equation into 2 parts)
/// 1. Reaction substep: This step has analytic solution and we get an exact equation for u(x,t+1).
/// u_s+1 = u_s / (u_s + (1-u_s) * exp(-dt))
/// 2. Diffusion step: This step is solved by taking the Fourier Transform of the PDE and convert the solution back.
/// u^_s+1 = u^_s * exp(-k^2 * dt) -> k is the wavenumber
/// Discretization scheme is explicit forward Euler time discretization.
///
/// Therefore, at each timestep we first calculate the solution to the recation equation and then pass this to the
/// diffusion equation as below:
/// u_s = u_old
/// u_reaction = u_s / (u_s + (1-u_s) * exp(-dt))
/// u^_diffusion = u^_reaction * exp(-k^2 * dt)
/// u_s+1 = F-1 (u^_diffusion)
/// u_current = u_s+1
///
/// Snapshot of solution u are written to a file at a certain interval defined by output_interval.

#include "init.h"
#include "diffusion_substep.h"
#include "output.h"

#include <fstream>
#include <iostream>
#include <stdexcept> // to handle exceptions
#include <cmath>
#include <complex>

#include <rarray>
#include <fftw3.h>


int main(int argc, char* argv[])
{
    //------------------ INITIALIZE --------------------------//

    // Obtain the simulation parameters from command-line inputs
    SimParameters sim_params = store_commandline_args(argc, argv);

    // Print the simulation parameters for confirmation
    print_sim_parameters(sim_params);

    // Store the useful simulation parameters to local variables
    int N = sim_params.N;           // Number of spatial grid points
    double L = sim_params.L;        // Length of spatial domain
    double dx = sim_params.dx;      // Spatial grid size
    double dt = sim_params.dt;      // Timestep size
    int Nt = sim_params.Nt;         // Total number of timesteps
    double A = sim_params.A;        // Amplitude of boundary condition at x = 0

    int output_interval = sim_params.output_interval;



    //------------------------- MARCH IN TIME ----------------------------//

    // Initialize vectors of solutions at current and old timesteps (size N)
    // Note: We don't include x=L to avoid duplication (periodic BC)
    // We are solving for the current solution
    rvector<double> u_old(N), u_current(N);


    // Impose initial condition: u(x,0) = A * [sin(pi*x/L)]^100
    for (int j = 0; j < N; j++)
    {
        u_old[j] = A * std::pow(sin (M_PI*j*dx/L) , 100);
    }
    

    // Fill solution at next timestep with zeros
    u_current.fill(0);


    // Begin the timeloop
    for (int s = 1; s <= Nt; s++)
    {
        // Calculate actual time
        double time = s * dt;

        // 1. Perform reaction substep
        // Declare vector to store the intermediate solution from reaction substep
        rvector<double> u_react(N);

        for (int j = 0; j < N; j++)
        {
            u_react[j] = u_old[j] / (u_old[j] + (1 - u_old[j]) * std::exp(-dt));
        }


        // 2. Perform diffusion substep
        solve_diffusion(L, dt, u_react, u_current);

 
        // 3. Enforce the periodic boundary conditions
        // u_current[N - 1] = u_current[0];


        //------------- Output the solution ------------//

        std::string filename = "results_N=" + std::to_string(N) + ".txt";

        // Print and save the solution (force priting for 1st timestep)
        if (s == 0 || s%output_interval==0)
        {
            output_solution(filename, N, time, dx, u_current);
            // std::cout << u_current << "\n";
        }

        // Swap current and next timesteps
        std::swap(u_current, u_old);
        }
    
}
