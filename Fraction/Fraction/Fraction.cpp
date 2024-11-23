﻿#include "Fraction.h" 
#include <stdexcept>
#include <numeric>

Fraction::Fraction(int numerator, int denominator) {
    setNumerator(numerator);
    setDenominator(denominator);
}

int Fraction::getNumerator() const { return this->numerator; }
int Fraction::getDenominator() const { return this->denominator; }

void Fraction::setNumerator(const int numerator) {
    this->numerator = numerator;
}

void Fraction::setDenominator(const int denominator) {
    if (denominator == 0) {
        std::cout << "ERROR: denominator can't be 0";
    }
    this->denominator = denominator;
}

void Fraction::reduction() {
    if (denominator == 0) {
        std::cout << "\nERROR: denominator is 0; changing to 1\n";
        denominator = 1;
    }
    Fraction c;
    int gcd = this->gcd();
    this->setDenominator(denominator / gcd);
    this->setNumerator(numerator / gcd);

    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

Fraction Fraction::operator+(const Fraction b) const {
    Fraction c;
    c.setDenominator(this->denominator * b.denominator);
    c.setNumerator(this->numerator * b.denominator + this->denominator * b.numerator);
    c.reduction();
    return c;
}

Fraction Fraction::operator-(const Fraction b) const {
    Fraction c;
    c.setDenominator(this->denominator * b.denominator);
    c.setNumerator(this->numerator * b.denominator - this->denominator * b.numerator);
    c.reduction();
    return c;
}

Fraction Fraction::operator*(const Fraction b) const {
    Fraction c;
    c.setDenominator(this->denominator * b.denominator);
    c.setNumerator(this->numerator * b.numerator);
    c.reduction();
    return c;
}

Fraction Fraction::operator/(const Fraction b) const {
    Fraction c;
    c.setDenominator(this->denominator * b.numerator);
    c.setNumerator(this->numerator * b.denominator);
    c.reduction();
    return c;
}

bool Fraction::operator<(const Fraction b) const {
    return (this->numerator * b.denominator < this->denominator * b.numerator);
}

bool Fraction::operator>(const Fraction b) const {
    return (this->numerator * b.denominator > this->denominator * b.numerator);
}

bool Fraction::operator==(const Fraction b) const {
    return (this->numerator * b.denominator == this->denominator * b.numerator);
}

bool Fraction::operator!=(const Fraction b) const {
    return (this->numerator * b.denominator != this->denominator * b.numerator);
}

void Fraction::input() {
    std::cin >> numerator;
    std::cout << '/' << "\n";
    std::cin >> denominator;
    while (denominator == 0) {
        std::cerr << "\nERROR: denominator is 0; changing to 1\n";
        denominator = 1;
    }
}

void Fraction::output() const {
    std::cout << this->numerator << '/' << this->denominator << "\n";
}

int Fraction::gcd() const {
    int a = abs(this->numerator);
    int b = abs(this->denominator);
    if (this->numerator == 0 && this->denominator == 0) {
        std::cout << "ERROR: both numerator and denominator are 0";
    }
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a; // наибольший общий делитель
}

Fraction Fraction::fromDouble(double value, int precision) {
    if (precision <= 0) {
        std::cout << "ERROR: precision must be >0";
    }
    int numerator;
    if (value >= 0) {
        numerator = static_cast<int>(value * precision + 0.5);
    }
    else {
        numerator = static_cast<int>(value * precision - 0.5);
    }
    int denominator = precision;
    Fraction fraction(numerator, denominator);
    fraction.reduction();
    return fraction;
}

double Fraction::toDouble() const {
    return static_cast<double>(numerator) / denominator;
}