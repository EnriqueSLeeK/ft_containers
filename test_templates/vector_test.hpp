/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:30:23 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/08 13:33:30 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TEST_HPP
# define VECTOR_TEST_HPP

#include "vector.hpp"
#include <vector>
#include "test.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
#include <ostream>

void print_check_result (bool res);

template <class vec_type, class Iter>
void    show_all(const vec_type &vec, Iter begin, Iter end) {
    show_status<vec_type>(vec);
    std::cout << "capacity: " << vec.capacity() << std::endl;
    show_list<Iter>(begin, end);
}

template <class vec_type>
void    show_list(const vec_type &vec, typename vec_type::size_type total_steps, std::string name) {
    std::cout << name << ": ";
    for (typename vec_type::size_type i = 0; i < total_steps; i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

template <typename T>
bool    size_capacity_test (T expected, T given) {
    if (expected == given)
        return (true);
    return (false);
}

template <class ft_vec, class vec>
bool    vec_equality (vec expected, ft_vec given) {
    for (std::size_t i = 0; i < expected.size(); i++)
        if (expected[i] != given[i])
            return (false);
    return (true);
}


template <class ft_vec_type, class vec_type>
void    test (const ft_vec_type &vec,
        const vec_type &expected_vec) {

    if (size_capacity_test(expected_vec.size(), vec.size())
            && vec_equality(vec, expected_vec))
        std::cout << ">>>> OK" << std::endl;

    else
        std::cout << "#### KO ####" << std::endl;
}

template <class ft_vec_type, class vec_type, class T>
void init_test (T *k, T val, std::string name) {

    std::cout << "#### Type: " << name << std::endl;
    std::cout << "Value type: ";
    ft_vec_type ft_vec;
    vec_type vec;
    std::cout << "Default constructor: ";
    test< ft_vec_type, vec_type >(ft_vec, vec);

    ft_vec_type ft_vec_1(5, val);
    vec_type vec_1(5, val);
    std::cout << "Value initialized constructor: ";
    test(ft_vec_1, vec_1);

    ft_vec_type ft_vec_2(k, k + 3);
    vec_type vec_2(k, k + 3);
    std::cout << "Value initialized constructor: ";
    test(ft_vec_2, vec_2);
}

template <class ft_vec_type, class vec_type, class T>
void push_pop_test (T *k, std::string name) {

    ft_vec_type ft_vec;
    vec_type vec;

    std::cout << "#### Type: " << name << std::endl;
    std::cout << "After push ------" << std::endl;
    for (int i = 0; i < 5; i++) {
        ft_vec.push_back(k[i]);
        vec.push_back(k[i]);
    }
    test(ft_vec, vec);

    std::cout << "After pop -------" << std::endl;
    for (int i = 0; i < 4; i++) {
        ft_vec.pop_back();
        vec.pop_back();
    }
    test(ft_vec, vec);
}

template <class ft_iter, class iter>
bool check_iterators (ft_iter fbegin, ft_iter fend, iter begin, iter end) {
    while (fbegin != fend && begin != end) {
        if ((*fbegin) != *(begin))
            return (false);
        ++fbegin;
        ++begin;
    }
    return (fbegin == fend && begin == end);
}

template <class ft_vec_type, class vec_type, class T>
void iterator_test ( T *k ) {
    ft_vec_type ft_vec(k, k + 3);
    vec_type vec(k, k + 3);
    if (check_iterators<typename ft_vec_type::iterator, typename vec_type::iterator>(
                ft_vec.begin(),
                ft_vec.end(),
                vec.begin(),
                vec.end())
        && check_iterators<typename ft_vec_type::reverse_iterator, typename vec_type::reverse_iterator>(
            ft_vec.rbegin(),
            ft_vec.rend(),
            vec.rbegin(),
            vec.rend()))
        std::cout << "OK" << std::endl;
    else
        std::cout << "KO" << std::endl;
}

template <class ft_vec_type, class vec_type, class T>
void insert_erase_test (T *k, T val, std::string name) {
    std::cout << "#### Type: " << name << std::endl;
    ft_vec_type ft_vec(k, k + 5);
    vec_type vec(k, k + 5);

    std::cout << "After insertion -------" << std::endl;
    std::cout << "Normal insertion ---: ";
    ft_vec.insert(ft_vec.begin() + 2, val);
    vec.insert(vec.begin() + 2, val);
    ft_vec.insert(ft_vec.begin(), val);
    vec.insert(vec.begin(), val);
    ft_vec.insert(ft_vec.end(), val);
    vec.insert(vec.end(), val);
    test(ft_vec, vec);
    std::cout << "Array insertion ---: ";
    vec.insert(vec.begin(), 3, val);
    ft_vec.insert(ft_vec.begin(), 3, val);
    vec.insert(vec.begin(), k + 1, k + 3);
    ft_vec.insert(ft_vec.begin(), k + 1, k + 3);
    test(ft_vec, vec);
    std::cout << "After erase -------: ";
    ft_vec.erase(ft_vec.begin() + 3);
    vec.erase(vec.begin() + 3);
    ft_vec.erase(ft_vec.begin() + 1, ft_vec.end());
    vec.erase(vec.begin() + 1, vec.end());
    test(ft_vec, vec);
}

template <class ft_vec_type, class vec_type, class T>
void    swap_test (T* k, std::string name) {

    std::cout << "### Type: " << name << std::endl;
    vec_type vec_1(k, k + 2);
    vec_type vec_2(k + 3, k + 5);

    ft_vec_type ft_vec_1(k, k + 2);
    ft_vec_type ft_vec_2(k + 3, k + 5);

    std::cout << "Before swap --------" << std::endl;
    test(ft_vec_1, vec_1);
    test(ft_vec_2, vec_2);

    std::cout << "After swap ---------" << std::endl;
    vec_1.swap(vec_2);
    ft_vec_1.swap(ft_vec_2);
    test(ft_vec_1, vec_1);
    test(ft_vec_2, vec_2);

    std::cout << "Another swap -------" << std::endl;
    swap(vec_1, vec_2);
    swap(ft_vec_1, ft_vec_2);
    test(ft_vec_1, vec_1);
    test(ft_vec_2, vec_2);
}

template <typename T>
void value_equality (T val_1, T val_2) {
    if (val_1 == val_2)
        std::cout << "OK" << std::endl;
    else
        std::cout << "KO" << std::endl;
}

template <class ft_vec_type, class vec_type, class T>
void    access_test (T* k, std::string name) {

    std::cout << "### Type: " << name << std::endl;
    ft_vec_type ft_vec(k, k+5);
    vec_type vec(k, k+5);

    std::cout << "Index access -------" << std::endl;
    T ft_tmp = ft_vec[2];
    T tmp = vec[2];
    value_equality(ft_tmp, tmp);
    std::cout << "At access -------" << std::endl;
    try {
        ft_vec.at(6);
    } catch (std::exception &e){
        std::cout << "ft exception OK" << std::endl;
    }
    ft_tmp = ft_vec.at(3);
    tmp = vec.at(3);
    value_equality(ft_tmp, tmp);

    std::cout << "Front access ----" << std::endl;
    value_equality(ft_vec.front(), vec.front());
    std::cout << "Back access -----" << std::endl;
    value_equality(ft_vec.back(), vec.back());
}

template <class ft_vec_type, class vec_type, class T>
void operator_test (T *arr, std::string name) {
    std::cout << "### Type: " << name << std::endl;

    ft_vec_type empty_1;
    ft_vec_type empty_2;
    ft_vec_type ft_vec_1(arr, arr + 5);
    ft_vec_type ft_vec_2(arr, arr + 2);
    ft_vec_type ft_vec_3(arr, arr + 2);
    ft_vec_type ft_vec_4(arr + 1, arr + 3);

    std::cout << "Operator ==" << std::endl;
    print_check_result(empty_1 == empty_2);
    print_check_result(!(ft_vec_1 == ft_vec_2));
    print_check_result(ft_vec_3 == ft_vec_2);
    std::cout << "Operator !=" << std::endl;
    print_check_result(ft_vec_1 != ft_vec_2);
    print_check_result(!(ft_vec_3 != ft_vec_2));
    std::cout << "Operator <" << std::endl;
    print_check_result(!(empty_1 < empty_2));
    print_check_result(!(ft_vec_1 < ft_vec_2));
    print_check_result(ft_vec_2 < ft_vec_1);
    print_check_result(!(ft_vec_4 < ft_vec_2));
    print_check_result(ft_vec_2 < ft_vec_4);
    print_check_result(!(ft_vec_2 < ft_vec_3));
    std::cout << "Operator >" << std::endl;
    print_check_result(!(empty_1 < empty_2));
    print_check_result(ft_vec_1 > ft_vec_2);
    print_check_result(!(ft_vec_2 > ft_vec_1));
    print_check_result(ft_vec_4 > ft_vec_2);
    print_check_result(!(ft_vec_2 > ft_vec_4));
    print_check_result(!(ft_vec_2 > ft_vec_3));
    std::cout << "Operator <=" << std::endl;
    print_check_result(!(ft_vec_1 <= ft_vec_2));
    print_check_result(ft_vec_2 <= ft_vec_1);
    print_check_result(!(ft_vec_4 <= ft_vec_2));
    print_check_result(ft_vec_2 <= ft_vec_4);
    print_check_result(ft_vec_2 <= ft_vec_3);
    std::cout << "Operator >=" << std::endl;
    print_check_result(ft_vec_1 >= ft_vec_2);
    print_check_result(!(ft_vec_2 >= ft_vec_1));
    print_check_result(ft_vec_4 >= ft_vec_2);
    print_check_result(!(ft_vec_2 >= ft_vec_4));
    print_check_result(ft_vec_2 >= ft_vec_3);
}

template <typename T>
void init_test_m (T* arr, T val, std::string name) {
    init_test< ft::vector<T>, std::vector<T>, T > (arr, val, name);
}

template <typename T>
void push_pop_test_m (T* arr, std::string name) {
    push_pop_test< ft::vector<T>, std::vector<T>, T >(arr, name);
}

template <typename T>
void iterator_test_m (T *arr) {
    iterator_test< ft::vector<T>, std::vector<T>, T > (arr);
}

template <typename T>
void insert_erase_test_m (T *arr, T val, std::string name) {
    insert_erase_test< ft::vector<T>, std::vector<T>, T > (arr, val, name);
}

template <typename T>
void swap_m (T *arr, std::string name) {
    swap_test< ft::vector<T>, std::vector<T>, T > (arr, name);
}

template <typename T>
void access_m (T *arr, std::string name) {
    access_test< ft::vector<T>, std::vector<T>, T > (arr, name);
}

template <typename T>
void operator_m (T *arr, std::string name) {
    operator_test< ft::vector<T>, std::vector<T>, T > (arr, name);
}
#endif
