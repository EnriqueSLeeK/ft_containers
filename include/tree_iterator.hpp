/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 23:00:01 by ensebast          #+#    #+#             */
/*   Updated: 2023/01/09 23:49:50 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft {

    template <typename T, typename Iterator>
    class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Iterator>{

        private:
            typedef Iterator                                                    iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
            typedef typename ft::iterator_traits<Iterator>::reference           reference;

        private:
            pointer curr;

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
                return (curr -> value);
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

            pointer successor (pointer node) {
                if (node -> right != NULL) {
                    node = node -> right;
                    while (node -> left != NULL)
                        node = node -> left;
                    return (node);
                }

                pointer y = node->parent;
                while (y != NULL && node == y->right) {
                    node = y;
                    y = y->parent;
                }
                return (y);
            }

            pointer predecessor (pointer node) {
                if (node -> left != NULL) {
                    node = node -> left;
                    while (node -> right != NULL)
                        node = node -> right;
                    return (node);
                }

                pointer y = node->parent;
                while (y != NULL && node == y->left) {
                    node = y;
                    y = y->parent;
                }
                return (y);
            }
    };
}

#endif
