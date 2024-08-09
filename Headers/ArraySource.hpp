#include "Stack.hpp"
#include "Iterator.hpp"
#include "DataSource.hpp"

#ifndef ARRAY__SOURCE__HPP
#define ARRAY__SOURCE__HPP

template <typename T>
class ArraySource : public DataSource<T>
{
public:
    bool hasNext() const override { return (current != bound); };
    T getElement() override;

    bool reset() override
    {
        this->current = &array[0];
        return true;
    };

    ArraySource<T> operator+(T element) const;
    ArraySource<T> &operator+=(T element);

    // Prefix decrement
    ArraySource<T> &operator--();

    // Postfix decrement
    ArraySource<T> operator--(int);

    ArraySource(T *base, int lenght);
    ~ArraySource() = default;
    ArraySource(ArraySource<T> const &other);
    ArraySource<T> &operator=(ArraySource<T> const &other);

private:
    void setBound();

    Stack<T> array;
    Iterator<T> current;
    Iterator<T> bound;
    int counter = 0;
};

template <typename T>
inline void ArraySource<T>::setBound()
{
    this->bound = &array[array.getSize()];
}

template <typename T>
inline T ArraySource<T>::getElement()
{
    if (hasNext())
    {
        counter++;
        return *current++;
    }
    else
        throw std::out_of_range("Array data source is out of bounds.");
}

template <typename T>
inline ArraySource<T> ArraySource<T>::operator+(T element) const
{
    ArraySource<T> other(*this);
    other.array.push(element);
    other.setBound();
    other = &other.array[counter];
    return other;
}

template <typename T>
inline ArraySource<T> &ArraySource<T>::operator+=(T element)
{
    this->array.push(element);
    setBound();
    current = &array[counter];
    return *this;
}

template <typename T>
inline ArraySource<T> &ArraySource<T>::operator--()
{
    if (current == &array[0])
        return;
    this->current--;
    counter--;
    return *this;
}

template <typename T>
inline ArraySource<T> ArraySource<T>::operator--(int)
{
    ArraySource<T> tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
inline ArraySource<T>::ArraySource(T *base, int lenght)
{
    for (size_t i = 0; i < lenght; i++)
        array.push(base[i]);
    setBound();
    current = &array[0];
}

template <typename T>
inline ArraySource<T>::ArraySource(ArraySource<T> const &other)
{
    this->array = other.array;
    this->counter = other.counter;
    setBound();
    current = &this->array[counter];
}

template <typename T>
inline ArraySource<T> &ArraySource<T>::operator=(ArraySource<T> const &other)
{
    this->array = other.array;
    this->counter = other.counter;
    setBound();
    current = &this->array[counter];
    return *this;
}

#endif