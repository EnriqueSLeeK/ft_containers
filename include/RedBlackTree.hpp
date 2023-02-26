/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:10:49 by ensebast          #+#    #+#             */
/*   Updated: 2023/02/02 20:19:13 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

#include <cstddef>
#include <memory>
#include <iostream>
#include <algorithm>
#include "utility.hpp"
#include "tree_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

# define RED false
# define BLACK true
    
    template < class T >
    struct node {

        typedef T   value_type;

        value_type  value;
        const bool  end_node;
        node        *left;
        node        *right;
        node        *parent;
        bool        color;

        node (const value_type &val) : value(val),
                                        end_node(false),
                                        left(NULL),
                                        right(NULL),
                                        parent(NULL),
                                        color(RED) {}
        node (void) : end_node(true),
                        left(NULL),
                        right(NULL),
                        parent(NULL),
                        color(BLACK) {}
    };

    template < class n_type,
             class v_type,
             class Compare = std::less<v_type>,
             class Allocator = std::allocator< n_type > >
    class RedBlackTree {
        private:
            typedef v_type                                                  value_type;
            typedef n_type                                                  node_type;
            typedef std::size_t                                             size_type;
            typedef std::ptrdiff_t                                          difference_type;
            typedef Compare                                                 compare_type;
            typedef Allocator                                               allocator_type;
            typedef typename Allocator::pointer                             pointer;
            typedef typename Allocator::const_pointer                       const_pointer;
            typedef node_type&                                              reference;
            typedef node_type*                                              node_pointer;
            typedef ft::tree_iterator<value_type, node_pointer>             iterator;
            typedef ft::tree_iterator<const value_type, node_pointer>       const_iterator;

        private:
            allocator_type  _allocator;
            compare_type    _comp;

            node_pointer    _root;
            node_pointer    _end;

            size_type       _size;

            RedBlackTree (void) {}

        public:

            RedBlackTree (Compare comp,
                const Allocator& alloc = Allocator()) :
                _allocator(alloc),
                _comp(comp),
                _root(NULL),
                _end(new node_type()),
                _size(0) { }

            ~RedBlackTree (void) {
                clean_up(_root);
                delete _end;
            }
            
            // Copy constructor
            RedBlackTree (const RedBlackTree &tree) :
                _allocator(tree._allocator),
                _comp(tree._comp),
                _root(NULL),
                _end(new node_type()),
                _size(0) {
                *this = tree;
            }
            
            RedBlackTree &operator=(const RedBlackTree &tree) {
                _allocator = tree._allocator;
                _comp = tree._comp;
                return (*this);
            }

            allocator_type getAllocator(void) const {
                return (_allocator);
            }

            compare_type getComparator(void) const {
                return (_comp);
            }

            node_pointer insert(const value_type &val) {

                node_pointer new_node = create_node(val);

                node_pointer y = NULL;

                for (node_pointer x = _root;
                        x != NULL && x != _end;
                        x = _comp(new_node->value, x->value) ? x->left : x->right)
                    y = x;

                if (_end->parent == NULL) {
                    new_node->right = _end;
                    _end->parent = new_node;
                }
                else if (_comp(_end->parent->value,
                            new_node->value)) {
                    _end->parent->right = NULL;
                    _end->parent = new_node;
                    new_node->right = _end;
                }

                new_node->parent = y;
                if (y == NULL)
                    _root = new_node;
                else if (_comp(new_node->value, y->value))
                    y->left = new_node;
                else
                    y->right = new_node;

                _size++;

                // Fix tree rotating some sections if necessary
                fixInsertRb(new_node);
                return (new_node);
            }

            void delete_node (node_pointer target) {

                if (target == NULL || target == _end)
                    return ;

                node_pointer x = NULL;
                node_pointer y = target;

                bool y_original_color = y->color;
                bool flag = false;

                if (target->right == _end)
                    flag = true;
                
                if (target->left == NULL) {
                    x = target->right;
                    transplant(target, target->right);
                }
                else if (target->right == NULL || target->right == _end) {
                    x = target->left;
                    transplant(target, target->left);
                }
                else {
                    y = minimum(target->right);
                    y_original_color = y->color;
                    x = y->right;
                    if (x != NULL
                        && y->parent == target) {
                        x->parent = y;
                    }
                    else {
                        transplant(y, y->right);
                        y->right = target->right;
                        if (y->right != NULL)
                            y->right->parent = y;
                    }
                    transplant(target, y);
                    y->left = target->left;
                    y->left->parent = y;
                    y->color = target->color;
                }

                _size--;

                destroy_node(target);
                
                if (y_original_color == BLACK)
                    deleteFix(x);

                if (!flag)
                    return ;
                
                pointer max = maximum(_root->right);
                if (max) {
                   max->right = _end; 
                   _end->parent = max;
                }
            }
            
            node_pointer get_root (void) const {
                return (_root);
            }

            node_pointer search (const value_type &val) const {
                value_type tmp = val;
                node_pointer curr = _root;

                while (curr != NULL && curr != _end) {
                    
                    if (curr->value == val)
                        return (curr);
                    curr = _comp(tmp, curr->value) ? curr -> left : curr -> right;
                }
                return (NULL);
            }

            node_pointer upper_bound (const value_type &val) const {
               value_type tmp = val;
                node_pointer curr = _root;

                while (curr != NULL && curr != _end) {
                    if (curr->value > tmp)
                        return (curr);
                    curr = _comp(tmp, curr->value) ? curr -> left : curr -> right;
                }
                return (_end);
            }

            node_pointer lower_bound (const value_type &val) const {
                value_type tmp = val;
                node_pointer curr = _root;
                node_pointer candidate = NULL;
                bool status = false;

                while (curr != NULL && curr != _end) {
                    status = curr->value >= tmp;
                    if (status)
                        candidate = curr;

                    curr = _comp(tmp, curr->value) ? curr -> left : curr -> right;
                }
                if (candidate == NULL)
                    return (_end);
                return (candidate);
            }

            size_t size (void) const {
                return (_size);
            }

            void clear_up (void) {
                clean_up(_root);
                _end->parent = NULL;
                _root = NULL;
                _size = 0;
            }

            pointer begin (void) const {
                pointer min_node = minimum(_root);
                if (min_node == NULL)
                    return (_end);
                return (min_node);
            }

            pointer end (void) const {
                return (_end);
            }

            // Swapping each other
            void swap (RedBlackTree &other) {
                std::swap(_allocator, other._allocator);
                std::swap(_comp, other._comp);
                std::swap(_root, other._root);
                std::swap(_size, other._size);
                std::swap(_end, other._end);
            }

        private:
            // Node creation
            node_pointer    create_node(const value_type &val) {
                node_pointer new_node = _allocator.allocate(1);
                _allocator.construct(new_node, val);
                return (new_node);
            }

            // Node destruction
            void            destroy_node(node_pointer node_obj) {
                if (node_obj == NULL || node_obj == _end)
                    return ;
                _allocator.destroy(node_obj);
                _allocator.deallocate(node_obj, 1);
            }

            // ref_node => the rotation will happen will happen in relation
            //                  to this node
            void            rotation_left (node_pointer ref_node) {
                node_pointer y = ref_node->right;
                if (y) {
                    ref_node->right = y->left;
                    if (y->left != NULL)
                        y->left->parent = ref_node;
                    y->parent = ref_node->parent;
                }

                if (ref_node->parent == NULL)
                    _root = y;
                else if (ref_node == ref_node->parent->left)
                    ref_node->parent->left = y;
                else
                    ref_node->parent->right = y;

                if (y)
                    y->left = ref_node;
                ref_node->parent = y;
            }

            void rotation_right (node_pointer ref_node) {

                node_pointer y = ref_node->left;

                if (y) {
                    ref_node->left = y->right;

                    if (y->right != NULL)
                        y->right->parent = ref_node;
                    y->parent = ref_node->parent;
                }

                if (ref_node->parent == NULL)
                    _root = y;
                else if (ref_node == ref_node->parent->right)
                    ref_node->parent->right = y;
                else
                    ref_node->parent->left = y;

                if (y)
                    y->right = ref_node;
                ref_node->parent = y;
            }

            void fixInsertRb (node_pointer new_node) {
                node_pointer y = NULL;

                while (new_node->parent != NULL && new_node->parent->color == RED) {

                    if (new_node->parent == new_node->parent->parent->left) {
                        y = new_node->parent->parent->right;
                        if (y != NULL && y->color == RED) {
                            new_node->parent->color = BLACK;
                            y->color = BLACK;
                            new_node->parent->parent->color = RED;
                            new_node = new_node->parent->parent;
                        }
                        else {
                            if (new_node == new_node->parent->right) {
                                new_node = new_node->parent;
                                rotation_left(new_node);
                            }
                            new_node->parent->color = BLACK;
                            new_node->parent->parent->color = RED;
                            rotation_right(new_node->parent->parent);
                        }
                    }

                    else {
                        y = new_node->parent->parent->left;
                        if (y != NULL && y->color == RED) {
                            new_node->parent->color = BLACK;
                            y->color = BLACK;
                            new_node->parent->parent->color = RED;
                            new_node = new_node->parent->parent;
                        }
                        else {
                            if (new_node == new_node->parent->left) {
                                new_node = new_node->parent;
                                rotation_right(new_node);
                            }
                            new_node->parent->color = BLACK;
                            new_node->parent->parent->color = RED;
                            rotation_left(new_node->parent->parent);
                        }
                    }

                }
                _root->color = BLACK;
            }

            void clean_up (node_pointer curr) {
                if (curr == NULL || curr == _end )
                    return ;
                clean_up(curr->left);
                clean_up(curr->right);
                destroy_node(curr);
            }

            void transplant (node_pointer u, node_pointer v) {
                if (u->parent == NULL)
                    _root = v;
                else if (u == u->parent->left)
                    u->parent->left = v;
                else
                    u->parent->right = v;

                if (v != NULL)
                    v->parent = u->parent;
            }

            pointer minimum (pointer relative_node) const {
                if (relative_node == NULL)
                    return (relative_node);
                while (relative_node->left != NULL)
                    relative_node = relative_node->left;
                return (relative_node);
            }

            pointer maximum (pointer relative_node) const {
                if (relative_node == NULL)
                    return (relative_node);
                while (relative_node->right != NULL
                        && relative_node->right != _end) {
                    relative_node = relative_node->right;
                }
                return (relative_node);
            }

            void deleteFix (node_pointer x) {
                node_pointer w = NULL;
                while (x != _end
                        && x != NULL
                        && x != _root
                        && x->color == BLACK) {
                    if (x == x->parent->left) {
                        w = x->parent->right;

                        if (w != 0) {
                            if (w->color == RED) {
                                w->color = BLACK;
                                x->parent->color = RED;
                                rotation_left(x->parent);
                                w = x->parent->right;
                            }
                            if ((w->left && w->left->color == BLACK)
                                && (w->right && w->right->color == BLACK)) {
                                w->color = RED;
                                x = x->parent;
                            }
                            else {
                                if (w->right && w->right->color == BLACK) {
                                    w->left->color = BLACK;
                                    w->color = RED;
                                    rotation_right(w);
                                    w = x->parent->right;
                                }
                                w->color = x->parent->color;
                                x->parent->color = BLACK;
                                w->right->color = BLACK;
                                rotation_left(x->parent);
                                x = _root;
                            }
                        }
                    }

                    else {
                        w = x->parent->left;

                        if (w != 0) {
                            if (w->color == RED) {
                                w->color = BLACK;
                                x->parent->color = RED;
                                rotation_right(x->parent);
                                w = x->parent->left;
                            }

                            if ((w->left && w->left->color == BLACK)
                                && (w->right && w->right->color == BLACK)) {
                                w->color = RED;
                                x = x->parent;
                            }
                            else {
                                if (w->left && w->left->color == BLACK) {
                                    w->right->color = BLACK;
                                    w->color = RED;
                                    rotation_left(w);
                                    w = x->parent->left;
                                }
                                w->color = x->parent->color;
                                x->parent->color = BLACK;
                                w->left->color = BLACK;
                                rotation_right(x->parent);
                                x = _root;
                            }
                        }
                    }
                }
                x->color = BLACK;
            }
            
            void show_map (pointer curr) {
                if (curr == NULL || curr == _end)
                    return ;
                show_map(curr->right);
                show_map(curr->left);
            }
    };

}

#endif
