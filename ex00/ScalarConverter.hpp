#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP
#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>


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
    char _charValue;
    int _intValue;
    float _floatValue;
    double _doubleValue;

    void convertToChar(const std::string &input);
    void convertToInt(void);
    void convertToFloat(void);
    void convertToDouble(const std::string &input);

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