/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:29:47 by ensebast          #+#    #+#             */
/*   Updated: 2023/02/02 22:44:33 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include <limits>
#include <iterator>
#include "algorithm.hpp"
#include "utility.hpp"
#include "type_traits.hpp"
#include "tree_iterator.hpp"
#include "RedBlackTree.hpp"
#include "reverse_iterator.hpp"

namespace ft {

    template<class Key,
        class T,
        class Compare = std::less< Key >,
        class Allocator = std::allocator< ft::pair< const Key, T > > >
        class map {
        public:
            typedef Key                                                     key_type;
            typedef T                                                       mapped_type;
            typedef ft::pair<const Key, T>                                  value_type;
            typedef std::size_t                                             size_type;
            typedef std::ptrdiff_t                                          difference_type;
            typedef Compare                                                 key_compare;

            class value_compare {

                friend class map;
                protected:
                    Compare comp;
                    value_compare (Compare comparator) : comp(comparator) {}
                public:
                    typedef bool        result_type;
                    typedef value_type  first_argument_type;
                    typedef value_type  second_argument_type;
                    bool operator()(first_argument_type &lhs, second_argument_type &rhs) const {
                        return (comp(lhs.first, rhs.first));
                    }
            };

            typedef Allocator                                               allocator_type;
            typedef value_type&                                             reference;
            typedef const value_type&                                       const_reference;
            typedef typename Allocator::pointer                             pointer;
            typedef typename Allocator::const_pointer                       const_pointer;
            typedef ft::node<value_type>                                    node;
            typedef node*                                                   node_pointer;
            typedef ft::tree_iterator<pointer, node_pointer>                iterator;
            typedef ft::tree_iterator<const_pointer, node_pointer>          const_iterator;
            typedef ft::reverse_iterator<iterator>                          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
            typedef ft::RedBlackTree<node, value_type, value_compare>       tree_type;

        private:
            value_compare   _val_comp;
            tree_type       _tree;

        public:

            //  Constructor ############################
            map (void) : _val_comp(key_compare()), _tree(value_compare(key_compare())) { }

            explicit map (Compare &comp,
                    const Allocator& alloc = Allocator()) :
                _val_comp(key_compare()), _tree(tree_type(value_compare(comp), alloc)) { }

            template< class InputIt >
            map( InputIt first, InputIt last,
                    const Compare& comp = Compare(),
                    const Allocator& alloc = Allocator(),
                    typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt>::type* = 0 ) :
                _val_comp(key_compare()), _tree(tree_type(value_compare(comp), alloc)) {
                insert(first, last);
            }

            map( const map& other ) :
                _val_comp(key_compare()),
                _tree(tree_type(other._tree.get_comparator(),
                    other._tree.get_allocator())) {
                *this = other;
            }
            //  Constructor end#########################

            //  Copy assign ############################
            map &operator=(const map& other) {
                _tree = other._tree;
                insert(other.begin(), other.end());
                return (*this);
            }
            //  Copy assign end#########################

            // Destructor ##############################
            ~map  (void) { }
            // Destructor end ##########################
            
            // Getter ##################################
            allocator_type get_allocator(void) const {
                return (_tree.get_allocator());
            }
            // Getter end ##############################

            // Accessor ################################
            T& at( const Key& key ) {
                node_pointer node = search(value_type(key, T()));
                if (node == NULL)
                    throw std::out_of_range("This element doesn't exist in the map");
                return (node->value.second);
            }

            const T& at(const Key& key) const {
                node_pointer node = search(value_type(key, T()));
                if (node == NULL)
                    throw std::out_of_range("This element doesn't exist in the map");
                return (node->value.second);
            }

            T& operator[] ( const Key& key ) {
                value_type val = value_type(key, T());
                node_pointer node = search(val);
                if (node == NULL)
                    return (_tree.insert(val)->value.second);
                return (node->value.second);
            }
            // Accessor end ############################

            // Iterators ###############################
            iterator begin (void) {
                return (iterator(_tree.begin()));
            } 

            const_iterator begin(void) const {
                return (const_iterator( _tree.begin()));
            }

            iterator end (void) {
                return (iterator(_tree.end()));
            }

            const_iterator end(void) const {
                return (const_iterator(_tree.end()));
            }

            reverse_iterator rbegin (void) {
                return (reverse_iterator(end()));
            }

            const_reverse_iterator rbegin(void) const {
                return (const_reverse_iterator(end()));
            }

            reverse_iterator rend (void) {
                return (reverse_iterator(begin()));
            }

            const_reverse_iterator rend(void) const {
                return (const_reverse_iterator(begin()));
            }
            // Iterators end ###########################

            // Capacity ################################
            bool empty (void) const {
                if (_tree.size() == 0)
                    return (true);
                return (false);
            }

            size_type size (void) const {
                return (_tree.size());
            }

            size_type max_size(void) const {
                return (std::numeric_limits<size_type>::max() / sizeof(node));
            }
            // Capacity end ############################

            // Modifiers ###############################
            void clear(void) {
                _tree.clear_up();
            }

            ft::pair<iterator, bool> insert ( const value_type& value ) {
                ft::pair<iterator, bool> status = ft::pair<iterator, bool>();
                node_pointer item =  search(value);
                if (item == NULL) {
                    status.first = iterator(_tree.insert(value));
                    status.second = true;
                }
                else {
                    status.first = iterator(item);
                    status.second = false;
                }
                return (status);
            }

            iterator insert ( iterator pos, const value_type& value ) {
                (void)pos;
                return (insert(value).first);
            }

            template< class InputIt >
            void insert ( InputIt first, InputIt last ,
                    typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt>::type* = 0 ) {
                for (InputIt curr = first;
                        curr != last;
                        curr++) {
                    insert(*curr);
                }
            }

            iterator erase( iterator pos ) {
                if (pos.base() != NULL)
                    _tree.delete_node(pos.base());
                return (pos);
            }

            iterator erase( iterator first, iterator last ) {
                for (iterator curr = first; curr != last;)
                    erase(curr++);
                return (last);
            }

            size_type erase( const Key& key ) {
                node_pointer target = search(value_type(key, T()));
                if (target == NULL)
                    return (0);
                _tree.delete_node(target);
                return (1);
            }

            void swap( map& other ) {
                _tree.swap(other._tree);
            }
            // Modifiers end ###########################

            // Lookup ##################################
            size_type count( const Key& key ) const {
                node_pointer node = search(value_type(key, mapped_key()));
                if (node == NULL)
                    return (0);
                return (1);
            }

            iterator find( const Key& key ) {
                node_pointer find_target = search(value_type(key, mapped_key()));
                if (find_target == NULL)
                    return (end());
                return (iterator(find_target));
            }

            const_iterator find( const Key& key ) const {
                node_pointer find_target = search(value_type(key, mapped_key()));
                if (find_target == NULL)
                    return (end());
                return (const_iterator(find_target));
            }

            iterator upper_bound( const Key& key ) {
                return (iterator(
                            upper_bound_aux(
                                value_type(key, mapped_key()))));
            }

            const_iterator upper_bound( const Key& key ) const {
                return (const_iterator(
                            upper_bound_aux(
                                value_type(key, mapped_key()))));
            }

            iterator lower_bound( const Key& key ) {
                return (iterator(
                            lower_bound_aux(
                                value_type(key, mapped_key()))));
            }

            const_iterator lower_bound( const Key& key ) const {
                return (const_iterator(
                            lower_bound_aux(
                                value_type(key, mapped_key()))));
            }

            ft::pair<iterator,iterator> equal_range( const Key& key ) {
                return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
            }

            ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
                return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
            }
            // Lookup end ##############################

            // Observer ################################
            key_compare key_comp(void) const {
                return (_tree.get_comparator());
            }

            ft::map<Key, T, Compare, Allocator>::value_compare value_comp(void) const {
                return (value_compare());
            }
            // Observer end ############################

        private:
            node_pointer search (const value_type &val) const {
                value_type tmp = val;
                node_pointer curr = _tree.get_root();

                while (curr != NULL && curr != _tree.end()) {
                    
                    if (curr->value.first == val.first)
                        return (curr);
                    curr = _val_comp(tmp, curr->value) ? curr -> left : curr -> right;
                }
                return (NULL);
            }

            node_pointer upper_bound_aux (const value_type &val) const {
                value_type tmp = val;
                node_pointer curr = _tree.get_root();

                while (curr != NULL && curr != _tree.end()) {
                    if (curr->value.first > tmp.first)
                        return (curr);
                    curr = _val_comp(tmp, curr->value) ? curr -> left : curr -> right;
                }
                return (_tree.end());
            }

            node_pointer lower_bound_aux (const value_type &val) const {
                value_type tmp = val;
                node_pointer curr = _tree.get_root();
                node_pointer candidate = NULL;
                bool status = false;

                while (curr != NULL && curr != _tree.end()) {
                    status = curr->value.first >= tmp.first;
                    if (status)
                        candidate = curr;

                    curr = _val_comp(tmp, curr->value) ? curr -> left : curr -> right;
                }
                if (candidate == NULL)
                    return (_tree.end());
                return (candidate);
            }
    };
    template< class Key, class T, class Compare, class Alloc >
    bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
                    const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(),
                                                        rhs.begin(), rhs.end()));
    }


    template< class Key, class T, class Compare, class Alloc >
    bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
                    const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                                rhs.begin(), rhs.end()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
                    const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return (!(lhs == rhs));
    }


    template< class Key, class T, class Compare, class Alloc >
    bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
                     const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return (lhs < rhs || lhs == rhs);
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
                    const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return (lhs != rhs && !(lhs < rhs));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
                    const ft::map<Key,T,Compare,Alloc>& rhs ) {
        return (!(lhs < rhs));
    }

    template< class Key, class T, class Compare, class Alloc >
    void swap( ft::map<Key,T,Compare,Alloc>& lhs,
            ft::map<Key,T,Compare,Alloc>& rhs ) {
        lhs.swap(rhs);
    }
}

#endif
