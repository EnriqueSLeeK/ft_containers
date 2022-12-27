/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 19:53:12 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/26 15:38:35 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft {

    template <class Category,
             class T,
             class Distance = std::ptrdiff_t,
             class Pointer = T*,
             class Reference = T&>
    struct iterator {
        typedef Category    iterator_category;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
    };

    struct random_access_iterator_tag {};
}


#endif
