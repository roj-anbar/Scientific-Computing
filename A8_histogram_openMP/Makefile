# Makefile for the histogram module and utilities.
# On the cluster, you will need to load at the gcc module before typing 'make'.
# Part of assignment 8 of PHY1610H, Winter 2025.

CXX= g++
CXXFLAGS= -O3 -g -Wall -Wfatal-errors -std=c++17 -fopenmp
LDLIBS = #-fopenmp

all: parallel_hist


# Object files
parallel_hist.o: parallel_hist.cpp calc_histogram.h read_data_parallel.h
read_data_parallel.o: read_data_parallel.cpp read_data_parallel.h
calc_histogram.o: calc_histogram.cpp calc_histogram.h


# Define targets (create compiled codes)
parallel_hist: parallel_hist.o read_data_parallel.o calc_histogram.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)


clean:
	$(RM) parallel_hist *.o

.PHONY: all clean