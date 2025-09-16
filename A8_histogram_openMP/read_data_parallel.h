/// @file read_data_parallel.h
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module to read the input file in parallel and store the log of data in a vector.

#ifndef READ_DATA_PARALLEL
#define READ_DATA_PARALLEL

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <sstream>
#include <stdexcept>

/// @brief Reads a file in parallel and returns a vector of logarithm values for each number.
/// This function reads a file, by dividing it into chunks to be read with a specified number of threads using OpenMP.
/// Each thread opens its own file stream, skips to its assigned starting line, and processes its chunk of lines.
/// For each line, the logarithm of the number in the specified base is calculated and stored in a preallocated vector.
/// @param filename The path to the input data file.
/// @param log_base The base of the logarithm used in the computation.
/// @param num_threads The number of threads to use for parallel processing.
/// @return std::vector<double> A vector containing the computed logarithm values corresponding to each line in the file.

std::vector<double> read_parallel(const std::string &filename, double log_base, int num_threads);

#endif