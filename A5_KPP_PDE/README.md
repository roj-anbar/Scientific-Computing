# **Simulation of 1D Non-linear Heat Diffusion (KPP-Fisher)**

## **Overview**
This project implements a numerical simulation for solving the **1D KPP-Fisher's heat diffusion** for assignment 5 of PHY1610 course. 

## **Problem Definitions**
The non-linear differential equation of interest for a 1d domain of x = [0, L] is:
\[
\frac{\partial u}{\partial t} = u(1-u) + \frac{\partial^2 u}{\partial x^2}
\]

The boundary and initial conditions are:
- **Boundary Conditions:**
  - u(0, t) = A*sin^2(t)
  - u(L, t) = 0
- **Initial Condition:**
  -  u(x, 0) = 0 



## **Numerical Method**

The numerical method uses **explicit forward Euler time discretization** and **finite difference spatial discretization**.

- The equation is discretized on a uniform grid** with N spatial points.
- The explicit forward Euler scheme*is used for time integration:
  u_{s+1} = G . u^s + dt . u_s - dt * (u_s)^2

- The coefficient matrix G is the matrix of coefficients for the spatial differentiations and is built based on different solver types.
- The solution is computed at each time step and written to an output file at specified intervals.


## **Implementation Details**
The solver supports **three different implementations** for matrix-vector multiplication:

1. **Full Matrix with Manual Multiplication**  
   - Uses an explicit triple loop to perform matrix-vector multiplication.
2. **Full Matrix with BLAS Multiplication**  
   - Uses BLAS routines on the full matrix to speed up matrix-vector multiplication.
3. **Tridiagonal Matrix with Banded BLAS Multiplication**  
   - Stores only the non-zero elements of G and performs efficient banded matrix-vector multiplication using BLAS.


## **Inputs**
The script takes the following parameters as input:

P = Number of output snapshots
L = Length of the spatial domain
A = Boundary condition amplitude
N = Number of grid points
T = Total simulation time
solver_type = Choose the type of solver from the 3 options below:
    1. full_mat_manual = Full matrix with manual multiplication
    2. full_mat_blas = Full matrix with BLAS multiplication
    3. tri_mat_blas = Tridiagonal matrix with banded BLAS multiplication

**Test values for inputs**
P = 400
L = 5
A = 0.2
N = 100
T = 10


## **Compilation and Usage**

### **Requirements**
- **C++ compiler** (e.g., `g++`)
- **OpenBLAS** (for optimized linear algebra operations)
- **rarray** (for array handling)

You have to load the above modules before compiling the program. On teach cluster do:
>> module load gcc rarray openblas


### **Compiling the Code**
The provided Makefile allows compilation with just running:
>> make


### **Running the Simulation**
The compiled executable is 'solve_heat_1d'. Run it with the following command:
>> ./solve_heat_1d P L A N T solver_type

