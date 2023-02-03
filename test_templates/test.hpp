/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:28:57 by ensebast          #+#    #+#             */
/*   Updated: 2023/02/02 01:41:43 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

#include <iostream>

template <typename T>
void show_status (const T &container) {
    std::cout << "Container status:" << std::endl;
    std::cout << "size: " << container.size() << std::endl;
}

template < class Iter >
void show_list (Iter begin, Iter end) {
    std::cout << "############## Show container #############" << std::endl;
    for (Iter curr = begin; curr != end; curr++)
        std::cout << *curr << std::endl;
    std::cout << "###########################################" << std::endl;
}

template < class Iter >
void show_map (Iter begin, Iter end) {
    std::cout << "############## Show container #############" << std::endl;
    for (Iter curr = begin; curr != end; curr++)
        std::cout << (*curr).first << " "
            << (*curr).second << std::endl;
    std::cout << "###########################################" << std::endl;
}
#endif
