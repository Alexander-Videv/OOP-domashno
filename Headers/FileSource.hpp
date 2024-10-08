#include "DataSource.hpp"
#include <cstring>
#include <fstream>

#ifndef FILE__SOURCE__HPP
#define FILE__SOURCE__HPP

template <typename T>
class FileSource : public DataSource<T>
{
public:
    bool reset() override;
    bool hasNext() const override;
    T getElement() override;
    void getAll(std::ostream &output);

    FileSource(const std::string &fileName);
    ~FileSource() { file.close(); };

    FileSource(FileSource<T> const &other) = delete;
    FileSource<T> &operator=(FileSource<T> const &other) = delete;

    FileSource(FileSource<T> &&other) = delete;
    FileSource<T> &operator=(FileSource<T> &&other) = delete;

private:
    std::ifstream file;
};

template <typename T>
inline bool FileSource<T>::reset()
{
    try
    {
        file.seekg(std::ios::beg);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    };
    return true;
}

template <typename T>
inline bool FileSource<T>::hasNext() const
{
    return (file.good());
};

template <typename T>
inline T FileSource<T>::getElement()
{
    int currPos = file.tellg();
    char *temp;
    file.getline(temp, 999, ' ');
    char *ptr = &(temp[strlen(temp)]);
    try
    {
        T(temp);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        file.seekg(currPos);
        return 0;
    }

    return T(temp);
}
template <typename T>
inline void FileSource<T>::getAll(std::ostream &output)
{
    while (this->hasNext())
        *this >> output;
};

template <typename T>
inline FileSource<T>::FileSource(const std::string &fileName)
{
    try
    {
        file.open(fileName);
        if (!file.good())
            throw std::invalid_argument("File is not open!");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
};

// integer specialisation
template <>
inline int FileSource<int>::getElement()
{
    int currPos = file.tellg();
    char temp = file.get();
    int result = 0;
    while (!isspace(temp))
    {
        result *= 10;
        try
        {
            result += atoi(&temp);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            file.seekg(currPos);
            throw;
        }
        temp = file.get();
        if (temp == '\0' || file.eof())
        {
            file.setstate(std::ios::failbit);
            throw std::out_of_range("");
            break;
        }
    }
    return result;
};
// double specialisation
template <>
inline double FileSource<double>::getElement()
{
    int currPos = file.tellg();
    char temp = file.get();
    int counter = 0;
    while (!isspace(temp))
    {
        counter++;
        temp = file.get();
        if (temp == '\0' || file.eof())
            break;
    }
    char *buffer = new char[counter + 1];
    if (file.eof())
        file.clear();

    file.seekg(currPos);
    file.getline(buffer, counter + 1, ' ');
    char *ptr = &(buffer[strlen(buffer) - 1]);
    double result;
    try
    {
        result = std::strtod(buffer, &ptr);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        file.seekg(currPos);
        return -1;
    }
    delete buffer;
    return result;
};
// char token specialisation
template <>
inline char FileSource<char>::getElement()
{
    int currPos = file.tellg();
    char *tempPtr = nullptr;
    char temp = file.get();
    if (isspace(temp))
        return ' ';
    tempPtr = &temp;
    try
    {
        std::strtok(tempPtr, " ");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        file.seekg(currPos);
        return ' ';
    }

    return *std::strtok(tempPtr, " ");
};

#endif