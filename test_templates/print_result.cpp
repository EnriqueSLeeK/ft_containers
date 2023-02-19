/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 23:36:04 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/06 23:37:00 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void print_check_result (bool res) {
    if (res)
        std::cout << "OK" << std::endl;
    else
        std::cout << "KO" << std::endl;
}
