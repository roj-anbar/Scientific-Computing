/// @file single_walker.cpp
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module to simulate the movement of a single walker through the lattice.

#include "single_walker.h"
#include <rarray>
#include <random>
#include <cmath>
#include <stdexcept>

/// @brief Chooses a move for the walker in a 2D lattice using weighted random sampling.
/// This is a local function that computes the direction of each move for the walker based on probabilities:
/// @param lattice 2D rarray matrix (N*M) representing the lattice (0 = empty, 1 = filled).
/// @param row The current row index of the walker.
/// @param col The current column index of the walker.
/// @param M The number of columns in the lattice.
/// @param N The number of rows in the lattice.
/// @param g Downward tendency (used to calculate up and down move probabilities).
/// @param generator A reference to the random number generator.
/// @return A pair (delta_row, delta_col) indicating the chosen move:
/// up: (-1, 0), down: (1, 0), left: (0, -1), right: (0, 1)
static std::pair<int, int> choose_move(const rmatrix<int> &lattice, int row, int col, int M, int N, double g, std::mt19937_64 &generator)
{
    // Calculate the weight of the probability of each move
    double w_left = 1.0;
    double w_right = 1.0;
    double w_up = 1.0 / g;
    double w_down = g;

    // Eliminate invalid moves by setting their weights to zero
    // Boundary cells or filled neighbors
    if (col == 0 || lattice[row][col - 1] == 1)
        w_left = 0;
    if (col == M - 1 || lattice[row][col + 1] == 1)
        w_right = 0;
    if (row == 0 || lattice[row - 1][col] == 1)
        w_up = 0;
    if (row == N - 1 || lattice[row + 1][col] == 1)
        w_down = 0;

    // Calculate z    
    double z = w_left + w_right + w_up + w_down;

    // Case of no valid moves
    if (z == 0)
        return std::make_pair(0, 0); 

    // Obtain probability of each move
    double p_left = w_left / z;
    double p_right = w_right / z;
    double p_up = w_up / z;
    double p_down = w_down / z;

    // Draw a random number that will be compared against probabilities
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double r = dist(generator);
    
    
    // Choose the move based on the cumulative distribution
    double cumulative = 0.0;

    if ((cumulative += p_left) > r)
        return std::make_pair(0, -1); // move left
    if ((cumulative += p_right) > r)
        return std::make_pair(0, 1); // move right
    if ((cumulative += p_up) > r)
        return std::make_pair(-1, 0); // move up

    return std::make_pair(1, 0);      // move down (last option)

}


/// @brief Simulates a single walker on a 2D lattice based and determines if the walker passes the lattice or not.
/// @param lattice 2D rarray matrix (N*M) representing the lattice (0 = empty, 1 = filled).
/// @param M The number of columns in the lattice.
/// @param N The number of rows in the lattice.
/// @param g Downward tendency (used to calculate up and down move probabilities).
/// @param max_steps Maximum number of allowed steps for each walker.
/// @param seed The seed for the random number generator.
/// @param initial_col The column index (0-indexed) in the top row where the walker starts.
/// @return Boolean that is true if the walker passes successfully through the lattice and false otherwise.
bool simulate_walker(const rmatrix<int> &lattice, int M, int N, double g, int max_steps, int seed, int initial_col)
{

    // Check initial conditions
    if (initial_col < 0 || initial_col >= M)
        throw std::invalid_argument("Initial column is out of bounds.");
    if (lattice[0][initial_col] == 1)
        throw std::invalid_argument("The initial cell is filled.");

    // Initialize random number generator with the given seed
    std::mt19937_64 generator(seed);

    // Set starting position
    int row = 0;
    int col = initial_col;

    // Simulation loop (move the walker through the lattice)
    for (int step = 0; step < max_steps; step++)
    {
        // Check if the walker has reached the bottom row -> stop if yes
        if (row == N - 1)
            return true;
        
        // Choose the move
        std::pair<int, int> move = choose_move(lattice, row, col, M, N, g, generator);

        // If no valid move is available terminate
        if (move.first == 0 && move.second == 0)
            return false;

        // Compute new position
        int new_row = row + move.first;
        int new_col = col + move.second;

        // Enforce boundaries: if the new position is out-of-bound, return false
        if (new_row < 0 || new_row >= N || new_col < 0 || new_col >= M)
            return false;

        // Update position
        row = new_row;
        col = new_col;
    }
    return false; // Walker did not reach the bottom within max_steps
}
