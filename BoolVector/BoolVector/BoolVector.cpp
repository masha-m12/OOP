#include "BoolVector.h"
#include <iostream>
#include <conio.h> 
#include <vector>

BoolVector::BoolVector(int length)
    : m_length(length) {
    m_cellCount = m_length / CellSize;
    if (m_length % CellSize != 0) {
        m_cellCount++;
    }
    m_cells = new Cell[m_cellCount];
}

BoolVector::BoolVector(int length, bool value) : m_length(length)
{
    m_cellCount = (length + CellSize - 1) / CellSize;
    m_cells = new Cell[m_cellCount]();
    if (value) {
        setAll(true);
    }
    else {
        setAll(false);
    }
}

BoolVector::BoolVector(const char* array)
{
    if (array == nullptr) {
        throw std::invalid_argument("Input array can't be 0");
    }
    m_length = std::strlen(array);
    m_cellCount = m_length / CellSize;
    if (m_length % CellSize != 0) {
        m_cellCount++;
    }
    m_cells = new Cell[m_cellCount];
    for (int i = 0; i < m_cellCount; i++) {
        m_cells[i] = 0;
    }
    for (int i = 0; i < m_length; i++) {
        if (array[i] == '1') {
            setBitValue(i, 1);
        }
    }
}

BoolVector::BoolVector(const BoolVector& other)
{
    m_cellCount = other.m_cellCount;
    m_length = other.m_length;
    m_cells = new Cell[m_cellCount];
    for (int i = 0; i < m_cellCount; i++) {
        m_cells[i] = other.m_cells[i];
    }
}

BoolVector::~BoolVector()
{
    delete[] m_cells;
}

int BoolVector::length() const
{
    return m_length;
}

void BoolVector::swap(BoolVector& other)
{
    std::swap(m_cells, other.m_cells);
    std::swap(m_cellCount, other.m_cellCount);
    std::swap(m_length, other.m_length);
}

void BoolVector::inversion()
{
    for (int i = 0; i < m_cellCount; i++) {
        m_cells[i] = ~m_cells[i];
    }
}

void BoolVector::inversionBit(int index)
{
    if (index < 0 || index >= m_length) {
        throw std::out_of_range("Index out of range");
    }
    setBitValue(index, !bitValue(index));
}

void BoolVector::setBit(int index, bool value)
{
    setBitValue(index, value);
}

void BoolVector::setBits(int index, int count, bool value)
{
    if (index < 0 || index + count > m_length) {
        throw std::out_of_range("Index out of range");
    }
    for (int i = index; i < index + count; ++i) {
        setBitValue(i, value);
    }
}

void BoolVector::setAll(bool value)
{
    if (value) {
        for (int i = 0; i < m_cellCount; ++i) {
            m_cells[i] = ~0;
        }
    }
    else {
        for (int i = 0; i < m_cellCount; ++i) {
            m_cells[i] = 0;
        }
    }
}

bool BoolVector::bitValue(int index) const
{
    if (index < 0 || index >= m_length) {
        throw std::out_of_range("Index out of range");
    }
    Cell mask = _mask(index);
    return m_cells[index / CellSize] & mask;
}

void BoolVector::setBitValue(int index, bool value)
{
    if (index < 0 || index >= m_length) {
        throw std::out_of_range("Index out of range");
    }
    Cell mask = _mask(index);
    if (value) {
        m_cells[index / CellSize] |= mask;
    }
    else {
        m_cells[index / CellSize] &= ~mask;
    }
}

int BoolVector::weight() const
{
    int count = 0;
    for (int i = 0; i < m_length; ++i) {
        count += bitValue(i);
    }
    return count;
}

BoolVector::Rank BoolVector::operator[](int index)
{
    if (index < 0 || index >= m_length) {
        throw std::out_of_range("Index out of range");
    }
    return Rank(&m_cells[index / CellSize], _mask(index));
}

const BoolVector::Rank BoolVector::operator[](int index) const
{
    if (index < 0 || index >= m_length) {
        throw std::out_of_range("Index out of range");
    }
    return Rank(&m_cells[index / CellSize], _mask(index));
}

BoolVector BoolVector::operator&(const BoolVector& other) const
{
    if (m_length != other.m_length) {
        throw std::invalid_argument("Vectors must have same length");
    }
    BoolVector result(*this);
    result &= other;
    return result;
}

BoolVector& BoolVector::operator&=(const BoolVector& other)
{
    if (m_length != other.m_length) {
        throw std::invalid_argument("Vectors must have same length");
    }
    for (int i = 0; i < m_cellCount; ++i) {
        m_cells[i] &= other.m_cells[i];
    }
    return *this;
}

BoolVector BoolVector::operator|(const BoolVector& other) const
{
    if (m_length != other.m_length) {
        throw std::invalid_argument("Vectors must have same length");
    }
    BoolVector result(*this);
    result |= other;
    return result;
}

BoolVector& BoolVector::operator|=(const BoolVector& other)
{
    if (m_length != other.m_length) {
        throw std::invalid_argument("Vectors must have same length");
    }
    for (int i = 0; i < m_cellCount; ++i) {
        m_cells[i] |= other.m_cells[i];
    }
    return *this;
}

BoolVector BoolVector::operator^(const BoolVector& other) const
{
    if (m_length != other.m_length) {
        throw std::invalid_argument("Vectors must have same length");
    }
    BoolVector result(*this);
    result ^= other;
    return result;
}

BoolVector& BoolVector::operator^=(const BoolVector& other) 
{
    if (m_length != other.m_length) {
        throw std::invalid_argument("Vectors must have same length");
    }
    for (int i = 0; i < m_cellCount; ++i) {
        m_cells[i] ^= other.m_cells[i];
    }
    return *this;
}

BoolVector BoolVector::operator>>(int shift) const
{
    if (shift < 0) {
        throw std::invalid_argument("Shift must be >0");
    }
    if (shift >= m_length) {
        return BoolVector(m_length);
    }
    BoolVector result(m_length);
    for (int i = m_length - 1; i >= shift; i--) {
        result[i] = bitValue(i - shift);
    }
    for (int i = 0; i < shift; i++) {
        result[i] = false;
    }
    return result;
}

BoolVector BoolVector::operator<<(int shift) const
{
    if (shift < 0) {
        throw std::invalid_argument("Shift must be >0");
    }
    if (shift >= m_length) {
        return BoolVector(m_length);
    }
    BoolVector result(m_length);
    for (int i = 0; i < m_length - shift; ++i) {
        result[i] = bitValue(i + shift);
    }
    for (int i = m_length - shift; i < m_length; ++i) {
        result[i] = false;
    }
    return result;
}

BoolVector& BoolVector::operator>>=(int shift)
{
    BoolVector shifted = *this >> shift;
    *this = shifted;
    return *this;
}

BoolVector& BoolVector::operator<<=(int shift)
{
    BoolVector shifted = *this << shift;
    *this = shifted;
    return *this;
}

BoolVector BoolVector::operator~() const
{
    BoolVector result(m_length);
    for (int i = 0; i < m_cellCount; ++i) {
        result.m_cells[i] = m_cells[i];
    }
    result.inversion();
    return result;
}

BoolVector& BoolVector::operator=(const BoolVector& other)
{
    if (this == &other) {
        return *this;
    }
    delete[] m_cells;
    m_length = other.m_length;
    m_cellCount = other.m_cellCount;
    m_cells = new Cell[m_cellCount];
    for (int i = 0; i < m_cellCount; ++i) {
        m_cells[i] = other.m_cells[i];
    }
    return *this;
}

BoolVector::Cell BoolVector::_mask(int index)
{
    Cell mask = 1;
    mask <<= CellSize - 1 - (index % CellSize);
    return mask;
}

int BoolVector::_excessRankCount() const
{
    return (m_cellCount * CellSize - m_length);
}

BoolVector::Rank::Rank(Cell* cell, Cell mask) : m_cell(cell), m_mask(mask) {
    if (m_cell == nullptr) {
        throw std::invalid_argument("Cell can't be 0");
    }
    if (m_mask <= 0) {
        throw std::invalid_argument("Mask must be >0");
    }
}

BoolVector::Rank& BoolVector::Rank::operator=(const Rank& other)
{
    return operator=(static_cast<bool>(other));
}

BoolVector::Rank& BoolVector::Rank::operator=(bool value)
{
    if (value) {
        *m_cell |= m_mask;
    }
    else {
        *m_cell &= ~m_mask;
    }
    return *this;
}

BoolVector::Rank::operator bool() const
{
    return (*m_cell & m_mask) != 0;
}

std::istream& operator>>(std::istream& is, BoolVector& boolVector)
{
    for (int i = 0; i < boolVector.length(); i++)
    {
        bool bit;
        is >> bit;
        boolVector.setBitValue(i, bit);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, BoolVector boolVector)
{
    for (int i = 0; i < boolVector.length(); i++)
        os << boolVector[i];
    return os;
}