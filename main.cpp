#include "Headers/Factory.hpp"
#include "Headers/MyString.hpp"
#include <cmath>

bool isPrime(int number)
{
    if (number < 2)
        return false;
    if (number == 2 || number == 3)
        return true;
    for (size_t i = 2; i <= number / 2; i++)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

int getNextPrime()
{
    static int current = 0;
    while (!isPrime(++current))
    {
    }

    return current;
}

bool max25(int a)
{
    static int intcount = 0;
    intcount++;
    return intcount < 25;
}

int getFibonnacci()
{
    int fib[25]{
        0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368};

    static int *ptr = &fib[0];
    return *ptr++;
}

int main()
{
    DefaultSource<MyString> strings;

    strings.printMultiple(25, std::cout);

    std::ofstream binfile("binaryNumbers.bin", std::ios_base::binary);
    if (!binfile.good())
        return -1;

    DataSource<int> *array[3] = {Factory<int>(TYPE::GENERATOR, getNextPrime), Factory<int>(TYPE::GENERATOR, rand), Factory<int>(TYPE::GENERATOR, getFibonnacci, max25)};

    AlternateSource<int> numbers(array, 3);

    numbers.printMultiple(1000, binfile);

    binfile.close();

    std::ifstream readBin("binaryNumbers.bin");
    if (!readBin.good())
        return -1;
    std::fstream convert("binaryNumbers.txt", std::ios::out | std::ios::trunc);
    if (!convert.good())
        return -1;
    int value;

    while (readBin >> value)
        convert << value << " ";

    readBin.close();
    convert.close();

    FileSource<int> numFIle("binaryNumbers.txt");

    numFIle.getAll(std::cout);
}