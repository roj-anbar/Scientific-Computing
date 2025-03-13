# **Simulation of 1D Non-linear Heat Diffusion (KPP-Fisher)**

## **Overview**
This project implements a numerical simulation with a splitting method for solving the **1D KPP-Fisher's heat diffusion** for assignment 6 of PHY1610 course. 

## **Problem Definitions**
The non-linear differential equation of interest for a 1d domain of x = [0, L] is:
\[
\frac{\partial u}{\partial t} = u(1-u) + \frac{\partial^2 u}{\partial x^2}
\]

The boundary and initial conditions are:
- **Boundary Conditions:**
  - u(0, t) = 0
  - u(L, t) = 0
- **Initial Condition:**
  -  u(x, 0) = A*sin(pi*x/L)^100



## **Numerical Method**

The solution to the 1D KPP-Fisher equation is computed numerically using a splitting approach that is described below.

- The equation is discretized on a uniform grid with N spatial points.

- Each time step is divided into two substeps:
  1. **Reaction substep**:
  In the first substep, the nonlinear reaction term is solved analytically at each spatial poin.
  u_s+1 = u_s / (u_s + (1-u_s) * exp(-dt))

  2. **Diffusion substep**: This step is solved by taking the Fourier Transform of the PDE and convert the solution back.
  u^_s+1 = u^_s * exp(-k^2 * dt)
  Here, k is the wavenumber.


- Therefore, at each timestep we first calculate the solution to the recation equation and then pass this to the diffusion equation as below:
>> u_s = u_old
>> u_reaction = u_s / (u_s + (1-u_s) * exp(-dt))
>> u^_diffusion = u^_reaction * exp(-k^2 * dt)
>> u_s+1 = F-1 (u^_diffusion)
>> u_current = u_s+1

- The solution u is computed at each timestep and snapshots of it are written to a file at a certain interval 'output_interval' calculated from the input variable 'P'.



## **Inputs**
The script takes the following parameters as input:

P = Number of output snapshots
L = Length of the spatial domain
A = Boundary condition amplitude
N = Number of grid points
T = Total simulation time

**Test values for inputs**
P = 400
L = 5
A = 1
N = 100
T = 10


## **Compilation and Usage**

### **Requirements**
- **C++ compiler** (e.g., `g++`)
- **rarray** (for array handling)
- **FFTW** (for fast Fourier transform)

You have to load the above modules before compiling the program. On teach cluster do:
>> module load gcc rarray fftw/3


### **Compiling the Code**
The provided Makefile allows compilation with just running:
>> make


### **Running the Simulation**
The compiled executable is 'solve_KPP_1d'. Run it with the following command:
>> ./solve_KPP_1d P L A N T 

