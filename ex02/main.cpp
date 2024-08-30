/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jp-de-to <jp-de-to@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:56:45 by joannpdetor       #+#    #+#             */
/*   Updated: 2024/08/30 21:05:03 by jp-de-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base * generate(void)
{
    int random = rand() % 3;
    if (random == 0)
        return new A;
    if (random == 1)
        return new B;
    return new C;
}

void identify(Base* p)
{
    if (p == NULL)
    {
        std::cerr << "Pointer is null, unable to determine the type.\n";
        return;
    }
    if (dynamic_cast<A*>(p))
        std::cout << "A\n";
    else if (dynamic_cast<B*>(p))
        std::cout << "B\n";
    else if (dynamic_cast<C*>(p))
        std::cout << "C\n";
}

void identify(Base& p) 
{
	
    try {
        A &a = dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        (void) a;
    } catch (std::exception &e) {
        try {
            B &b = dynamic_cast<B&>(p);
            std::cout << "B" << std::endl;
            (void) b;
        } catch (std::exception &e) {
            try {
                C &c = dynamic_cast<C&>(p);
                std::cout << "C" << std::endl;
                (void) c;
            } catch (std::exception &e) {
                std::cout << "Unknown type" << std::endl;
            }
        }
    }
}

int main() 
{
	srand(time(NULL));
    for (int i = 0; i < 5; ++i) 
    {
        Base* basePtr = generate();
        std::cout << "Pointer identification: ";
        identify(basePtr);

        std::cout << "Reference identification: ";
        identify(*basePtr);
        std::cout << "\n";
        delete (basePtr); 
    }

    return 0;
}