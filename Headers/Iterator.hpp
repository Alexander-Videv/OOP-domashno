#ifndef ITERATOR_HPP
#define ITERATOR_HPP

template <typename T>
class Iterator
{
private:
    T *ptr = nullptr;

public:
    T operator*() const { return *ptr; };
    T *operator->() { return ptr; };

    // Prefix increment
    Iterator &operator++()
    {
        ptr++;
        return *this;
    };

    // Postfix increment
    Iterator operator++(int)
    {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    };
    // Prefix decrement
    Iterator &operator--()
    {
        ptr--;
        return *this;
    };

    // Postfix decrement
    Iterator operator--(int)
    {
        Iterator tmp = *this;
        --(*this);
        return tmp;
    };

    friend bool operator==(const Iterator &a, const Iterator &b) { return a.ptr == b.ptr; };
    friend bool operator!=(const Iterator &a, const Iterator &b) { return a.ptr != b.ptr; };

public:
    Iterator() = default;
    Iterator(T *object) { ptr = object; };
    ~Iterator() = default;
};

#endif