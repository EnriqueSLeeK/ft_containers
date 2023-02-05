/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 22:26:36 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/31 23:06:21 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include "RedBlackTree.hpp"
#include "algorithm.hpp"
#include <memory>
#include <limits>
#include <functional>

namespace ft {
template< class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key> >
    class set {
        public:
            typedef Key                                                     key_type;
            typedef Key                                                     value_type;
            typedef std::size_t                                             size_type;
            typedef std::ptrdiff_t                                          difference_type;
            typedef Compare                                                 key_compare;
            typedef Compare                                                 value_compare;
            typedef Allocator                                               allocator_type;
            typedef value_type&                                             reference;
            typedef const value_type&                                       const_reference;
            typedef typename Allocator::pointer                             pointer;
            typedef typename Allocator::const_pointer                       const_pointer;
            typedef ft::node<value_type>                                    node;
            typedef node*                                                   node_pointer;
            typedef ft::tree_iterator<value_type, node_pointer>             iterator;
            typedef ft::tree_iterator<const value_type, node_pointer>       const_iterator;
            typedef ft::reverse_iterator<iterator>                          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
            typedef ft::RedBlackTree<node, value_type, key_compare>         tree_type;
        
        private:
            tree_type _tree;

        public:
            // Constructors #########################################
            set(void) : _tree(tree_type(Compare(), Allocator())) { }

            explicit set( const Compare& comp,
                        const Allocator& alloc = Allocator() ) :
                _tree(tree_type(comp, alloc)) { }

            template< class InputIt >
            set( InputIt first, InputIt last,
                const Compare& comp = Compare(),
                const Allocator& alloc = Allocator(),
                typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt>::type = 0 ) :
                    _tree(tree_type(comp, alloc)) {
                insert(first, last);
            }

            set( const set& other ) : _tree(other._tree) { }

            // Constructors end######################################
            // Copy assign ##########################################
            set& operator=( const set& other ) {
                _tree = other._tree;
            }
            // Copy assign end#######################################
            // Getter ###############################################
            allocator_type get_allocator(void) const {
                return (_tree.getAllocator());
            }
            // Getter end ###########################################

            // Iterators ############################
            iterator begin(void) {
                return (iterator(_tree.begin()));
            }
            const_iterator begin(void) const {
                return (const_iterator(_tree.begin()));
            }

            iterator end(void) {
                return (iterator(_tree.end()));
            }

            const_iterator end(void) const {
                return (iterator(_tree.end()));
            }

            reverse_iterator rbegin(void) {
                return (reverse_iterator(end()));
            }

            const_reverse_iterator rbegin() const {
                return (reverse_iterator(end()));
            }

            reverse_iterator rend(void) {
                return (reverse_iterator(begin()));
            }

            const_reverse_iterator rend(void) const {
                return (reverse_iterator(begin()));
            }
            // Iterators end ########################

            // Capacity ##############################
            bool empty(void) const {
                if (_tree.size() == 0)
                    return (true);
                return (false);
            }

            size_type size(void) const {
                return (_tree.size());
            }

            size_type max_size(void) const {
                return (std::numeric_limits<size_type>::max() / sizeof(node));
            }
            // Capacity end ###########################

            // Modifiers ##############################
            void clear(void) {
                _tree.clear_up();
            }

            ft::pair<iterator, bool> insert ( const value_type& value ) {
                ft::pair<iterator, bool> status = ft::pair<iterator, bool>();
                status.second = false;
                if (search(value) == NULL) {
                    status.first = iterator(_tree.insert(value));
                    status.second = true;
                }
                return (status);
            }

            iterator insert ( iterator pos, const value_type& value ) {
                (void)pos;
                return (insert(value).first);
            }

            template< class InputIt >
            void insert ( InputIt first, InputIt last,
                            typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt>::type = 0) {
                for (InputIt curr = first; curr != last; curr++)
                    insert(*curr);
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
                node_pointer target = _tree.search(key);
                if (target == NULL)
                    return (0);
                _tree.delete_node(target);
                return (1);
            }

            void swap( set& other ) {
                _tree.swap(other._tree);
            }
            // Modifiers end###########################
            
            // Lookup #################################
            size_type count( const Key& key ) const {
                node_pointer target = _tree.search(value_type(key));
                if (target == NULL)
                    return (0);
                return (1);
            }

            iterator find( const Key& key ) {
                node_pointer find_target = _tree.search(key);
                if (find_target == NULL)
                    return (end());
                return (iterator(find_target));
            }

            const_iterator find( const Key& key ) const {
                node_pointer find_target = _tree.search(key);
                if (find_target == NULL)
                    return (end());
                return (const_iterator(find_target));
            }

            iterator upper_bound( const Key& key ) {
                return (iterator(_tree.upper_bound(key)));
            }

            const_iterator upper_bound( const Key& key ) const {
                return (const_iterator(_tree.upper_bound(key)));
            }

            iterator lower_bound( const Key& key ) {
                return (iterator(_tree.lower_bound(key)));
            }

            const_iterator lower_bound( const Key& key ) const {
                return (const_iterator(_tree.lower_bound(key)));
            }

            ft::pair<iterator,iterator> equal_range( const Key& key ) {
                return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
            }

            ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
                return (ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
            }
            // Lookup end #############################
            //  Observers #############################
            key_compare key_comp(void) const {
                return (_tree.getComparator());
            }

            ft::set<Key, Compare, Allocator>::value_compare value_comp(void) const {
                return (Compare());
            }
            //  Observers end##########################
    };
    template< class Key, class Compare, class Alloc >
    bool operator==( const ft::set<Key,Compare,Alloc>& lhs,
                    const ft::set<Key,Compare,Alloc>& rhs ) {
        return (lhs.size() == rhs.size() && ft::equal(lhs, rhs));
    }


    template< class Key,  class Compare, class Alloc >
    bool operator<( const ft::set<Key,Compare,Alloc>& lhs,
                    const ft::set<Key,Compare,Alloc>& rhs ) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
                    rhs.begin(), rhs.end()));
    }

    template< class Key, class Compare, class Alloc >
    bool operator!=( const ft::set<Key,Compare,Alloc>& lhs,
                    const ft::set<Key,Compare,Alloc>& rhs ) {
        return (!(lhs == rhs));
    }


    template< class Key, class Compare, class Alloc >
    bool operator<=( const ft::set<Key,Compare,Alloc>& lhs,
                     const ft::set<Key,Compare,Alloc>& rhs ) {
        return (lhs < rhs || lhs == rhs);
    }

    template< class Key, class Compare, class Alloc >
    bool operator>( const ft::set<Key,Compare,Alloc>& lhs,
                    const ft::set<Key,Compare,Alloc>& rhs ) {
        return ((lhs != rhs)  && !(lhs < rhs));
    }

    template< class Key, class Compare, class Alloc >
    bool operator>=( const ft::set<Key,Compare,Alloc>& lhs,
                    const ft::set<Key,Compare,Alloc>& rhs ) {
        return (lhs > rhs || lhs == rhs);
    }

    template< class Key, class Compare, class Alloc >
    void swap( ft::set<Key,Compare,Alloc>& lhs,
                ft::set<Key,Compare,Alloc>& rhs ) {
        lhs.swap(rhs);
    }
}
#endif
