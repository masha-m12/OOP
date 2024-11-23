#pragma once
#include <iostream>
#include <cmath>
#include <numeric>
#include <stdexcept>
 
class Fraction
{
public:
    Fraction(int numerator = 0, int denominator = 1);

    int getNumerator() const;
    int getDenominator() const;

    void setNumerator(int numerator);
    void setDenominator(int denominator);

    Fraction operator +(const Fraction b) const;
    Fraction operator -(const Fraction b) const;
    Fraction operator *(const Fraction b) const;
    Fraction operator /(const Fraction b) const;

    bool operator <(const Fraction b) const;
    bool operator >(const Fraction b) const;
    bool operator ==(const Fraction b) const;
    bool operator !=(const Fraction b) const;

    void reduction();
    void input();
    void output() const;

    static Fraction fromDouble(double value, int precision);
    double toDouble() const;

private:
    int numerator;
    int denominator;
    int gcd() const;
};