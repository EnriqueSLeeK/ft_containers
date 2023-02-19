/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:29:24 by ensebast          #+#    #+#             */
/*   Updated: 2023/02/03 00:13:49 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_TEST_HPP
# define STACK_TEST_HPP

#include "stack.hpp"
#include "test.hpp"
#include <stack>
#include <string>
#include <ostream>
#include <iostream>
#include <stdexcept>

void print_check_result (bool res);

template <class ft_stack_type, class stack_type, class T>
void init_test (T *k, T val, std::string name) {

    std::cout << "#### Type: " << name << std::endl;
    std::cout << "Default constructor" << std::endl;
    stack_type stack;
    ft_stack_type ft_stack;
    if (stack.empty() == ft_stack.empty())
        std::cout << "OK" << std::endl;
    else
        std::cout << "KO" << std::endl;

    std::cout << "Push pop test ------" << std::endl;
    for (int i = 0; i < 5; i++) {
        ft_stack.push(k[i]);
        stack.push(k[i]);
    }
    ft_stack.push(val);
    stack.push(val);

    bool status = true;
    for (int i = 0; i < 4; i++) {
        if (stack.top() != ft_stack.top()
                || stack.size() != ft_stack.size())
            status = false;
        ft_stack.pop();
        stack.pop();
    }
    std::cout << (status ? "OK" : "KO") << std::endl;
}



template <class ft_stack_type, class stack_type, class T>
void operator_test (T *arr, std::string name) {
    std::cout << "### Type: " << name << std::endl;

    ft_stack_type empty_1;
    ft_stack_type empty_2;

    ft_stack_type ft_stack_1;
    ft_stack_type ft_stack_2;
    ft_stack_type ft_stack_3;
    ft_stack_type ft_stack_4;
    for (int i = 0; i < 6; i++) {
        if (i < 2) {
            ft_stack_2.push(arr[i]);
            ft_stack_3.push(arr[i]);
        }
        if (i > 0 && i < 4)
            ft_stack_4.push(arr[i]);
        ft_stack_1.push(arr[i]);
    }

    std::cout << "Operator ==" << std::endl;
    print_check_result(empty_1 == empty_2);
    print_check_result(!(ft_stack_1 == ft_stack_2));
    print_check_result(ft_stack_3 == ft_stack_2);
    std::cout << "Operator !=" << std::endl;
    print_check_result(ft_stack_1 != ft_stack_2);
    print_check_result(!(ft_stack_3 != ft_stack_2));
    std::cout << "Operator <" << std::endl;
    print_check_result(!(empty_1 < empty_2));
    print_check_result(!(ft_stack_1 < ft_stack_2));
    print_check_result(ft_stack_2 < ft_stack_1);
    print_check_result(!(ft_stack_4 < ft_stack_2));
    print_check_result(ft_stack_2 < ft_stack_4);
    print_check_result(!(ft_stack_2 < ft_stack_3));
    std::cout << "Operator >" << std::endl;
    print_check_result(!(empty_1 < empty_2));
    print_check_result(ft_stack_1 > ft_stack_2);
    print_check_result(!(ft_stack_2 > ft_stack_1));
    print_check_result(ft_stack_4 > ft_stack_2);
    print_check_result(!(ft_stack_2 > ft_stack_4));
    print_check_result(!(ft_stack_2 > ft_stack_3));
    std::cout << "Operator <=" << std::endl;
    print_check_result(!(ft_stack_1 <= ft_stack_2));
    print_check_result(ft_stack_2 <= ft_stack_1);
    print_check_result(!(ft_stack_4 <= ft_stack_2));
    print_check_result(ft_stack_2 <= ft_stack_4);
    print_check_result(ft_stack_2 <= ft_stack_3);
    std::cout << "Operator >=" << std::endl;
    print_check_result(ft_stack_1 >= ft_stack_2);
    print_check_result(!(ft_stack_2 >= ft_stack_1));
    print_check_result(ft_stack_4 >= ft_stack_2);
    print_check_result(!(ft_stack_2 >= ft_stack_4));
    print_check_result(ft_stack_2 >= ft_stack_3);
}

template <typename T>
void init_test_m (T* arr, T val, std::string name) {
    init_test< ft::stack<T>, std::stack<T>, T > (arr, val, name);
}

template <typename T>
void operator_m (T *arr, std::string name) {
    operator_test< ft::stack<T>, std::stack<T>, T > (arr, name);
}

#endif