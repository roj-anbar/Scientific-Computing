/// @file setup_lattice.h
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module to setup the porous media by filling the 2D lattice randomly.

#ifndef SETUP_LATTICE
#define SETUP_LATTICE

#include <rarray>
#include <random>

/// @brief Fills up an N x M lattice where each cell is filled with probability 1-p.
/// A Bernoulli distribution is used because for generating binary outcomes.
/// "success" with probability 1-p results in a filled cell (value = 1).
/// "failure" with probability p results in an empty cell (value = 0).
/// @param M Number of columns in the lattice.
/// @param N Number of rows in the lattice.
/// @param p Probability that a cell is empty.
/// @param lattice The 2D lattice (N*M rarray matrix of integers) to be filled randomly with 0 and 1.
/// @param seed The initial seed for the random number generator.
void setup_lattice(int M, int N, double p, rmatrix<int> &lattice, int seed);

#endif