/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:05:47 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/27 21:44:45 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft {

    template< class InputIt1, class InputIt2 >
    bool equal( InputIt1 first1, InputIt1 last1,
                InputIt2 first2, InputIt2 last2 ) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 != *first2)
                return (false);
            first1++;
            first2++;
        }
        if (first1 != last1 || first2 != last2)
            return (false);
        return (true);
    }
    
    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2 ) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2)
                return (true);
            if (*first1 > *first2)
                return (false);
            first1++;
            first2++;
        }
        return (first1 == last1 && first2 != last2);
    }
}

#endif
