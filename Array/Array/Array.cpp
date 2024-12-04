#include "Array.h" 
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

Array::Array(int size)
{
    if (size < 0)
    {
        size = -size;
    }
    m_size = size;
    m_array = new int[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = int();
    }
}

Array::Array(const Array& other)
{
    m_size = other.m_size;
    m_array = new int[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = other.m_array[i];
    }
}

Array::Array(Array&& other) noexcept
{
    m_size = other.m_size;
    m_array = other.m_array;
    other.m_size = 0;
    other.m_array = nullptr;
}

Array::~Array()
{
    delete[] m_array;
}

void Array::input() {
    for (int i = 0; i < m_size; i++) {
        std::cin >> m_array[i];
    }
}

void Array::output() const {
    for (int i = 0; i < m_size; i++) {
        std::cout << m_array[i] << " ";
    }
    std::cout << '\n';
}

int Array::size() const
{
    return m_size;
}

void Array::swap(Array& other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
}

int Array::findValue(const int& value) const {
    for (int i = 0; i < m_size; ++i) {
        if (m_array[i] == value) return i;
    }
    return -1;
}

void Array::sort() {
    for (size_t i = 0; i < m_size - 1; i++) {
        for (size_t j = 0; j < m_size - i - 1; j++) {
            if (m_array[j] > m_array[j + 1]) {
                std::swap(m_array[j], m_array[j + 1]);
            }
        }
    }
}
bool Array::insertByIndex(const int index, const int& value)
{
    if (index < 0 || index > m_size)
    {
        return false;
    }
    int* newArray = new int[m_size + 1];
    for (int i = 0; i < index; i++)
    {
        newArray[i] = m_array[i];
    }
    newArray[index] = value;
    for (int i = index + 1; i < m_size + 1; i++)
    {
        newArray[i] = m_array[i - 1];
    }
    delete[] m_array;
    m_array = newArray;
    m_size++;
    return true;
}

bool Array::deleteByIndex(const int index) {
    if (index >= m_size || index < 0)
    {
        return false;
    }
    for (int i = index; i <= m_size - 1; i++) {
        m_array[i] = m_array[i + 1];
    }
    m_size--;
    return true;
}

bool Array::deleteByValue(const int& value) {
    int index = findValue(value);
    return deleteByIndex(index);
}

void Array::deleteAll(const int& value) {
    int index = findValue(value);
    while (index != -1) {
        deleteByIndex(index);
        index = findValue(value);
    }
}

int& Array::max() {
    assert(m_size > 0);
    int* max_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] > *max_element) max_element = &m_array[i];
    return *max_element;
}

int& Array::min() {
    assert(m_size > 0);
    int* min_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] < *min_element) min_element = &m_array[i];
    return *min_element;
}

const int& Array::max() const {
    assert(m_size > 0);
    const int* max_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] > *max_element) max_element = &m_array[i];
    return *max_element;
}

const int& Array::min() const {
    assert(m_size > 0);
    const int* min_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] < *min_element) min_element = &m_array[i];
    return *min_element;
}

Array::iterator Array::begin()
{
    return m_array;
}

Array::iterator Array::end()
{
    return m_array + m_size;
}

const Array::iterator Array::begin() const
{
    return m_array;
}

const Array::iterator Array::end() const
{
    return m_array + m_size;
}

bool Array::insertBefore(iterator pos, const int& value) {
    if (pos < begin() || pos > end()) return false;
    int index = pos - begin();
    return insertByIndex(index, value);
}

bool Array::deleteRange(iterator start, iterator end) {
    if (start < begin() || end > this->end() || start >= end) return false;
    int numToRemove = end - start;
    int newSize = m_size - numToRemove;
    int* newArray = new int[newSize];
    int i = 0;
    for (iterator it = begin(); it < start; ++it) newArray[i++] = *it;
    for (iterator it = end; it < this->end(); ++it) newArray[i++] = *it;
    delete[] m_array;
    m_array = newArray;
    m_size = newSize;
    return true;
}

int& Array::operator[](int index) {
    if (index < 0 && index >= m_size) {
        std::cout << "Index error\n";
        return m_array[0];
    }
    else {
        return m_array[index];
    }
}

const int& Array::operator[](int index) const
{
    if (index < 0 && index >= m_size) {
        std::cout << "Index error\n";
        return m_array[0];
    }
    else {
        return m_array[index];
    }
}

Array& Array::operator=(const Array& other)
{
    if (m_size == other.m_size)
    {
        for (int i = 0; i < m_size; ++i)
        {
            m_array[i] = other.m_array[i];
        }
    }
    else
    {
        Array copy(other);
        swap(copy);
    }
    return *this;
}

Array& Array::operator=(Array&& other) noexcept
{
    std::cout << "other: " << &other << " \n";
    swap(other);
    return *this;
}

Array Array::operator+(const Array& other) const
{
    Array result(m_size + other.m_size);
    int i = 0;
    for (; i < m_size; ++i) {
        result[i] = m_array[i];
    }
    for (int j = 0; j < other.m_size; ++j) {
        result[i + j] = other.m_array[j];
    }
    return result;
}

Array& Array::operator+=(const Array& other)
{
    operator+(other).swap(*this);
    return *this;
}

bool Array::operator==(const Array& other) const {
    if (m_size != other.m_size)
        return false;
    for (int i = 0; i < m_size; ++i)
        if (m_array[i] != other.m_array[i])
            return false;
    return true;
}

bool Array::operator!=(const Array& other) const {
    return !(*this == other);
}

std::istream& operator>>(std::istream& is, Array& arr) {
    int size;
    is >> size;
    if (size < 0) {
        size = -size;
    }
    for (int i = 0; i < size; ++i) {
        is >> arr[i];
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Array& arr) {
    os << "[";
    for (int i = 0; i < arr.size(); ++i) {
        os << arr[i];
        if (i < arr.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}