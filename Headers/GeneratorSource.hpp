#include "DataSource.hpp"
#include "Generator.hpp"

template <typename T>
class GeneratorSource : public DataSource<T>
{
private:
    Generator<T> gen;

public:
    T getElement() override;
    bool hasNext() const override;
    bool reset() override;

    void addRule(bool (*func)(T)) { gen.addRule(func); };

    GeneratorSource(T (*func)());

    ~GeneratorSource() = default;
};

template <typename T>
inline GeneratorSource<T>::GeneratorSource(T (*func)()) : gen(func)
{
}

template <typename T>
inline T GeneratorSource<T>::getElement()
{
    return gen.generate();
}

template <typename T>
inline bool GeneratorSource<T>::hasNext() const
{
    return gen.getFlag();
}

template <typename T>
inline bool GeneratorSource<T>::reset()
{
    return false;
}
