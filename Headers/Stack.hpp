#include <cstddef>
#include <utility>
#include <iostream>

#ifndef STACK_HPP
#define STACK_HPP

template <typename T, int CAPACITY = 4>

class Stack
{
public:
    void push(const T &element);
    void pop();
    void print() const;
    bool isEmpty() const;

public:
    int getSize() const;
    int getCapacity() const;

public:
    Stack();
    Stack(T *base, int lenght);
    Stack(int capacity);
    ~Stack();

    Stack(Stack const &other);
    Stack(Stack &&other);

    Stack<T> &operator=(Stack<T> const &other);
    Stack<T> &operator=(Stack<T> &&other);

    T &operator[](int index);
    const T &operator[](int index) const;

    operator bool() const { return !isEmpty(); };

private:
    T *array = nullptr;
    int capacity = CAPACITY;
    int size = 0;

    void copy(Stack const &other);
    void move(Stack &&other);
    void free();
    void resize(int newCap);
};

template <typename T, int CAPACITY>
inline void Stack<T, CAPACITY>::copy(Stack const &other)
{
    T *buffer = new T[other.size];
    for (size_t i = 0; i < other.size; i++)
        buffer[i] = other.array[i];

    if (this->array)
        free();

    this->size = other.size;
    this->capacity = other.capacity;
    this->array = buffer;
    buffer = nullptr;
}

template <typename T, int CAPACITY>
inline void Stack<T, CAPACITY>::move(Stack &&other)
{
    if (this->array)
        free();

    this->array = other.array;
    other.array = nullptr;
    this->size = other.size;
    this->capacity = other.capacity;
}

template <typename T, int CAPACITY>
inline void Stack<T, CAPACITY>::free()
{
    delete[] this->array;
    this->size = 0;
    this->capacity = 0;
}

template <typename T, int CAPACITY>
inline void Stack<T, CAPACITY>::resize(int newCap)
{
    T *buffer = new T[newCap];
    for (size_t i = 0; i < this->size; i++)
        buffer[i] = array[i];

    this->array = buffer;
    this->capacity = newCap;
    buffer = nullptr;
}

template <typename T, int CAPACITY>
inline void Stack<T, CAPACITY>::push(const T &element)
{
    if (size >= capacity - 1)
        resize(capacity * 2);

    array[size++] = element;
}

template <typename T, int CAPACITY>
inline void Stack<T, CAPACITY>::pop()
{
    if (size == 0)
        return;

    array[size--] = 0;

    if (size <= capacity / 2)
        resize(capacity / 2);
}

template <typename T, int CAPACITY>
inline Stack<T, CAPACITY>::Stack()
{
    array = new T[CAPACITY];
    size = 0;
    capacity = 4;
}

template <typename T, int CAPACITY>
inline Stack<T, CAPACITY>::Stack(int capacity)
{
    array = new T[capacity];
    this->capacity = capacity;
    size = 0;
}

template <typename T, int CAPACITY>
inline Stack<T, CAPACITY>::~Stack()
{
    free();
}

template <typename T, int CAPACITY>
inline Stack<T, CAPACITY>::Stack(Stack const &other)
{
    copy(other);
}

template <typename T, int CAPACITY>
inline Stack<T, CAPACITY>::Stack(Stack &&other)
{
    move(std::move(other));
}

template <typename T, int CAPACITY>
inline Stack<T> &Stack<T, CAPACITY>::operator=(Stack<T> const &other)
{
    if (this == &other)
        return *this;

    copy(other);
    return *this;
}

template <typename T, int CAPACITY>
inline Stack<T> &Stack<T, CAPACITY>::operator=(Stack<T> &&other)
{
    if (this == &other)
        return *this;
    move(std::move(other));
    return *this;
}

template <typename T, int CAPACITY>
void Stack<T, CAPACITY>::print() const
{
    for (size_t i = 0; i < this->size; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;

    std::cout << "Size is : " << this->getSize() << " Capacity is : " << this->getCapacity() << "\n";
}

template <typename T, int CAPACITY>
int Stack<T, CAPACITY>::getSize() const
{
    return size;
}

template <typename T, int CAPACITY>
int Stack<T, CAPACITY>::getCapacity() const
{
    return capacity;
}

template <typename T, int CAPACITY>
bool Stack<T, CAPACITY>::isEmpty() const
{
    return !size;
}

template <typename T, int CAPACITY>
inline T &Stack<T, CAPACITY>::operator[](int index)
{
    if (index > capacity)
        throw;
    return array[index];
}

template <typename T, int CAPACITY>
inline const T &Stack<T, CAPACITY>::operator[](int index) const
{
    if (index > size)
        throw;
    return array[index];
}

template <typename T, int CAPACITY>
inline Stack<T, CAPACITY>::Stack(T *base, int lenght)
{
    this->array = new T[lenght];
    for (size_t i = 0; i < lenght; i++)
        push(base[i]);
    capacity = lenght;
    size = lenght;
}

#endif