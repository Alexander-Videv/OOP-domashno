#include "DataSource.hpp"
#include "Stack.hpp"
#include "Iterator.hpp"

template <typename T>
class AlternateSource : public DataSource<T>
{
private:
    Stack<DataSource<T> *> collection;
    Iterator<DataSource<T> *> current;
    Iterator<DataSource<T> *> bound;
    bool reset() override { return true; }
    void setBound();

public:
    bool hasNext() const override;
    T getElement() override;
    void push(DataSource<T> &data)
    {
        this->collection.push(&data);
        setBound();
    };

    AlternateSource() = default;
    ~AlternateSource() = default;
};

template <typename T>
inline void AlternateSource<T>::setBound()
{
    this->bound = &collection[collection.getSize()];
}

template <typename T>
inline bool AlternateSource<T>::hasNext() const
{
    for (size_t i = 0; i < collection.getCapacity(); i++)
        if (this->collection[i]->hasNext())
            return true;
    return false;
}

template <typename T>
inline T AlternateSource<T>::getElement()
{
    if (!hasNext())
        return 0;
    for (size_t i = 0; i < collection.getSize(); i++)
        if (this->collection[i]->hasNext())
            return this->collection[i]->getElement();
    return 0;
}
