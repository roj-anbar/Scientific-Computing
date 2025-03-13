/// @file init.cpp
/// @author Rojin Anbarafshan
/// @date March 07, 2025
/// @brief Main script for solving the 1D non-linear heat diffusion equation (KPP-Fisher's PDE).
/// Boundary conditions are:
/// BC1: u(x=0,t) = A(sin(t))^2; BC2: u(x=L,t) = 0; initial condition: u(x,0) = 0
/// Discretization scheme is explicit forward Euler time discretization and central finite difference spatial discretization.
/// The solution at each timestep can be obtained from the previous timestep by:
/// u_s+1 = (G * u_s) + (dt * u_s) - (dt * u_s^2)
/// Matrix by vector multiplication (G * u_s) will be handled separately based on the defined solver type
/// and then the other terms will be added to it.
/// Snapshot of solution u are written to a file at a certain interval defined by output_interval.

#include "init.h"
#include "matrix_generate.h"
#include "multiply_matrix_vector.h"
#include "output.h"

#include <fstream>
#include <iostream>
#include <stdexcept> // to handle exceptions

#include <rarray>
#include <cblas.h>


int main(int argc, char* argv[])
{
    //------------------ INITIALIZE --------------------------//

    // Obtain the simulation parameters from command-line inputs
    SimParameters sim_params = store_commandline_args(argc, argv);

    // Print the simulation parameters for confirmation
    print_sim_parameters(sim_params);

    // Store the useful simulation parameters to local variables
    int N = sim_params.N;           // Number of spatial grid points
    double dx = sim_params.dx;      // Spatial grid size
    double dt = sim_params.dt;      // Timestep size
    double Nt = sim_params.Nt;      // Total number of timesteps
    double alfa = sim_params.alfa;  // dt/dx^2
    double A = sim_params.A;        // Amplitude of boundary condition at x = 0

    //double P = sim_params.P;        // Number of snapshots to output
    int output_interval = sim_params.output_interval;

    // Solver type can be:
    // 1. 'full_mat_manual': using full matrix + explicit triple loop
    // 2. 'full_mat_blas'  : using full matrix + BLAS
    // 3. 'tri_mat_blas'   : using tridiagonal matrix + BLAS
    std::string solver_type = sim_params.solver_type;




    //------------------ ASSEMBLE VECTORS AND MATRICES --------------------//

    // Initialize the matrix of coefficients
    rmatrix<double> G_full;
    rmatrix<double> G_tri;

    // Build the matrix of coefficients based on the solver_type
    if (solver_type == "full_mat_manual" || solver_type == "full_mat_blas"){

        // Initialize the matrix of coefficients (N*N array)
        G_full = rmatrix<double>(N, N);
        G_full.fill(0.0);

        make_coeff_matrix_full(N, alfa, G_full);
    }

    else if(solver_type == "tri_mat_blas"){
        G_tri = rmatrix<double>(N, 3);
        make_coeff_matrix_tri(N, alfa, G_tri);
    }

    else{
        throw std::runtime_error("Solver type not supported. Please choose from 'full_mat_manual', 'full_mat_blas', or 'tri_mat_blas'! ");
    }



    //------------------------- MARCH IN TIME ----------------------------//

    // Initialize vectors of solutions at current and old timesteps (size N*1)
    // We aare solving for the current solution
    rvector<double> u_current(N);
    rvector<double> u_old(N);

    // Impose initial condition: u(x,0) = 0
    u_old.fill(0);

    // Fill solution at next timestep with zeros
    u_current.fill(0);

    // Begin the timeloop
    for (int s = 1; s <= Nt; s++)
    {
        // Calculate actual time
        double time = s * dt; 

        // Initialize a vector to store G*u_old
        rvector<double> Gu(N);
        Gu.fill(0.0);

        // 1. Calculate G*u: Perform matrix-vector multiplication based on the defined solver_type

        if (solver_type == "full_mat_manual"){
            matrix_vector_multiply_manual(N, G_full, u_old, Gu);
        }

        else if (solver_type == "full_mat_blas"){
            matrix_vector_multiply_blas(N, G_full, u_old, Gu);
        }

        else if (solver_type == "tri_mat_blas"){
            matrix_vector_multiply_blas_tri(N, G_tri, u_old, Gu);
        }


        // 2. Add the other terms
        for (int i = 0; i < N; i++)
            u_current[i] = Gu[i] + dt * u_old[i] - dt * u_old[i] * u_old[i];

        // 3. Impose boundary conditions
        u_current[0] = A * sin(time) * sin(time);
        u_current[N - 1] = 0.0;


        //------------- Output the solution ------------//

        std::string filename = "results_" + solver_type + ".txt";

        // Print and save the solution (force priting for 1st timestep)
        if (s%output_interval==0)
            output_solution(filename, N, time, dx, u_current);
            //std::cout << u_current << "\n";


        // Swap current and next timesteps
        std::swap(u_current, u_old);
        


    }
    
}
