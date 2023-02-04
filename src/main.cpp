/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 14:48:43 by ensebast          #+#    #+#             */
/*   Updated: 2023/02/02 02:05:24 by ensebast         ###   ########.fr       */
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
    int k[6] = {1, 2, 3, 4, 5, 6};
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

    std::cout << "Initialization Test" << std::endl;
    init_map_test_b< std::map<int, std::string>,
                     ft::map<int, std::string> >
                        (ft_pair_list, pair_list);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Accessor test" << std::endl;
    access_map_test_b< std::map<int, std::string>,
                       ft::map<int, std::string> >
                          (ft_pair_list, pair_list, 3, 99);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Capacity test" << std::endl;
    capacity_test_b< std::map<int, std::string>,
                     ft::map<int, std::string> >
                          (ft_pair_list, pair_list);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Insertion and erase test" << std::endl;
    insert_delete_test_b < std::map<int, std::string>,
                           ft::map<int, std::string> >
                            (ft_pair_list, pair_list);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Swap" << std::endl;
    swap_test_b < std::map<int, std::string>,
                  ft::map<int, std::string> >
                    (ft_pair_list, pair_list);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Element access" << std::endl;
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Operands" << std::endl;
    std::cout << "------------------------" << std::endl;

    return (0);
}
