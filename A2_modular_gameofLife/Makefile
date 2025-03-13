# Makefile for gameof1d

CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall
RM = rm -f

all: gameof1d

gameof1d: initialization.o calculate_next_alive_status.o output_single_timestep.o gameof1d.o
	$(CXX) -o gameof1d initialization.o calculate_next_alive_status.o output_single_timestep.o gameof1d.o 


initialization.o: initialization.cpp initialization.h
	$(CXX) -c $(CXXFLAGS) -o initialization.o initialization.cpp


calculate_next_alive_status.o: calculate_next_alive_status.cpp calculate_next_alive_status.h
	$(CXX) -c $(CXXFLAGS) -o calculate_next_alive_status.o calculate_next_alive_status.cpp


output_single_timestep.o: output_single_timestep.cpp output_single_timestep.h
	$(CXX) -c $(CXXFLAGS) -o output_single_timestep.o output_single_timestep.cpp


gameof1d.o: gameof1d.cpp initialization.h
	$(CXX) -c $(CXXFLAGS) -o gameof1d.o gameof1d.cpp



clean:
	$(RM) initialization.o calculate_next_alive_status.o output_single_timestep.o gameof1d.o



.PHONY: all clean