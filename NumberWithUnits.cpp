#include "NumberWithUnits.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace ariel
{
    map<string, map<string, double>> NumberWithUnits::u;

    void NumberWithUnits::read_units(ifstream &file)
    {
        if (file)
        {
            string myText;
            while (getline(file, myText))
            {
                string dadName, equalOperator, sunName;
                double a, num;
                istringstream iss(myText);
                iss >> skipws >> a >> dadName >> equalOperator >> num >> sunName;
                //cout << dadName << " is " << num << sunName << endl;
                if (!u.count(dadName))
                {
                    u.insert({dadName, map<string, double>{}});
                }
                if (!u.count(sunName))
                {
                    u.insert({sunName, map<string, double>{}});
                }

                for (auto i : u.at(sunName))
                {
                    u.at(i.first).insert({dadName, 1 / (i.second * num)});
                    u.at(dadName).insert({i.first, (i.second * num)});
                }

                for (auto i : u.at(dadName))
                {
                    u.at(i.first).insert({sunName, (i.second * num)});
                    u.at(sunName).insert({i.first, 1 / (i.second * num)});
                }

                u.at(dadName).insert({sunName, num});
                u.at(sunName).insert({dadName, (1 / num)});
            }
        }
    }

    NumberWithUnits::NumberWithUnits(double n, std::string s)
    {

        num = n;
        name = s;
    }

    //compare function
    bool NumberWithUnits::operator==(const NumberWithUnits &n) const { return true; }
    bool NumberWithUnits::operator!=(const NumberWithUnits &n) const { return true; }
    bool NumberWithUnits::operator<=(const NumberWithUnits &n) const { return true; }
    bool NumberWithUnits::operator<(const NumberWithUnits &n) const { return true; }
    bool NumberWithUnits::operator>(const NumberWithUnits &n) const { return true; }
    bool NumberWithUnits::operator>=(const NumberWithUnits &n) const { return true; }

    //plus, minus function
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &n) { return *this; }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &n) { return *this; }

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
