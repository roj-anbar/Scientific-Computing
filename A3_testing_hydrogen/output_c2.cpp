// output_c2.cpp
#include "output.h"
#include <fstream>

#include <catch2/catch_all.hpp>

// Test for 'writeText' function
TEST_CASE("writeText test")
{
    // create file:
    rvector<double> a(3);
    a = 1,2,3;
    writeText("testoutputarr.txt", a);
    // read back:
    std::ifstream in("testoutputarr.txt");
    std::string s[3];
    in >> s[0] >> s[1] >> s[2];
    // check
    REQUIRE(s[0]=="1");
    REQUIRE(s[1]=="2");
    REQUIRE(s[2]=="3");
}


//Test for 'writeBinary' function
TEST_CASE("writeBinary test")
{
    // create file:
    rvector<double> a(3);
    a = 1, 2, 3;
    writeBinary("testoutputarr.bin", a);

    // read back:
    std::ifstream in("testoutputarr.bin", std::ios::binary);
    double b[3]; // to store the read values
    in.read(reinterpret_cast<char*>(b), 3 * sizeof(double)); // use in.read() to read a binary file

    // check (use Catch::Approx to avoid precision issues)
    REQUIRE(b[0] == Catch::Approx(1.0));
    REQUIRE(b[1] == Catch::Approx(2.0));
    REQUIRE(b[2] == Catch::Approx(3.0));
}