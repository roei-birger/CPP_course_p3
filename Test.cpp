#include "NumberWithUnits.hpp"
#include "doctest.h"
#include <iostream>
#include <sstream>

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
    NumberWithUnits::read_units(units_MyFile);
}

//Basic tests
TEST_CASE("Equal function")
{
    NumberWithUnits u5{2, "km"};
    NumberWithUnits u6{2, "km"};
    NumberWithUnits u9{500, "kg"};
    NumberWithUnits u15{30, "min"};
    NumberWithUnits u16{30, "min"};
    NumberWithUnits u17{0.5, "hour"};

    CHECK_EQ(u9, u9);
    CHECK_EQ(u5, u6);
    CHECK_EQ(u6, u5);
    CHECK_EQ(u16, u15);
    CHECK_EQ(u15, u16);
    CHECK_EQ(u17, u16); //diff type
    CHECK_EQ(u16, u17);
}

TEST_CASE("Equal function unconnected type")
{
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u5{2, "km"};
    NumberWithUnits u12{2, "ton"};
    NumberWithUnits u18{60, "hour"};
    NumberWithUnits u19{3.33, "ILS"}; //1 dolar
    NumberWithUnits u22{6, "USD"};

    CHECK_THROWS(u12.operator==(u5));
    CHECK_THROWS(u5.operator==(u12));
    CHECK_THROWS(u22.operator==(u1));
    CHECK_THROWS(u19.operator==(u18));
}

TEST_CASE("not equal function")
{
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u2{1000, "cm"}; //10 meter
    NumberWithUnits u3{50, "m"};
    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u7{200, "g"};
    NumberWithUnits u8{1000, "g"}; //1 kg
    NumberWithUnits u9{500, "kg"};
    NumberWithUnits u10{1200, "kg"}; //1.2 ton
    NumberWithUnits u11{1.5, "ton"};
    NumberWithUnits u12{2, "ton"};
    NumberWithUnits u16{30, "min"};
    NumberWithUnits u17{0.5, "hour"};
    NumberWithUnits u18{60, "hour"};
    NumberWithUnits u20{1, "ILS"};
    NumberWithUnits u21{2, "USD"};

    CHECK_NE(u1, u2); //same type
    CHECK_NE(u2, u1);
    CHECK_NE(u3, u4);
    CHECK_NE(u7, u8);
    CHECK_NE(u9, u10);
    CHECK_NE(u11, u12);
    CHECK_NE(u17, u18);
    CHECK_NE(u21, u20); //diff type
    CHECK_NE(u16, u18);
}

TEST_CASE("not equal function unconnected type")
{
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u5{2, "km"};
    NumberWithUnits u11{1.5, "ton"};
    NumberWithUnits u12{2, "ton"};
    NumberWithUnits u18{60, "hour"};
    NumberWithUnits u19{3.33, "ILS"}; //1 dolar
    NumberWithUnits u22{6, "USD"};

    CHECK_THROWS(u11.operator!=(u4));
    CHECK_THROWS(u4.operator!=(u11));
    CHECK_THROWS(u12.operator!=(u5));
    CHECK_THROWS(u5.operator!=(u12));
    CHECK_THROWS(u22.operator!=(u1));
    CHECK_THROWS(u19.operator!=(u18));
}

TEST_CASE("Less equal function")
{
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
    NumberWithUnits u16{30, "min"};
    NumberWithUnits u17{0.5, "hour"};
    NumberWithUnits u18{60, "hour"};

    CHECK_LE(u1, u1); //same type
    CHECK_LE(u5, u6);
    CHECK_LE(u6, u5);
    CHECK_LE(u1, u2);
    CHECK_LE(u3, u4);
    CHECK_LE(u7, u8);
    CHECK_LE(u9, u10);
    CHECK_LE(u11, u12);
    CHECK_LE(u13, u14);
    CHECK_LE(u17, u18);
    CHECK_LE(u16, u17); //diff type
    CHECK_LE(u16, u18);
    CHECK_LE(u8, u9);
}

TEST_CASE("Less equal function unconnected type")
{
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u5{2, "km"};
    NumberWithUnits u11{1.5, "ton"};
    NumberWithUnits u12{2, "ton"};
    NumberWithUnits u18{60, "hour"};
    NumberWithUnits u19{3.33, "ILS"}; //1 dolar
    NumberWithUnits u22{6, "USD"};

    CHECK_THROWS(u11.operator<=(u4));
    CHECK_THROWS(u4.operator<=(u11));
    CHECK_THROWS(u12.operator<=(u5));
    CHECK_THROWS(u5.operator<=(u12));
    CHECK_THROWS(u22.operator<=(u1));
    CHECK_THROWS(u19.operator<=(u18));
}

TEST_CASE("Less than function")
{
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u2{1000, "cm"}; //10 meter
    NumberWithUnits u3{50, "m"};
    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u7{200, "g"};
    NumberWithUnits u8{1000, "g"}; //1 kg
    NumberWithUnits u9{500, "kg"};
    NumberWithUnits u10{1200, "kg"}; //1.2 ton
    NumberWithUnits u11{1.5, "ton"};
    NumberWithUnits u12{2, "ton"};
    NumberWithUnits u13{30, "sec"};
    NumberWithUnits u14{60, "sec"}; //1 min
    NumberWithUnits u16{30, "min"};
    NumberWithUnits u17{0.5, "hour"};
    NumberWithUnits u18{60, "hour"};

    CHECK_LT(u1, u2); //same type
    CHECK_LT(u3, u4);
    CHECK_LT(u7, u8);
    CHECK_LT(u9, u10);
    CHECK_LT(u11, u12);
    CHECK_LT(u13, u14);
    CHECK_LT(u17, u18);
    CHECK_LE(u16, u18); //diff type
    CHECK_LE(u1, u4);
}

TEST_CASE("Less than function unconnected type")
{
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u5{2, "km"};
    NumberWithUnits u11{1.5, "ton"};
    NumberWithUnits u12{2, "ton"};
    NumberWithUnits u18{60, "hour"};
    NumberWithUnits u19{3.33, "ILS"}; //1 dolar
    NumberWithUnits u22{6, "USD"};

    CHECK_THROWS(u11.operator<(u4));
    CHECK_THROWS(u4.operator<(u11));
    CHECK_THROWS(u12.operator<(u5));
    CHECK_THROWS(u5.operator<(u12));
    CHECK_THROWS(u22.operator<(u1));
    CHECK_THROWS(u19.operator<(u18));
}

TEST_CASE("greater equal function")
{
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
    NumberWithUnits u16{30, "min"};
    NumberWithUnits u17{0.5, "hour"};
    NumberWithUnits u18{60, "hour"};

    CHECK_GE(u9, u9); //same type
    CHECK_GE(u1, u1);
    CHECK_GE(u5, u6);
    CHECK_GE(u6, u5);
    CHECK_GE(u2, u1);
    CHECK_GE(u4, u3);
    CHECK_GE(u8, u7);
    CHECK_GE(u10, u9);
    CHECK_GE(u12, u11);
    CHECK_GE(u14, u13);
    CHECK_GE(u18, u17);
    CHECK_GE(u18, u16); //diff type
    CHECK_GE(u4, u1);
}

TEST_CASE("greater  equal function unconnected type")
{
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u5{2, "km"};
    NumberWithUnits u11{1.5, "ton"};
    NumberWithUnits u12{2, "ton"};
    NumberWithUnits u18{60, "hour"};
    NumberWithUnits u19{3.33, "ILS"}; //1 dolar
    NumberWithUnits u22{6, "USD"};

    CHECK_THROWS(u11.operator>=(u4));
    CHECK_THROWS(u4.operator>=(u11));
    CHECK_THROWS(u12.operator>=(u5));
    CHECK_THROWS(u5.operator>=(u12));
    CHECK_THROWS(u22.operator>=(u1));
    CHECK_THROWS(u19.operator>=(u18));
}

TEST_CASE("greater than function")
{
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u2{1000, "cm"}; //10 meter
    NumberWithUnits u3{50, "m"};
    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u7{200, "g"};
    NumberWithUnits u8{1000, "g"}; //1 kg
    NumberWithUnits u9{500, "kg"};
    NumberWithUnits u10{1200, "kg"}; //1.2 ton
    NumberWithUnits u11{1.5, "ton"};
    NumberWithUnits u12{2, "ton"};
    NumberWithUnits u13{30, "sec"};
    NumberWithUnits u14{60, "sec"}; //1 min
    NumberWithUnits u16{30, "min"};
    NumberWithUnits u17{0.5, "hour"};
    NumberWithUnits u18{60, "hour"};

    CHECK_GT(u2, u1); //same type
    CHECK_GT(u4, u3);
    CHECK_GT(u8, u7);
    CHECK_GT(u10, u9);
    CHECK_GT(u12, u11);
    CHECK_GT(u14, u13);
    CHECK_GT(u18, u17);
    CHECK_GE(u18, u16); //diff type
    CHECK_GE(u4, u1);
}

TEST_CASE("greater than function unconnected type")
{
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u5{2, "km"};
    NumberWithUnits u11{1.5, "ton"};
    NumberWithUnits u12{2, "ton"};
    NumberWithUnits u18{60, "hour"};
    NumberWithUnits u19{3.33, "ILS"}; //1 dolar
    NumberWithUnits u22{6, "USD"};

    CHECK_THROWS(u11.operator>(u4));
    CHECK_THROWS(u4.operator>(u11));
    CHECK_THROWS(u12.operator>(u5));
    CHECK_THROWS(u5.operator>(u12));
    CHECK_THROWS(u22.operator>(u1));
    CHECK_THROWS(u19.operator>(u18));
}

TEST_CASE("plus function same type")
{
    //create NumberWithUnits
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u2{1000, "cm"}; //10 meter
    NumberWithUnits u5{2, "km"};
    NumberWithUnits u6{2, "km"};
    NumberWithUnits u13{30, "sec"};
    NumberWithUnits u14{60, "sec"}; //1 min
    NumberWithUnits u15{30, "min"};
    NumberWithUnits u16{30, "min"};
    NumberWithUnits u17{0.5, "hour"};
    NumberWithUnits u18{60, "hour"};

    CHECK_EQ(u1 + u1, u2);
    CHECK_EQ(u5 + u6, NumberWithUnits(4, "km"));
    CHECK_EQ(u6 + u5, NumberWithUnits(4, "km"));
    CHECK_EQ(u15 + u16, NumberWithUnits(60, "min"));
    CHECK_EQ(u16 + u15, NumberWithUnits(60, "min"));
    CHECK_EQ(u13 + u14, NumberWithUnits(90, "sec"));
    CHECK_EQ(u17 + u18, NumberWithUnits(60.5, "hour"));
}

TEST_CASE("plus function connect type")
{
    //create NumberWithUnits
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u2{1000, "cm"}; //10 meter
    NumberWithUnits u15{30, "min"};
    NumberWithUnits u16{30, "min"};
    NumberWithUnits u19{3.33, "ILS"}; //1 dolar
    NumberWithUnits u21{2, "USD"};

    CHECK_EQ(u1 + u1, u2);
    CHECK_EQ(u15 + u16, NumberWithUnits(1, "hour"));
    CHECK_EQ(u16 + u15, NumberWithUnits(1, "hour"));
    CHECK_EQ(u19 + u21, NumberWithUnits(3, "USD"));
    CHECK_EQ(u2 + u1 + u1, NumberWithUnits(2000, "cm"));
}

TEST_CASE("plus function unconnected type")
{
    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u11{1.5, "ton"};

    CHECK_THROWS(u11 + u4); //diff type
    CHECK_THROWS(u4 + u11);
}

TEST_CASE("plus equal function same type")
{
    NumberWithUnits temp_min_p(30, "min");
    temp_min_p += NumberWithUnits(30, "min");
    CHECK_EQ(temp_min_p, NumberWithUnits(60, "min"));

    NumberWithUnits temp_km_p(3, "km");
    temp_km_p += NumberWithUnits(3, "km");
    CHECK_EQ(temp_km_p, NumberWithUnits(6, "km"));
}

TEST_CASE("plus equal function connect type")
{
    NumberWithUnits temp_min_p(30, "min");
    temp_min_p += NumberWithUnits(1, "hour");
    CHECK_EQ(temp_min_p, NumberWithUnits(90, "min"));

    NumberWithUnits temp_hour_p(1, "hour");
    temp_hour_p += NumberWithUnits(30, "min");
    CHECK_EQ(temp_hour_p, NumberWithUnits(1.5, "hour"));

    NumberWithUnits temp_USD_p(3, "USD");
    temp_USD_p += NumberWithUnits(3.33, "ILS");
    CHECK_EQ(temp_USD_p, NumberWithUnits(4, "USD"));

    NumberWithUnits temp_ILS_p(3.33, "ILS");
    temp_ILS_p += NumberWithUnits(1, "USD");
    CHECK_EQ(temp_ILS_p, NumberWithUnits(6.66, "ILS"));
}

TEST_CASE("plus equal function unconnected type")
{

    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u11{1.5, "ton"};

    CHECK_THROWS(u11 += u4); //unconnected type
    CHECK_THROWS(u4 += u11);
}

TEST_CASE("minus function same type")
{
    //create NumberWithUnits
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u2{1000, "cm"}; //10 meter
    NumberWithUnits u5{2, "km"};
    NumberWithUnits u6{2, "km"};
    NumberWithUnits u13{30, "sec"};
    NumberWithUnits u14{60, "sec"}; //1 min
    NumberWithUnits u15{30, "min"};
    NumberWithUnits u16{30, "min"};
    NumberWithUnits u17{0.5, "hour"};
    NumberWithUnits u18{60, "hour"};

    CHECK_EQ(u1 - u2, NumberWithUnits(-500, "cm"));
    CHECK_EQ(u15 - u16, NumberWithUnits(0, "min"));
    CHECK_EQ(u16 - u15, NumberWithUnits(0, "min"));
    CHECK_EQ(NumberWithUnits(4, "km") - u5, u6);
    CHECK_EQ(NumberWithUnits(4, "km") - u6, u5);
    CHECK_EQ(NumberWithUnits(60, "min") - u15, u16);
    CHECK_EQ(NumberWithUnits(60, "min") - u16, u15);
    CHECK_EQ(NumberWithUnits(90, "sec") - u13, u14);
    CHECK_EQ(NumberWithUnits(60.5, "hour") - u17, u18);
}

TEST_CASE("minus function connect type")
{
    //create NumberWithUnits
    NumberWithUnits u1{500, "cm"};
    NumberWithUnits u2{1000, "cm"}; //10 meter
    NumberWithUnits u15{30, "min"};
    NumberWithUnits u16{30, "min"};
    NumberWithUnits u19{3.33, "ILS"}; //1 dolar
    NumberWithUnits u21{2, "USD"};

    CHECK_EQ(u15 - u16, NumberWithUnits(0, "hour"));
    CHECK_EQ(u16 - u15, NumberWithUnits(0, "hour"));
    CHECK_EQ(u21 - u19, NumberWithUnits(1, "USD"));
    CHECK_EQ(u2 - u1 - u1, NumberWithUnits(0, "cm"));
    CHECK_EQ(u2 - u1 - u1, NumberWithUnits(0, "m"));
}

TEST_CASE("minus function unconnected type")
{
    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u11{1.5, "ton"};

    CHECK_THROWS(u11 - u4); //unconnected type
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

    NumberWithUnits temp_USD_m(3, "USD");
    temp_USD_m -= NumberWithUnits(3.33, "ILS");
    CHECK_EQ(temp_USD_m, NumberWithUnits(2, "USD"));

    NumberWithUnits temp_ILS_m(6.66, "ILS");
    temp_ILS_m -= NumberWithUnits(1, "USD");
    CHECK_EQ(temp_ILS_m, NumberWithUnits(3.33, "ILS"));
}

TEST_CASE("minus equal function unconnected type")
{
    NumberWithUnits u4{5000, "m"}; //5 km
    NumberWithUnits u11{1.5, "ton"};

    CHECK_THROWS(u11 -= u4); //unconnected type
    CHECK_THROWS(u4 -= u11);
}

TEST_CASE("++ 'pre' function")
{
    NumberWithUnits pp_pre(1, "km");
    ++pp_pre;
    CHECK_EQ(pp_pre, NumberWithUnits(2, "km"));
    CHECK_EQ((++pp_pre), NumberWithUnits(3, "km"));
    CHECK_EQ((++++++pp_pre), NumberWithUnits(6, "km"));
    CHECK_EQ((++--pp_pre), NumberWithUnits(6, "km"));
}

TEST_CASE("++ 'post' function")
{
    NumberWithUnits pp_post(1, "USD");
    pp_post++;
    CHECK_EQ(pp_post, NumberWithUnits(2, "USD"));
    CHECK_EQ((pp_post++), NumberWithUnits(2, "USD"));
    CHECK_EQ(pp_post, NumberWithUnits(3, "USD"));
}

TEST_CASE("-- 'pre' function")
{
    NumberWithUnits pp_pre(5, "ton");
    --pp_pre;
    CHECK_EQ(pp_pre, NumberWithUnits(4, "ton"));
    CHECK_EQ((--pp_pre), NumberWithUnits(3, "ton"));
    CHECK_EQ((--++pp_pre), NumberWithUnits(3, "ton"));
}

TEST_CASE("-- 'post' function")
{
    NumberWithUnits pp_post(9, "sec");
    pp_post--;
    CHECK_EQ(pp_post, NumberWithUnits(8, "sec"));
    CHECK_EQ((pp_post--), NumberWithUnits(8, "sec"));
    CHECK_EQ(pp_post, NumberWithUnits(7, "sec"));
}

TEST_CASE("++ 'post' function")
{
    NumberWithUnits pp_post(1, "USD");
    pp_post++;
    CHECK_EQ(pp_post, NumberWithUnits(2, "USD"));
    CHECK_EQ((pp_post++), NumberWithUnits(2, "USD"));
    CHECK_EQ(pp_post, NumberWithUnits(3, "USD"));
}

TEST_CASE("+ 'unary' function")
{
    NumberWithUnits p_u(7, "ILS");
    CHECK_EQ((+p_u), NumberWithUnits(7, "ILS"));

    NumberWithUnits p_u1(-7, "ILS");
    CHECK_EQ((+p_u1), NumberWithUnits(-7, "ILS"));
}

TEST_CASE("- 'unary' function")
{
    NumberWithUnits p_u(7, "ILS");
    CHECK_EQ((-p_u), NumberWithUnits(-7, "ILS"));

    NumberWithUnits p_u1(-7, "ILS");
    CHECK_EQ((-p_u1), NumberWithUnits(7, "ILS"));
}

TEST_CASE("* 'from left' function")
{
    NumberWithUnits mul(7, "ILS");
    CHECK_EQ((2 * mul), NumberWithUnits(14, "ILS"));

    NumberWithUnits mul1(-7, "g");
    CHECK_EQ((2 * mul1), NumberWithUnits(-14, "g"));
    CHECK_EQ((2 * mul1 * 2), NumberWithUnits(-28, "g"));
}

TEST_CASE("* 'from right' function")
{
    NumberWithUnits mul3(7, "ILS");
    CHECK_EQ((mul3 * 2), NumberWithUnits(14, "ILS"));

    NumberWithUnits mul4(-7, "g");
    CHECK_EQ((mul4 * 2), NumberWithUnits(-14, "g"));
    CHECK_EQ((2 * mul4 * 2), NumberWithUnits(-28, "g"));
}

TEST_CASE("<< function")
{
    NumberWithUnits temp_output(7, "ILS");
    ostringstream oss;
    oss << temp_output;
    CHECK_EQ(oss.str(), "7[ILS]");

    NumberWithUnits temp_output1(-9, "km");
    ostringstream oss1;
    oss1 << temp_output1;
    CHECK_EQ(oss1.str(), "-9[km]");
}

TEST_CASE(">> function")
{
    NumberWithUnits temp_input(7, "ILS");

    istringstream iss("20 [sec]");
    iss >> temp_input;
    CHECK_EQ(temp_input, NumberWithUnits(20, "sec"));

    istringstream iss1(" 5 [USD]");
    iss1 >> temp_input;
    CHECK_EQ(temp_input, NumberWithUnits(5, "USD"));

    istringstream iss2("6[ g ]");
    iss2 >> temp_input;
    CHECK_EQ(temp_input, NumberWithUnits(6, "g"));

    istringstream iss3(" 900 [ton] ");
    iss3 >> temp_input;
    CHECK_EQ(temp_input, NumberWithUnits(900, "ton"));

    istringstream iss4(" -16 [m] ");
    iss4 >> temp_input;
    CHECK_EQ(temp_input, NumberWithUnits(-16, "m"));

    istringstream iss5(" -7 [hour] ");
    iss5 >> temp_input;
    CHECK_EQ(temp_input, NumberWithUnits(-7, "hour"));
}

TEST_CASE("insert illigel char")
{
    CHECK_THROWS(NumberWithUnits temp_output(7, "IlS"));
    CHECK_THROWS(NumberWithUnits temp_output(7, "IlS"));
    CHECK_THROWS(NumberWithUnits temp_output(17, "ils"));
    CHECK_THROWS(NumberWithUnits temp_output(27, "USd"));
    CHECK_THROWS(NumberWithUnits temp_output(37, "Us2"));
    CHECK_THROWS(NumberWithUnits temp_output(47, "Km"));
    CHECK_THROWS(NumberWithUnits temp_output(57, "KM"));
    CHECK_THROWS(NumberWithUnits temp_output(67, "kM"));
    CHECK_THROWS(NumberWithUnits temp_output(77, "roei"));
}

TEST_CASE("Mathematical rules order of operations")
{
    CHECK_EQ(2 * NumberWithUnits(-7, "hour") + NumberWithUnits(7, "hour"), NumberWithUnits(-7, "hour"));
    NumberWithUnits temp1(1, "USD");
    CHECK_EQ(2 * ++temp1 + NumberWithUnits(3.33, "ILS") * 3, NumberWithUnits(7, "USD"));
    NumberWithUnits temp2(1, "USD");
    CHECK_EQ(2 * temp2++ + NumberWithUnits(3.33, "ILS") * 3, NumberWithUnits(5, "USD"));
}