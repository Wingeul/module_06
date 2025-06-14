#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP
#include <iostream>
#include <string>
#include <cstdlib>
#include <exception>
#include <climits>
#include <limits>

#define int_min std::numeric_limits<int>::min()
#define int_max std::numeric_limits<int>::max()

class ScalarConverter {
public:
    ScalarConverter(const std::string input);
    ~ScalarConverter();
    ScalarConverter(const ScalarConverter &other);
    ScalarConverter &operator=(const ScalarConverter &other);

    const std::string &getInput(void) const { return _input; }
    void printValues() const;


    void convert(const std::string &input);

private:

    ScalarConverter();

    const std::string _input;
    std::string _specialValues;
    char _charValue;
    int _intValue;
    float _floatValue;
    double _doubleValue;

    bool checkInput(const std::string &input);

    void convertToChar(const std::string &input);
    void convertToInt(void);
    void convertToFloat(void);
    void convertToDouble(const std::string &input);

    char getCharValue(void) const { return _charValue; }
    int getIntValue(void) const { return _intValue; }
    float getFloatValue(void) const { return _floatValue; }
    double getDoubleValue(void) const { return _doubleValue; }

    void printChar(void) const;
    void printInt(void) const;
    void printFloat(void) const;
    void printDouble(void) const;

    class ConversionError : public std::exception
    {
        public:
            virtual const char *what() const throw()
            {    
                return "Conversion error: Invalid input";
            }
    };
};

#endif