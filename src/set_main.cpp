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

#include "set_test.hpp"
#include <utility>
#include <string>
#include <ostream>
#include <iostream>

#include "set.hpp"
#include <set>

int main() {
    int data[6] = {1, 2, 3, 4, 5, 6};

    std::string data_string[6] = {std::string("aaaa"),
        std::string("bbbb"),
        std::string("cccc"),
        std::string("dddd"),
        std::string("eeee"),
        std::string("ffff")};

    std::cout << "Initialization Test" << std::endl;
    init_set_test_b< std::set<int>,
                     ft::set<int> > (data);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Capacity test" << std::endl;
    capacity_test_b< std::set<int>,
                     ft::set<int> > (data);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Insertion and erase test" << std::endl;
    insert_delete_test_b < std::set<int>,
                           ft::set<int> > (data);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Swap" << std::endl;
    swap_test_b < std::set<int>,
                  ft::set<int> > (data);
    std::cout << "------------------------" << std::endl;
    
    std::cout << "Look up test" << std::endl;
    look_up_test_b < std::set<int>,
                      ft::set<int> >
                        (data, 3, -1);
    std::cout << "------------------------" << std::endl;

    std::cout << ">>> Operator test" << std::endl;
    operator_test_b < std::set<int>,
                      ft::set<int> > (data);
    std::cout << "------------------------" << std::endl;

    return (0);
}
