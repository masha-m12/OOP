#include "BoolMatrix.h"
#include <iostream>
#include <vector>

BoolMatrix::BoolMatrix(int rows, int columns, bool value)
    : m_rows(rows), m_columns(columns) {
    if (rows <= 0 || columns <= 0) {
        throw std::invalid_argument("Rows and columns must be >0");
    }
    m_matrix = new BoolVector[m_rows];
    for (int i = 0; i < m_rows; ++i) {
        m_matrix[i] = BoolVector(m_columns, value);
    }
}

BoolMatrix::BoolMatrix(const char** charMatrix, int rows, int columns)
    : m_rows(rows), m_columns(columns) {
    if (rows <= 0 || columns <= 0) {
        throw std::invalid_argument("Rows and columns must be >0");
    }
    m_matrix = new BoolVector[m_rows];
    for (int i = 0; i < m_rows; ++i) {
        m_matrix[i] = BoolVector(charMatrix[i]);
    }
}

BoolMatrix::BoolMatrix(const BoolMatrix& other)
    : m_rows(other.m_rows), m_columns(other.m_columns) {
    m_matrix = new BoolVector[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_matrix[i] = other.m_matrix[i];
    }
}

BoolMatrix::~BoolMatrix()
{
    delete[] m_matrix;
}

int BoolMatrix::getRows() const
{
	return m_rows;
}

int BoolMatrix::getColumns() const
{
	return m_columns;
}

void BoolMatrix::swap(BoolMatrix& other) {
    std::swap(m_rows, other.m_rows);
    std::swap(m_columns, other.m_columns);
    std::swap(m_matrix, other.m_matrix);
}

int BoolMatrix::weight() const {
    int count = 0;
    for (int i = 0; i < m_rows; ++i) {
        count += m_matrix[i].weight();
    }
    return count;
}

int BoolMatrix::rowWeight(int row) const
{
    if (row < 0 || row >= m_rows) {
        throw std::out_of_range("Index out of range");
    }
    return m_matrix[row].weight();
}

BoolVector BoolMatrix::conjunctionAllRows() const
{
    BoolVector bv(m_rows, 1);
    for (int i = 0; i < m_rows; i++) {
        bv = bv & m_matrix[i];
    }
    return bv;
}

BoolVector BoolMatrix::disjunctionAllRows() const
{
    BoolVector bv(m_rows, 0);
    for (int i = 0; i < m_rows; i++)
        bv = bv | m_matrix[i];
    return bv;
}

void BoolMatrix::inversion(int row, int column)
{
    if (row < 0 || row >= m_rows || column < 0 || column >= m_columns) {
        throw std::out_of_range("Index out of range");
    }
    m_matrix[row].inversionBit(column);
}

void BoolMatrix::inversionComponents(int row, int column, int count)
{
    if (row < 0 || row >= m_rows || column < 0 || column >= m_columns) {
        throw std::out_of_range("Index out of range");
    }
    for (int i = 0; i < count; i++)
        m_matrix[row].inversionBit(column+i);
}

void BoolMatrix::set(int row, int column, bool value)
{
    if (row < 0 || row >= m_rows || column < 0 || column >= m_columns) {
        throw std::out_of_range("Index out of range");
    }
    m_matrix[row].setBitValue(column, value);
}

void BoolMatrix::setComponents(int row, int column, bool value, int count)
{
    if (row < 0 || row >= m_rows || column < 0 || column >= m_columns) {
        throw std::out_of_range("Index out of range");
    }
    m_matrix[row].setBits(column, count, value);
}

BoolMatrix& BoolMatrix::operator=(const BoolMatrix& other)
{
    BoolMatrix bm(other);
    swap(bm);
    return *this;
}

BoolVector& BoolMatrix::operator[](int index)
{
    if (index >= m_rows) {
        throw std::out_of_range("Row index out of range");
    }
    return m_matrix[index];
}

const BoolVector& BoolMatrix::operator[](int index) const
{
    if (index >= m_rows) {
        throw std::out_of_range("Row index out of range");
    }
    return m_matrix[index];
}

BoolMatrix BoolMatrix::operator&(const BoolMatrix& other) const
{
    if (m_rows != other.m_rows || m_columns != other.m_columns) {
        throw std::invalid_argument("Matrices must be same size");
    }
    BoolMatrix result(*this);
    result &= other;
    return result;
}

BoolMatrix& BoolMatrix::operator&=(const BoolMatrix& other)
{
    if (m_rows != other.m_rows || m_columns != other.m_columns) {
        throw std::invalid_argument("Matrices must be same size");
    }
    for (int i = 0; i < m_rows; i++) {
        m_matrix[i] &= other.m_matrix[i];
    }
    return *this;
}

BoolMatrix BoolMatrix::operator|(const BoolMatrix& other) const
{
    if (m_rows != other.m_rows || m_columns != other.m_columns) {
        throw std::invalid_argument("Matrices must be same size");
    }
    BoolMatrix result(*this);
    result |= other;
    return result;
}

BoolMatrix& BoolMatrix::operator|=(const BoolMatrix& other)
{
    if (m_rows != other.m_rows || m_columns != other.m_columns) {
        throw std::invalid_argument("Matrices must be same size");
    }
    for (int i = 0; i < m_rows; i++) {
        m_matrix[i] |= other.m_matrix[i];
    }
    return *this;
}

BoolMatrix BoolMatrix::operator^(const BoolMatrix& other) const
{
    if (m_rows != other.m_rows || m_columns != other.m_columns) {
        throw std::invalid_argument("Matrices must be same size");
    }
    BoolMatrix result(*this);
    result ^= other;
    return result;
}

BoolMatrix& BoolMatrix::operator^=(const BoolMatrix& other)
{
    if (m_rows != other.m_rows || m_columns != other.m_columns) {
        throw std::invalid_argument("Matrices must be same size");
    }
    for (int i = 0; i < m_rows; i++) {
        m_matrix[i] ^= other.m_matrix[i];
    }
    return *this;
}

BoolMatrix BoolMatrix::operator~() const
{
    BoolMatrix result(*this);
    for (int i = 0; i < m_rows; i++) {
        result[i].inversion();
    }
    return result;
}

std::istream& operator>>(std::istream& is, BoolMatrix& matrix)
{
    for (int i = 0; i < matrix.getRows(); i++)
        is >> matrix[i];
    return is;
}

std::ostream& operator<<(std::ostream& os, const BoolMatrix& matrix)
{
    for (int i = 0; i < matrix.getRows(); i++)
        os << matrix[i] << "\n";
    return os;
}