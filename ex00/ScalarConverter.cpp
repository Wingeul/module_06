#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
    std::cout << "ScalarConverter default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const std::string input) : _input(input)
{
    std::cout << "ScalarConverter parameterized constructor called with input: " << input << std::endl;
    convert(input);
    this->printValues();
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
    std::cout << "ScalarConverter copy constructor called" << std::endl;
    *this = other;
    this->printValues();
}

ScalarConverter::~ScalarConverter()
{
    std::cout << "ScalarConverter destructor called" << std::endl;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
    std::cout << "ScalarConverter assignment operator called" << std::endl;
    if (this != &other)
    {
        _charValue = other._charValue;
        _intValue = other._intValue;
        _floatValue = other._floatValue;
        _doubleValue = other._doubleValue;
    }
    return *this;
}

void ScalarConverter::convert(const std::string &input)
{
    try
    {
        convertToDouble(input);
        convertToInt();
        convertToChar(input);
        convertToFloat();
    }
    catch (const ConversionError &e)
    {
        std::cerr << e.what() << std::endl;
        return ;
    }
}

void ScalarConverter::printValues() const
{
    std::cout << "Char: " << _charValue << std::endl;
    std::cout << "Int: " << _intValue << std::endl;
    std::cout << "Float: " << _floatValue << std::endl;
    std::cout << "Double: " << _doubleValue << std::endl;
}

void ScalarConverter::convertToChar(const std::string &input)
{
    if (input.length() == 1 && !std::isdigit(input[0]))
    {
        _charValue = input[0];
        return;
    }
    if (_intValue < 0 || _intValue > 127)
        throw ConversionError();
    _charValue = static_cast<char>(_intValue);

    if (!std::isprint(_charValue))
        throw ConversionError();
}


void ScalarConverter::convertToInt(void)
{
    try
    {
        _intValue = static_cast<int>(_doubleValue);
    }
    catch (const std::exception &e)
    {
        throw ConversionError();
    }
}

void ScalarConverter::convertToFloat(void)
{
    try
    {
        _floatValue = static_cast<float>(_doubleValue);
    }
    catch (const std::exception &e)
    {
        throw ConversionError();
    }
}

void ScalarConverter::convertToDouble(const std::string &input)
{
    try
    {
        const char* str = input.c_str();
        char* endPtr = NULL;
        _doubleValue = std::strtod(str, &endPtr);
        if (endPtr == str || *endPtr != '\0')
        {
            throw ConversionError();
        }
    }
    catch (const std::exception &e)
    {
        throw ConversionError();
    }
}
