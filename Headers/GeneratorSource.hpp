#include "DataSource.hpp"
#include "Generator.hpp"

#ifndef GENERATOR__SOURCE__HPP
#define GENERATOR__SOURCE__HPP

template <typename T>
class GeneratorSource : public DataSource<T>
{
public:
    T getElement() override;
    bool hasNext() const override;
    bool reset() override;

    template <typename... args>
    void addRule(bool (*func)(T), args &...other)
    {
        gen.addRule(func);
        addRule(other...);
    };

    void addRule() { return; }

    template <typename... args>
    GeneratorSource(T (*func)(), args... rules);

    ~GeneratorSource() = default;

private:
    Generator<T> gen;

    void setGen(T (*func)()) { this->gen.setGen(func); };
};

template <typename T>
template <typename... args>
inline GeneratorSource<T>::GeneratorSource(T (*func)(), args... rules) : gen(func)
{
    addRule(rules...);
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

#endif