/// @file multiply_matrix_vector.cpp
/// @author Rojin Anbarafshan
/// @date March 07, 2025
/// @brief Module for handling the matrix-vector multiplication as a part of solving the 1d PDE for heat diffusion.
/// Options are:
/// 1. 'manual'   : using explicit triple loop for matrix-vector multiplication
/// 2. 'blas'     : using BLAS with full matrix for matrix-vector multiplication
/// 3. 'blas_tri' : using BLAS banded solver with only the non-zero elements for matrix-vector multiplication

#include "multiply_matrix_vector.h"
#include <rarray>
#include <cblas.h>



/// @brief Function to handle matrix-vector multiplication manually using an explicit triple loop.
/// It multiplies an NxN matrix G with the Nx1 vector u and stores the result in Gu using BLAS.
/// @param N Size of the matrix G (NxN) and the vector u (Nx1).
/// @param G Input matrix of size NxN (full matrix of coefficients).
/// @param u Input vector of size Nx1 (solution at previous timestep).
/// @param Gu Output vector (pre-allocated) of size Nx1.
void matrix_vector_multiply_manual(const int N, rmatrix<double> &G, rvector<double> &u, rvector<double> &Gu)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            Gu[i] += G[i][j] * u[j];
}


/// @brief Function to handle matrix-vector multiplication using BLAS.
/// It multiplies an NxN matrix G with the Nx1 vector u and stores the result in Gu using BLAS.
/// @param N Size of the matrix G (NxN) and the vector u (Nx1).
/// @param G Input matrix of size NxN (full matrix of coefficients).
/// @param u Input vector of size Nx1 (solution at previous timestep).
/// @param Gu Output vector (pre-allocated) of size Nx1.
void matrix_vector_multiply_blas(const int N, rmatrix<double> &G, rvector<double> &u, rvector<double> &Gu)
{
    // C = a* (A.B) + b*C
    // cblas_dgemv(CblasRowMajor, CblasNoTrans,
    //             first dim of A, dim of C,
    //             a, first element of A, leading dim A,
    //             first element of B, leading dim B,
    //             b, first element of C, leading dim C)

    double a = 1.0;
    double b = 0.0; 
    
    cblas_dgemv(CblasRowMajor, CblasNoTrans, N, N, a, G.data(), N, u.data(), 1, b, Gu.data(), 1);
}


/// @brief Function to handle matrix-vector multiplication using banded feature of BLAS.
/// It multiplies a 3xN matrix G_tri with the Nx1 vector u and stores the result in Gu using BLAS.
/// @param N Number of the columns of G_tri (3xN) and size of the vector u (Nx1).
/// @param G_tri Input matrix of size 3xN (just the tridiagonal elements of the matrix of coefficients).
/// @param u Input vector of size Nx1 (solution at previous timestep).
/// @param Gu Output vector (pre-allocated) of size Nx1.
void matrix_vector_multiply_blas_tri(const int N, rmatrix<double> &G_tri, rvector<double> &u, rvector<double> &Gu)
{

    double a = 1.0;
    double b = 0.0;

    // Define KL and KU for tridiagonal matrix (1 sub-diagonal, 1 super-diagonal)
    const int KL = 1;
    const int KU = 1;

    // Leading dimension (must be at least KL + KU + 1)
    const int lda = 3;  //tridiagonal matrix

    cblas_dgbmv(CblasRowMajor, CblasNoTrans, N, N, KL, KU, a, G_tri.data(), lda, u.data(), 1, b, Gu.data(), 1);
}

