/// @file calc_histogram_local.h
/// @author Rojin Anbarafshan
/// @date April 2025
/// @brief Module to compute the histogram of the log-transformed dataset locally on each rank.
/// The counts for each bin index are calculated and returned.

#ifndef CALC_HISTOGRAM_LOCAL
#define CALC_HISTOGRAM_LOCAL

#include <vector>
#include <cmath>

/// @brief Computes the histogram of log-transformed dataset locally on each rank.
/// This function takes a vector of data points on the current MPI rank, applies a logarithm transformation with the given
/// log_base, and bins the transformed values into a histogram.
/// Each data point x is transformed as:   y = log(x) / log(log_base)
/// The bin index is computed as:    bin_index = floor((y - min_bin) / bin_width)
/// If bin_index is out of the valid range (bin_index> n_bins-1), it is clamped accordingly.
/// @param data_local The vector of data points on the current rank.
/// @param log_base The base of the logarithm transformation.
/// @param n_bins The number of histogram bins.
/// @param min_bin The starting value (lower bound) for the histogram bins.
/// @param bin_width The width of each histogram bin.
/// @param counts_local Output vector (of size n_bins) where the count for each bin is stored.
/// @return rvector<double> The updated counts_local vector containing the histogram counts.
std::vector<double> compute_histogram_local(const std::vector<double> &data_local,
                                        double log_base,
                                        int n_bins,
                                        int min_bin,
                                        int bin_width,
                                        std::vector<double> &counts_local);

#endif