#pragma once
#include <iostream>
#include <stdexcept>
#include <cstring>

class BoolVector {

public:
    class Rank;

public:
    using Cell = unsigned char;
    static const int CellSize = 8;

    BoolVector(int length = CellSize);
    BoolVector(int length, bool value);
    BoolVector(const char* bits);
    BoolVector(const BoolVector& other);
    ~BoolVector();

    int length() const;

    void swap(BoolVector& other);

    void inversion();
    void inversionBit(int index);

    void setBit(int index, bool value);
    void setBits(int index, int count, bool value);
    void setAll(bool value);

    bool bitValue(int index) const;
    void setBitValue(int index, bool value);

    int weight() const;

    Rank operator[](int index);
    const Rank operator [](int index) const;

    BoolVector operator&(const BoolVector& other) const;
    BoolVector& operator&=(const BoolVector& other);

    BoolVector operator|(const BoolVector& other) const;
    BoolVector& operator|=(const BoolVector& other);

    BoolVector operator^(const BoolVector& other) const;
    BoolVector& operator^=(const BoolVector& other);

    BoolVector operator>>(int shift) const;
    BoolVector operator<<(int shift) const;
    BoolVector& operator>>=(int shift);
    BoolVector& operator<<=(int shift);

    BoolVector operator~() const;

    BoolVector& operator=(const BoolVector& other);

private:
    static Cell _mask(int index);
    int _excessRankCount() const;

private:
    Cell* m_cells = nullptr;
    int m_cellCount = 0;
    int m_length = 0;
};

class BoolVector::Rank
{
public:
    Rank() = default;
    Rank(Cell* cell, Cell mask);
    Rank& operator=(const Rank& other);
    Rank& operator=(bool value);
    operator bool() const;

private:
    Cell* m_cell = nullptr;
    Cell m_mask = 0;
};

std::istream& operator>>(std::istream& is, BoolVector& boolVector);
std::ostream& operator<<(std::ostream& os, BoolVector boolVector);