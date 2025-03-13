# Makefile for the solve_heat_1d module and utilities.
# On the cluster, you will need to load at the gcc, rarray, and openBLAS modules before typing 'make'.
# Part of assignment 5 of PHY1610H, Winter 2025.

CXX= g++
CXXFLAGS= -O3 -g -Wall -Wfatal-errors -std=c++17
LDLIBS= -lopenblas

all: solve_heat_1d

# Object files
solve_heat_1d.o: solve_heat_1d.cpp init.h matrix_generate.h
init.o: init.cpp init.h
matrix_generate.o: matrix_generate.cpp matrix_generate.h
multiply_matrix_vector.o: multiply_matrix_vector.cpp multiply_matrix_vector.h
output.o: output.cpp output.h

# Define targets (create compiled codes)
solve_heat_1d: solve_heat_1d.o init.o matrix_generate.o multiply_matrix_vector.o output.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)



clean:
	$(RM) solve_heat_1d solve_heat_1d.o init.o matrix_generate.o multiply_matrix_vector.o output.o