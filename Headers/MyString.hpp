#include <cstring>
#include <iostream>

#ifndef MY__STRING__HPP
#define MY__STRING__HPP

class MyString
{
public:
    MyString() { generate(); };
    ~MyString() = default;

private:
    std::string word;

    void generate()
    {
        while (word.length() < 10)
            word += (char((rand() % 26 + 1) + 96));
    }

    friend std::ostream &operator<<(std::ostream &output, const MyString &input)
    {
        output << input.word;
        return output;
    };
};

#endif