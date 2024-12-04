#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>

class Array
{
public:
    typedef int* iterator;

public:
    Array(int size = 10);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array();

    void input();
    void output() const;

    int size() const;
    void swap(Array& other) noexcept;

    int findValue(const int& value) const;
    void sort();

    bool insertByIndex(const int index, const int& value);

    bool deleteByIndex(const int index);
    bool deleteByValue(const int& value);
    void deleteAll(const int& value);

    int& max();
    int& min();
    const int& max() const;
    const int& min() const;

    iterator begin();
    iterator end();
    const iterator begin() const;
    const iterator end() const;

    bool insertBefore(iterator pos, const int& value);
    bool deleteRange(iterator start, iterator end);

    int& operator[](int index);
    const int& operator[](int index) const;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    Array operator+(const Array& other) const;
    Array& operator+=(const Array& other);
    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;

private:
    int* m_array = nullptr;
    int m_size = 0;
};

std::istream& operator>>(std::istream& is, Array& arr); 
std::ostream& operator<<(std::ostream& os, const Array& arr);