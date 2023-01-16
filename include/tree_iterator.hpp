/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:00:01 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/16 00:03:04 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft {

    template <typename T, typename Iterator>
    class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>{

        public:
            typedef Iterator                                                        iterator_type;
            typedef T*                                                              val_pointer;
            typedef typename ft::iterator_traits<val_pointer>::pointer              pointer;
            typedef typename ft::iterator_traits<val_pointer>::reference            reference;
            typedef typename ft::iterator_traits<val_pointer>::value_type           value_type;
            typedef typename ft::iterator_traits<val_pointer>::difference_type      difference_type;
            typedef typename ft::iterator_traits<val_pointer>::iterator_category    iterator_category;

        private:
            iterator_type curr;

        public:
            tree_iterator (void) { }
            tree_iterator( iterator_type x ) : curr(x){ }
            template< class U >
            tree_iterator( const tree_iterator<T, Iterator>& other ) : curr(other.base()) { }

            template< class U >
            tree_iterator& operator=( const tree_iterator<U, Iterator>& other ) {
                curr = other.base();
                return (*this);
            }

            iterator_type base() const {
                return (curr);
            }

            reference operator*() const {
                return ((*curr).value);
            }

            pointer operator->() const {
                return (&(operator*()));
            }

            tree_iterator& operator++() {
                curr = successor(curr);
                return (*this);
            }

            tree_iterator& operator--() {
                curr = predecessor(curr);
                return (*this);
            }

            tree_iterator operator++( int ) {
                tree_iterator tmp = (*this);
                operator++();
                return (tmp);
            }

            tree_iterator operator--( int ) {
                tree_iterator tmp = (*this);
                operator--();
                return (tmp);
            }

            bool operator== (const tree_iterator<T, Iterator> &other) {
                return (other.base() == curr);
            }

            bool operator!= (const tree_iterator<T, Iterator> &other) {
                return (other.base() != curr);
            }

        private:

            iterator_type successor (iterator_type node) {
                if (node -> right != NULL) {
                    node = node -> right;
                    while (node -> left != NULL)
                        node = node -> left;
                    return (node);
                }

                iterator_type y = node->parent;
                while (y != NULL && node == y->right) {
                    node = y;
                    y = y->parent;
                }
                return (y);
            }

            iterator_type predecessor (iterator_type node) {
                if (node -> left != NULL) {
                    node = node -> left;
                    while (node -> right != NULL)
                        node = node -> right;
                    return (node);
                }

                iterator_type y = node->parent;
                while (y != NULL && node == y->left) {
                    node = y;
                    y = y->parent;
                }
                return (y);
            }
    };
}

#endif
