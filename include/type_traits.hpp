/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 00:53:13 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/26 16:05:17 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

#include <limits>
#include <uchar.h>

namespace ft {

    template < bool B, class T = void >
    struct enable_if {};

    template < class T >
    struct enable_if<true, T> { typedef T type; };
    
    template < class T >
    struct is_pair {
        static const bool value = false;
    };

    // Just selector to use the right function
    template < class K, class V >
    struct is_pair< ft::pair<K, V> > {
        static const bool value = true;
    };

    template < class T >
    struct is_integral {
        static const bool value = false;
    };

    template <>
    struct is_integral<bool> {
        static const bool value = true;
    };

    template <>
    struct is_integral<char> {
        static const bool value = true;
    };

    template <>
    struct is_integral<int> {
        static const bool value = true;
    };

    template <>
    struct is_integral<long> {
        static const bool value = true;
    };

    template <>
    struct is_integral<long long> {
        static const bool value = true;
    };

    template <>
    struct is_integral<short> {
        static const bool value = true;
    };

    template <>
    struct is_integral<char16_t> {
        static const bool value = true;
    };

    template <>
    struct is_integral<char32_t> {
        static const bool value = true;
    };

    template <>
    struct is_integral<wchar_t> {
        static const bool value = true;
    };
}

#endif
