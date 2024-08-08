#include "DataSource.hpp"
#include "Stack.hpp"
#include "Iterator.hpp"

template <typename T>
class AlternateSource : public DataSource<T>
{
private:
    Stack<DataSource<T> *> collection;
    Stack<bool> map;
    Iterator<DataSource<T> *> first;
    Iterator<DataSource<T> *> bound;
    int counter = 0;
    bool reset() override { return true; }
    void setBound();
    void setFirst();
    bool checkMap() const;
    void fixMap();

public:
    bool hasNext() const override;
    T getElement() override;
    void push(DataSource<T> &data)
    {
        if (&data == nullptr)
            return;

        this->collection.push(&data);

        map.push(data.hasNext());

        setBound();
        setFirst();
    };

    AlternateSource();
    AlternateSource(DataSource<T> **DataArray, int lenght);
    ~AlternateSource() = default;
};

template <typename T>
inline void AlternateSource<T>::setBound()
{
    this->bound = &collection[collection.getSize()];
}

template <typename T>
inline void AlternateSource<T>::setFirst()
{
    first = &collection[0];
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
        return 0;
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
inline AlternateSource<T>::AlternateSource()
{
    setBound();
    setFirst();
}

template <typename T>
inline AlternateSource<T>::AlternateSource(DataSource<T> **DataArray, int lenght)
{
    for (size_t i = 0; i < lenght; i++)
    {
        this->collection.push(DataArray[i]);
        map.push(DataArray[i]->hasNext());
    }
    setBound();
    setFirst();
}
