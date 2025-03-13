// @file P1_slidingAvg.cpp
// PHY1610 Assignment 1: Compute the time-averaged norm of coordinates over 'n' previous timepoints
// run: ./slidingAvg <inputFilename> <outputFilename> <n>
//
// INPUTS: 
// 1. An integer called 'n' determining the number of previous values to consider for averaging
// 2. A .dat file containing the space-time data in a specific format:
//    each line should contain exactly three values (time, x, and y) separated by spaces or tabs
// 
// OUTPUTS:
// 1. A file with two columns of the averaged time and the averaged norm of 2d coordinates


#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::string;

// Define a local structure called 'Data' containing 3 vectors for time, x, y
struct Data
{
    vector<double> t;    // time
    vector<double> norm; //norm of x and y
};


// Process the raw input file:
// 1. Reads the input file; 2. Calculates the norm of each row; 3. store time and norm in a custom data type called 'Data'
Data process_input(const string& inputFileName)
{   
    //
    std::ifstream inputFile(inputFileName);

    Data data;

    // Temperoray variables for storing the values from each line of the file
    double tempT, tempX, tempY;

    // Read the file line by line and store data from each line to the corresponding variable (using >> operator from fstream)
    // Assuming input file format as: each line contains exactly three values (time, x, and y) separated by spaces or tabs
    // Only store time and norm
    while (inputFile >> tempT >> tempX >> tempY)
    {
        data.t.push_back(tempT); 
        data.norm.push_back(std::sqrt(tempX * tempX + tempY * tempY));
    }

    // Close the file
    inputFile.close(); 

    // Return the processed data
    return data; 
}



// Calculates the windowed average of width n for each element of a vector (starting from element 'start')
double calc_avg_n(const vector<double> &original, int start, int n)
{
    double sum = 0;
    for (int i = start; i < start+n; ++i)
    {
        sum += original[i];
    }
    return sum / n; //(end - start + 1);
}

// Loop over the rows (each timepoint) and calculate the averages
// Start from the (n-1)-th element (because we need at least n values for averaging) -> n-1 because indexing is 0-based
void write_averaged_data(const string &outputFileName, const vector<double> &t, const vector<double> &norm, int n)
{
    // Open the output file
    std::ofstream outputFile(outputFileName);

    // Calculate average from index (n-1) to the end
    for (int ele = n - 1; ele < size(t); ele++)
    {
        double t_avg    = calc_avg_n(t, ele - n + 1, n);
        double norm_avg = calc_avg_n(norm, ele - n + 1, n);

        // Write the results to the output file line-by-line
        outputFile << t_avg << " " << norm_avg << "\n";
    }

    outputFile.close();
}



int main(int argc, char *argv[])
{
    // Check if the correct number of arguments was entered by user
    if (argc != 4)
    {
        std::cerr << "Wrong number of arguments was entered! Try again! \n";
        return 1; // terminates program if inputs are wrong
    }

    // Assign command-line arguments to variables
    string inputFileName = argv[1];
    string outputFileName = argv[2];
    int n = std::stoi(argv[3]); // convert the 3rd argument 'n' to an integer


    // Read the input file and retrieve the data
    Data data = process_input(inputFileName);

    // Access individual vectors
    const auto &t = data.t; // Access time vector
    const auto &norm = data.norm; // Access vector of calculated norms


    write_averaged_data(outputFileName, data.t, data.norm, n);

    std::cout << "Averaged data successfully written to " << outputFileName << std::endl;
}

// Open the output file
// std::ofstream outputFile(outputFileName);

// Loop over the rows (each timepoint) and calculate the averages
// Start from the (n-1)-th element (because we need at least n values for averaging) -> n-1 because indexing is 0-based
// int ele;
// for (ele = n-1; ele < size(t); ele++)
//{

// Declare output variables (average of norms and times)
//   double t_avg, norm_avg;

// t_avg    = calc_avg_n(t, ele-n+1, n);
// norm_avg = calc_avg_n(norm, ele-n+1, n);

// Write the results to the output file line-by-line
// outputFile << t_avg << " " << norm_avg << "\n";
//}

// Close the file
// outputFile.close();