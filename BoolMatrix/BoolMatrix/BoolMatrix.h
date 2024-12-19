#pragma once
#include <iostream>
#include <vector>
#include "../../BoolVector/BoolVector/BoolVector.h" 

class BoolMatrix {

public:

    BoolMatrix(int rows, int columns, bool value);
    BoolMatrix(const char** charMatrix, int rows, int columns);
    BoolMatrix(const BoolMatrix& other);
    ~BoolMatrix();

    int getRows() const;
    int getColumns() const;

    void swap(BoolMatrix& other);
    int weight() const;
    int rowWeight(int row) const;

    BoolVector conjunctionAllRows() const;
    BoolVector disjunctionAllRows() const;

    void inversion(int row, int column);
    void inversionComponents(int row, int column, int count);

    void set(int row, int column, bool value);
    void setComponents(int row, int column, bool value, int count);

    BoolMatrix& operator=(const BoolMatrix& other);

    BoolVector& operator[](int index);
    const BoolVector& operator[](int index) const;

    BoolMatrix operator&(const BoolMatrix& other) const;
    BoolMatrix& operator&=(const BoolMatrix& other);

    BoolMatrix operator|(const BoolMatrix& other) const;
    BoolMatrix& operator|=(const BoolMatrix& other);

    BoolMatrix operator^(const BoolMatrix& other) const;
    BoolMatrix& operator^=(const BoolMatrix& other);

    BoolMatrix operator~() const;

private:
    BoolVector* m_matrix = nullptr;
    int m_rows;
    int m_columns;

};

std::istream& operator>>(std::istream& is, BoolMatrix& matrix);
std::ostream& operator<<(std::ostream& os, const BoolMatrix& matrix);