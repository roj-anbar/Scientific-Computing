# Makefile for the solve_KPP_1d module and utilities.
# On the cluster, you will need to load at the gcc, rarray, and fftw modules before typing 'make'.
# Part of assignment 7 of PHY1610H, Winter 2025.

CXX= g++
CXXFLAGS= -O3 -g -Wall -Wfatal-errors -std=c++17
LDLIBS= 

all: percolation_model


# Object files
percolation_model.o: percolation_model.cpp init.h setup_lattice.h single_walker.h 
init.o: init.cpp init.h
setup_lattice.o: setup_lattice.cpp setup_lattice.h
single_walker.o: single_walker.cpp single_walker.h

# Define targets (create compiled codes)
percolation_model: percolation_model.o init.o setup_lattice.o single_walker.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

run: percolation_model 
	./percolation_model 200 200 0.7 2.0 25 20 12345

clean:
	$(RM) percolation_model *.o