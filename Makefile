# The Makefile for gameof1d

gameof1d: initialization.o gameof1d.o
	g++ -o gameof1d initialization.o gameof1d.o 


initialization.o: initialization.cpp initialization.h
	g++ -std=c++17 -O3 -c -o initialization.o initialization.cpp


gameof1d.o: gameof1d.cpp initialization.h
	g++ -std=c++17 -O3 -c -o gameof1d.o gameof1d.cpp
