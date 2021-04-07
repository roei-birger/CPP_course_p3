#include "NumberWithUnits.hpp"
#include "doctest.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace ariel;
using namespace std;

TEST_CASE("Load & Read from file test")
{
    //open file
    ofstream MyFile("filename.txt");

    // Write to the file
    MyFile << "1 km = 1000 m\n1 m = 100 cm\n1 kg = 1000 g\n1 ton = 1000 kg\n1 hour = 60 min\n1 min = 60 sec\n1 USD = 3.33 ILS";
    MyFile.close();

    ifstream units_MyFile{"filename.txt"};
    CHECK_NOTHROW(NumberWithUnits::read_units(units_MyFile));

    // MyFile.seekp(0);
    // MyFile << "vdvdvdv";
}

//create NumberWithUnits
NumberWithUnits u1{500, "cm"};
NumberWithUnits u2{1000, "cm"}; //10 meter
NumberWithUnits u3{50, "m"};
NumberWithUnits u4{5000, "m"}; //5 km
NumberWithUnits u5{2, "km"};
NumberWithUnits u6{2, "km"};
NumberWithUnits u7{200, "g"};
NumberWithUnits u8{1000, "g"}; //1 kg
NumberWithUnits u9{500, "kg"};
NumberWithUnits u10{1200, "kg"}; //1.2 ton
NumberWithUnits u11{1.5, "ton"};
NumberWithUnits u12{1.5, "ton"};
NumberWithUnits u13{30, "sec"};
NumberWithUnits u14{60, "sec"}; //1 min
NumberWithUnits u15{30, "min"};
NumberWithUnits u16{30, "min"};
NumberWithUnits u17{0.5, "hour"};
NumberWithUnits u18{60, "hour"};
NumberWithUnits u19{3.33, "ILS"}; //1 dolar
NumberWithUnits u20{1, "ILS"};
NumberWithUnits u21{2, "USD"};
NumberWithUnits u22{6, "USD"};

//Basic test
TEST_CASE("Compare function")
{

    CHECK(1 == 1);
}
