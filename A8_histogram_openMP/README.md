# **Parallel Histogram Computation: OpenMP**

## **Overview**
This project computes the histogram of the logarithm of an input dataset in parallel using OpenMP. The program reads numeric values from an input file, applies a logarithmic transformation with a user-specified base, and bins the log-transformed values into intervals of width 1. The final histogram is written to an output file in a two-column format where the first column is the lower bound of each bin and the second column is the count of data points in that bin.

## **Input Parameters**
The program accepts two command-line arguments:

- log_base: The base used for computing the logarithm. (Choosing an appropriate log base is important; for instance, if you require at least 30 bins over your data’s range, you might select a base close to 1.3 for this dataset.)

- input_filename: The path to the file containing the input numeric data (one value with fixed length per line).


## **Modules and Functions**

### 1. **Read data in parallel module (read_data_parallel.cpp)**

- **Purpose:** 
Reads the input file concurrently using OpenMP and computes the logarithm of each data value with the specified base.

- **Function:**
  - `std::vector<double> read_parallel(const std::string &filename, double log_base, int num_threads)`:  
    Opens the file, splits the workload among threads, and calculates the logarithm for each value.
    Note: This module assumes fixed-length lines for efficient offset-based reading. If your data does not meet this requirement, consider modifying the file reading logic.



### 2. **Calculate histogram module (calc_histogram.cpp)**

- **Purpose:**  
Computes the histogram of the log-transformed data by dividing the data range into unit-width bins.

- **Function:**
  - `rmatrix<double> calc_histogram(const std::vector<double> &data)`:  
    Determines the minimum and maximum of the log-transformed values, creates bins for each integer interval [k,k+1), and counts the number of data points per bin.
    Note: The function handles the upper edge of the data range by assigning overflow values to the last bin.

### 3. **Main driver module (parallel_hist.cpp)**

- **Purpose:**  
Coordinates the execution of the program by parsing input arguments, invoking the data reading and histogram calculation modules, and writing the results.

- **Workflow:**
  - Parse the command-line arguments for log_base and input_filename.
  - Read and log-transform the input data in parallel.
  - Calculate the histogram from the log-transformed data in parallel.
  - Write the histogram (bin starting point and count) to an output file, whose name reflects the log base and number of threads used.
  - Report the total execution time.



## **Compilation and Usage**

### **Requirements:**
- **C++ compiler** (e.g., `g++`)
- **rarray** (for array handling)
- **OpenMP** for parallel execution.

For running the program on Teach Cluster the above modules should be loaded before compilation as:
>> module load gcc rarray


### **Compilation:**
A Makefile is provided. To build the project, simply run:
>> make


### **Running the Simulation:**

You can run the executable directly with your parameters using the following command:
>> ./parallel_hist log_base input_filename

For example, to use a logarithm base of 1.5 with a data file named data.txt:
>> ./parallel_hist 1.5 data.dat

### Cleaning the build:
To remove compiled objects and the executable, run:
>> make clean


## **Run on Teach cluster**
To facilitate running the program on the Teach Cluster, a set of SLURM job scripts has been created for three different thread numbers (1, 16, and 40). Each script sets the appropriate environment variable (typically using export OMP_NUM_THREADS=<n>) and submits the job with resource requests tuned to the expected load.
To submit a job, ssh to the cluster and run:
>> sbatch job_name.sh