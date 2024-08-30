/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:14:40 by joannpdetor       #+#    #+#             */
/*   Updated: 2024/08/29 17:25:15 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <cctype>
# include <limits>
# include <iomanip>
# include <exception>

enum type
{
    NONE,
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    FLOATPSEUDO,
    DOUBLEPSEUDO,
};

typedef struct
{
    char        charScalar;
    int         intScalar;
    float       floatScalar;
    double      doubleScalar;
    std::string msgScalar[4];
} scalar;

class ScalarConverter
{
    public :
        static void convert(std::string value);

    private :
        ScalarConverter();
        ScalarConverter(const ScalarConverter& other);
        ScalarConverter& operator=(const ScalarConverter& other);
        ~ScalarConverter();

        //detect the type of literal
        static type detectType(std::string &value);
        
        //convert
        static void convertToDouble(std::string value, type literal);
        static void convertToChar(type literal);
        static void convertToInt(type literal);
        static void convertToFloat(std::string value, type literal);

        //check overflow
        static bool isOverflow(type literal);

        //set conversions
        static scalar _results;
        static void setScalarConversions(std::string valu, type literal);

        //display conversions
        static void displayConversion();
};

#endif