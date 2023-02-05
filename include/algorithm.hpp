/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:05:47 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/07 00:30:37 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP
#include <iostream>
namespace ft {

    template< class InputIt1, class InputIt2 >
    bool equal( InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2 ) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 != *first2)
                return (false);
            ++first1;
            ++first2;
        }
        if (first1 != last1 || first2 != last2)
            return (false);
        return (true);
    }
    
    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2 ) {
        while (first1 != last1) {
            if (first2 == last2 || *first2 < *first1)
                return (false);
            else if (*first1 < *first2)
                return (true);
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }
}

#endif
