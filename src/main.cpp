/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 14:48:43 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/10 00:11:39 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_test.hpp"
#include "utility.hpp"
#include <utility>
#include <string>
#include <ostream>
#include <iostream>

#include "map.hpp"
#include <map>

int main() {
    int k[6] = {1, 10, 12, 13, 14, 15};
    std::string p[6] = {std::string("aaaa"),
        std::string("bbbb"),
        std::string("cccc"),
        std::string("dddd"),
        std::string("eeee"),
        std::string("ffff")};
    ft::pair<int, std::string> ft_pair_list[6];
    std::pair<int, std::string> pair_list[6];
    for (int i = 0; i < 6; i++) {
        ft_pair_list[i] = ft::pair<int, std::string>(k[i], p[i]);
        pair_list[i] = std::pair<int, std::string>(k[i], p[i]);
    }
    ft::map<int, std::string> ft_m;

    ft_m.insert(ft_pair_list[0]);
    ft_m.insert(ft_pair_list[1]);
    ft_m.insert(ft_pair_list[2]);

    /*
    std::cout << "Initialization Test" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Basic push pop test" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Iterator test" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Insertion and erase test" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Swap" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Element access" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Operands" << std::endl;
    std::cout << "------------------------" << std::endl;
    */

    return (0);
}
