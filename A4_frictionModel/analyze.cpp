/// @file analyze.cpp
/// @author Ramses van Zon (commented by Rojin Anbarafshan)
/// @date February 13, 2025
/// @brief Analyzes a sample spatial timeseries dataset to estimate the friciton rate.
///
/// This program reads a sample timeseries position dataset from a file, computes velocity using numerical differentiation,
/// estimates the friction rate, and finally writes the results to an ouput file.
///
/// The script supports command-line arguments to specify input and output files.

#include "friction.h"
#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>


/// @brief Reads timeseries data, computes the friction rate, and outputs the results.
///
/// This function does all the necessary analysis. It processes the input data file containing time and position values.
/// It computes velocity using 'numdiff' function from 'friction.h' and then estimates the friction constant through
/// 'frictionrate' function from 'friction.h'. It finally writes the results to an output file.
/// @param filename name of the input file containing the sample timeseries dataset
/// @param outfilename name of the output file to store the analysis results 
void analyze_data(const std::string& filename,
                  const std::string& outfilename)
{
    std::ifstream fin;
    fin.open(filename);
    long long n=0;
    std::string line;
    while (std::getline(fin,line)) {
        if (line[0] != '#') {
            n++;
        }
    }
    fin.close();
    fin.open(filename);
    rvector<double> t(n);
    rvector<double> z(n);
    n = 0;
    while (std::getline(fin,line) and n < t.size()) {
        if (line[0] != '#') {
            std::stringstream s(line);
            s >> t[n] >> z[n];
            n++;
        }
    }
    fin.close();
    // compute alpha
    double dt = t[1]-t[0];
    rvector<double> dzdt = numdiff(dt, z);
    double alpha = frictionrate(dt, dzdt);
    // report
    std::ostream* fout;
    if (outfilename == "-")
        fout = &std::cout;
    else
        fout = new std::ofstream(outfilename);
    *fout << "# filename " << filename << "\n";
    *fout << "# n " << n << "\n";
    *fout << "# dt " << dt << "\n";
    *fout << "# alpha " << alpha << '\n';
    if (outfilename != "-") {
        delete fout;
        std::cout << "Output written to '" << outfilename << "'.\n";        
    }
}

/// @brief Function to parse command-line arguments for the data analysis program.
///
/// This function reads and processess command-line arguments to extract the input and output file names.
/// If the output file is set to "-", the results will be printed to the console.
/// @param argc number of command-line arguments
/// @param argv array of argument strings
/// @param filename name of the input file containing the sample timeseries dataset
/// @param outfilename name of the output file to store the analysis results
int read_command_line(int argc, char* argv[],
                      std::string& filename,
                      std::string& outfilename)
{
    using boost::program_options::value;
    boost::program_options::options_description desc("Options for analyze");
    desc.add_options()
        ("help,h",                                      "Print help message")
        ("file,f",    value<std::string>(&filename),    "file from which read the data")
        ("output,o",  value<std::string>(&outfilename), "file to write result (- means console)");
    boost::program_options::variables_map args;
    try {
        store(parse_command_line(argc, argv, desc), args);
        notify(args);
    }
    catch (...) {
        std::cerr << "ERROR in command line arguments!\n" << desc;
        return 2;
    }
    if (args.count("help")) {
        std::cout << "Usage:\n    " << argv[0] << " [OPTIONS]\n" << desc;
        return 1;
    }
    return 0;
}


/// @brief Main function for analyzing time-series friction model data.
///
/// This function initializes default input and output file names, processes command-line arguments, and performs
/// data analysis to compute the friction rate.
/// @param argc number of command-line arguments
/// @param argv array of argument strings
int main(int argc, char* argv[])
{
    // Define defaults settings
    std::string filename = "testmodel.dat";
    std::string outfilename = "-";
    // Parse the command line
    int status = read_command_line(argc, argv, filename, outfilename);
    if (status > 0) 
        return status - 1;
    // Go to work
    analyze_data(filename, outfilename);
}
