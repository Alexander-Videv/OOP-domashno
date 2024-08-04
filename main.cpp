#include "Headers/ArraySource.hpp"
#include "Headers/AlternateSource.hpp"
#include "Headers/DefaultSource.hpp"

int main()
{

    int array[5] = {1, 2, 3, 4, 5};

    ArraySource<int> mySource(array, 5);

    // mySource >> std::cout >> std::cout >> std::cout >> std::cout >> std::cout;

    // mySource += 89;
    // mySource + 102;

    // std::cout << std::boolalpha << mySource.hasNext();

    // mySource >> std::cout >> std::cout >> std::cout;

    // mySource--;

    // --mySource;

    // mySource >> std::cout >> std::cout;

    AlternateSource<int> alternate;
    DefaultSource<int> def;
    DefaultSource<int> def2;

    alternate.push(def);
    alternate.push(def2);

    alternate.push(mySource);

    alternate >> std::cout >> std::cout;
    alternate >> std::cout;

    alternate >> std::cout >> std::cout >> std::cout;

    return 0;
}