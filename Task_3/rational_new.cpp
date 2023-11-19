#include "rational.h"

unsigned int greatest_common_divisor(unsigned int a, unsigned int b);
unsigned int least_common_multiple(unsigned int a, unsigned int b);
void reduction(int *a, int *b);

Rational::Rational() : num(0), denom(1) {}

/*
Rational::Rational()
{
    this->num = 1;
    this->denom = 1;
}
*/

Rational::Rational(int numerator, int denominator)
{
    if (denominator == 0) {
        std::stringstream ss;
        ss << "Argument must not be zero";
        throw std::invalid_argument(ss.str());
    }

    num = numerator;
    denom = denominator;
    if (denom < 0) {
        num = -num;
        denom = -denom;
    }
}

int Rational::Numerator() const
{
    return num;
}

int Rational::Denominator() const
{
    return denom;
}


Rational operator+(const Rational& a, const Rational& b)
{
    Rational temp;
    if (a.Denominator() == b.Denominator())
    {
        temp.denom = a.Denominator();
        temp.num = a.Numerator() + b.Numerator();
        reduction(&temp.num, &temp.denom);
        return temp;
    }
    else
    {
        temp.denom = least_common_multiple(a.Denominator(), b.Denominator());
        temp.num = (temp.denom / a.Denominator()) * a.Numerator() + (temp.denom / b.Denominator()) * b.Numerator();
        reduction(&temp.num, &temp.denom);
        return temp;
    }
}

Rational operator-(const Rational& a, const Rational& b)
{
    Rational temp;
    if (a.Denominator() == b.Denominator())
    {
        temp.denom = a.Denominator();
        temp.num = a.Numerator() - b.Numerator();
        reduction(&temp.num, &temp.denom);
        return temp;
    }
    else
    {
        temp.denom = least_common_multiple(a.Denominator(), b.Denominator());
        temp.num = (temp.denom / a.Denominator()) * a.Numerator() - (temp.denom / b.Denominator()) * b.Numerator();
        reduction(&temp.num, &temp.denom);
        return temp;
    }
}

Rational operator*(const Rational& a, const Rational& b)
{
    Rational temp;
    temp.denom = a.Denominator() * b.Denominator();
    temp.num = a.Numerator() * b.Numerator();
    reduction(&temp.num, &temp.denom);
    return temp;
}

Rational operator/(const Rational& a, const Rational& b)
{
    if (b.Numerator() == 0) {
        std::stringstream ss;
        ss << "Division by zero";
        throw std::domain_error(ss.str());
    }
    Rational temp;
    int swap_num = 0, swap_denom;
    swap_denom = b.Numerator();
    swap_num = b.Denominator();

    temp.denom = a.Denominator() * swap_denom;
    temp.num = a.Numerator() * swap_num;
    reduction(&temp.num, &temp.denom);
    return temp;
}

std::istream& operator>>(std::istream& in, Rational& a)
{
    std::string temp = {}, sep = {}, sep2 = {};
    bool flag = false, neg = false;
    in >> temp;
    for (int i = 0; i < temp.length(); i++) 
    {
        if (temp[0] == '-' && neg == false)
        {
            neg = true;
            continue;
        }
        if (temp[i] == '/' && flag == true)
        {
            std::stringstream ss;
            ss << "Invalid data format!";
            throw std::invalid_argument(ss.str());
            break;
        }
        if (temp[i] == '/') flag = true;
        if (!isdigit(temp[i]) && temp[i] != '/')
        {
            std::stringstream ss;
            ss << "Invalid data format!";
            throw std::invalid_argument(ss.str());
            break;
        }
        if (flag == false) sep += temp[i]; 
        else if (temp[i] != '/') sep2 += temp[i];
    }
    if (neg == true)
        a.num = atoi(sep.c_str()) * (-1);
    else 
        a.num = atoi(sep.c_str());
    a.denom = atoi(sep2.c_str());
    sep.erase();
    sep2.erase();
    temp.erase();
    if (a.Denominator() == 0) 
    {
        std::stringstream ss;
        ss << "Argument must not be zero";
        throw std::invalid_argument(ss.str());
    }
    //std::cout << "IS NUM -> " << a.num << "; IS DENOM -> " << a.denom << '\n';
    return in;
}

std::ostream& operator<<(std::ostream& out, const Rational& a)
{
    std::string temp = {};
    temp += " RESULT -> ";
    temp += std::to_string(a.Numerator());
    temp += '/';
    temp += std::to_string(a.Denominator());
    temp += ' ';
    //std::cout << temp << '\n';
    out << temp;
    return out;
}

bool operator==(const Rational& a, const Rational& b)
{
    Rational temp1, temp2;
    temp1.denom = a.Denominator();
    temp1.num = a.Numerator();
    temp2.denom = b.Denominator();
    temp2.num = b.Numerator();
    reduction(&temp1.num, &temp1.denom);
    reduction(&temp2.num, &temp2.denom);
    return (temp1.num == temp2.num && temp1.denom == temp2.denom) ? true : false;
}

unsigned int greatest_common_divisor(unsigned int a, unsigned int b) {
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return greatest_common_divisor(a % b, b);
    return greatest_common_divisor(a, b % a);
}

unsigned int least_common_multiple(unsigned int a, unsigned int b) {
    return (a * b) / greatest_common_divisor(a, b);
}

void reduction(int* a, int* b)
{
    int conv = greatest_common_divisor(*a<0 ? *a*(-1) : *a, *b);
    *a /= conv;
    *b /= conv;
}