# Makefile for the solve_KPP_1d module and utilities.
# On the cluster, you will need to load at the gcc, rarray, and fftw modules before typing 'make'.
# Part of assignment 6 of PHY1610H, Winter 2025.

CXX= g++
CXXFLAGS= -O3 -g -Wall -Wfatal-errors -std=c++17
LDLIBS= -lfftw3

all: solve_KPP_1d
test: test_fft

# Object files
solve_KPP_1d.o: solve_KPP_1d.cpp init.h diffusion_substep.h output.h 
init.o: init.cpp init.h
diffusion_substep.o: diffusion_substep.cpp diffusion_substep.h
output.o: output.cpp output.h
test_fft.o: test_fft.cpp init.h diffusion_substep.h

# Define targets (create compiled codes)
solve_KPP_1d: solve_KPP_1d.o init.o diffusion_substep.o output.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

test_fft: test_fft.o init.o diffusion_substep.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) solve_KPP_1d solve_KPP_1d.o init.o diffusion_substep.o output.o test_fft test_fft.o