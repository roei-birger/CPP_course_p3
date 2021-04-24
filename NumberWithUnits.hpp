#pragma once //for once compiling

#include <fstream>
#include <sstream>
#include <map>

namespace ariel
{
    class NumberWithUnits
    {
        double num;
        std::string name;

    public:
        static void read_units(std::ifstream &);
        static std::map<std::string, std::map<std::string, double>> u;
        NumberWithUnits(double, const std::string&);

        //compare function
        bool operator==(const NumberWithUnits &n) const;
        bool operator!=(const NumberWithUnits &n) const;
        bool operator<=(const NumberWithUnits &n) const;
        bool operator<(const NumberWithUnits &n) const;
        bool operator>(const NumberWithUnits &n) const;
        bool operator>=(const NumberWithUnits &n) const;

        //plus, minus function
        NumberWithUnits &operator+=(const NumberWithUnits &n);
        NumberWithUnits &operator-=(const NumberWithUnits &n);

        NumberWithUnits &operator++();         // prefix  - ++a
        NumberWithUnits operator++(int); // postfix - a++

        NumberWithUnits &operator--();         // prefix  - --a
        NumberWithUnits operator--(int); // postfix - a--

        //plus, minus function
        friend NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2);

        //unary function
        friend NumberWithUnits operator+(const NumberWithUnits &n1);
        friend NumberWithUnits operator-(const NumberWithUnits &n1);

        //mul with double num function
        friend NumberWithUnits operator*(const NumberWithUnits &n1, const double num);
        friend NumberWithUnits operator*(const double num, const NumberWithUnits &n1);

        //input, output
        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &n);
        friend std::istream &operator>>(std::istream &is, NumberWithUnits &n);
    };

}