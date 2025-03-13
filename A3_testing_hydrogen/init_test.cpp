// init_test.cpp: a unit testsuite for 'init' module using Catch2
#include "init.h"
#include <cmath> //needed for absolute value
#include <catch2/catch_all.hpp>

// Implement multiple tests for 'initMatrix':

// Test 1: check 'initMatrix' for the case of empty matrix (n=0)
TEST_CASE("initMatrix test1: must return empty matrix for n = 0")
{
    rmatrix<double> m = initMatrix(0);
    // check if matrix is empty
    REQUIRE(m.size() == 0);
}

// Test 2: check 'initMatrix' for the case of 1-element matrix (n=1)
TEST_CASE("initMatrix test2: must return certain value for n = 1")
{
    rmatrix<double> m = initMatrix(1);

    // check the size of the matrix
    REQUIRE(m.size() == 1);

    // check the value (should not include the sign)
    REQUIRE(std::abs(m[0][0]) == Catch::Approx(97.0/2500.0));
}

// Test 3: check 'initMatrix' for the case of an invalid n
// n should be a cube of an odd number
TEST_CASE("initMatrix test3: must fail if n is not a cube of an odd number")
{
    // If initMatrix(n) throws an exception, the test should pass
    REQUIRE_THROWS(initMatrix(100)); 
}
