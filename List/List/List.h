#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename T>
class List
{
    struct Node;

public:
    template <typename ItemType>
    class TemplateIterator;
    using iterator = TemplateIterator<T>;
    using const_iterator = TemplateIterator<const T>;

public:
    List();
    List(const T* array, int const size);
    List(const List<T>& other);
    ~List();

    int size() const;
    void swap(List<T>& other);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    iterator findValue(const T& key);

    void addToHead(const T& value);
    void addToTail(const T& value);
    void addAtPosition(int position, const T& value);
    void addAfterKey(const T& key, const T& value);
    iterator addByIterator(iterator position, const T& value);

    void deleteFromHead();
    void deleteFromTail();
    void deleteAtPosition(int position);
    void deleteByKey(const T& key);
    iterator deleteByIterator(iterator position);
    iterator deleteRangeByIterator(iterator begin, iterator end);

    T min() const;
    T max() const;

    bool isEmpty() const;

    void clear();
    void sort();

    List<T>& operator=(const List<T>& other);

    T& operator[](int index);
    const T& operator[](int index) const;

    bool operator==(const List<T>& other) const;
    bool operator!=(const List<T>& other) const;

    List<T> operator+(const List<T>& other) const;
    List<T>& operator+=(const List<T>& other);

private:
    int m_size = 0;
    Node* m_head = nullptr;
    Node* m_tail = nullptr;
};

template <typename T>
std::istream& operator>>(std::istream& is, List<T>& other);

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& other);


template <typename T>
struct List<T>::Node
{
    Node(Node* next = nullptr, Node* prev = nullptr);
    Node(const T& value, Node* next = nullptr, Node* prev = nullptr);

    T value;
    Node* next = nullptr;
    Node* prev = nullptr;
};

template <typename T>
template <typename ItemType>
class List<T>::TemplateIterator
{
public:
    using value_type = ItemType;
    using reference = ItemType&;
    using pointer = ItemType*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;

    TemplateIterator(Node* node);

    ItemType& operator*();
    const ItemType& operator*() const;
    TemplateIterator operator++();
    TemplateIterator operator--();
    TemplateIterator operator++(int);
    TemplateIterator operator--(int);
    bool operator==(const TemplateIterator& other) const;
    bool operator!=(const TemplateIterator& other) const;

protected:
    Node* m_node = nullptr;
};

template <typename T>
List<T>::List()
    : m_head(new Node())
    , m_tail(new Node())
{
    m_head->next = m_tail;
    m_tail->prev = m_head;
}

template<typename T>
inline List<T>::List(const T* array, int const size)
    : m_head(new Node())
    , m_tail(new Node())
{
    m_head->next = m_tail;
    m_tail->prev = m_head;
    for (int i = 0; i < size; i++)
        addToTail(array[i]);
}

template<typename T>
List<T>::List(const List<T>& other)
    : m_head(new Node())
    , m_tail(new Node())
{
    m_head->next = m_tail;
    m_tail->prev = m_head;
    Node* runner = other.m_head->next;
    while (runner != other.m_tail)
    {
        addToTail(runner->value);
        runner = runner->next;
    }
}

template <typename T>
List<T>::~List()
{
    clear();
    delete m_head;
    delete m_tail;
}

template <typename T>
int List<T>::size() const
{
    return m_size;
}

template<typename T>
void List<T>::swap(List<T>& other)
{
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_size, other.m_size);
}

template <typename T> typename
List<T>::iterator List<T>::begin()
{
    return iterator(m_head->next);
}

template <typename T> typename
List<T>::iterator List<T>::end()
{
    return iterator(m_tail);
}

template <typename T> typename
List<T>::const_iterator List<T>::begin() const
{
    return const_iterator(m_head->next);
}

template <typename T> typename
List<T>::const_iterator List<T>::end() const
{
    return const_iterator(m_tail);
}

template <typename T> typename
List<T>::iterator List<T>::findValue(const T& key)
{
    iterator runner = begin();
    while (runner != end())
    {
        if ((*runner) == key) {
            return runner;
        }
        runner = ++runner;
    }
    return end();
}

template<typename T>
void List<T>::addToHead(const T& value)
{
    Node* node = new Node(value, m_head->next, m_head);
    m_head->next->prev = node;
    m_head->next = node;
    ++m_size;
}

template <typename T>
void List<T>::addToTail(const T& value)
{
    Node* node = new Node(value, m_tail, m_tail->prev);
    m_tail->prev->next = node;
    m_tail->prev = node;
    ++m_size;
}

template<typename T>
void List<T>::addAtPosition(int position, const T& value)
{
    if (position < 0 || position > m_size) {
        throw std::out_of_range("Position out of range");
    }
    if (position == 0) {
        addToHead(value);
        return;
    }
    if (position == m_size) {
        addToTail(value);
        return;
    }
    Node* runner = m_head->next;
    for (int i = 0; i < position; ++i) {
        runner = runner->next;
    }
    Node* node = new Node(value, runner, runner->prev);
    runner->prev->next = node;
    runner->prev = node;
    ++m_size;
}

template<typename T>
void List<T>::addAfterKey(const T& key, const T& value)
{
    Node* runner = m_head->next;
    while (runner != m_tail) {
        if (runner->value == key) {
            Node* node = new Node(value, runner->next, runner);
            if (runner->next) {
                runner->next->prev = node;
            }
            runner->next = node;
            ++m_size;
            return;
        }
        runner = runner->next;
    }
}

template<typename T> typename
List<T>::iterator List<T>::addByIterator(iterator position, const T& value)
{
    Node* node = new Node(value, position.m_node, position.m_node->prev);
    position.m_node->prev->next = node;
    position.m_node->prev = node;
    ++m_size;
    return iterator(node);
}

template <typename T>
void List<T>::deleteFromHead() {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    Node* node = m_head->next;
    m_head->next = node->next;
    node->next->prev = m_head;
    delete node;
    --m_size;
}

template <typename T>
void List<T>::deleteFromTail() {
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    Node* node = m_tail->prev;
    m_tail->prev = node->prev;
    node->prev->next = m_tail;
    delete node;
    --m_size;
}

template <typename T>
void List<T>::deleteAtPosition(int position) {
    if (position < 0 || position >= m_size) {
        throw std::out_of_range("Invalid position");
    }
    if (position == 0) {
        deleteFromHead();
        return;
    }
    if (position == m_size - 1) {
        deleteFromTail();
        return;
    }
    Node* runner = m_head->next;
    for (int i = 0; i < position; ++i) {
        runner = runner->next;
    }
    runner->prev->next = runner->next;
    if (runner->next) {
        runner->next->prev = runner->prev;
    }
    delete runner;
    --m_size;
}

template<typename T>
void List<T>::deleteByKey(const T& key)
{
    Node* runner = m_head->next;
    while (runner != m_tail)
    {
        if (runner->value == key)
        {
            if (runner->prev) {
                runner->prev->next = runner->next;
            }
            if (runner->next) {
                runner->next->prev = runner->prev;
            }
            if (runner == m_head->next) {
                m_head->next = runner->next;
            }
            if (runner == m_tail->prev) {
                m_tail->prev = runner->prev;
            }
            delete runner;
            --m_size;
            return;
        }
        runner = runner->next;
    }
}

template <typename T> typename
List<T>::iterator List<T>::deleteByIterator(iterator position)
{
    if (position == end()) {
        return position;
    }
    Node* node = position.m_node;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    --m_size;
    return iterator(node->next);
}

template <typename T> typename
List<T>::iterator List<T>::deleteRangeByIterator(iterator begin, iterator end)
{
    if (begin == end || begin == this->end() || end == this->end()) {
        return end;
    }
    iterator runner = begin;
    iterator next;
    while (runner != end) {
        next = deleteByIterator(runner);
        runner = next;
    }
    return end;
}

template<typename T>
T List<T>::min() const
{
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    T min = m_head->next->value;
    Node* runner = m_head->next->next;
    while (runner != m_tail) {
        if (runner->value < min) {
            min = runner->value;
        }
        runner = runner->next;
    }
    return min;
}

template<typename T>
T List<T>::max() const
{
    if (isEmpty()) {
        throw std::out_of_range("List is empty");
    }
    T max = m_head->next->value;
    Node* runner = m_head->next->next;
    while (runner != m_tail) {
        if (runner->value > max) {
            max = runner->value;
        }
        runner = runner->next;
    }
    return max;
}

template<typename T>
bool List<T>::isEmpty() const
{
    return m_size == 0;
}

template <typename T>
void List<T>::clear()
{
    if (!size())
    {
        return;
    }
    Node* runner = m_head->next;
    while (runner != m_tail)
    {
        Node* node = runner;
        runner = runner->next;
        delete node;
    }
    m_head->next = m_tail;
    m_tail->prev = m_head;
    m_size = 0;
}

template <typename T>
void List<T>::sort()
{
    if (isEmpty() || !m_head->next) {
        return;
    }
    for (Node* i = m_head->next->next; i != m_tail; i = i->next) {
        Node* j = i;
        while (j->prev != m_head && j->value < j->prev->value) {
            std::swap(j->value, j->prev->value);
            j = j->prev;
        }
    }
}

template<typename T>
List<T>& List<T>::operator=(const List& other)
{
    List<T> list(other);
    swap(list);
    return *this;
}

template<typename T>
T& List<T>::operator[](int index)
{
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    Node* runner = m_head->next;
    for (int i = 0; i < index; i++) {
        runner = runner->value;
    }
    return runner->value;
}

template<typename T>
const T& List<T>::operator[](int index) const
{
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    Node* runner = m_head->next;
    for (int i = 0; i < index; ++i) {
        runner = runner->value;
    }
    return runner->value;
}

template<typename T>
bool List<T>::operator==(const List<T>& other) const
{
    if (m_size != other.m_size) {
        return false;
    }
    Node* runner1 = m_head->next;
    Node* runner2 = other.m_head->next;
    while (runner1 != m_tail) {
        if (runner1->value != runner2->value) {
            return false;
        }
        runner1 = runner1->next;
        runner2 = runner2->next;
    }
    return true;
}

template<typename T>
bool List<T>::operator!=(const List<T>& other) const
{
    return !(*this == other);
}

template<typename T>
List<T> List<T>::operator+(const List<T>& other) const
{
    List<T> result(*this);
    Node* runner = other.m_head->next;
    while (runner != m_tail) {
        result.addToTail(runner->value);
        runner = runner->next;
    }
    return result;
}

template<typename T>
List<T>& List<T>::operator+=(const List<T>& other)
{
    operator+(other).swap(*this);
    return *this;
}

template <typename T>
List<T>::Node::Node(Node* next, Node* prev)
    : next(next)
    , prev(prev)
{}

template <typename T>
List<T>::Node::Node(const T& value, Node* next, Node* prev)
    : value(value)
    , next(next)
    , prev(prev)
{}

template <typename T>
template <typename ItemType>
List<T>::TemplateIterator<ItemType>::TemplateIterator(Node* node)
    : m_node(node)
{}

template <typename T>
template <typename ItemType>
ItemType& List<T>::TemplateIterator<ItemType>::operator*()
{
    return m_node->value;
}

template <typename T>
template <typename ItemType>
const ItemType& List<T>::TemplateIterator<ItemType>::operator*() const
{
    return m_node->value;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator++()
{
    m_node = m_node->next;
    return *this;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator--()
{
    m_node = m_node->prev;
    return *this;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator++(int)
{
    TemplateIterator old = *this;
    m_node = m_node->next;
    return old;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator--(int)
{
    TemplateIterator old = *this;
    m_node = m_node->prev;
    return old;
}

template <typename T>
template <typename ItemType>
bool List<T>::TemplateIterator<ItemType>::operator==(const TemplateIterator& other) const
{
    return (m_node == other.m_node);
}

template <typename T>
template <typename ItemType>
bool List<T>::TemplateIterator<ItemType>::operator!=(const TemplateIterator& other) const
{
    return (m_node != other.m_node);
}

template <typename T>
std::istream& operator>>(std::istream& is, List<T>& other)
{
    int size = other.size();
    other.clear();
    for (int i = 0; i < size; i++) {
        T value;
        is >> value;
        other.addToTail(value);
    }
    return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, List<T>& other)
{
    for (T& value : other)
    {
        os << value << " ";
    }
    os << "\n";
    return os;
}