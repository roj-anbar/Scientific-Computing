// @file P1_slidingAvg.cpp
// PHY1610 Assignment 1: Compute the time-averaged norm of coordinates over 'n' previous timepoints
// Usage: ./P1_slidingAvg <inputFilename> <outputFilename> <n>
//
// INPUTS: 
// 1. An integer called 'n' specifying the number of previous values for averaging
// 2. A .dat file containing the space-time data in a specific format:
//    each line should contain exactly three values (time, x, and y) separated by spaces or tabs
// 
// OUTPUTS:
// 1. A file with two columns of the averaged time and the averaged norm of 2D coordinates


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath> //added for the use of sqrt

using std::vector;
using std::string;



// Function 1: Process the raw input file:
// 1. Reads the input file; 2. Calculates the norm for each row; 3. Stores time and norm in separate vectors
void process_input(const string &inputFileName, vector<double> &t, vector<double> &norm)
{   
    std::ifstream inputFile(inputFileName);

    // Temperoray variables for storing the values from each line of the file
    double tempT, tempX, tempY;

    // Read the file line by line (using >> operator from fstream) and store data from each line to the corresponding variable
    // Only store time and norm
    while (inputFile >> tempT >> tempX >> tempY)
    {
        t.push_back(tempT); 
        norm.push_back(std::sqrt(tempX * tempX + tempY * tempY));
    }

    // Close the file
    inputFile.close(); 

}



// Function 2: Calculates the windowed average of width n for each element of a vector (starts the window from element 'start')
double calc_avg_n(const vector<double> &original, int start, int n)
{
    double sum = 0;
    for (int i = start; i < start+n; ++i)
    {
        sum += original[i];
    }
    return sum / n; 
}



// Function 3: Writes averaged data to output
// 1. Loops over the rows (each timepoint) and call 'calc_avg_n' on both time and norm; 2. Writes the averaged variables to output file
void write_averaged_data(const string &outputFileName, const vector<double> &t, const vector<double> &norm, int n)
{
    // Open the output file
    std::ofstream outputFile(outputFileName);

    // Calculate average from index (n-1) to the end
    // Start from (n-1)-th element because we need at least n values for averaging -> n-1 because indexing is 0-based
    for (int ele = n - 1; ele < size(t); ele++)
    {
        double t_avg    = calc_avg_n(t, ele - n + 1, n);
        double norm_avg = calc_avg_n(norm, ele - n + 1, n);

        // Write the results to the output file line-by-line
        outputFile << t_avg << " " << norm_avg << "\n";
    }

    outputFile.close();
}




// ------------------ main --------------------- //

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

    // Declare variables to store time and norm
    vector<double> t, norm;

    //  Read the input file and retrieve the data
    process_input(inputFileName, t, norm);

    write_averaged_data(outputFileName, t, norm, n);

    std::cout << "Averaged data successfully written to " << outputFileName << '\n';
}

