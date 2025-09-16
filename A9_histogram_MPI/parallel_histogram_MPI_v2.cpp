/// @file parallel_hist_MPI.cpp
/// @author Rojin Anbarafshan
/// @date April 2025
/// @brief Main driver program to compute the histogram of the logarithm of input data in parallel on a distributed memory system using MPI.
///
/// This program reads numerical data from a specified file, computes the logarithm of each value
/// using a user-specified logarithmic base, and constructs a histogram of the log-transformed data.
/// The resulting histogram is written to an output text file (and also printed to console) in two columns: the starting point of
/// each bin and the count of data points in that bin.
/// The program expects three command-line arguments:
///   1. `log base`: the base of the logarithm (can be a floating point number).
///   2. `data filename`: the name of the input file containing numeric values (one per line).
///   3. `batch size`: number of lines (data points) to be read at once.
/// The histogram is both stored to a file and printed to console in a two-column format:
/// First column is the start value of each bin, and the second column is the count of data points in that bin.

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <algorithm>

#include <rarray>
#include <mpi.h>
#include "calc_histogram_local.h"


/// @brief Main function that reads input data, computes the histogram of log-transformed values.
/// @param argc Number of command-line arguments.
/// @param argv Array of command-line argument strings.
/// @return Print output of histogram results in two columns: 1. starting point of each bin, 2. normalized count of data points in that bin.
int main(int argc, char *argv[])
{
    //------------------------------- MPI Initialize --------------------------------//

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    //-------------------------Parse command-line arguments --------------------------//
    // Check if correct number of arguments was entered by user (argc is one more than actual input arguments)
    if (argc != 4)
    {
        if (rank == 0)
            std::cerr << "Missing arguments: You must input values for (log_base, data filename, batch size)! \n";
        MPI_Abort(MPI_COMM_WORLD, 1); // terminates if inputs are wrong (1 is error code)
    }

    double log_base = std::stod(argv[1]);   // log base
    std::string dat_filename = argv[2];     // data filename
    

    // ------------------------- Declare parameters and arrays -------------------------
    // Histogram parameters
    int min_data = 718;                                                       // Min of data
    int max_data = 3500000;                                                   // Max of data
    int min_bin = static_cast<int>(std::log(min_data) / std::log(log_base));  // Min log value
    int max_bin = static_cast<int>(std::log(max_data) / std::log(log_base));  // Max log value
    int n_bins = max_bin - min_bin;                                           // Number of total bins
    int bin_width = 1;                                                        // (max_bin - min_bin) / n_bins

    // Arrays
    std::vector<double> counts_local(n_bins);       // Count of each bin locally (on each rank)
    std::vector<double> counts_global(n_bins);      // Count of each bin globally (will be used as second column of hist_global)
    rmatrix<double> hist_global(n_bins, 2);         // Final global histogram (col1: bin start value, col2: count)

    // Initialize global hist on root process
    if (rank == 0)
    {
        for (int i = 0; i < n_bins; i++){
            hist_global[i][0] = min_bin + i * bin_width; //start of the bin
            hist_global[i][1] = 0.0;                     //initial count in each bin
        }
    }


    //------------------------------- Read data in parallel ---------------------------------//
    // Each process opens the file independently and reads its assigned lines.

    // For recording execution time
    double start_time = MPI_Wtime();

    // Open the file
    std::ifstream dataFile(dat_filename);

    // Check if the file exists
    if (!dataFile.is_open())
    {
        throw std::runtime_error("Could not open file: " + dat_filename);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }


    // Each process will collect the lines that belong to it
    std::vector<double> data_local;  // Vector to store all the data on each rank
    std::string line;                // Gets the current line
    double value;                    // Temporary variable for storing value from each line
    int line_index = 0;              //

    while (std::getline(dataFile, line))
    {
        std::istringstream iss(line);
        if (iss >> value)
        {
            // Assign this line to the process if (line_index % size) equals rank
            if (line_index % size == rank)
                data_local.push_back(value);
        }
        line_index++;
    }
    dataFile.close();


    // --------------------------------- Compute histogram ------------------------------------//
    // Compute the local histogram of log-transformed values of local data on each rank
    compute_histogram_local(data_local, log_base, n_bins, min_bin, bin_width, counts_local);

    // Reduce local histograms into a global histogram on rank 0
    MPI_Reduce(counts_local.data(), counts_global.data(), n_bins, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);



    //------------------------------ Output global Histogram (rank 0) ------------------------//
    // On rank 0, accumulate the counts into hist_global.
    if (rank == 0)
    {
        // Sum the global counts to get total number of data points (for normalization)
        double total_count = 0; 
        for (int i = 0; i < n_bins; i++)
            total_count += counts_global[i];
        

        // Accumulate counts on global histogram and normalize
        for (int i = 0; i < n_bins; i++)
            hist_global[i][1] = counts_global[i] / total_count;

        // Print execution time
        double end_time = MPI_Wtime();
        std::cout << "Total execution time for version 2: " << (end_time - start_time) << " seconds" << std::endl;

        // Print the global histogram
        std::cout << "Histogram (bin_start, normalized_count):\n";
        for (int i = 0; i < n_bins; i++)
            std::cout << hist_global[i][0] << "\t" << hist_global[i][1] << "\n";

    }
        
    // Finalize MPI
    MPI_Finalize();
    return 0;
}

