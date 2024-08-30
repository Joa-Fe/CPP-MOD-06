/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joannpdetorres <joannpdetorres@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:11:26 by joannpdetor       #+#    #+#             */
/*   Updated: 2024/07/29 22:10:03 by joannpdetor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

void testSerialization(Data* data) 
{
    uintptr_t serializedData = Serializer::serialize(data);
    Data* deserializedData = Serializer::deserialize(serializedData);

    std::cout << BOLD <<"Original Data Address: " << data << std::endl;
    std::cout << "Serialized Data Address: " << serializedData << std::endl;
    std::cout << "Deserialized Data Address: " << deserializedData << std::endl << std::endl;

    if (data == deserializedData) {
        std::cout << BOLD << GREEN <<"Test passed. Pointers match." << std::endl;
        std::cout << "Number: " << deserializedData->number << ", Name: " << deserializedData->name << NC << std::endl << std::endl;
    } else {
        std::cout << BOLD << RED <<"Test failed. Pointers do not match." << NC << std::endl << std::endl;
    }
}

int main() 
{
    Data data1 = {2024, "JEUX OLYMPIQUES"};
    std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
    std::cout << BOLD << YELLOW << "\nTest Case 1: Basic test with a normal Data object\n\n" << NC;
    
    testSerialization(&data1);

    Data data2 = {10, ""};
    std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
    std::cout << BOLD << YELLOW << "\nTest Case 2: Data object with empty string\n\n" << NC;
    testSerialization(&data2);

    Data data3 = {2147483647, "Max Int"};
    std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
    std::cout << BOLD << YELLOW << "\nTest Case 3: Data object with large integer value\n\n" << NC;
    testSerialization(&data3);

    Data data4 = {100, "!@#$%^&*()_+|"};
    std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
    std::cout << BOLD << YELLOW << "\nTest Case 4: Data object with special characters in the string\n\n" << NC;
    
    testSerialization(&data4);

    std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
    std::cout << BOLD << YELLOW << "\nTest Case 5:  Null pointer case\n\n" << NC;
    Data* nullData = NULL;
    uintptr_t serializedNull = Serializer::serialize(nullData);
    Data* deserializedNull = Serializer::deserialize(serializedNull);
    if (deserializedNull == NULL) {
        std::cout << GREEN << "Test passed. Null pointers handled correctly." << NC <<std::endl;
    } else {
        std::cout << RED << "Test failed. Null pointer handling error." << NC << std::endl;
    }
    std::cout << "\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
    return 0;
}