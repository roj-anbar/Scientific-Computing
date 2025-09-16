/// @file calc_histogram.cpp
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module to compute the histogram of a dataset and write the result to a file.
/// The histogram is written in a two-column format:
/// First column is the start value of each bin, and the second column is the count of data points in that bin.

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm> //for min, max
#include <omp.h>
#include <rarray>

#include "calc_histogram.h"

/// @brief Computes the histogram of a data and writes it to an output file.
/// The function divides the data range into equal-width bins, counts the number of data points in each bin,
/// and writes the result to a file with two columns: the starting value of the bin and the number of points in it.
/// @param data Vector of data values.
/// @return An rarray matrix of size n_bins*2 called 'histogram' which include the bin indices in first columns and the
/// count of data in each bin in the second column.
rmatrix<double> calc_histogram(const std::vector<double> &data)
{

    // 1. Find min and max of data (log-transformed)
    double min_val = *std::min_element(data.begin(), data.end());
    double max_val = *std::max_element(data.begin(), data.end());

    // 2. Determine the number of bins needed to have 1 bin for each order of magnitude
    int min_bin = static_cast<int>(std::floor(min_val));
    int max_bin = static_cast<int>(std::ceil(max_val));
    int n_bins = max_bin - min_bin; // each bin corresponds to an interval [k, k+1)

    // 3. Initialize vector storing histogram bins and counts
    // first column: bin indices, second column: bin indices
    rmatrix<double> histogram(n_bins, 2);

    // 4. Calculate index for each bin
    for (int n = 0; n < n_bins; n++)
    {
        double bin_start = min_bin + n;
        histogram[n][0] = bin_start;
    }


    // 5. Count values into bins
    #pragma omp parallel for default(none) shared(data, n_bins, min_bin, histogram)

    // Loop over each data point
    for (std::size_t i = 0; i < data.size(); i++)
    {
        const double &x = data[i];

        // Calculate the index of bin that this point belongs to
        int bin_index = static_cast<int>(std::floor(x)) - min_bin;

        // Handle the last bin
        if (bin_index >= n_bins)
            bin_index = n_bins - 1;

        // Use atomic update to avoid race conditions.
        #pragma omp atomic

        // Add one to the count of corresponding bin index (second column)
        histogram[bin_index][1]++;
    }

    return histogram;
}
