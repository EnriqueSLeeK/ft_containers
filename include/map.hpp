/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:29:47 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/29 15:53:00 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include <functional>
#include <iterator>
#include "utility.hpp"
#include "map_iterator.hpp"
#include "RedBlackTree.hpp"
#include "reverse_iterator.hpp"

template<class Key,
    class T,
    class Compare = std::less< Key >,
    class Allocator = std::allocator< std::pair< const Key, T > > >
    class map {
    private:
        typedef Key                                                     key_type;
        typedef T                                                       mapped_key;
        typedef ft::pair<const Key, T>                                  value_type;
        typedef std::size_t                                             size_type;
        typedef std::ptrdiff_t                                          difference_type;
        typedef Compare                                                 key_compare;
        typedef Allocator                                               allocator_type;
        typedef value_type&                                             reference;
        typedef const value_type&                                       const_reference;
        typedef typename Allocator::pointer                             pointer;
        typedef typename Allocator::const_pointer                       const_pointer;
        typedef ft::map_iterator<value_type>                            iterator;
        typedef ft::map_iterator<const value_type>                      const_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
        typedef ft::node<value_type>                                    node;
        typedef ft::RedBlackTree<node, value_type, key_compare>         tree;

    private:

    public:
        class value_compare {

            friend class map;
            protected:
                Compare comp;
            public:
                typedef bool        result_type;
                typedef value_type  first_argument_type;
                typedef value_type  second_argument_type;
                bool operator()(first_argument_type &lhs, second_argument_type &rhs) {
                    return (comp(lhs.first, rhs.first));
                }
        };

};

#endif
