/// @file multiply_matrix_vector.cpp
/// @author Rojin Anbarafshan
/// @date March 07, 2025
/// @brief Module for handling the matrix-vector multiplication as a part of solving the 1d PDE for heat diffusion.
/// Options are:
/// 1. 'manual'   : using explicit triple loop for matrix-vector multiplication
/// 2. 'blas'     : using BLAS with full matrix for matrix-vector multiplication
/// 3. 'blas_tri' : using BLAS banded solver with only the non-zero elements for matrix-vector multiplication


#ifndef MULTIPLY_MATRIX_VECTOR
#define MULTIPLY_MATRIX_VECTOR

#include <rarray>
#include <cblas.h>

/// @brief Function to handle matrix-vector multiplication manually using an explicit triple loop.
/// It multiplies an NxN matrix G with the Nx1 vector u and stores the result in Gu using BLAS.
/// @param N Size of the matrix G (NxN) and the vector u (Nx1).
/// @param G Input matrix of size NxN (full matrix of coefficients).
/// @param u Input vector of size Nx1 (solution at previous timestep).
/// @param Gu Output vector (pre-allocated) of size Nx1.
void matrix_vector_multiply_manual(const int N, rmatrix<double> &G, rvector<double> &u, rvector<double> &Gu);

/// @brief Function to handle matrix-vector multiplication using BLAS.
/// It multiplies an NxN matrix G with the Nx1 vector u and stores the result in Gu using BLAS.
/// @param N Size of the matrix G (NxN) and the vector u (Nx1).
/// @param G Input matrix of size NxN (full matrix of coefficients).
/// @param u Input vector of size Nx1 (solution at previous timestep).
/// @param Gu Output vector (pre-allocated) of size Nx1.
void matrix_vector_multiply_blas(const int N, rmatrix<double> &G, rvector<double> &u, rvector<double> &Gu);

/// @brief Function to handle matrix-vector multiplication using banded feature of BLAS.
/// It multiplies a 3xN matrix G_tri with the Nx1 vector u and stores the result in Gu using BLAS.
/// @param N Number of the columns of G_tri (3xN) and size of the vector u (Nx1).
/// @param G_tri Input matrix of size 3xN (just the tridiagonal elements of the matrix of coefficients).
/// @param u Input vector of size Nx1 (solution at previous timestep).
/// @param Gu Output vector (pre-allocated) of size Nx1.
void matrix_vector_multiply_blas_tri(const int N, rmatrix<double> &G_tri, rvector<double> &u, rvector<double> &Gu);

#endif