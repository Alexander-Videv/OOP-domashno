#include "Stack.hpp"

template <typename T>
class Generator
{
private:
    T(*gen)
    ();

    Stack<bool (*)(T), 10> rules;
    T last;
    bool flag = false;

public:
    Generator(T (*gen)());
    ~Generator() = default;

    Generator(Generator &other) { this->gen = other.gen; }
    Generator operator=(Generator &other) { this->gen = other.gen; }

    void addRule(bool (*rule)(T));
    T generate();
    bool canGenerate() const;
    void setGen(T (*gen)()) { this->gen = gen; };
    void setFlag() { flag = canGenerate(); }
    bool getFlag() const { return flag; };
};

template <typename T>
inline T Generator<T>::generate()
{
    if (flag)
    {
        setFlag();
        last = gen();
        return last;
    }
    else
        return 0;
}

template <typename T>
inline Generator<T>::Generator(T (*gen)())
{
    this->gen = gen;
    flag = true;
}

template <typename T>
inline void Generator<T>::addRule(bool (*rule)(T))
{
    rules.push(rule);
}

template <typename T>
inline bool Generator<T>::canGenerate() const
{
    if (!flag)
        return flag;
    if (rules)
    {
        for (size_t i = 0; i < rules.getSize(); i++)
            if (!(rules[i](last)))
                return false;
    }
    return flag;
}
