/// @file parallel_hist_MPI.cpp
/// @author Rojin Anbarafshan
/// @date April 2025
/// @brief Main driver program (first version) to compute the histogram of the logarithm of input data in parallel on a distributed memory system using MPI.
///
/// This program reads numerical data from a specified file, computes the logarithm of each value
/// using a user-specified logarithmic base, and constructs a histogram of the log-transformed data.
/// The resulting histogram is written to an output text file (and also printed to console) in two columns: the starting point of
/// each bin and the count of data points in that bin.
/// The program expects three command-line arguments:
///   1. `log base`: the base of the logarithm (can be a floating point number).
///   2. `data filename`: the name of the input file containing numeric values (one per line).
///   3. `batch size`: number of lines (data points) to be read at once.
/// The histogram is printed to console in a two-column format:
/// First column is the start value of each bin, and the second column is the normalized count of data points in that bin.

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
/// @return Output text file of histogram results in two columns: 1. starting point of each bin, 2. count of data points in that bin.
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
    int Z = std::stoi(argv[3]);             // batch size

    int local_size = Z / size;              // Size of data sent to each rank for each batch

    // Check if batch size is divisible by #processes
    if (Z % size != 0)
    {
        if (rank == 0)
            std::cerr << "Error: Batch size Z must be divisible by the number of MPI processes." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // ------------------------- Declare parameters and arrays -------------------------
    // Histogram parameters
    int min_data = 718;                                                       // Min of data
    int max_data = 3500000;                                                   // Max of data
    int min_bin = static_cast<int>(std::log(min_data) / std::log(log_base));  // Min log value
    int max_bin = static_cast<int>(std::log(max_data) / std::log(log_base));  // Max log value
    int n_bins = max_bin - min_bin;                                           // Number of total bins
    int bin_width = 1;                                                        // (max_bin - min_bin) / n_bins

    // Arrays
    std::vector<double> data_batch(Z);                  // Holds one full batch on rank 0
    std::vector<double> data_batch_local(local_size);   // Vector to store data at each rank (for current batch)
    std::vector<double> data_local;                     // Vector to store all the data on each rank
    std::vector<double> counts_local(n_bins);           // Count of each bin locally (on each rank)
    std::vector<double> counts_global(n_bins);          // Count of each bin globally (will be used as second column of hist_global)
    rmatrix<double> hist_global(n_bins, 2);         // Final global histogram (col1: bin start value, col2: count)

    // Initialize global hist on root process
    if (rank == 0)
    {
        for (int i = 0; i < n_bins; i++)
        {
            hist_global[i][0] = min_bin + i * bin_width; //start of the bin
            hist_global[i][1] = 0.0;                     //initial count in each bin
        }
    }


    //------------------------------- Open file (only on rank 0) ---------------------------------//
 
    // Open the file only on the first rank
    std::ifstream dataFile;
    if (rank == 0)
    {
        // Open the file
        dataFile.open(dat_filename);

        // Check if the file exists
        if (!dataFile.is_open())
            throw std::runtime_error("Could not open file: " + dat_filename);
    }

    // For recording execution time
    double start_time = MPI_Wtime();


    // --------------------------------- Batch processing loop ----------------------------------//

    // Exit flag
    bool done = false;

    while (true)
    {
 
        // Read one batch on rank 0
        if (rank == 0)
        {
            std::string line; // gets the current line
            double value;     // temporary variable for storing value from each line
            int count = 0;    // tempprary variable for counting read lines in each batch

            while (count < Z && std::getline(dataFile, line))
            {
                std::istringstream iss(line);
                if (iss >> value){
                    data_batch[count] = value;
                    count++;
                }
            }

            // If fewer than Z lines are read, then we're done
            if (count < Z)
                done = true;
        }

        // Finished reading one batch

        // Broadcast the 'done' flag so all ranks know whether to stop
        MPI_Bcast(&done, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD); //broadcast 1 boolean from rank 0

        // Exit condition for while(true) loop
        if (done)
            break;

        // Distribute (scatter) the current batch from rank 0 to all other ranks
        MPI_Scatter(data_batch.data(), local_size, MPI_DOUBLE,
                    data_batch_local.data(), local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Append received local data to the data_local vector (which store all data for each rank)
        data_local.insert(data_local.end(), data_batch_local.begin(), data_batch_local.end());
    }

    // Finished reading the whole file and distributed among all ranks
    // Close the file on rank 0
    if (rank == 0)
        dataFile.close();

    // --------------------------------- Compute histogram ----------------------------------//
    // Now that all data is distributed we should calculate the histogram locally on each rank.

    // Compute the local histogram of log-transformed data on each rank
    compute_histogram_local(data_local, log_base, n_bins, min_bin, bin_width, counts_local);

    // Reduce local histograms into a global histogram on rank 0
    MPI_Reduce(counts_local.data(), counts_global.data(), n_bins, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


    
    //------------------------------ Output global Histogram (rank 0) ------------------------//
    // On rank 0, accumulate the counts into hist_global.
    if (rank == 0){

        // Sum the global counts to get total number of data points (for normalization)
        double total_count = 0; 
        for (int i = 0; i < n_bins; i++)
            total_count += counts_global[i];
        

        // Accumulate counts on global histogram and normalize
        for (int i = 0; i < n_bins; i++)
            hist_global[i][1] = counts_global[i] / total_count;
        

        // Print execution time
        double end_time = MPI_Wtime();
        std::cout << "Total execution time for version 1: " << (end_time - start_time) << " seconds" << std::endl;

        // Print the global histogram
        std::cout << "Histogram (bin_start, normalized_count):\n";
        for (int i = 0; i < n_bins; i++)
            std::cout << hist_global[i][0] << "\t" << hist_global[i][1] << "\n";


    }
        
    // Finalize MPI
    MPI_Finalize();
    return 0;
}

