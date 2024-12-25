#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include "../../BoolVector/BoolVector/BoolVector.h" 

class Set : public BoolVector
{
public:

    Set();
    Set(const char* arr, int const size);
    Set(const Set& other);
    ~Set();

    bool contains(char element) const;

    char min() const;
    char max() const;

    int power() const;

    Set& operator=(const Set& other);
    bool operator==(const Set& other) const;
    bool operator!=(const Set& other) const;

    Set operator|(const Set& other) const;
    Set& operator|=(const Set& other);

    Set operator&(const Set& other) const;
    Set& operator&=(const Set& other);

    Set operator/(const Set& other) const;
    Set& operator/=(const Set& other);

    Set operator~() const;

    Set operator+(char element) const;
    Set& operator+=(char element);

    Set operator-(char element) const;
    Set& operator-=(char element);

    static const int start = 48;
    static const int end = 57;
    static const int charSize = end - start;

private:
    void addElement(const char element);
    void deleteElement(const char element);
};

std::ostream& operator<<(std::ostream& os, const Set& set);
std::istream& operator>>(std::istream& is, Set& set);