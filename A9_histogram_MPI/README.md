# **Parallel Histogram Computation: MPI**

## **Overview**
This project computes the histogram of the logarithm of an input dataset in parallel using MPI. The program reads numeric values from an input file, applies a logarithmic transformation with a user-specified base, and bins the log-transformed values into intervals of width 1. The final histogram is written to console in a two-column format where the first column is the lower bound of each bin and the second column is the normalized count of data points in that bin.

**Note:** There are two versions of the main driver:
- **Version 1:** The root process reads the input file in batches, scatters the data among MPI processes, and each process accumulates its data before computing a histogram.
- **Version 2:** Every MPI process independently opens the input file and reads only the lines assigned to it (based on its rank), then computes its local histogram. The histograms are then reduced to form the global normalized histogram.

## **Input Parameters**
The program accepts two command-line arguments:

- log_base: The base used for computing the logarithm. (Choosing an appropriate log base is important; for instance, if you require at least 30 bins over your data’s range, you might select a base close to 1.3 for this dataset).

- input_filename: The path to the file containing the input numeric data (one value with fixed length per line).

- batch_size: The number of lines (data points) to be read at once.  
   _Note:_ This parameter is used only by Version 1.

## **Modules and Functions**

### 1. **Calculate histogram module (calc_histogram_local.cpp)**

- **Purpose:**  
Computes the histogram of the log-transformed data locally on each MPI process.

- **Function:**
  - `std::vector<double> compute_histogram_local(const std::vector<double> &data_local,
                                                double log_base,
                                                int n_bins,
                                                int min_bin,
                                                int bin_width,
                                                std::vector<double> &counts_local)`:  
    This function takes a vector of data points on the current MPI rank, applies a logarithm transformation with the given log_base, and bins the transformed values into a histogram.
    Each data point x is transformed as:   y = log(x) / log(log_base).
     The bin index is computed as:    bin_index = floor((y - min_bin) / bin_width)
    Note: The function handles the upper edge of the data range by assigning overflow values to the last bin.

### 2. **Main driver modules**
Coordinates the execution of the program by parsing input arguments, invoking the data reading and histogram calculation modules, and writing the results.
There are two versions:
  
#### Version 1: `parallel_histogram_MPI.cpp`
- **Purpose:**  
  The root process reads the input file in batches (of size specified by the user) and distributes each batch among MPI processes using `MPI_Scatter`. Each process appends its received data points to a local accumulator vector. Once the entire file has been read, each process computes a histogram on its full local dataset, and the local histograms are reduced to form a global normalized histogram on the root.
  
#### Version 2: `parallel_histogram_MPI_v2.cpp`
- **Purpose:**  
  Each MPI process opens the input file independently and reads only the lines assigned to it based on the global line index (i.e., a line is assigned to process `rank` if `(line_index % num_processes) == rank`). Each process then computes a histogram on its local dataset, and the histograms are reduced to form the global normalized histogram on the root.


- **Workflow for both versions:**
  1. Parse the command-line arguments for log_base, input_filename, and batch_size .
  2. Read and log-transform the input data in parallel.
  3. Calculate the local histogram from the log-transformed data in parallel on each rank.
  4. Use `MPI_Reduce` to sum the local histograms into a global histogram on rank 0.
  5. Normalize the histogram by dividing each bin count by the total number of data points.
  6. Output the final histogram (bin start and normalized count) and report execution time.



## **Compilation and Usage**

### **Requirements:**
- **MPI:** OpenMPI for for parallel execution.
- **C++ compiler:** `g++`.
- **rarray:** for array handling.


For running the program on Teach Cluster the above modules should be loaded before compilation as:
>> module load gcc/13 openmpi/5 rarray


### **Compilation:**
A Makefile is provided. To build the project (for bothe versions), simply run:
>> make


### **Running the Simulation:**

You can run the executable directly with your parameters using the following command:
>> ./parallel_histogram_MPI log_base input_filename batch_size
>> ./parallel_histogram_MPI_v2 log_base input_filename batch_size

For example, to use a logarithm base of 1.5 with a data file named data.txt and batch size of 10000:
>> ./parallel_histogram_MPI 1.5 data.dat 10000

### Cleaning the build:
To remove compiled objects and the executable, run:
>> make clean


## **Run on Teach cluster**
To facilitate running the program on the Teach Cluster, a set of SLURM job scripts has been created for five different MPI processes (P = 1, 8, 20, 40 and 80). Each script sets the appropriate environment variable and submits the job running both versions with resource requests.
To submit a job, ssh to the cluster and run:
>> sbatch job_name.sh