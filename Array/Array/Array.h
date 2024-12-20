#pragma once 
#include <iostream> 
#include <stdexcept> 
#include <algorithm>
#include <cassert>

template <typename ItemType>
class Array
{
public:
    typedef ItemType* iterator;
    typedef ItemType value_type;
    typedef ItemType& reference;
    typedef ItemType* pointer;
    typedef int difference_type;

public:
    Array(int size = 10);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array();

    void input();
    void output() const;

    int size() const;
    void swap(Array& other) noexcept;

    int findValue(const ItemType& value) const;
    void sort();

    bool insertByIndex(const int index, const ItemType& value);
    bool deleteByIndex(const int index);
    bool deleteByValue(const ItemType& value);
    void deleteAll(const ItemType& value);

    ItemType& max();
    ItemType& min();
    const ItemType& max() const;
    const ItemType& min() const;

    iterator begin();
    iterator end();
    const iterator begin() const;
    const iterator end() const;

    bool insertBefore(iterator pos, const ItemType& value);
    bool deleteRange(iterator start, iterator end);

    ItemType& operator[](int index);
    const ItemType& operator[](int index) const;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    Array operator+(const Array& other) const;
    Array& operator+=(const Array& other);
    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;

private:
    ItemType* m_array = nullptr;
    int m_size = 0;
};

template <typename T>
std::istream& operator>>(std::istream& is, Array<T>& arr);

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr);


template <typename ItemType>
Array<ItemType>::Array(int size)
{
    if (size < 0)
    {
        size = -size;
    }
    m_size = size;
    m_array = new ItemType[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = ItemType();
    }
}

template <typename ItemType>
Array<ItemType>::Array(const Array& other)
{
    m_size = other.m_size;
    m_array = new ItemType[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = other.m_array[i];
    }
}

template <typename ItemType>
Array<ItemType>::Array(Array&& other) noexcept
{
    m_size = other.m_size;
    m_array = other.m_array;
    other.m_size = 0;
    other.m_array = nullptr;
}

template <typename ItemType>
Array<ItemType>::~Array()
{
    delete[] m_array;
}

template <typename ItemType>
void Array<ItemType>::input() {
    for (int i = 0; i < m_size; i++) {
        std::cin >> m_array[i];
    }
}

template <typename ItemType>
void Array<ItemType>::output() const {
    for (int i = 0; i < m_size; i++) {
        std::cout << m_array[i] << " ";
    }
    std::cout << '\n';
}

template <typename ItemType>
int Array<ItemType>::size() const
{
    return m_size;
}

template <typename ItemType>
void Array<ItemType>::swap(Array& other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
}

template <typename ItemType>
int Array<ItemType>::findValue(const ItemType& value) const {
    for (int i = 0; i < m_size; ++i) {
        if (m_array[i] == value) return i;
    }
    return -1;
}

template <typename ItemType>
void Array<ItemType>::sort() {
    for (size_t i = 0; i < m_size - 1; i++) {
        for (size_t j = 0; j < m_size - i - 1; j++) {
            if (m_array[j] > m_array[j + 1]) {
                std::swap(m_array[j], m_array[j + 1]);
            }
        }
    }
}

template <typename ItemType>
bool Array<ItemType>::insertByIndex(const int index, const ItemType& value)
{
    if (index < 0 || index > m_size)
    {
        return false;
    }
    ItemType* newArray = new ItemType[m_size + 1];
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

template <typename ItemType>
bool Array<ItemType>::deleteByIndex(const int index) {
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

template <typename ItemType>
bool Array<ItemType>::deleteByValue(const ItemType& value) {
    int index = findValue(value);
    return deleteByIndex(index);
}

template <typename ItemType>
void Array<ItemType>::deleteAll(const ItemType& value) {
    int index = findValue(value);
    while (index != -1) {
        deleteByIndex(index);
        index = findValue(value);
    }
}

template <typename ItemType>
ItemType& Array<ItemType>::max() {
    assert(m_size > 0);
    ItemType* max_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] > *max_element) max_element = &m_array[i];
    return *max_element;
}

template <typename ItemType>
ItemType& Array<ItemType>::min() {
    assert(m_size > 0);
    ItemType* min_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] < *min_element) min_element = &m_array[i];
    return *min_element;
}

template <typename ItemType>
const ItemType& Array<ItemType>::max() const {
    assert(m_size > 0);
    const ItemType* max_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] > *max_element) max_element = &m_array[i];
    return *max_element;
}

template <typename ItemType>
const ItemType& Array<ItemType>::min() const {
    assert(m_size > 0);
    const ItemType* min_element = m_array;
    for (int i = 1; i < m_size; ++i)
        if (m_array[i] < *min_element) min_element = &m_array[i];
    return *min_element;
}

template <typename ItemType> typename
Array<ItemType>::iterator Array<ItemType>::begin()
{
    return m_array;
}

template <typename ItemType> typename
Array<ItemType>::iterator Array<ItemType>::end()
{
    return m_array + m_size;
}

template <typename ItemType>
const typename Array<ItemType>::iterator Array<ItemType>::begin() const
{
    return m_array;
}

template <typename ItemType>
const typename Array<ItemType>::iterator Array<ItemType>::end() const
{
    return m_array + m_size;
}

template <typename ItemType>
bool Array<ItemType>::insertBefore(iterator pos, const ItemType& value) {
    if (pos < begin() || pos > end()) return false;
    int index = pos - begin();
    return insertByIndex(index, value);
}

template <typename ItemType>
bool Array<ItemType>::deleteRange(iterator start, iterator end) {
    if (start < begin() || end > this->end() || start >= end)
        return false;
    int numToRemove = end - start;
    int newSize = m_size - numToRemove;
    ItemType* newArray = new ItemType[newSize];
    int i = 0;
    for (iterator it = begin(); it < start; ++it) newArray[i++] = *it;
    for (iterator it = end; it < this->end(); ++it) newArray[i++] = *it;
    delete[] m_array;
    m_array = newArray;
    m_size = newSize;
    return true;
}

template <typename ItemType>
ItemType& Array<ItemType>::operator[](int index) {
    if (index < 0 && index >= m_size) {
        std::cout << "Index error\n";
        return m_array[0];
    }
    else {
        return m_array[index];
    }
}

template <typename ItemType>
const ItemType& Array<ItemType>::operator[](int index) const
{
    if (index < 0 && index >= m_size) {
        std::cout << "Index error\n";
        return m_array[0];
    }
    else {
        return m_array[index];
    }
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(const Array& other)
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

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(Array&& other) noexcept
{
    std::cout << "other: " << &other << " \n";
    swap(other);
    return *this;
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+(const Array& other) const
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

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator+=(const Array& other)
{
    operator+(other).swap(*this);
    return *this;
}

template<typename ItemType>
bool Array<ItemType>::operator==(const Array& other) const {
    if (m_size != other.m_size)
        return false;
    for (int i = 0; i < m_size; ++i)
        if (m_array[i] != other.m_array[i])
            return false;
    return true;
}

template<typename ItemType>
bool Array<ItemType>::operator!=(const Array& other) const {
    return !(*this == other);
}

template<typename ItemType>
std::istream& operator>>(std::istream& is, Array<ItemType>& arr) {
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

template<typename ItemType>
std::ostream& operator<<(std::ostream& os, const Array<ItemType>& arr) {
    os << "[";
    for (int i = 0; i < arr.size(); ++i) {
        os << arr[i];
        if (i < arr.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}