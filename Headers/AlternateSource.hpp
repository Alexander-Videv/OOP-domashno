#include "DataSource.hpp"
#include "Stack.hpp"
#include "Iterator.hpp"

#ifndef ALTERNATE__SOURCE__HPP
#define ALTERNATE__SOURCE__HPP

template <typename T>
class AlternateSource : public DataSource<T>
{

public:
    bool hasNext() const override;
    T getElement() override;
    void push(DataSource<T> &data);

    AlternateSource() = default;
    AlternateSource(DataSource<T> **DataArray, int lenght);
    ~AlternateSource() = default;

    AlternateSource<T>(AlternateSource<T> const &other);
    AlternateSource<T> &operator=(AlternateSource<T> const &other);

private:
    bool reset() override;
    bool checkMap() const;
    void fixMap();

    Stack<DataSource<T> *> collection;
    Stack<bool> map;
    int counter = 0;
};

template <typename T>
inline AlternateSource<T> &AlternateSource<T>::operator=(AlternateSource<T> const &other)
{
    this->collection = other.collection;
    this->map = other.map;
    this->counter = other.counter;
    return *this;
}

template <typename T>
inline bool AlternateSource<T>::reset()
{
    for (size_t i = 0; i < collection.getSize(); i++)
        if (!(collection[i]->reset()))
            return false;
    counter = 0;
    return true;
}

template <typename T>
inline bool AlternateSource<T>::checkMap() const
{
    for (size_t i = 0; i < collection.getSize(); i++)
        if (map[i])
            return true;
    return false;
}

template <typename T>
inline void AlternateSource<T>::fixMap()
{
    for (size_t i = 0; i < collection.getSize(); i++)
    {
        if (collection[i]->hasNext())
            map[i] = true;
        else
            map[i] = false;
    }
}

template <typename T>
inline bool AlternateSource<T>::hasNext() const
{
    return checkMap();
}

template <typename T>
inline T AlternateSource<T>::getElement()
{
    if (!hasNext())
        throw std::out_of_range("Alternate data source is out of bouds.");
    else
    {
        while (map[counter] != true)
        {
            counter++;
            counter %= collection.getSize();
        }
        T buffer;
        buffer = collection[counter]->getElement();
        fixMap();
        if ((counter == collection.getSize() - 1) && hasNext())
            counter = 0;
        else
            counter++;

        return buffer;
    }
}

template <typename T>
inline void AlternateSource<T>::push(DataSource<T> &data)
{
    if (&data == nullptr)
        return;

    this->collection.push(&data);

    map.push(data.hasNext());
}

template <typename T>
inline AlternateSource<T>::AlternateSource(DataSource<T> **DataArray, int lenght)
{
    for (size_t i = 0; i < lenght; i++)
    {
        this->collection.push(DataArray[i]);
        map.push(DataArray[i]->hasNext());
    }
}

#endif

template <typename T>
inline AlternateSource<T>::AlternateSource(AlternateSource<T> const &other)
{
    this->collection = other.collection;
    this->map = other.map;
    this->counter = other.counter;
}
