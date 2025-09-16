/// @file read_data_parallel.cpp
/// @author Rojin Anbarafshan
/// @date March 2025
/// @brief Module to read the input file in parallel and store the log of data in a vector.

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <sstream>
#include <stdexcept>

#include "read_data_parallel.h"

/// @brief Reads a file in parallel and returns a vector of logarithm values for each number.
/// This function reads a file, by dividing it into chunks to be read with a specified number of threads using OpenMP.
/// Each thread opens its own file stream, skips to its assigned starting line, and processes its chunk of lines.
/// For each line, the logarithm of the number in the specified base is calculated and stored in a preallocated vector.
/// @param filename The path to the input data file.
/// @param log_base The base of the logarithm used in the computation.
/// @param num_threads The number of threads to use for parallel processing.
/// @return std::vector<double> A vector containing the computed logarithm values corresponding to each line in the file.

std::vector<double> read_parallel(const std::string &filename, double log_base, int num_threads)
{
    // Open the file
    std::ifstream dataFile(filename);

    // Check if the file exists
    if (!dataFile.is_open()) throw std::runtime_error("Could not open file: " + filename);  

    // Length of each line (fixed number of charachters)
    int line_chars = 8;

    // Count total lines of the file
    int total_lines = 0;
    std::string line;
    while (std::getline(dataFile, line))
        total_lines++;
    dataFile.close();

    // Allocate vector to store the data points
    std::vector<double> log_data(total_lines);

    // Number of lines to be read by each thread
    int lines_per_thread = total_lines / num_threads; 

    // Read file in parallel
    #pragma omp parallel num_threads(num_threads) default(none) shared(log_data, filename, log_base, total_lines, lines_per_thread, line_chars, num_threads)
    {
        int thread_id = omp_get_thread_num();    // current thread ID
        //int nthreads = omp_get_num_threads(); // total number of threads

        // Calculate start and end lines to be read by each thread

        // starting line to be read by this thread
        int start_line = thread_id * lines_per_thread;      
        
        // end line to be read by this thread
        int end_line;
        if (thread_id == num_threads - 1)
            end_line = total_lines; // last thread reads to the end
        else
            end_line = start_line + lines_per_thread; // other threads get fixed chunk
    
   
        // Open file and read the assigned lines for this thread
        std::ifstream file(filename);

        // Calculate offset bytes for this thread
        std::streamoff offset = static_cast<std::streamoff>(start_line) * (line_chars + 1);
        
        // seek to the correct starting byte
        file.seekg(offset, std::ios::beg);

        // Read assigned lines for this thread
        std::string current_line;
        for (int i = start_line; i < end_line && std::getline(file, current_line); i++)
        {
            std::istringstream iss(current_line); //gets each line
            double val;
            iss >> val;
            log_data[i] = std::log(val) / std::log(log_base);
        }
    }

    return log_data;
}
