#include "Headers/ArraySource.hpp"
#include "Headers\AlternateSource.hpp"

int main()
{

    int array[5] = {1, 2, 3, 4, 5};

    ArraySource<int> mySource(array, 5);

    // mySource >> std::cout >> std::cout >> std::cout >> std::cout >> std::cout;

    // mySource += 89;
    // mySource + 102;

    // std::cout << mySource.hasElement();

    // mySource >> std::cout >> std::cout >> std::cout;

    // mySource--;

    // --mySource;

    // mySource >> std::cout >> std::cout;

    AlternateSource<int> alternate;

    alternate.push(mySource);

    mySource--;
    mySource--;

    alternate >> std::cout;

    return 0;
}