#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const std::string input) : _input(input)
{
    _specialValues = "";
    convert(input);
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
    *this = other;
    this->printValues();
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
    if (this != &other)
    {
        _specialValues = other._specialValues;
        _charValue = other._charValue;
        _intValue = other._intValue;
        _floatValue = other._floatValue;
        _doubleValue = other._doubleValue;
    }
    return *this;
}

bool ScalarConverter::checkInput(const std::string &input)
{
    if (input.compare("nan") == 0 || input.compare("+inf") == 0 || input.compare("-inf") == 0
        || input.compare("+inff") == 0 || input.compare("-inff") == 0)
    {
        _specialValues = input;
        this->printValues();
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
    printChar();
    printInt();
    printFloat();
    printDouble();
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

void ScalarConverter::printChar(void) const
{
    std::cout << "Char: ";
    if (!isprint(_charValue))
        std::cout << "Non displayable" << std::endl;
    else if (_specialValues != "")
        std::cout << "impossible" << std::endl;
    else
        std::cout << _charValue << std::endl;
}

void ScalarConverter::printInt(void) const
{
    std::cout << "Int: ";
    if (_doubleValue <= int_min || _doubleValue >= int_max)
        std::cout << "out of bounds" << std::endl;
    else if (_specialValues != "")
        std::cout << "impossible" << std::endl;
    else
        std::cout << _intValue << std::endl;
}

void ScalarConverter::printFloat(void) const
{
    std::cout << "Float: ";
    if (_specialValues.compare("nan") == 0)
        std::cout << "nanf" << std::endl;
    else if (_specialValues.compare("+inf") == 0 || _specialValues.compare("+inff") == 0)
        std::cout << "+inff" << std::endl;
    else if (_specialValues.compare("-inf") == 0 || _specialValues.compare("-inff") == 0)
        std::cout << "-inff" << std::endl;
    else if (_floatValue - _intValue == 0)
        std::cout << _floatValue << ".0f" << std::endl;
    else
        std::cout << _floatValue << "f" << std::endl;
}

void ScalarConverter::printDouble(void) const
{
    std::cout << "Double: ";
    if (_specialValues.compare("nan") == 0)
        std::cout << "nan" << std::endl;
    else if (_specialValues.compare("+inf") == 0 || _specialValues.compare("+inff") == 0)
        std::cout << "+inf" << std::endl;
    else if (_specialValues.compare("-inf") == 0 || _specialValues.compare("-inff") == 0)
        std::cout << "-inf" << std::endl;
    else if (_floatValue - _intValue == 0)
        std::cout << _doubleValue << ".0" << std::endl;
    else
        std::cout << _doubleValue << std::endl;
}
