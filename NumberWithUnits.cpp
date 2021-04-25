#include "NumberWithUnits.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#define EPS 0.001
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
                    u.at(i.first).insert({dadName, 1 / (num * i.second)});
                    u.at(dadName).insert({i.first, i.second * num});
                }

                for (auto i : u.at(dadName))
                {
                    u.at(i.first).insert({sunName, num / i.second});
                    u.at(sunName).insert({i.first, i.second / num});
                }

                u.at(dadName).insert({sunName, num});
                u.at(sunName).insert({dadName, (1 / num)});
            }
            file.close();
        }
        else
        {
            throw invalid_argument("File not found");
        }
    }

    bool isConnect(const string &one, const string &two)
    {
        return NumberWithUnits::u.at(one).count(two) == 1;
    }

    NumberWithUnits::NumberWithUnits(const double n, const string &s) : num(n), name(s)
    {
        if (u.count(s) == 0)
        {
            throw runtime_error("Unknown _unit");
        }
        
    }

    //compare function
    bool NumberWithUnits::operator==(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {
            return (abs(num - n.num) < EPS);
        }
         if (isConnect(name, n.name))
        {
            double tempAmount = u.at(n.name).at(name);
            return (abs(num - (tempAmount * n.num)) < EPS);
        }
        throw invalid_argument("Units do not match - [" + n.name + "] cannot be converted to [" + name + "]");
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {

            return num != n.num;
        }
        if (isConnect(name, n.name))
        {
            double tempAmount = u.at(n.name).at(name);
            return !(abs(num - (tempAmount * n.num)) < EPS);
        }
        throw invalid_argument("Units do not match - [" + n.name + "] cannot be converted to [" + name + "]");
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {
            return num <= n.num;
        }
        if (isConnect(name, n.name))
        {
            double tempAmount = NumberWithUnits::u.at(name).at(n.name);
            return (tempAmount * num <= n.num);
        }
        throw invalid_argument("Units do not match - [" + n.name + "] cannot be converted to [" + name + "]");
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {
        
            return num < n.num;
        }
        if (isConnect(name, n.name))
        {
            double tempAmount = NumberWithUnits::u.at(name).at(n.name);
            return (tempAmount * num < n.num);
        }
        throw invalid_argument("Units do not match - [" + n.name + "] cannot be converted to [" + name + "]");
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {
            
            return num > n.num;
        }
        if (isConnect(name, n.name))
        {
            double tempAmount = NumberWithUnits::u.at(name).at(n.name);
            return (tempAmount * num > n.num);
        }
        throw invalid_argument("Units do not match - [" + n.name + "] cannot be converted to [" + name + "]");
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {
            
            return num >= n.num;
        }
        if (isConnect(name, n.name))
        {
            double tempAmount = NumberWithUnits::u.at(name).at(n.name);
            return (tempAmount * num >= n.num);
        }
        throw invalid_argument("Units do not match - [" + n.name + "] cannot be converted to [" + name + "]");
    }

    //plus, minus function
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &n)
    {

        if (name == n.name)
        {
            num += n.num;
            return *this;
        }
        if (isConnect(name, n.name))
        {
            double tempAmount = NumberWithUnits::u.at(n.name).at(name);
            num += (n.num * tempAmount);
            return *this;
        }
        throw invalid_argument("Units do not match - [" + n.name + "] cannot be converted to [" + name + "]");
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &n)
    {
        if (name == n.name)
        {
            num -= n.num;
            return *this;
        }
        if (isConnect(name, n.name))
        {
            double tempAmount = NumberWithUnits::u.at(n.name).at(name);
            num -= (n.num * tempAmount);
            return *this;
        }
        throw invalid_argument("Units do not match - [" + n.name + "] cannot be converted to [" + name + "]");
    }

    NumberWithUnits &NumberWithUnits::operator++() // prefix  - ++a
    {
        num++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int) // postfix - a++
    {
        NumberWithUnits copy = *this;
        num++;
        return copy;
    }

    NumberWithUnits &NumberWithUnits::operator--() // prefix  - --a
    {
        num--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int) // postfix - a--
    {
        NumberWithUnits copy = *this;
        num--;
        return copy;
    }

    //plus, minus function
    NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double tempNum = 0;

        if (n1.name == n2.name)
        {
            tempNum = n1.num + n2.num;
            return NumberWithUnits(tempNum, n1.name);
        }
        if (isConnect(n1.name, n2.name))
        {
            double tempAmount = NumberWithUnits::u.at(n2.name).at(n1.name);
            tempNum = n1.num + (n2.num * tempAmount);
            return NumberWithUnits(tempNum, n1.name);
        }
        throw invalid_argument("Units do not match - [" + n2.name + "] cannot be converted to [" + n1.name + "]");
    }

    NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double tempNum = 0;

        if (n1.name == n2.name)
        {
            tempNum = n1.num - n2.num;
            return NumberWithUnits(tempNum, n1.name);
        }
        if (isConnect(n1.name, n2.name))
        {
            double tempAmount = NumberWithUnits::u.at(n2.name).at(n1.name);
            tempNum = n1.num - (n2.num * tempAmount);
            return NumberWithUnits(tempNum, n1.name);
        }

        throw invalid_argument("Units do not match - [" + n2.name + "] cannot be converted to [" + n1.name + "]");
    }

    //unary function
    NumberWithUnits operator+(const NumberWithUnits &n1) { return NumberWithUnits(+n1.num, n1.name); }
    NumberWithUnits operator-(const NumberWithUnits &n1) { return NumberWithUnits(-n1.num, n1.name); }

    //mul with double num function
    NumberWithUnits operator*(const NumberWithUnits &n1, const double num) { return NumberWithUnits(num * n1.num, n1.name); }
    NumberWithUnits operator*(const double num, const NumberWithUnits &n1) { return NumberWithUnits(num * n1.num, n1.name); }

    //input, output
    std::ostream &operator<<(std::ostream &os, const NumberWithUnits &n) { return os << n.num << "[" << n.name << "]"; }
    std::istream &operator>>(std::istream &is, NumberWithUnits &n)
    {
        double insertValue = 0;
        string insertName;

        char openSign = '\0';
        char closeSign = '\0';

        is >> skipws >> insertValue >> openSign >> insertName;
        if (insertName.at(insertName.length() - 1) == ']')
        {
            insertName = insertName.substr(0, insertName.length() - 1);
        }
        else
        {
            is >> skipws >> closeSign;
        }

        if (NumberWithUnits::u.count(insertName) == 0)
        {
            throw invalid_argument("Incorrect input");
        }

        n.num = insertValue;
        n.name = insertName;
        return is;
    }
};