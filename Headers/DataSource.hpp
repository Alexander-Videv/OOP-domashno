// Main header, needs to be abstract and template//

#include "Stack.hpp"
#include "Iterator.hpp"

#ifndef DATA_SOURCE_HPP
#define DATA_SOURCE_HPP

template <typename T>
class DataSource
{
public:
    virtual bool hasElement() const { return iterator != bound; };
    virtual bool reset() = 0;
    T getElement()
    {
        if (hasElement())
        {
            counter++;
            return *iterator++;
        }
        else
            std::cerr << "no more elements";
        return 0;
    };
    void getMultiple(int number);

    T operator()() { return getElement(); };
    DataSource &operator>>(std::ostream &destination)
    {
        destination << getElement();
        return *this;
    };
    operator bool() { return hasElement(); };

public:
    Iterator<T> begin() { return Iterator<T>(&Data[counter]); };

    Iterator<T> end() { return Iterator<T>(&Data[Data.getSize()]); };

    DataSource()
    {
        iterator = begin();
        bound = end();
    };
    DataSource(T *base, int lenght)
    {
        Data = Stack(base, lenght);
        iterator = begin();
        bound = end();
    };
    virtual ~DataSource() = default;

protected:
    Stack<T> Data;
    Iterator<T> iterator;
    Iterator<T> bound;
    int counter = 0;
};

template <typename T>
inline void DataSource<T>::getMultiple(int number)
{
    for (size_t i = 0; i < number; i++)
    {
        if (!hasElement())
            break;
        getElement();
    }
}

#endif