/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 14:48:43 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/15 23:27:30 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "map_test.hpp"
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

    ft::map<int, std::string> ft_map;
    std::map<int, std::string> std_map;

    ft_map.insert(ft_pair_list[0]);
    ft_map.insert(ft_pair_list[1]);
    ft_map.insert(ft_pair_list[2]);

    std_map.insert(pair_list[0]);
    std_map.insert(pair_list[1]);
    std_map.insert(pair_list[2]);

    ft::map<int, std::string>::iterator it = ft_map.begin();
    ft::map<int, std::string>::iterator end = ft_map.end();

    std::map<int, std::string>::iterator iit = std_map.begin();
    std::map<int, std::string>::iterator iend = std_map.end();

    for (ft::map<int, std::string>::iterator curr = it;
            curr != end; curr++) {
        std::cout << (*curr).second << std::endl;
    }

    for (std::map<int, std::string>::iterator curr = iit;
            curr != iend; curr++) {
        std::cout << (*curr).second << std::endl;
    }

    ft::map<int, std::string>::reverse_iterator rit = ft_map.rbegin();
    ft::map<int, std::string>::reverse_iterator rend = ft_map.rend();

    for (ft::map<int, std::string>::reverse_iterator curr = rit;
            curr != rend; curr++) {
        std::cout << (*curr).second << std::endl;
    }

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
