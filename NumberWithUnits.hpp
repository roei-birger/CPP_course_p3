#pragma once //for once compiling

#include <fstream>
#include <vector>

namespace ariel
{
    class NumberWithUnits
    {
        struct unitNode
        {
            std::string nameOfUnit;
            std::string nameToComper;
            int numToComper;

            unitNode(std::string name, std::string comperName, int comperNum)
                : nameOfUnit(name), nameToComper(comperName), numToComper(comperNum)
            {
            }
        };

        std::vector<unitNode> v;

    public:

        void read_units(std::ifstream);

        NumberWithUnits(int, std::string);

        //compare function
        bool operator==(const NumberWithUnits &n) const;
        bool operator!=(const NumberWithUnits &n) const;
        bool operator<=(const NumberWithUnits &n) const;
        bool operator<(const NumberWithUnits &n) const;
        bool operator>(const NumberWithUnits &n) const;
        bool operator>=(const NumberWithUnits &n) const;

        //plus, minus function
        bool operator+=(const NumberWithUnits &n);
        bool operator-=(const NumberWithUnits &n);

        NumberWithUnits &operator++();         // prefix  - ++a
        const NumberWithUnits operator++(int); // postfix - a++

        NumberWithUnits &operator--();         // prefix  - --a
        const NumberWithUnits operator--(int); // postfix - a--

        //plus, minus function
        friend NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2);

        //unary function
        friend NumberWithUnits operator+(const NumberWithUnits &n1);
        friend NumberWithUnits operator-(const NumberWithUnits &n1);

        //mul with double num function
        friend NumberWithUnits operator*(const NumberWithUnits &n1, const double num);

        //input, output
        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &n);
        friend std::istream &operator>>(std::istream &is, NumberWithUnits &n);
    };

}