#include "Set.h"

Set::Set() : BoolVector(charSize) {}

Set::Set(const char* arr, int const size)
    : BoolVector(charSize)
{
    for (int i = 0; i < size; i++)
        addElement(arr[i]);
}

Set::Set(const Set& other) : BoolVector(other) {}

Set::~Set() {}

bool Set::contains(char element) const {
    if (element < start || element >= end) {
        throw std::out_of_range("Element out of range");
    }
    return bitValue(element - start);
}

char Set::min() const {
    for (size_t i = 0; i < charSize; ++i) {
        if (bitValue(i)) {
            return i + start;
        }
    }
    throw std::runtime_error("Set is empty");
}

char Set::max() const {
    for (size_t i = charSize; i > 0; --i) {
        if (bitValue(i - 1)) {
            return (i - 1) + start;
        }
    }
    throw std::runtime_error("Set is empty");
}

int Set::power() const {
    return weight();
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        BoolVector::operator=(other);
    }
    return *this;
}

bool Set::operator==(const Set& other) const {
    for (size_t i = 0; i < charSize; i++) {
        if (bitValue(i) != other.bitValue(i)) {
            return false;
        }
    }
    return true;
}

bool Set::operator!=(const Set& other) const {
    return !(*this == other);
}

Set Set::operator|(const Set& other) const {
    Set result = *this;
    result |= other;
    return result;
}

Set& Set::operator|=(const Set& other) {
    for (size_t i = 0; i < charSize; ++i) {
        this->setBitValue(i, this->bitValue(i) || other.bitValue(i));
    }
    return *this;
}

Set Set::operator&(const Set& other) const {
    Set result = *this;
    result &= other;
    return result;
}

Set& Set::operator&=(const Set& other) {
    for (size_t i = 0; i < charSize; ++i) {
        this->setBitValue(i, this->bitValue(i) && other.bitValue(i));
    }
    return *this;
}

Set Set::operator/(const Set& other) const {
    Set result = *this;
    result /= other;
    return result;
}

Set& Set::operator/=(const Set& other) {
    for (size_t i = 0; i < charSize; ++i) {
        this->setBitValue(i, this->bitValue(i) && !other.bitValue(i));
    }
    return *this;
}

Set Set::operator~() const {
    Set result = *this;
    result.inversion();
    return result;
}

Set Set::operator+(char element) const {
    Set result = *this;
    result.addElement(element);
    return result;
}

Set& Set::operator+=(char element) {
    addElement(element);
    return *this;
}

Set Set::operator-(char element) const {
    Set result = *this;
    result.deleteElement(element);
    return result;
}

Set& Set::operator-=(char element) {
    deleteElement(element);
    return *this;
}

void Set::addElement(char element) {
    if (element < start || element >= end) {
        throw std::out_of_range("Element out of range");
    }
    setBitValue(element - start, true);
}

void Set::deleteElement(char element) {
    if (element < start || element >= end) {
        throw std::out_of_range("Element out of range");
    }
    setBitValue(element - start, false);
}

std::ostream & operator<<(std::ostream & os, const Set & cs) {
    os << "{ ";
    for (size_t i = 0; i < cs.charSize; ++i) {
        if (cs.bitValue(i)) os << static_cast<char>(i + cs.start) << " ";
    }
    os << "}";
    return os;
}

std::istream& operator>>(std::istream& is, Set& cs) {
    char c;
    while (is >> c) {
        if (c >= cs.start && c < cs.end) {
            cs.setBitValue(c - cs.start, true);
        }
    }
    return is;
}