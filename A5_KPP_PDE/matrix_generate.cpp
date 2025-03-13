/// @file matrix_generate.cpp
/// @author Rojin Anbarafshan
/// @date March 07, 2025
/// @brief Module for creating the matrix of coefficients of 1d heat PDE with Dirichlet BCs.
/// Options for the matrix are:
/// 1. 'full_matrix': using full matrix
/// 2. 'tri_matrix' : using tridiagonal matrix

#include "matrix_generate.h"
#include <rarray>


/// @brief Function to build the full matrix of coefficients G for 1D heat equation based on simulation parameters.
/// @param N Number of grid points.
/// @param alfa Simulation parameter equal to dt/dx^2.
/// @param G rarray matrix of size NxN to store the coefficients.
void make_coeff_matrix_full(const int N, const double &alfa, rmatrix<double> &G)
{
    // Construct the matrix by filling the diagonal, upper-diagonal, and lower-diagonal elements
    for (int i = 0; i < N; i++)
    {
        G[i][i] = 1 - 2 * alfa; // diagonal elements
        if (i < N-1)
            G[i][i + 1] = alfa; // upper-diagonal elements
        if (i > 0)
            G[i][i - 1] = alfa; // lower-diagonal elements

    }

    // Applying the Dirichlet boundary conditions to the matrix
    // First ensure that the first and last rows are zeros then fill the only necessary element
    for (int j = 0; j < N; j++)
    {
        G[0][j] = 0.0;     // set first row to zero
        G[N - 1][j] = 0.0; // set last row to zero
    }

    G[0][0] = 1.0;         // from BC at x=0
    G[N - 1][N - 1] = 1.0; // from BC at x=L
}


/// @brief Function to build the tridiagonal matrix of coefficients for 1D heat equation based on simulation parameters.
/// @param N Number of grid points.
/// @param alfa Simulation parameter equal to dt/dx^2.
/// @param G_tri rarray matrix of size 3xN to store only the upper,lower, and diagonal elements of matrix of coefficients G.
/// First row is upper-diagonal elements, second row is diagonal and third row is lower-diagonal.
/// Since upper and lower diagonal elements have size N-1, there is an extra zeros but this is taken care of in BLAS.
void make_coeff_matrix_tri(const int N, const double &alfa, rmatrix<double> &G_tri)
{

    // Construct the matrix by filling the diagonal, upper-diagonal, and lower-diagonal elements
    for (int i = 0; i < N; i++)
    {
        G_tri[i][1] = 1 - 2 * alfa; // diagonal elements (row 1)

        if (i < N - 1)
            G_tri[i + 1][0] = alfa; // upper diagonal (row 0, shifted right)

        if (i > 0)
            G_tri[i - 1][2] = alfa; // Lower diagonal (row 2, shifted left)
    }

    // Applying the Dirichlet boundary conditions to the matrix (only affects diagonal elements)
    G_tri[0][1] = 1.0;     // from BC at x=0
    G_tri[N - 1][1] = 1.0; // from BC at x=L

}

