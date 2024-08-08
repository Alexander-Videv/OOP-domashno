#include "ArraySource.hpp"
#include "AlternateSource.hpp"
#include "DefaultSource.hpp"
#include "FileSource.hpp"
#include "GeneratorSource.hpp"

enum class TYPE
{
    GENERATOR,
    FILE,
    ALTERNATE,
    ARRAY,
    DEFAULT,
    INVALID
};

template <typename GenType, typename... args>
std::enable_if_t<std::is_constructible<GenType, args...>::value, GenType *>
CreateGenerator(args &&...arguments)
{
    return new GenType(std::forward<args>(arguments)...);
}
template <typename GenType, typename... args>
std::enable_if_t<!std::is_constructible<GenType, args...>::value, GenType *>
CreateGenerator(args &&...arguments)
{
    return nullptr;
}

template <typename T, typename... args>
DataSource<T> *Factory(TYPE type, args... parameters)
{
    // TYPE type = parse<T>(parameters...);
    switch (type)
    {
    case TYPE::GENERATOR:
        return CreateGenerator<GeneratorSource<T>>(std::forward<args>(parameters)...);
        break;

    case TYPE::FILE:
        return CreateGenerator<FileSource<T>>(std::forward<args>(parameters)...);
        break;

    case TYPE::ALTERNATE:
        return CreateGenerator<AlternateSource<T>>(std::forward<args>(parameters)...);
        break;

    case TYPE::ARRAY:
        return CreateGenerator<ArraySource<T>>(std::forward<args>(parameters)...);
        break;

    case TYPE::DEFAULT:
        return CreateGenerator<DefaultSource<T>>(std::forward<args>(parameters)...);
        break;

    default:
        throw std::invalid_argument("Unable to create source.");
        break;
    }
}

// template <typename T, typename... args>
// TYPE parse(args... parameters)
// {
//     if (parameters...[0] == T(*)())
//         return TYPE::GENERATOR;
//     if (typeid(parameters..[0]) == typeid(const char *))
//         return TYPE::FILE;
//     if (typeid(parameters...[0]) == typeid(DataSource<T> **))
//         return TYPE::ALTERNATE;
//     if (typeid(parameters...[0]) == typeid(T *))
//         return TYPE::ARRAY;
//     try
//     {
//         DataSource<T>(parameters...);
//         return TYPE::DEFAULT;
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     return TYPE::INVALID;
// }