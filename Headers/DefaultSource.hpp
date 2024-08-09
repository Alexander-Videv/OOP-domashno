#include "DataSource.hpp"

#ifndef DEFAULT__SOURCE__HPP
#define DEFAULT__SOURCE__HPP

template <typename T>
class DefaultSource : public DataSource<T>
{
private:
public:
    bool hasNext() const override { return true; };
    bool reset() override { return false; }

    template <typename... args>
    T getElement(args...);

    T getElement() override { return T(); }

    DefaultSource() = default;
    ~DefaultSource() = default;
};

template <typename T>
template <typename... args>
inline T DefaultSource<T>::getElement(args... input)
{
    return T(input...);
}

#endif