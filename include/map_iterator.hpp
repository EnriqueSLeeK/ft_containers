/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:00:01 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/27 23:32:47 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft {

    template <typename T>
    class map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>{

        private:
            typedef T                                                    iterator_type;
            typedef typename ft::iterator_traits<T>::iterator_category   iterator_category;
            typedef typename ft::iterator_traits<T>::value_type          value_type;
            typedef typename ft::iterator_traits<T>::difference_type     difference_type;
            typedef typename ft::iterator_traits<T>::pointer             pointer;
            typedef typename ft::iterator_traits<T>::reference           reference;

        private:
            pointer curr;

        public:
            map_iterator (void) { }
            explicit map_iterator( iterator_type x ) : curr(x) { }
            template< class U >
            map_iterator( const map_iterator<U>& other ) : curr(other.base()) { }

            template< class U >
            map_iterator& operator=( const map_iterator<U>& other ) {
                curr = other.base();
                return (*this);
            }

            iterator_type base() const {
                return (curr);
            }

            reference operator*() const {
                return (*(curr));
            }

            pointer operator->() const {
                return (&(operator*()));
            }

            map_iterator& operator++() {
                curr++;
                return (*this);
            }

            map_iterator& operator--() {
                curr--;
                return (*this);
            }

            map_iterator operator++( int ) {
                map_iterator tmp = (*this);
                curr++;
                return (tmp);
            }

            map_iterator operator--( int ) {
                map_iterator tmp = (*this);
                curr--;
                return (tmp);
            }
    };

    template< class Iterator1, class Iterator2 >
    bool operator==( const ft::map_iterator<Iterator1>& lhs,
                    const ft::map_iterator<Iterator2>& rhs ) {
        return (lhs.base() == rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator!=( const ft::map_iterator<Iterator1>& lhs,
                    const ft::map_iterator<Iterator2>& rhs ) {
        return (lhs.base() != rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<( const ft::map_iterator<Iterator1>& lhs,
                    const ft::map_iterator<Iterator2>& rhs ) {
        return (lhs.base() < rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<=( const ft::map_iterator<Iterator1>& lhs,
                    const ft::map_iterator<Iterator2>& rhs ) {
        return (lhs.base() <= rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator>( const ft::map_iterator<Iterator1>& lhs,
                    const ft::map_iterator<Iterator2>& rhs ) {
        return (lhs.base() > rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator>=( const ft::map_iterator<Iterator1>& lhs,
                    const ft::map_iterator<Iterator2>& rhs ) {
        return (lhs.base() >= rhs.base());
    }
}

#endif
