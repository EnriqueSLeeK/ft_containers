/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:29:24 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/16 00:14:55 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TEST_HPP
# define MAP_TEST_HPP

#include <map>
#include "map.hpp"
#include "test.hpp"
#include "utility.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
#include <ostream>

template <typename std_tree, typename ft_tree>
bool check_equality (std_tree std_map, ft_tree ft_map) {
    if (std_map.size() != ft_map.size())
        return (false);

    typename std_tree::iterator begin = std_map.begin();
    typename std_tree::iterator end = std_map.end();

    typename ft_tree::iterator fbegin = ft_map.begin();
    typename ft_tree::iterator fend = ft_map.end();

    while (begin != end || fbegin != fend) {
        if (begin.second != fbegin.second)
            return (false);
        begin++;
        fbegin++;
    }

    return (begin == end && fbegin == fend);
}

template <typename Key_type, typename Val_type>
void init_map_test (ft::pair<Key_type, Val_type> *data) {
    std::map<Key_type, Val_type> std_map;
    ft::map<Key_type, Val_type> ft_map;
    check_equality(std_map, ft_map);
}

#endif
