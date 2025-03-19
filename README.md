# **Percolation Model in 2D Lattice**

## **Overview**
This project simulates a percolation modeling in a two-dimensional lattice for assignment 7 of PHY1610 course. 
In our model, each cell in an N×M lattice is randomly designated as either **filled** or **empty**; each cell is empty with probability *p*. A "walker" is then placed in every empty cell in the top row. At each time step the walker moves one cell in one of four directions (left, right, up, or down) with certain probabilities defined by a downward tendency parameter *g*, as follows:
- **Left:**  l = 1/z
- **Right:** r = 1/z
- **Up:**    u = 1/gz
- **Down:**  d = g/z

where $ z = l + r + u + d $.
Moves that would take the walker outside the lattice or into a filled cell are invalidated by setting their probability to zero (and thus they are not chosen). To improve statistics, the simulation launches *K* independent walkers from each empty top-row cell and stops advancing a walker when it reaches the bottom row or when the maximum number of steps (computed as *S(M² + N²)*) is reached.

The final output is the fraction of walkers that successfully traverse the lattice (i.e. reach the bottom) printed on the display.


## **Input Parameters**
The simulation parameters are provided via command-line and include:

- M: Number of columns (lattice is M cells wide).
- N: Number of rows (lattice is N cells high).
- p: Probability of each cell being empty.
- g: Downwards tendency (positive constant).
- K: Number of repetitions (#walkers per each empty cell).
- S: Parameter used in max number of steps for each walker.
- seed: Initial seed for random generator.

Using these parameters, the maximum number of allowed steps for each walker is then calculated as: max_steps = S*(M^2 + N^2)



## **Modules and Functions**

### 1. **init Module**
Module for initializing the simulation parameters for solving the percolation model for a 2D lattice.

- **Files:** `init.h`, `init.cpp`

- **Purpose:** 
  - Defines the `SimParameters` structure.
  - Provides functions to parse command-line arguments and store simulation parameters.

- **Functions:**
  - `store_commandline_args(int argc, char* argv[])`:  
    Reads the command-line arguments and returns a `SimParameters` object.

  - `print_sim_parameters(const SimParameters &sim_params)`:  
    Prints the simulation parameters for verification.


### 2. **Lattice Setup Module:**
Module to setup the porous media by filling the 2D lattice randomly.
Fills each cell with probability 1-p using Bernoulli distribution to generate binary outcomes.

- **Files:** `setup_lattice.h`, `setup_lattice.cpp`

- **Purpose:**  
  - Initializes a two-dimensional boolean lattice representing the porous medium.
  - Each cell is set to either filled (`true`) or empty (`false`) using a Bernoulli distribution.  

- **Functions:**
  - `setup_lattice(int M, int N, double p, rmatrix<bool> &lattice, int seed)`:  
    Fills an M×N lattice so that each cell is empty with probability p. "Success" with probability 1-p results in a filled cell (value = 1). "Failure" with probability p results in an empty cell (value = 0).


### 3. **Single Walker Module:**
Chooses a move for the walker on a 2D lattice using weighted random sampling.

- **Files:** `single_walker.h`, `single_walker.cpp`

- **Purpose:**  
  - Simulates the motion of a single walker on the lattice.
  - The walker chooses its move (left, right, up, or down) based on the weighted probabilities derived from g.

- **Functions:**
  - `choose_move(const rmatrix<bool> &lattice, int row, int col, int M, int N, double g, int seed)`:  
    (Local function) Computes raw weights for left, right, up, and down moves using the downward tendency parameter g. Invalid moves (those that would leave the lattice or go into a filled cell) are set to zero. The function normalizes these weights into probabilities and randomly selects a move for the walker using the cumulative probability method.
  - `simulate_walker(const rmatrix<bool> &lattice, int M, int N, double g, int max_steps, int seed, int initial_col)`:  
    Initializes the walker at the given column in the top row. Then it simulates movement for up to max_steps. If the walker reaches the bottom row (row index N−1), the function returns true; otherwise, it returns false.


### 4. **Main Driver Module:**
Main driver script to simulate the percolation model through a 2D lattice.

- **File:** `percolation_model.cpp`

- **Purpose:**  
  - Reads simulation parameters.
  - Sets up the lattice.
  - Launches K walkers from every empty cell in the top row.
  - Counts the total number of walkers and those that successfully reach the bottom.
  - Computes and outputs the fraction of successful walkers.

- **Function `main()`:**
  1. Parse parameters using `store_commandline_args()` and print them.
  2. Initialize the lattice using `setup_lattice()`.
  3. For each empty cell in the top row, simulate K walkers with `simulate_walker()`.
  4. Compute the fraction of walkers reaching the bottom.
  5. Output the result.


 


## **Compilation and Usage**

### **Requirements:**
- **C++ compiler** (e.g., `g++`)
- **rarray** (for array handling)

For running the program on Teach Cluster the above modules should be loaded before compilation as:
>> module load gcc rarray


### **Compilation:**
A Makefile is provided. To build the project, simply run:
>> make


### **Running the Simulation:**

The Makefile includes a `run` target that executes the simulation with the following example parameters:

M = 200
N = 200
p = 0.7
g = 2.0
K = 25
S = 200
seed = 12345

To run the simulation with these parameters, type:
>> make run
 
Alternatively, you can run the executable directly with your parameters with the following command:
>> ./percolation_model M N p g K S seed

### Cleaning the build:
To remove compiled objects and the executable, run:
>> make clean