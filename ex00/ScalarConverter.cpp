/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:18:29 by joannpdetor       #+#    #+#             */
/*   Updated: 2024/08/29 17:26:56 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

scalar      ScalarConverter::_results;

// constructors, destructor & operator /////////////////////////////////////////////////////////////////////

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) { (void)other; return *this; }
ScalarConverter::~ScalarConverter() {} 

// detect the type of literal /////////////////////////////////////////////////////////////////////////////

type ScalarConverter::detectType(std::string &value)
{
    // check if value = empty
    if (value.empty())
        return (NONE);
    // detect if value = char
    if (value.size() == 3 && value[0] == '\'' && value[2] == '\'')
        return (value = value[1], CHAR);
    //detect if value = pseudo literal
    std::string floatPseudo[3] = {"+inff", "-inff", "nanf"};
    std::string doublePseudo[3] = {"+inf", "-inf", "nan"};
    for (int i = 0; i < 3; ++i)
    {
        if (value == floatPseudo[i])
            return (FLOATPSEUDO);
        if (value == doublePseudo[i])
            return (DOUBLEPSEUDO);
    }
    // detect if value = int or float or double
    std::string tmp = value;
    if (tmp[0] == '+' || tmp[0] == '-')
        tmp.erase(0, 1);
    int decOrExp = 0;
    for (std::size_t i = 0; i < tmp.size(); ++i)
    {
        if (i == tmp.size() - 1 && decOrExp == 1 && std::isdigit(tmp[i - 1]) && (tmp[i] == 'f' || tmp[i] == 'F')) // check if it is a float
            return (value.erase(value.size()-1, 1), FLOAT);
        if (i > 0 && (tmp[i] == '.' || tmp[i] == 'e'))
        {
            decOrExp++;
            if (decOrExp > 1)
                return (NONE);
            if (tmp[i] == 'e' && tmp[i + 1] && (tmp[i + 1] == '-' || tmp[i + 1] == '+'))
                i++;
        }
        else if (!std::isdigit(tmp[i]))
            return (NONE);
    }
    if (decOrExp == 0)
        return (INT);
    return (DOUBLE);
}

// overflow ////////////////////////////////////////////////////////////////////////////////////////////

bool ScalarConverter::isOverflow(type literal)
{
    if (literal == CHAR)
    {
        return (_results.doubleScalar < std::numeric_limits<char>::min() || 
                _results.doubleScalar > std::numeric_limits<char>::max());
    }
    else if (literal == INT)
    {
        return (_results.doubleScalar < std::numeric_limits<int>::min() || 
                _results.doubleScalar > std::numeric_limits<int>::max());
    }
    else if (literal == FLOAT)
    {
        // Vérifie si la valeur est en dehors des limites de float
        return (_results.doubleScalar < -std::numeric_limits<float>::max() || 
                _results.doubleScalar > std::numeric_limits<float>::max() ||
                (_results.doubleScalar > 0 && _results.doubleScalar < std::numeric_limits<float>::min()) || 
                (_results.doubleScalar < 0 && _results.doubleScalar > -std::numeric_limits<float>::min()));
    }
    // Ajouter un cas par défaut ou lancer une exception si le type est invalide
    return false;
}

// convert /////////////////////////////////////////////////////////////////////////////////////////////

void ScalarConverter::convertToDouble(std::string value, type literal)
{
    switch (literal)
    {
        case DOUBLEPSEUDO:
            _results.msgScalar[3] = value;
            break;
        case FLOATPSEUDO:
            value.erase(value.size()-1, 1);
            _results.msgScalar[3] = value;
            break;
        case CHAR:
            _results.doubleScalar = static_cast<double>(value[0]);
            break;
        default:
            try {
                std::stringstream ss(value);
				double result;
				if (!(ss >> result))
					throw(std::invalid_argument("conversion in double failed"));
				_results.doubleScalar = result;
            } 
            catch(const std::out_of_range& e) {
                throw (std::exception());
            }
            break;
    }
}

void ScalarConverter::convertToChar(type literal)
{
    if (literal == FLOATPSEUDO || literal == DOUBLEPSEUDO || isOverflow(CHAR) == true)
        _results.msgScalar[0] = "impossible";
    else 
    {
        _results.charScalar = static_cast<char>(_results.doubleScalar);
        if (!std::isprint(_results.charScalar))
            _results.msgScalar[0] = "non displayable";
    }
}

void ScalarConverter::convertToInt(type literal)
{
    if (literal == FLOATPSEUDO || literal == DOUBLEPSEUDO || isOverflow(INT) == true)
        _results.msgScalar[1] = "impossible";
    else
        _results.intScalar = static_cast<int>(_results.doubleScalar);
}

void ScalarConverter::convertToFloat(std::string value, type literal)
{
    switch (literal)
    {
        case DOUBLEPSEUDO:
            value.push_back('f');
            _results.msgScalar[2] = value;
            break;
        case FLOATPSEUDO:
            _results.msgScalar[2] = value;
            break;
        default:
            if (isOverflow(FLOAT))
                _results.msgScalar[2] = "impossible";
            else 
                _results.floatScalar = static_cast<float>(_results.doubleScalar);
            break;
    }
}

// set conversions ///////////////////////////////////////////////////////////////////////////////

void ScalarConverter::setScalarConversions(std::string value, type literal)
{
    convertToDouble(value, literal);
    convertToChar(literal);
    convertToInt(literal);
    convertToFloat(value, literal);
}

// display conversions ///////////////////////////////////////////////////////////////////////////

void ScalarConverter::displayConversion()
{
    std::string scalar[4] = {"char: ", "int: ", "float: ", "double: "};
    
    for (int i = 0; i < 4; ++i)
    {
        std::cout << scalar[i];
        if (!_results.msgScalar[i].empty())
            std::cout << _results.msgScalar[i] << '\n';
        else
        {
            if (i == 0)
                std::cout << "'" << _results.charScalar << "'\n";
            else if (i == 1)
                std::cout << _results.intScalar << '\n';
            else if (i == 2)
                std::cout << std::fixed << std::setprecision(1) << _results.floatScalar << "f\n";
            else
                std::cout << std::fixed << std::setprecision(1) << _results.doubleScalar << '\n';
        }
    }
}

// MAIN FUNCTION ////////////////////////////////////////////////////////////////////////////////

void ScalarConverter::convert(std::string value)
{
    try {
        type literal = detectType(value);
        if (literal == NONE)
            throw std::exception();
        setScalarConversions(value, literal);
    }
    catch (std::exception &e) {
        for (int i = 0; i < 4; ++i) 
            _results.msgScalar[i] = "impossible";
    }
    displayConversion();
}
