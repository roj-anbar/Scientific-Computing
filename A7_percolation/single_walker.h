/// @file single_walker.h
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module to simulate the movement of a single walker through the lattice.

#ifndef SINGLE_WALKER
#define SINGLE_WALKER

#include <rarray>
#include <random>
#include <cmath>
#include <stdexcept>

/// @brief Simulates a single walker on a 2D lattice based and determines if the walker passes the lattice or not.
/// @param lattice 2D rarray matrix (N*M) representing the lattice (0 = empty, 1 = filled).
/// @param M The number of columns in the lattice.
/// @param N The number of rows in the lattice.
/// @param g Downward tendency (used to calculate up and down move probabilities).
/// @param max_steps Maximum number of allowed steps for each walker.
/// @param seed The seed for the random number generator.
/// @param initial_col The column index (0-indexed) in the top row where the walker starts.
/// @return Boolean that is true if the walker passes successfully through the lattice and false otherwise.
bool simulate_walker(const rmatrix<int> &lattice, int M, int N, double g, int max_steps, int seed, int initial_col);

#endif