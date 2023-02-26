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

#include "stack_test.hpp"
#include <string>
#include <ostream>
#include <iostream>

void stack_test() {
    int k[6] = {1, 2, 3, 4, 5 };

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

    std::cout << ">>> Operands" << std::endl;
    operator_m<int>(k);
    operator_m<std::string>(p);
    std::cout << "------------------------" << std::endl;
}
