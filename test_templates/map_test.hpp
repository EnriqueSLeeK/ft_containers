/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:29:24 by ensebast          #+#    #+#             */
/*   Updated: 2023/02/03 00:13:49 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TEST_HPP
# define MAP_TEST_HPP

#include "map.hpp"
#include "test.hpp"
#include "utility.hpp"

#include <map>
#include <string>
#include <iostream>
#include <stdexcept>

template <typename std_tree, typename ft_tree>
bool check_equality (std_tree std_map, ft_tree ft_map) {

    if (std_map.size() != ft_map.size())
        return (false);

    typename std_tree::iterator begin = std_map.begin();
    typename std_tree::iterator end = std_map.end();

    typename ft_tree::iterator fbegin = ft_map.begin();
    typename ft_tree::iterator fend = ft_map.end();

    typename std_tree::reverse_iterator rbegin = std_map.rbegin();
    typename std_tree::reverse_iterator rend = std_map.rend();

    typename ft_tree::reverse_iterator rfbegin = ft_map.rbegin();
    typename ft_tree::reverse_iterator rfend = ft_map.rend();

    while (begin != end && fbegin != fend
            && rbegin != rend && rfbegin != rfend) {

        if ((*begin).first != (*fbegin).first ||
                (*begin).second != (*fbegin).second) {
            return (false);
        }

        if ((*rbegin).first != (*rfbegin).first ||
                (*rbegin).second != (*rfbegin).second) {
            return (false);
        }

        ++begin;
        ++fbegin;

        ++rbegin;
        ++rfbegin;
    }

    return (begin == end && fbegin == fend
            && rbegin == rend && rfbegin == rfend);
}

template <typename std_map_type, typename ft_map_type,
         typename std_data, typename ft_data >
void init_map_test (ft_data *fdata, std_data *data) {

    std::cout << "Copy constructor and contructor test" << std::endl;
    std::cout << "Every test will call the copy constructor" <<std::endl;
    std::cout << "Every test will use the normal iterator and the reverse iterator" <<std::endl;


    std::cout << "Default" << std::endl;
    std_map_type std_map;
    ft_map_type ft_map;
    std::cout << (check_equality(std_map, ft_map) ? "OK" : "KO") << std::endl;

    std::cout << "Fill constructor" << std::endl;
    std_map_type s_map_2(data, data + 6);
    ft_map_type f_map_2(fdata, fdata + 6);
    std::cout << (check_equality(s_map_2, f_map_2) ? "OK" : "KO") << std::endl;

    std_map_type s_map_3(data + 1, data + 4);
    ft_map_type f_map_3(fdata + 1, fdata + 4);
    std::cout << (check_equality(s_map_3, f_map_3) ? "OK" : "KO") << std::endl;
}

template <typename std_map_type, typename ft_map_type,
         typename std_data, typename ft_data,
         typename key_type >
void    accessor_test(ft_data *fdata, std_data *data,
        key_type valid, key_type invalid) {
    std::cout << "Accessor test" << std::endl;
    std::cout << "at access" << std::endl;
    std_map_type smap(data, data + 6);
    ft_map_type fmap(fdata, fdata + 6);

    try {
        if (fmap.at(valid) == smap.at(valid))
            std::cout << "OK";
    } catch (std::exception &e) {
        std::cout << "KO";
    }
    std::cout << std::endl;

    try {
        fmap.at(invalid);
        std::cout << "KO";
    } catch (std::exception &e) {
        std::cout << "OK";
    }
    std::cout << std::endl;

    std::cout << "[] operator accessor" << std::endl;
    try {
        if (fmap[valid] == smap[valid])
            std::cout << "OK";
    } catch (std::exception &e) {
        std::cout << "KO";
    }
    std::cout << std::endl;

    try {
        if (fmap[invalid] == smap[invalid])
            std::cout << "OK";
    } catch (std::exception &e) {
        std::cout << "KO";
    }
    std::cout << std::endl;
}

template <typename std_map_type, typename ft_map_type,
         typename std_data, typename ft_data >
void init_map_test_b (ft_data *fdata, std_data *data) {
    init_map_test< std_map_type,
                    ft_map_type,
                    std_data,
                    ft_data > (fdata, data);
}


template <typename std_map_type, typename ft_map_type,
         typename std_data, typename ft_data >
void capacity_test(std_data *data, ft_data *fdata) {
    std_map_type map(data, data + 6);
    ft_map_type fmap(fdata, fdata + 6);
    if (map.size() == fmap.size())
        std::cout << "OK";
    else
        std::cout << "KO";
    std::cout << std::endl;

    std_map_type map2(data, data + 6);
    ft_map_type fmap2(fdata, fdata + 6);
    if (map2.size() == fmap2.size())
        std::cout << "OK";
    else
        std::cout << "KO";
    std::cout << std::endl;
}

template <typename std_map_type, typename ft_map_type,
         typename std_data, typename ft_data>
void insert_delete_test(std_data *data, ft_data *fdata) {
    std_map_type map;
    ft_map_type fmap;

    std::cout << "Random insertion" << std::endl;
    map.insert(data[5]);
    map.insert(data[4]);
    map.insert(data[0]);
    map.insert(data[2]);
    map.insert(data[0]);
    map.insert(data[0]);
    map.insert(data[0]);
    fmap.insert(fdata[5]);
    fmap.insert(fdata[4]);
    fmap.insert(fdata[0]);
    fmap.insert(fdata[2]);
    fmap.insert(fdata[0]);
    fmap.insert(fdata[0]);
    fmap.insert(fdata[0]);
    std::cout << (check_equality(map, fmap) ? "OK" : "KO") << std::endl;

    std::cout << "Clear everything" << std::endl;
    map.clear();
    fmap.clear();
    std::cout << (check_equality(map, fmap) ? "OK" : "KO") << std::endl;

    std::cout << "Insert and individual deletion" << std::endl;

    fmap.insert(fdata[5]);
    fmap.insert(fdata[1]);
    fmap.insert(fdata[3]);
    fmap.insert(fdata[2]);
    fmap.insert(fdata[4]);
    fmap.insert(fdata[0]);
    /*
    fmap.insert(fdata[0]);
    fmap.insert(fdata[1]);
    fmap.insert(fdata[2]);
    fmap.insert(fdata[3]);
    fmap.insert(fdata[4]);
    fmap.insert(fdata[5]);
    */


    /*
    typename ft_map_type::iterator fbegin = fmap.begin();
    typename ft_map_type::iterator fend = fmap.end();
    show_map(fbegin, fend);

    typename ft_map_type::iterator test = fmap.begin();
    */

    typename ft_map_type::iterator fbegin = fmap.begin();
    typename ft_map_type::iterator fend = fmap.end();
    show_map(fbegin, fend);

    //fmap.erase(++fmap.begin(), --fmap.end());
    fmap.erase(++fmap.begin(), fmap.end());
    /*
    fmap.erase(++fmap.begin());
    fmap.erase(++++fmap.begin());
    fmap.erase(--fmap.end());
    */


    fbegin = fmap.begin();
    fend = fmap.end();
    show_map(fbegin, fend);

    //map.insert(data[1]);
    //map.insert(data[2]);
    //map.insert(data[3]);
    //map.insert(data[4]);
    //map.insert(data[5]);
    //std::cout << (check_equality(map, fmap) ? "OK" : "KO") << std::endl;

}

template <typename std_map_type, typename ft_map_type,
         typename std_data, typename ft_data,
         typename key_type >
void access_map_test_b (ft_data *fdata, std_data *data,
        key_type valid, key_type invalid) {
    accessor_test< std_map_type,
                    ft_map_type,
                    std_data,
                    ft_data > (fdata, data, valid, invalid);
}

template <typename std_map_type, typename ft_map_type,
         typename std_data, typename ft_data >
void capacity_test_b (ft_data *fdata, std_data *data) {
    capacity_test < std_map_type,
                    ft_map_type,
                    std_data,
                    ft_data > (data, fdata);
}

template <typename std_map_type, typename ft_map_type,
         typename std_data, typename ft_data >
void insert_delete_test_b (ft_data *fdata, std_data *data){
    insert_delete_test < std_map_type,
                         ft_map_type,
                         std_data,
                         ft_data > (data, fdata);
}

#endif
