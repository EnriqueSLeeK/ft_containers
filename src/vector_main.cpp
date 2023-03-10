/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 14:48:43 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/07 00:41:12 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_test.hpp"
#include <string>
#include <ostream>
#include <iostream>

void vector_test (){
    int k[6] = {1, 10, 12, 13, 14, 15};
    std::string p[6] = {std::string("aaaa"),
        std::string("bbbb"),
        std::string("cccc"),
        std::string("dddd"),
        std::string("eeee"),
        std::string("ffff")};

    std::cout << "Initialization Test" << std::endl;
    init_test_m<int>(k, 1);
    init_test_m<std::string>(p, std::string("test"));
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Basic push pop test" << std::endl;
    push_pop_test_m<int>(k);
    push_pop_test_m<std::string>(p);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Iterator test" << std::endl;
    iterator_test_m<int>(k);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Insertion and erase test" << std::endl;
    insert_erase_test_m<int>(k, 99999);
    insert_erase_test_m<std::string>(p, std::string("test"));
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Swap" << std::endl;
    swap_m<int>(k);
    swap_m<std::string>(p);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Element access" << std::endl;
    access_m<int>(k);
    access_m<std::string>(p);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Operands" << std::endl;
    operator_m<int>(k);
    operator_m<std::string>(p);
    std::cout << "------------------------" << std::endl;
}
