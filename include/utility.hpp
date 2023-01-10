/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 21:59:27 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/09 23:23:18 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP
namespace ft {

    template < class T1, class T2 >
    struct pair {

        T1  first;
        T2  second;

        pair () : first(T1()), second(T2()) {}

        pair( const T1& x, const T2& y ) : first(x), second(y) { }

        template< class U1, class U2 >
        pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) { }

        pair( const pair<T1, T2>& p ) : first(p.first), second(p.second) {}

        pair &operator=(const pair &other) {
            first = other.first;
            second = other.second;
            return (*this);
        };

    };

    template< class T1, class T2 >
    ft::pair<T1, T2> make_pair( T1 t, T2 u ) {
        return (pair<T1, T2>(t, u));
    }

    template< class T1, class T2 >
    bool operator==( const ft::pair<T1,T2>& lhs,
            const ft::pair<T1,T2>& rhs ) {
        return (lhs.first == rhs.first
                && lhs.second == rhs.second);
    }

    template< class T1, class T2 >
    bool operator!=( const ft::pair<T1,T2>& lhs,
            const ft::pair<T1,T2>& rhs ) {
        return (!(lhs == rhs));
    }

    template< class T1, class T2 >
    bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
        if (lhs.first == rhs.first)
            return (lhs.second < rhs.second);
        return (lhs.first < rhs.first);
    }

    template< class T1, class T2 >
    bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
        return (!(lhs < rhs));
    }

    template< class T1, class T2 >
    bool operator<= ( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
        return (lhs < rhs || lhs == rhs);
    }

    template< class T1, class T2 >
    bool operator>= ( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
        return (lhs > rhs || lhs == rhs);
    }
}

#endif
