/// @file parallel_hist.cpp
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Main driver program to compute the logarithm of input data and generate its histogram.
///
/// This program reads numerical data from a specified file, computes the logarithm of each value
/// using a user-specified logarithmic base, and constructs a histogram of the log-transformed data.
/// The resulting histogram is written to an output text file in two columns: the starting point of
/// each bin and the count of data points in that bin.
/// The program expects two command-line arguments:
///   1. `log_base` — the base of the logarithm (can be a floating point number).
///   2. `data filename` — the name of the input file containing numeric values (one per line).

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iomanip> // to create filename

#include <omp.h>
#include "read_data_parallel.h"
#include "calc_histogram.h"

/// @brief Main function that reads input data, computes log-transformed values, and writes a histogram.
/// @param argc Number of command-line arguments.
/// @param argv Array of command-line argument strings.
/// @return Output text file of histogram results in two columns: 1. starting point of each bin, 2. count of data points in that bin.
int main(int argc, char *argv[])
{
    //------------------------------- INITIALIZE --------------------------------//
    // Parse command-line arguments

    // Check if the correct number of arguments was entered by user
    // (argc is one more than actual input arguments)
    if (argc != 3)
    {
        std::cerr << "Missing arguments: You must input values for (log_base, data filename)! \n";
        throw std::runtime_error("Not enough input arguments."); // terminates program if inputs are wrong
    }

    double log_base = std::stod(argv[1]);
    std::string dat_filename = argv[2];



    //------------------------------- Read data ---------------------------------//
    // For recording execution time
    double start_time = omp_get_wtime();

    int num_threads = omp_get_max_threads();

    std::vector<double> log_data = read_parallel(dat_filename, log_base, num_threads);

    //---------------------- Calculate histogram -------------------------//
    //int num_bins = 20;

    rmatrix<double> hist_data;
    hist_data = calc_histogram(log_data);

    //---------------------- Write to file -------------------------//

    // Create output filename
    // std::string output_filename = "output_hist_log="+ std::to_string(static_cast<int>(log_base*100)/100.0) + "_nthreads=" + std::to_string(num_threads)+".txt";
    std::ostringstream oss;
    oss << "output_hist_log=" << std::fixed << std::setprecision(2) << log_base
        << "_nthreads=" << num_threads << ".txt";
    std::string output_filename = oss.str();

    // Open output file
    std::ofstream outfile(output_filename);

    // Check if it opens properly
    if (!outfile.is_open())
    {
        throw std::runtime_error("Could not open output file.");
    }

    // Write elapsed time to output file
    double end_time = omp_get_wtime();
    outfile << "Elapsed time with num_threads = " << num_threads <<": " << (end_time - start_time) * 1000 << " milliseconds\n";

    // Output each bin's lower bound and its count
    int n_bins = hist_data.size() / 2; // since it hasd 2 columns

    for (int n = 0; n < n_bins; n++)
    {
        outfile << hist_data[n][0] << " " << hist_data[n][1] << "\n";
    }

    outfile.close();

    
    //std::cout << "Elapsed time: " << (end_time - start_time)*1000 << " milliseconds\n";

}
   
