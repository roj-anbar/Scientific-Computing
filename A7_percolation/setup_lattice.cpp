/// @file setup_lattice.cpp
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module to setup the porous media by filling the 2D lattice randomly.

#include "setup_lattice.h"
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
void setup_lattice(int M, int N, double p, rmatrix<int> &lattice, int seed)
{
    // Initialize random number generator with the provided seed
    std::mt19937_64 generator(seed);

    // Define Bernoulli distribution with success probability of 1-p (returns boolean)
    // "Success" (true) means cell is filled (value 1) and "failure" (false) means empty (value 0).
    std::bernoulli_distribution distribution(1 - p);

    // Loop over each element of the array and fill with generated state
    for (int n = 0; n < N; n++) 
    {
        for (int m = 0; m < M; m++)
        {
            if (distribution(generator)){
                lattice[n][m] = 1;
            }
            else{
                lattice[n][m] = 0;
            }
            //lattice[n][m] = distribution(generator);
        }
    }
        

}