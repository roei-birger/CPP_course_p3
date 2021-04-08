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
NumberWithUnits u12{2, "ton"};
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

//Basic tests
TEST_CASE("Equal function")
{
    CHECK_EQ(u9, u9);
    CHECK_EQ(u5, u6);
    CHECK_EQ(u6, u5);
    CHECK_EQ(u16, u15);
    CHECK_EQ(u15, u16);
    CHECK_EQ(u17, u16);
    CHECK_EQ(u16, u17);
}

TEST_CASE("Equal function diff type")
{
    CHECK_THROWS(u12.operator==(u5)); //diff type
    CHECK_THROWS(u5.operator==(u12));
}

TEST_CASE("not equal function")
{
    CHECK_NE(u1, u2); //same type
    CHECK_NE(u2, u1);
}

TEST_CASE("not equal function diff type")
{
    CHECK_THROWS(u11.operator!=(u4)); //diff type
    CHECK_THROWS(u4.operator!=(u11));
}

TEST_CASE("Less equal function")
{
    CHECK_LE(u1, u2); //same type
    CHECK_LE(u2, u1);
    CHECK_LE(u3, u4);
    CHECK_LE(u11, u12);
    CHECK_LE(u9, u9);
}

TEST_CASE("Less equal function diff type")
{
    CHECK_THROWS(u11.operator<=(u4)); //diff type
    CHECK_THROWS(u4.operator<=(u11));
}

TEST_CASE("Less than function")
{
    CHECK_LT(u3, u4); //same type
    CHECK_LT(u11, u12);
}

TEST_CASE("Less than function diff type")
{
    CHECK_THROWS(u11.operator<(u4)); //diff type
    CHECK_THROWS(u4.operator<(u11));
}

TEST_CASE("greater equal function")
{
    CHECK_GE(u1, u2); //same type
    CHECK_GE(u2, u1);
    CHECK_GE(u4, u3);
    CHECK_GE(u12, u11);
    CHECK_GE(u9, u9);
}

TEST_CASE("greater  equal function diff type")
{
    CHECK_THROWS(u11.operator>=(u4)); //diff type
    CHECK_THROWS(u4.operator>=(u11));
}

TEST_CASE("greater than function")
{
    CHECK_GT(u4, u3); //same type
    CHECK_GT(u12, u11);
}

TEST_CASE("greater than function diff type")
{
    CHECK_THROWS(u11.operator>(u4)); //diff type
    CHECK_THROWS(u4.operator>(u11));
}

TEST_CASE("plus function same type")
{
    CHECK_EQ(u15 + u16, NumberWithUnits(60, "min"));
    CHECK_EQ(u16 + u15, NumberWithUnits(60, "min"));
}

TEST_CASE("plus function connect type")
{
    CHECK_EQ(u15 + u16, u18);
    CHECK_EQ(u16 + u15, u18);
}

TEST_CASE("plus function unconnected type")
{
    CHECK_THROWS(u11 + u4); //diff type
    CHECK_THROWS(u4 + u11);
}

TEST_CASE("plus function same type")
{
    NumberWithUnits temp_min_p(30, "min");
    temp_min_p += NumberWithUnits(30, "min");
    CHECK_EQ(temp_min_p, NumberWithUnits(60, "min"));

    NumberWithUnits temp_km_p(3, "km");
    temp_km_p += NumberWithUnits(3, "km");
    CHECK_EQ(temp_km_p, NumberWithUnits(6, "km"));
}

TEST_CASE("plus function connect type")
{
    NumberWithUnits temp_min_p(30, "min");
    temp_min_p += NumberWithUnits(1, "hour");
    CHECK_EQ(temp_min_p, NumberWithUnits(90, "min"));

    NumberWithUnits temp_hour_p(1, "hour");
    temp_hour_p += NumberWithUnits(30, "min");
    CHECK_EQ(temp_hour_p, NumberWithUnits(1.5, "hour"));
}

TEST_CASE("plus function unconnected type")
{
    CHECK_THROWS(u11 += u4); //diff type
    CHECK_THROWS(u4 += u11);
}


TEST_CASE("minus function same type")
{
    CHECK_EQ(u15 - u16, NumberWithUnits(0, "min"));
    CHECK_EQ(u16 - u15, NumberWithUnits(0, "min"));
}

TEST_CASE("minus function connect type")
{
    CHECK_EQ(u15 - u16, NumberWithUnits(0, "hour"));
    CHECK_EQ(u16 - u15, NumberWithUnits(0, "hour"));
}

TEST_CASE("minus function unconnected type")
{
    CHECK_THROWS(u11 - u4); //diff type
    CHECK_THROWS(u4 - u11);
}

TEST_CASE("minus equal function same type")
{
    NumberWithUnits temp_min_m(30, "min");
    temp_min_m -= NumberWithUnits(0, "min");
    CHECK_EQ(temp_min_m, NumberWithUnits(30, "min"));

    NumberWithUnits temp_km_m(3, "km");
    temp_km_m -= NumberWithUnits(2, "km");
    CHECK_EQ(temp_km_m, NumberWithUnits(1, "km"));
}

TEST_CASE("minus equal function connect type")
{
    NumberWithUnits temp_min_m(30, "min");
    temp_min_m -= NumberWithUnits(0.25, "hour");
    CHECK_EQ(temp_min_m, NumberWithUnits(15, "min"));

    NumberWithUnits temp_hour_m(1, "hour");
    temp_hour_m -= NumberWithUnits(30, "min");
    CHECK_EQ(temp_hour_m, NumberWithUnits(0.5, "hour"));
}

TEST_CASE("minus equal function unconnected type")
{
    CHECK_THROWS(u11 -= u4); //diff type
    CHECK_THROWS(u4 -= u11);
}
