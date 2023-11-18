#pragma once

#include <iostream>
#include <sstream>
#include <istream>
#include <ostream>

class Rational {
public:
    Rational();
    Rational(int numerator, int denominator);

    int Numerator() const;
    int Denominator() const;

    friend Rational operator+(const Rational& a, const Rational& b);
    friend Rational operator*(const Rational& a, const Rational& b);
    friend Rational operator/(const Rational& a, const Rational& b);
    friend Rational operator-(const Rational& a, const Rational& b);
    friend bool operator==(const Rational& a, const Rational& b);
    friend std::ostream& operator<<(std::ostream& out, const Rational& a);
    friend std::istream& operator>>(std::istream& in, Rational& a);
private:
    int num, denom;
};
