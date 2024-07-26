#include "DataSource.hpp"

template <typename T>
class AlternateSource : public DataSource<DataSource<T> *>
{
private:
    bool reset() override { return true; }

public:
    bool hasElement();
    T getElement();
    void push(DataSource<T> &data) { this->Data.push(&data); };

    AlternateSource() = default;
    ~AlternateSource() = default;
};

template <typename T>
inline bool AlternateSource<T>::hasElement()
{
    for (size_t i = 0; i < this->Data.getCapacity(); i++)
        if (this->Data[i].hasElement())
            return true;
    return false;
}

template <typename T>
inline T AlternateSource<T>::getElement()
{
    if (!hasElement)
        return 0;
    for (DataSource<T> *i = this->iterator; i < this->bound; i++)
        if (this->Data[i].hasElement())
            return this->Data[i].getElement();
    return 0;
}
