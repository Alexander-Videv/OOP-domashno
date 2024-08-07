#include "Headers/ArraySource.hpp"
#include "Headers/AlternateSource.hpp"
#include "Headers/DefaultSource.hpp"
#include "Headers/FileSource.hpp"
#include "Headers/GeneratorSource.hpp"
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

    for (size_t i = 0; i < 25; i++)
        strings >> std::cout;

    std::ofstream binfile("binaryNumbers.bin", std::ios_base::binary);

    GeneratorSource<int> fib(getFibonnacci);
    fib.addRule(max25);

    GeneratorSource<int> primes(getNextPrime);

    GeneratorSource<int> randos(rand);

    AlternateSource<int> numbers;
    numbers.push(primes);
    numbers.push(randos);
    numbers.push(fib);

    for (size_t i = 0; i < 1000; i++)
        numbers >> binfile;

    std::fstream convert("binaryNumbers.txt");
    convert.open("binaryNumbers.bat");
    FileSource<int> numFIle("binaryNumbers.txt");
    while (numFIle.hasNext())
        numFIle >> std::cout;
}