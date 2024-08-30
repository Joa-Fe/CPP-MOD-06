/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joannpdetorres <joannpdetorres@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:18:18 by joannpdetor       #+#    #+#             */
/*   Updated: 2024/07/28 17:18:24 by joannpdetor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int main(int argc, char *argv[])
{
    if ( argc != 2 )
    {
        std::cerr << "Error: enter only ./convert 'literal' \n";
        return (1);
    }
    try
    {
        std::string value(argv[1]);
        ScalarConverter::convert(value);
    }
    catch (std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return (0);
}