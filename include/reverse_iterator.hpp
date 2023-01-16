/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 20:34:59 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/11 19:02:01 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft {

    template <class Iter>
    class reverse_iterator : public ft::iterator<
                             typename ft::iterator_traits<Iter>::iterator_category,
                             typename ft::iterator_traits<Iter>::value_type,
                             typename ft::iterator_traits<Iter>::difference_type,
                             typename ft::iterator_traits<Iter>::pointer,
                             typename ft::iterator_traits<Iter>::reference>{

        private:
            typedef Iter                                                    iterator_type;
            typedef typename ft::iterator_traits<Iter>::iterator_category   iterator_category;
            typedef typename ft::iterator_traits<Iter>::value_type          value_type;
            typedef typename ft::iterator_traits<Iter>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iter>::pointer             pointer;
            typedef typename ft::iterator_traits<Iter>::reference           reference;

        private:
            iterator_type   curr;

        public:
            reverse_iterator (void) { }
            explicit reverse_iterator( iterator_type x ) : curr(x) { }
            template< class U >
            reverse_iterator( const reverse_iterator<U>& other ) : curr(other.base()) { }

            template< class U >
            reverse_iterator& operator=( const reverse_iterator<U>& other ) {
                curr = other.base();
                return (*this);
            }

            iterator_type base() const {
                return (curr);
            }

            reference operator*() const {
                iterator_type tmp = curr;
                return (*(--tmp));
            }

            pointer operator->() const {
                return (&(operator*()));
            }

            reference operator[]( difference_type n ) const {
                return (base()[-n - 1]);
            }

            reverse_iterator& operator++() {
                curr--;
                return (*this);
            }

            reverse_iterator& operator--() {
                curr++;
                return (*this);
            }

            reverse_iterator operator++( int ) {
                reverse_iterator tmp = (*this);
                curr--;
                return (tmp);
            }

            reverse_iterator operator--( int ) {
                reverse_iterator tmp = (*this);
                curr++;
                return (tmp);
            }

            reverse_iterator operator+( difference_type n ) const {
                reverse_iterator tmp = (*this);
                tmp.curr -= n;
                return (tmp);
            }

            reverse_iterator operator-( difference_type n ) const {
                reverse_iterator tmp = (*this);
                tmp.curr += n;
                return (tmp);
            }

            reverse_iterator& operator+=( difference_type n ) {
                curr -= n;
                return (*this);
            }
            reverse_iterator& operator-=( difference_type n ) {
                curr += n;
                return (*this);
            }
    };

    template< class Iterator1, class Iterator2 >
    bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs ) {
        return (lhs.base() == rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs ) {
        return (lhs.base() != rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs ) {
        return (lhs.base() < rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs ) {
        return (lhs.base() <= rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs ) {
        return (lhs.base() > rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs ) {
        return (lhs.base() >= rhs.base());
    }

    template< class Iter >
    reverse_iterator<Iter>
        operator+( typename reverse_iterator<Iter>::difference_type n,
                const reverse_iterator<Iter>& it ) {
            return (it.base() - n);
        }

    template< class Iterator1, class Iterator2 >
    typename reverse_iterator<Iterator1>::difference_type
        operator-( const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs ) {
            return (rhs.base() - lhs.base());
        }
}

#endif
