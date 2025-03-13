// eigenval_test.cpp: a unit testsuite for 'eigenval' module using Catch2
#include "eigenval.h"
//#include <cmath> //needed for absolute value
#include <catch2/catch_all.hpp>

// Implement multiple tests for 'groundState':

// Test 1: check 'groundState' for identity matrix
// groundstate of the identity matrix is 1
TEST_CASE("groundState test1: must return 1 for identity matrix")
{
    rmatrix<double> m(2, 2);
    m.fill({{1,0}, {0,1}});
    double e;
    rvector<double> a;
    groundState(m, e, a);

    // check if returned value equals to one (with an increased tolerance)
    REQUIRE(e == Catch::Approx(1.0).epsilon(1e-3));
}

// Test 2: check 'groundState' for diagonal matrix
// ground state of a diagonal matrix is its smallest element
TEST_CASE("groundState test2: must return the smallest element for a diagonal matrix")
{
    rmatrix<double> m(4, 4);
    m.fill({{5,0,0,0},
            {0,7,0,0},
            {0,0,12,0},
            {0,0,0,3}});
    double e;
    rvector<double> a;
    groundState(m, e, a);

    // check if returned value equals to one
    REQUIRE(e == Catch::Approx(3.0).epsilon(1e-3));
}

// Test 3: check 'groundState' for a specific matrix
// ground state energy of the matrix {{-1,1},{2,0}} is -2
TEST_CASE("groundState test3: must return -2 for matrix {{-1,1},{2,0}}")
{
    rmatrix<double> m(2, 2);
    m.fill({{-1, 1}, {2, 0}});
    double e;
    rvector<double> a;
    groundState(m, e, a);

    // check if returned value equals to one
    REQUIRE(e == Catch::Approx(-2.0).epsilon(1e-3));
}

// Test 4: check 'groundState' for an invalid matrix
// ground state should fail for the matrix {{1,1},{2,0}}
TEST_CASE("groundState test4: must fail for matrix {{1,1},{2,0}}")
{
    rmatrix<double> m(2, 2);
    m.fill({{1, 1}, {2, 0}});
    double e;
    rvector<double> a;

    // check if it fails
    REQUIRE_THROWS(groundState(m, e, a));
}
