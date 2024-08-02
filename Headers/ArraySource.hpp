#include "Stack.hpp"
#include "Iterator.hpp"
#include "DataSource.hpp"

template <typename T>
class ArraySource : public DataSource<T>
{
private:
    Stack<T> array;
    int counter = 0;
    Iterator<T> current;
    Iterator<T> bound;

    void setBound();

public:
    bool hasNext() const override
    {
        if (current != bound)
            return true;
        else
            return false;
    };
    T getElement() override
    {
        if (hasNext())
        {
            counter++;
            return *current++;
        }
        else
        {
            // throw std::out_of_range("No more elements.");
            return -1;
        }
    };

    bool reset() override
    {
        this->current = &array[0];
        return true;
    };

    void operator+(T element)
    {
        this->array.push(element);
        setBound();
        current = &array[counter];
    };
    void operator+=(T element)
    {
        this->array.push(element);
        setBound();
        current = &array[counter];
    };

    // Prefix decrement
    void operator--()
    {
        if (current == &array[0])
            return;

        this->current--;
        counter--;
    };

    // Postfix decrement
    void operator--(int)
    {
        if (current == &array[0])
            return;
        --this->current;
        counter--;
    };

    ArraySource(T *base, int lenght);
    ~ArraySource() = default;
};

template <typename T>
inline void ArraySource<T>::setBound()
{
    this->bound = &array[array.getSize()];
}

template <typename T>
inline ArraySource<T>::ArraySource(T *base, int lenght)
{
    for (size_t i = 0; i < lenght; i++)
        array.push(base[i]);
    setBound();
    current = &array[0];
}
