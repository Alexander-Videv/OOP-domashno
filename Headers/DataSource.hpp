#include <iostream>
#include <stdexcept>

#ifndef DATA_SOURCE_HPP
#define DATA_SOURCE_HPP

template <typename T>
class DataSource
{
private:
public:
    DataSource() = default;
    virtual ~DataSource() = default;

    virtual bool hasNext() const = 0;
    virtual T getElement() = 0;
    virtual void printMultiple(int number, std::ostream &output);
    virtual bool reset() = 0;

    virtual T operator()();
    virtual DataSource &operator>>(std::ostream &output);
    virtual operator bool();
};

template <typename T>
inline void DataSource<T>::printMultiple(int number, std::ostream &output)
{
    for (size_t i = 0; i < number; i++)
        if (hasNext())
            *this >> output;
        else
            break;
}

template <typename T>
inline T DataSource<T>::operator()()
{
    return getElement();
}

template <typename T>
inline DataSource<T> &DataSource<T>::operator>>(std::ostream &output)
{
    try
    {
        output << getElement() << " ";
    }
    catch (const std::exception &e)
    {
    }

    return *this;
}

template <typename T>
inline DataSource<T>::operator bool()
{
    return hasNext();
}

#endif