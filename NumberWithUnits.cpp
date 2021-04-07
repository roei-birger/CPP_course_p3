#include "NumberWithUnits.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace ariel
{
    void NumberWithUnits::read_units(ifstream &file)
    {
        if(file){}
    }

    NumberWithUnits::NumberWithUnits(double n, std::string s)
    {

        for (unsigned int i = 0; i < v.size(); i++)
        {
            if (v.at(i).nameOfUnit == s)
            {
                num = n;
                name = s;
                break;
            }
        }
        //throw invalid_argument("wrong input");
    }

    //compare function
    bool NumberWithUnits::operator==(const NumberWithUnits &n) const { return true; }
    bool NumberWithUnits::operator!=(const NumberWithUnits &n) const { return true; }
    bool NumberWithUnits::operator<=(const NumberWithUnits &n) const { return true; }
    bool NumberWithUnits::operator<(const NumberWithUnits &n) const { return true; }
    bool NumberWithUnits::operator>(const NumberWithUnits &n) const { return true; }
    bool NumberWithUnits::operator>=(const NumberWithUnits &n) const { return true; }

    //plus, minus function
    bool NumberWithUnits::operator+=(const NumberWithUnits &n) { return true; }
    bool NumberWithUnits::operator-=(const NumberWithUnits &n) { return true; }

    NumberWithUnits &NumberWithUnits::operator++() { return *this; }                              // prefix  - ++a
    const NumberWithUnits NumberWithUnits::operator++(int) { return NumberWithUnits(num, name); } // postfix - a++

    NumberWithUnits &NumberWithUnits::operator--() { return *this; }                              // prefix  - --a
    const NumberWithUnits NumberWithUnits::operator--(int) { return NumberWithUnits(num, name); } // postfix - a--

    //plus, minus function
    NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2) { return NumberWithUnits(1, "name"); }
    NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2) { return NumberWithUnits(1, "name"); }

    //unary function
    NumberWithUnits operator+(const NumberWithUnits &n1) { return NumberWithUnits(1, "name"); }
    NumberWithUnits operator-(const NumberWithUnits &n1) { return NumberWithUnits(1, "name"); }

    //mul with double num function
    NumberWithUnits operator*(const NumberWithUnits &n1, const double num) { return NumberWithUnits(1, "name"); }
    NumberWithUnits operator*(const double num, const NumberWithUnits &n1) { return NumberWithUnits(1, "name"); }

    //input, output
    std::ostream &operator<<(std::ostream &os, const NumberWithUnits &n) { return os << n.num << "[" << n.name << "]"; }
    std::istream &operator>>(std::istream &is, NumberWithUnits &n) { return is; }
};
