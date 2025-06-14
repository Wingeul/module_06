#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
    std::cout << "ScalarConverter default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const std::string input) : _input(input)
{
    std::cout << "ScalarConverter parameterized constructor called with input: " << input << std::endl;
    convert(input);
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

bool checkInput(const std::string &input)
{
    if (input.compare("nan") == 0 || input.compare("inf") == 0 || input.compare("-inf") == 0)
    {
        std::cout << "Input is a special floating-point value: " << input << std::endl;
        return false;
    }
    if (input.find_last_of("f") != std::string::npos && input.find_last_of("f") != input.length() - 1)
    {
        std::cout << "Invalid input" << std::endl;
        return false;
    }
    if (input.find_first_of(".") != std::string::npos)
    {
        unsigned long dotposition = input.find_first_of(".");
        if (dotposition == 0 || dotposition == input.length() - 1)
        {
            std::cout << "Invalid Decimal" << std::endl;
            return false;
        }
        if (isdigit(input[dotposition - 1]) == false || isdigit(input[dotposition + 1]) == false)
        {
            std::cout << "Invalid Decimal" << std::endl;
            return false;
        }
    }
    if (input.find_last_of("+-") != std::string::npos && input.find_last_of("+-") != 0)
    {
        std::cout << "Invalid input" << std::endl;
        return false;
    }
    if (input.length() > 1 && input.find_first_not_of("0123456789.f") != std::string::npos)
    {
        std::cout << "Invalid input" << std::endl;
        return false;
    }
    return true;
}

void ScalarConverter::convert(const std::string &input)
{
    if (!checkInput(input))
        return;
    try
    {
        convertToDouble(input);
        convertToInt();
        convertToChar(input);
        convertToFloat();
    }
    catch (const ConversionError &e)
    {
        throw ConversionError();
    }
    this->printValues();
}

void ScalarConverter::printValues() const
{
    if (!isprint(_charValue))
        std::cout << "Char: Non displayable" << std::endl;
    else
        std::cout << "Char: " << _charValue << std::endl;
    std::cout << "Int: " << _intValue << std::endl;
    std::cout << "Float: " << _floatValue;
    if (_floatValue - _intValue == 0)
        std::cout << ".0f" << std::endl;
    else
        std::cout << "f" << std::endl;
    std::cout << "Double: " << _doubleValue;
    if (_floatValue - _intValue == 0)
        std::cout << ".0" << std::endl;
    else
        std::cout << std::endl;
}

void ScalarConverter::convertToChar(const std::string &input)
{
    if (input.length() == 1 && !std::isdigit(input[0]))
    {
        _charValue = input[0];
        _intValue = static_cast<int>(_charValue);
        _floatValue = static_cast<float>(_charValue);
        _doubleValue = static_cast<double>(_charValue);
        return;
    }
    else
        _charValue = static_cast<unsigned char>(_intValue);
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
        std::cout << _doubleValue << std::endl;
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
        _doubleValue = atof(input.c_str());
    }
    catch (const std::exception &e)
    {
        throw ConversionError();
    }
}
