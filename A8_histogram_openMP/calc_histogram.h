/// @file calc_histogram.h
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module to compute the histogram of a dataset and write the result to a file.
/// The histogram is written in a two-column format:
/// First column is the start value of each bin, and the second column is the count of data points in that bin.

#ifndef CALC_HISTOGRAM
#define CALC_HISTOGRAM

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm> // for min, max
#include <omp.h>
#include <rarray>

/// @brief Computes the histogram of a data and writes it to an output file.
/// The function divides the data range into equal-width bins, counts the number of data points in each bin,
/// and writes the result to a file with two columns: the starting value of the bin and the number of points in it.
/// @param data Vector of data values.
/// @return An rarray matrix of size n_bins*2 called 'histogram' which includes the bin indices in first columns and the
/// count of data in each bin in the second column.
rmatrix<double> calc_histogram(const std::vector<double> &data);

#endif