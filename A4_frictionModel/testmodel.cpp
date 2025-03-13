/// @file testmodel.cpp
/// @author Ramses van Zon (commented by Rojin Anbarafshan)
/// @date February 13, 2025
/// @brief Generates and saves a sample timeseries spatial dataset to a file.
///
/// This script creates a timeseries spatial dataset of a falling object in a viscous liquid using certain model parameters.
/// It takes command-line arguments and writes the results to a specified file named "testmodel.dat".
/// If command-line arguments are not passed, it will create a dataset with default parameters:
/// alpha= 0.125, v0= 10, z0= 0, g= 9.8, dt= 0.25, and t ranging from 0 to 16.

#include "model.h"
#include <fstream>
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

/// @brief Function to compute the position values over a time range using model parameters and writes the results to specified file.
///
/// This function uses the global function 'compute_model_Z' from 'model.h'.
/// @param filename time step at which position is calculated
/// @param t1 start time
/// @param t2 end time 
/// @param dt time step size (between two data point)
/// @param p model parameters including  friction rate, gravity, initial velocity and height
void generate_data(const std::string& filename,
                   double t1, double t2, double dt,
                   const ModelParameters& p)
{
    const int n = int((t2-t1)/dt)+1;
    const rvector<double> z = compute_model_z(t1, t2, dt, p);
    const rvector<double> t = linspace(t1, t2, n);
    std::ofstream fout(filename);
    fout << "# alpha " << p.alpha << "\n"
         << "# g " << p.g << "\n"
         << "# dt " << dt << "\n"
         << "# t1 " << t1 << "\n"
         << "# t2 " << t2 << "\n"         
         << "# v0 " << p.v0 << "\n"
         << "# z0 " << p.z0 << "\n";
    for (int i = 0; i < n; i++) 
        fout << t[i] << " " << " " << z[i] << "\n";
    fout.close();
}

/// @brief Function to parse command-line arguments for model simulation.
///
/// This function reads and processess user-specified command-line arguments to set simulation parameters
/// such as time range, step size, friction, gravity, and output filename.
/// @param argc number of command-line arguments
/// @param argv array of argument strings
/// @param filename name of the output file
/// @param t1 start time
/// @param t2 end time
/// @param dt time step size
/// @param p model parameters including friction constant (alpha), gravitational acceleration (g),
///          initial velocity (v0), and initial height (z0)
int read_command_line(int argc, char* argv[],
                      std::string& filename,
                      double& t1, double& t2, double& dt,
                      ModelParameters& p)
{
    using boost::program_options::value;
    boost::program_options::options_description desc("Options for testmodel");
    desc.add_options()
        ("help,h",                                   "Print help message")
        ("t1,i",      value<double>(&t1),             "initial time")
        ("t2,t",      value<double>(&t2),             "final time")
        ("dt,d",      value<double>(&dt),             "time step")
        ("alpha,a",   value<double>(&p.alpha),        "friction constant")
        ("gravity,g", value<double>(&p.g),            "gravitational acceleration")
        ("v0,v",      value<double>(&p.v0),           "initial vertical velocity")
        ("z0,z",      value<double>(&p.z0),           "initial height")
        ("file,f",    value<std::string>(&filename), "file into which write the data");
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

/// @brief Main function to execute the sample dataset creation.
///
/// This function initializes default simulation parameters, reads and processess command-line arguments,
/// and generates model data saving it to a file.
/// @param argc number of command-line arguments
/// @param argv array of argument strings
int main(int argc, char* argv[])
{
    // Define defaults settings
    ModelParameters p { 0.125f, 9.8f, 0.0f, 10.0f }; 
    double t1 = 0.0f;
    double t2 = 20.0f;
    double dt = 0.125f;
    std::string filename = "testmodel.dat";
    // Parse the command line
    int status = read_command_line(argc, argv, filename, t1, t2, dt, p);
    if (status > 0) 
        return status - 1;
    generate_data(filename, t1, t2, dt, p);
    std::cout << "Output written to '" << filename << "'.\n";        
}
