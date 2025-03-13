\mainpage Friction Rate Model
This is a package for computing the friction rate based on a sample time-series of positions. It aims to find an estimate of friction constant from a falling motion of an object in a viscous liquid.

It includes modules for generating synthetic data, analyzing velocity changes, and estimating friction rate using numerical differentiation.
The package consists of:
- A "friction" module that computes the friction rate based on velocity samples taken at fixed time intervals.
- A "model" module that generates sample time-series data based on user-specified parameters or default values.

# Generating sample data
You can generate synthetic sample data using the "model" module. The data represents position (z) over time (t) under a given friction model. 

## Defaul model parameters
If not parameters are provided, the dataset is created using the following default values:
- Friction constant: alpha= 0.125
- Initial velocity: v0= 10
- Initial position: z0= 0
- Gravitational acceleration: g= 9.8
- Time step: dt= 0.25
- Time range: t= 0 to 16

## Running the model
To generate a sample dataset with the default parameters run:
<br>
\code
    make testmodel.dat
\endcode

Alternatively, you can specify custom parameters via command-line arguments.


# Performing data analysis
Once the sample data is generated, you can analyze the frition rate from velocity changes over time. To perform the data analysis on the generated data run:
<br>
\code
    make analysis
\endcode

This will process the dataset, apply numerical differentiation, estimate the friction coefficient, and output the results.


# Generating documentation
The package also includes Doxygen documentation for detailed explanation of functions and code structure.

Run the following commands to generate the documentation: 
<br>
\code
    doxygen -g
    sed -i 's/PROJECT_NAME[ ]*=.*/PROJECT_NAME=Friction Rate Model/' Doxyfile
    doxygen
    make -C latex
\endcode

Ensure that Doxygen and Latex are installed before running these commands.
The resulting documentation will be in latex/refman.pdf and html/index.html.


# Dependencies
To run this package, the following dependencies must be installed on your system:
- C++ Compiler (e.g., gcc)
- Boost C++ Libraries (program_options)
- rarray Library (for handling numerical arrays)
- Doxygen & LaTeX (for generating documentation)


# Example usage
Below is showing an example use of the package that generates sample dataset (with default parameters), analyze it, and creates documentation:
<br>
\code
    make testmodel.dat
    make analysis
    make doc
\endcode


# Improving stability
It should be noted that the current implementation of the "frictionrate" function in "friction" module is susceptible to numerical instability and may produce NaN or Inf values due to division by a near-zero value during the computation. Specifically, "frictionrate" is dividing by the change in velocity over time, which is computed using numerical differentiation. If two consecutive velocity values in the dataset are nearly identical, then this will result in a near-zero denominator leading to instability.

## Possible fixes
To make "frictionrate" more robust, consider the following modifications:
- Apply a threshold to prevent division by near-zero values. For instance, implement an if to checke if dv/dt was smaller than a threshold (e.g. 1e-6), then set it to a specified value.
- Use a moving average of a smoothing filter before differentiation. In this way, you can reduce the high-frequency noises in the data that might cause small velocity changes.
- Check if the final calculated value of friction rate is physically valid. If it exceeds a realistic range, then report a warning.
