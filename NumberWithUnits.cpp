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
            file.close();
        }
        else
        {
            throw invalid_argument("File not found");
        }
    }

    bool isConnect(const string one, const string two)
    {
        return NumberWithUnits::u.at(one).count(two);
    }

    NumberWithUnits::NumberWithUnits(const double n, const string s) : num(n), name(s)
    {

        // cout << s <<" - " <<(u.count(s))<<endl;
        

        // if (!u.count(s))
        // {
        //     cout << s << endl;
        //     throw runtime_error("Unknown _unit");
        // }
        // else
        // {
        //     num = n;
        //     name = s;
        // }
    }

    //compare function
    bool NumberWithUnits::operator==(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {
            if (num != n.num)
            {
                return false;
            }
            return true;
        }
        else if (!isConnect(name, n.name))
        {
            throw invalid_argument("not connect units");
        }
        else
        {
            double tempAmount = NumberWithUnits::u.at(name).at(n.name);
            return (tempAmount * num == n.num);
        }
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {
            if (num != n.num)
            {
                return true;
            }
            return false;
        }
        else if (!isConnect(name, n.name))
        {
            throw invalid_argument("not connect units");
        }
        else
        {
            double tempAmount = NumberWithUnits::u.at(name).at(n.name);
            return !(tempAmount * num == n.num);
        }
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {
            if (num <= n.num)
            {
                return true;
            }
            return false;
        }
        else if (!isConnect(name, n.name))
        {
            throw invalid_argument("not connect units");
        }
        else
        {
            double tempAmount = NumberWithUnits::u.at(name).at(n.name);
            return (tempAmount * num <= n.num);
        }
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {
            if (num < n.num)
            {
                return true;
            }
            return false;
        }
        else if (!isConnect(name, n.name))
        {
            throw invalid_argument("not connect units");
        }
        else
        {
            double tempAmount = NumberWithUnits::u.at(name).at(n.name);
            return (tempAmount * num < n.num);
        }
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {
            if (num > n.num)
            {
                return true;
            }
            return false;
        }
        else if (!isConnect(name, n.name))
        {
            throw invalid_argument("not connect units");
        }
        else
        {
            double tempAmount = NumberWithUnits::u.at(name).at(n.name);
            return (tempAmount * num > n.num);
        }
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &n) const
    {
        if (name == n.name)
        {
            if (num >= n.num)
            {
                return true;
            }
            return false;
        }
        else if (!isConnect(name, n.name))
        {
            throw invalid_argument("not connect units");
        }
        else
        {
            double tempAmount = NumberWithUnits::u.at(name).at(n.name);
            return (tempAmount * num >= n.num);
        }
    }

    //plus, minus function
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &n)
    {

        if (name == n.name)
        {
            num += n.num;
            return *this;
        }
        else if (!isConnect(name, n.name))
        {
            throw invalid_argument("not connect units");
        }
        else
        {
            double tempAmount = NumberWithUnits::u.at(n.name).at(name);
            num += (n.num * tempAmount);
            return *this;
        }
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &n)
    {
        if (name == n.name)
        {
            num -= n.num;
            return *this;
        }
        else if (!isConnect(name, n.name))
        {
            throw invalid_argument("not connect units");
        }
        else
        {
            double tempAmount = NumberWithUnits::u.at(n.name).at(name);
            num -= (n.num * tempAmount);
            return *this;
        }
    }

    NumberWithUnits &NumberWithUnits::operator++() // prefix  - ++a
    {
        num++;
        return *this;
    }
    const NumberWithUnits NumberWithUnits::operator++(int) // postfix - a++
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
    const NumberWithUnits NumberWithUnits::operator--(int) // postfix - a--
    {
        NumberWithUnits copy = *this;
        num--;
        return copy;
    }

    //plus, minus function
    NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double tempNum;

        if (n1.name == n2.name)
        {
            tempNum = n1.num + n2.num;
            return NumberWithUnits(tempNum, n1.name);
        }
        else if (!isConnect(n1.name, n2.name))
        {
            throw invalid_argument("not connect units");
        }
        else
        {
            double tempAmount = NumberWithUnits::u.at(n2.name).at(n1.name);
            tempNum = n1.num + (n2.num * tempAmount);
            return NumberWithUnits(tempNum, n1.name);
        }
    }
    NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double tempNum;

        if (n1.name == n2.name)
        {
            tempNum = n1.num - n2.num;
            return NumberWithUnits(tempNum, n1.name);
        }
        else if (!isConnect(n1.name, n2.name))
        {
            throw invalid_argument("not connect units");
        }
        else
        {
            double tempAmount = NumberWithUnits::u.at(n2.name).at(n1.name);
            tempNum = n1.num - (n2.num * tempAmount);
            return NumberWithUnits(tempNum, n1.name);
        }
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
        double insertValue;
        string insertName;

        char openSign, closeSign;

        is >> skipws >> insertValue >> openSign >> insertName >> closeSign;
        if (closeSign != ']')
        {
            insertName = insertName.substr(0, insertName.length() - 1);
        }

        if (!NumberWithUnits::u.count(insertName))
        {
            throw invalid_argument("Incorrect input");
        }

        n.num = insertValue;
        n.name = insertName;
        return is;
    }
};