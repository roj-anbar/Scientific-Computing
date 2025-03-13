/// @file matrix_generate.h
/// @author Rojin Anbarafshan
/// @date March 07, 2025
/// @brief Module for creating the matrix of coefficients of 1d heat PDE with Dirichlet BCs.
/// Options for the matrix are:
/// 1. 'full_matrix': using full matrix
/// 2. 'tri_matrix' : using tridiagonal matrix

#ifndef MATRIX_GENERATE
#define MATRIX_GENERATE
#include <rarray>


/// @brief Function to build the full matrix of coefficients G for 1D heat equation based on simulation parameters.
/// @param N Number of grid points.
/// @param alfa Simulation parameter equal to dt/dx^2.
/// @param G rarray matrix of size NxN to store the coefficients.
void make_coeff_matrix_full(const int N, const double &alfa, rmatrix<double> &G);

/// @brief Function to build the tridiagonal matrix of coefficients for 1D heat equation based on simulation parameters.
/// @param N Number of grid points.
/// @param alfa Simulation parameter equal to dt/dx^2.
/// @param G_tri rarray matrix of size 3xN to store only the upper,lower, and diagonal elements of matrix of coefficients G.
/// First row is diagonal elements, second row is upper diagonal and third row is lower diagonal.
/// Since upper and lower diagonal elements have size N-1, there is an extra zeros at the end which should be omitted later.
void make_coeff_matrix_tri(const int N, const double &alfa, rmatrix<double> &G_tri);

#endif