#include "DataSource.hpp"

template <typename T>
class ArraySource : public DataSource<T>
{
private:
    Iterator<T> first;

    void setBound();

public:
    bool reset() override
    {
        this->iterator = first;
        return true;
    };

    void operator+(T element)
    {
        this->Data.push(element);
        setBound();
        this->iterator = this->begin();
    };
    void operator+=(T element)
    {
        this->Data.push(element);
        setBound();
        this->iterator = this->begin();
    };

    // Prefix decrement
    void operator--()
    {
        this->iterator--;
    };

    // Postfix decrement
    void operator--(int)
    {
        --this->iterator;
    };

    ArraySource(T *base, int lenght) : DataSource<T>(base, lenght) { first = this->begin(); };
    ~ArraySource() = default;
};

template <typename T>
inline void ArraySource<T>::setBound()
{
    this->bound = &(this->Data[this->Data.getSize()]);
}
