/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 21:57:16 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/31 22:26:17 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft {

    template< class T, class Container = ft::vector<T> >
        class stack {
            public:
                typedef Container                           container_type;
                typedef typename Container::value_type      value_type;
                typedef typename Container::size_type       size_type;
                typedef typename Container::reference       reference;
                typedef typename Container::const_reference const_reference;
            protected:
                Container c;
            public:
                explicit stack( const Container& cont = Container() ) : c(cont) { }

                stack( const stack& other ) : c(other.c) { }

                ~stack(void) {}

                stack& operator=( const stack& other ) {
                    c = other.c;
                    return (*this);
                }

                
                bool empty(void) const {
                    if (c.size() == 0)
                        return (true);
                    return (false);
                }

                size_type size(void) const {
                    return (c.size());
                }

                reference top(void) {
                    return (c.back());
                }
            
                const_reference top(void) const {
                    return (c.back());
                }

                void push( const value_type& value ) {
                    c.push_back(value);
                }

                void pop(void) {
                    c.pop_back();
                }

            template< class type, class container_type >
            friend bool operator==( const ft::stack<type,container_type>& lhs,
                                        const ft::stack<type,container_type>& rhs );

            template< class type, class container_type >
            friend bool operator!=( const ft::stack<type,container_type>& lhs,
                                        const ft::stack<type,container_type>& rhs );

            template< class type, class container_type >
            friend bool operator<=( const ft::stack<type,container_type>& lhs,
                                        const ft::stack<type,container_type>& rhs );

            template< class type, class container_type >
            friend bool operator>=( const ft::stack<type,container_type>& lhs,
                                        const ft::stack<type,container_type>& rhs );

            template< class type, class container_type >
            friend bool operator>( const ft::stack<type,container_type>& lhs,
                                        const ft::stack<type,container_type>& rhs );

            template< class type, class container_type >
            friend bool operator<( const ft::stack<type,container_type>& lhs,
                                        const ft::stack<type,container_type>& rhs );

        };

    template< class T, class Container >
    bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return (lhs.c == rhs.c);
    }

    template< class T, class Container >
    bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return (lhs.c != rhs.c);
    }

    template< class T, class Container >
    bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return (lhs.c < rhs.c);
    }

    template< class T, class Container >
    bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return (lhs.c <= rhs.c);
    }

    template< class T, class Container >
    bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return (lhs.c > rhs.c);
    }

    template< class T, class Container >
    bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
        return (lhs.c >= rhs.c);
    }

}
#endif
