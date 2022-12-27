/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:04:03 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/26 16:08:03 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft {

    template <typename T>
    class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>{

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
            random_access_iterator (void) { }
            explicit random_access_iterator( iterator_type x ) : curr(x) { }
            template< class U >
            random_access_iterator( const random_access_iterator<U>& other ) : curr(other.base()) { }

            template< class U >
            random_access_iterator& operator=( const random_access_iterator<U>& other ) {
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

    template< class Iterator1, class Iterator2 >
    bool operator==( const ft::random_access_iterator<Iterator1>& lhs,
                    const ft::random_access_iterator<Iterator2>& rhs ) {
        return (lhs.base() == rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator!=( const ft::random_access_iterator<Iterator1>& lhs,
                    const ft::random_access_iterator<Iterator2>& rhs ) {
        return (lhs.base() != rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<( const ft::random_access_iterator<Iterator1>& lhs,
                    const ft::random_access_iterator<Iterator2>& rhs ) {
        return (lhs.base() < rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<=( const ft::random_access_iterator<Iterator1>& lhs,
                    const ft::random_access_iterator<Iterator2>& rhs ) {
        return (lhs.base() <= rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator>( const ft::random_access_iterator<Iterator1>& lhs,
                    const ft::random_access_iterator<Iterator2>& rhs ) {
        return (lhs.base() > rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator>=( const ft::random_access_iterator<Iterator1>& lhs,
                    const ft::random_access_iterator<Iterator2>& rhs ) {
        return (lhs.base() >= rhs.base());
    }

    template< class Iter >
    random_access_iterator<Iter>
        operator+( typename random_access_iterator<Iter>::difference_type n,
                const random_access_iterator<Iter>& it ) {
            return (it.base() + n);
        }

    template< class Iterator1, class Iterator2 >
    typename random_access_iterator<Iterator1>::difference_type
        operator-( const random_access_iterator<Iterator1>& lhs,
                const random_access_iterator<Iterator2>& rhs ) {
            return (lhs.base() - rhs.base());
        }
}

#endif
