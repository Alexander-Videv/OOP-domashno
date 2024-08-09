#include "ArraySource.hpp"
#include "AlternateSource.hpp"
#include "DefaultSource.hpp"
#include "FileSource.hpp"
#include "GeneratorSource.hpp"

#ifndef FACTORY__HPP
#define FACTORY__HPP

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

#endif