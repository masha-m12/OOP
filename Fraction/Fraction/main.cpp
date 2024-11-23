#include <iostream>
#include <iomanip>
#include <conio.h>
#include "Fraction.h"

int main()
{
    Fraction a;
    std::cout << "Enter fraction a: ";
    a.input();
    std::cout << "Fraction a: ";
    a.output();

    Fraction b;
    std::cout << "Enter fraction b: ";
    b.input();
    std::cout << "Fraction b: ";
    b.output();

    std::cout << "a + b = ";
    (a + b).output();

    std::cout << "a - b = ";
    (a - b).output();

    std::cout << "a * b = ";
    (a * b).output();

    std::cout << "a / b = ";
    (a / b).output();

    std::cout << "a > b = " << ((a > b) ? "True" : "False") << "\n";
    std::cout << "a < b = " << ((a < b) ? "True" : "False") << "\n";
    std::cout << "a == b = " << ((a == b) ? "True" : "False") << "\n";
    std::cout << "a != b = " << ((a != b) ? "True" : "False") << "\n";

    std::cout << "a to double: " << a.toDouble() << "\n";
    std::cout << "b to double: " << b.toDouble() << "\n";
    
    std::cout << "Enter c double value to convert to fraction: ";
    double value;
    std::cin >> value;
    
    std::cout << "Enter precision for conversion: ";
    int precision;
    std::cin >> precision;

    Fraction fromC = Fraction::fromDouble(value, precision);

    std::cout << "Fraction from c double: ";
    fromC.output();

    return 0;
}