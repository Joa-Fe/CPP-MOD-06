/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:00:29 by joannpdetor       #+#    #+#             */
/*   Updated: 2024/08/29 17:20:09 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include <iostream>
# include <string>
# include "stdint.h"

# define BOLD "\033[1m"
# define HIGHLIGHT "\033[7m"
# define YELLOW "\033[1;33m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define NC "\033[0m"

typedef struct Data
{
    int             number;
    std::string     name;
} Data;

class Serializer
{
    public :
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);

    private :
        Serializer();
        Serializer(const Serializer& other);
        Serializer& operator=(const Serializer& other);
        ~Serializer();
};

#endif