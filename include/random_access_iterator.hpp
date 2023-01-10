/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:04:03 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/07 00:12:59 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft {

    template <typename T>
    class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>{

        public:
            typedef T                                                    iterator_type;
            typedef typename ft::iterator_traits<T>::iterator_category   iterator_category;
            typedef typename ft::iterator_traits<T>::value_type          value_type;
            typedef typename ft::iterator_traits<T>::difference_type     difference_type;
            typedef typename ft::iterator_traits<T>::pointer             pointer;
            typedef typename ft::iterator_traits<T>::reference           reference;

        private:
            iterator_type curr;

        public:

            random_access_iterator (void) : curr(NULL) { }

            explicit random_access_iterator( iterator_type x ) : curr(x) { }

            template< class U >
            random_access_iterator( const random_access_iterator<U>& other ) : curr(other.base()) { }

            template< class U >
            random_access_iterator& operator=( const random_access_iterator<U>& other ) {
                curr = other.base();
                return (*this);
            }

            ~random_access_iterator (void) { }

            iterator_type base() const {
                return (curr);
            }

            reference operator*() const {
                return (*(curr));
            }

            pointer operator->() const {
                return (&(operator*()));
            }

            reference operator[]( difference_type n ) const {
                return (base()[n]);
            }

            random_access_iterator& operator++() {
                curr++;
                return (*this);
            }

            random_access_iterator& operator--() {
                curr--;
                return (*this);
            }

            random_access_iterator operator++( int ) {
                random_access_iterator tmp = (*this);
                curr++;
                return (tmp);
            }

            random_access_iterator operator--( int ) {
                random_access_iterator tmp = (*this);
                curr--;
                return (tmp);
            }

            random_access_iterator operator+( difference_type n ) const {
                random_access_iterator tmp = (*this);
                tmp.curr += n;
                return (tmp);
            }

            random_access_iterator operator-( difference_type n ) const {
                random_access_iterator tmp = (*this);
                tmp.curr -= n;
                return (tmp);
            }

            random_access_iterator& operator+=( difference_type n ) {
                curr += n;
                return (*this);
            }
            random_access_iterator& operator-=( difference_type n ) {
                curr -= n;
                return (*this);
            }
    };

    template< class Iterator >
    bool operator==( const random_access_iterator<Iterator>& lhs,
                    const random_access_iterator<Iterator>& rhs ) {
        return (lhs.base() == rhs.base());
    }

    template< class Iterator >
    bool operator!=( const random_access_iterator<Iterator>& lhs,
                    const random_access_iterator<Iterator>& rhs ) {
        return (lhs.base() != rhs.base());
    }

    template< class Iterator>
    bool operator<( const random_access_iterator<Iterator>& lhs,
                    const random_access_iterator<Iterator>& rhs ) {
        return (lhs.base() < rhs.base());
    }

    template< class Iterator >
    bool operator<=( const random_access_iterator<Iterator>& lhs,
                    const random_access_iterator<Iterator>& rhs ) {
        return (lhs.base() <= rhs.base());
    }

    template< class Iterator >
    bool operator>( const random_access_iterator<Iterator>& lhs,
                    const random_access_iterator<Iterator>& rhs ) {
        return (lhs.base() > rhs.base());
    }

    template< class Iterator>
    bool operator>=( const random_access_iterator<Iterator>& lhs,
                    const random_access_iterator<Iterator>& rhs ) {
        return (lhs.base() >= rhs.base());
    }

    template< class Iterator >
    typename Iterator::difference_type
        operator-( const Iterator& lhs,
                const Iterator& rhs ) {
            return (lhs.base() - rhs.base());
        }
}

#endif
