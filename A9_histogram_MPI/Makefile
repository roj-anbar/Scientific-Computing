# Makefile for the parallel histogram computation and utilities.
# On the cluster, you will need to load the gcc, openMPI, and rarray modules before typing 'make'.
# Part of assignment 8 of PHY1610H, Winter 2025.

# Compiler: Use the OpenMPI C++ compiler wrapper
MPICXX= mpicxx #g++
CXXFLAGS= -O2 -Wall -std=c++17 
# Libraries: mpicxx will link MPI libraries automatically
LDLIBS = 

all: parallel_histogram_MPI parallel_histogram_MPI_v2


# Object files
parallel_histogram_MPI.o: parallel_histogram_MPI.cpp calc_histogram_local.h
parallel_histogram_MPI_v2.o: parallel_histogram_MPI_v2.cpp calc_histogram_local.h
calc_histogram_local.o: calc_histogram_local.cpp calc_histogram_local.h


# Define targets (create compiled codes)
parallel_histogram_MPI: parallel_histogram_MPI.o calc_histogram_local.o
	$(MPICXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

parallel_histogram_MPI_v2: parallel_histogram_MPI_v2.o calc_histogram_local.o
	$(MPICXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)


clean:
	$(RM) parallel_histogram_MPI parallel_histogram_MPI_v2 *.o

.PHONY: all clean