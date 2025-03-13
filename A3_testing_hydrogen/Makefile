# Makefile
CXX= g++

CATCH2_BASE?= /Users/rojin/Projects/my_libs/catch2/
CATCH2_INC= $(CATCH2_BASE)include
CATCH2_LIB= $(CATCH2_BASE)lib

CXXFLAGS=-std=c++17 -O3 -Wall -g -I$(CATCH2_INC)
LDFLAGS=-g -L$(CATCH2_LIB)

all: hydrogen
test: integratedtest run_output_c2 run_init_test run_eigenval_test 

# Object files
hydrogen.o: hydrogen.cpp eigenval.h output.h init.h
eigenval.o: eigenval.cpp eigenval.h
output.o: output.cpp output.h
init.o: init.cpp init.h

# Test files
init_test.o: init_test.cpp init.h
eigenval_test.o: eigenval_test.cpp eigenval.h
output_c2.o: output_c2.cpp output.h


# Define targets (creates compiled codes)
hydrogen: hydrogen.o eigenval.o output.o init.o
	$(CXX) $(LDFLAGS) -o $@ $^
init_test: init_test.o init.o
	$(CXX) $(LDFLAGS) -o $@ $^ -lCatch2Main -lCatch2	
eigenval_test: eigenval_test.o eigenval.o
	$(CXX) $(LDFLAGS) -o $@ $^ -lCatch2Main -lCatch2	
output_c2: output_c2.o output.o
	$(CXX) $(LDFLAGS) -o $@ $^ -lCatch2Main -lCatch2


# Run tests
run_init_test: ./init_test
	./init_test -s
run_eigenval_test: ./eigenval_test
	./eigenval_test -s
run_output_c2: ./output_c2
	./output_c2 -s

# Define integrated test
data.txt data.bin cout.txt: hydrogen
	./hydrogen > cout.txt
integratedtest: data0.txt data0.bin cout0.txt \
				data.txt data.bin cout.txt
	diff cout.txt cout0.txt
	diff data.txt data0.txt
	cmp data.bin data0.bin


clean:
	$(RM) hydrogen.o eigenval.o output.o init.o init_test.o eigenval_test.o output_c2.o data.txt data.bin cout.txt testoutputarr.txt testoutputarr.bin
.PHONY: run_init_test run_eigenval_test run_output_c2 integratedtest all clean test
