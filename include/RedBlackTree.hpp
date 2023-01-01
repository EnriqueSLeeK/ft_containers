/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:10:49 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/31 21:51:46 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

#include <memory>
#include <algorithm>
#include "reverse_iterator.hpp"
#include "utility.hpp"
#include "tree_iterator.hpp"


namespace ft {

# define RED false
# define BLACK true
    
    template < class T >
    struct node {
            typedef T   value_type;

            value_type  value;
            node        *left;
            node        *right;
            node        *parent;
            bool        color;

            node (void) : left(NULL), right(NULL), parent(NULL), color(RED) {}
            node (const value_type &val) : value(val), left(NULL), right(NULL), parent(NULL), color(RED) {}
    };

    template <typename T>
    bool operator== (const node<T> &first, const node<T> &other) {
        return (first.value == other.value);
    }

    template <typename T>
    bool operator< (const node<T> &first, const node<T> &other) {
        return (first.value < other.value);
    }


    template < class n_type, class v_type, class Compare = std::less<n_type>, class Allocator = std::allocator< n_type > >
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

            size_type       _size;

        public:
            RedBlackTree (void) :
                _allocator(allocator_type()),
                _comp(compare_type()),
                _size(0) {
                    _root = NULL;
            }

            RedBlackTree (Compare &comp,
                const Allocator& alloc = Allocator()) :
                _allocator(alloc),
                _comp(comp),
                _size(0) {
                    _root = NULL;
            }

            ~RedBlackTree (void) {
                clean_up(_root);
                destroy_node(NULL);
            }

            
            // Copy constructor
            RedBlackTree (const RedBlackTree &tree) {
                *this = tree;
            }
            
            RedBlackTree &operator=(const RedBlackTree &tree) {
                if (_root != tree._root)
                    clean_up(_root);
                _root = tree._root;
                _size = tree._size;
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
                node_pointer x = _root;
                while (x != NULL) {
                    y = x;
                    if (_comp(new_node->value, x->value))
                        x = x -> left;
                    else
                        x = x -> right;
                }
                new_node->parent = y;
                if (y == NULL)
                    _root = new_node;
                else if (_comp(new_node->value, y->value))
                    y->left = new_node;
                else
                    y->right = new_node;
                new_node->left = NULL;
                new_node->right = NULL;
                _size++;
                fixInsertRb(new_node);
                return (new_node);
            }

            void delete_node (node_pointer target) {
                node_pointer y = target;
                node_pointer x = NULL;
                bool y_original_color = y->color;

                if (target->left == NULL) {
                    x = target->right;
                    transplant(target, target->right);
                }
                else if (target->right == NULL) {
                    x = target->left;
                    transplant(target, target->left);
                }
                else {
                    y = minimum(target->right);
                    y_original_color = y->color;
                    x = y->right;
                    if (y->parent == target)
                        x->parent = y;
                    else {
                        transplant(y, y->right);
                        y->right = target->right;
                        y->right->parent = y;
                    }
                    transplant(target, y);
                    y->left = target->left;
                    y->left->parent = y;
                    y->color = target->color;
                }

                if (y_original_color == BLACK)
                    deleteFix(x);

                _size--;
                destroy_node(target);
            }

            node_pointer search (const value_type &val) {
                node_pointer curr = _root;
                while (curr != NULL || val.first != curr->first)
                    curr = _comp(val, curr->value) ? curr -> right : curr -> left;
                return (curr);
            }

            iterator upper_bound (const value_type &val) {
                iterator iter = iterator(begin());
                for (size_type i = 0; i < _size; i++) {
                    if (_comp(val, *iter))
                        break ;
                    ++iter;
                }
                return (iter);
            }

            const_iterator upper_bound (const value_type &val) const {
                const_iterator iter = iterator(begin());
                for (size_type i = 0; i < _size; i++) {
                    if (_comp(val, *iter))
                        break ;
                    ++iter;
                }
                return (iter);
            }

            iterator lower_bound (const value_type &val) {
                iterator iter = iterator(begin());
                for (size_type i = 0; i < _size; i++) {
                    if (!(_comp(*iter, val)))
                        return (iter);
                    ++iter;
                }
                return (iterator(end()));
            }

            const_iterator lower_bound (const value_type &val) const {
                const_iterator iter = iterator(begin());
                for (size_type i = 0; i < _size; i++) {
                    if (!(_comp(*iter, val)))
                        return (iter);
                    ++iter;
                }
                return (const_iterator(end()));
            }

            size_t size (void) const {
                return (_size);
            }

            void clear_up (void) {
                clean_up(_root);
                _size = 0;
            }

            node_pointer begin(void) {
                return (minimum());
            }

            node_pointer end(void) {
                return (maximum());
            }

            void swap( RedBlackTree &other) {
                std::swap(_allocator, other._allocator);
                std::swap(_comp, other._comp);
                std::swap(_root, other._root);
                std::swap(_size, other._size);
            }

        private:
            // Node creation
            node_pointer    create_node(const value_type &val) {
                node_pointer new_node = _allocator.allocate(1);
                _allocator.construct(new_node, val);
                new_node -> left = NULL;
                new_node -> right = NULL;
                new_node -> parent = NULL;
                return (new_node);
            }

            // Node destruction
            void            destroy_node(node_pointer node_obj) {
                _allocator.destroy(node_obj);
                _allocator.deallocate(node_obj, 1);
            }

            // ref_node => the rotation will happen will happen in relation
            // to this node
            void            rotation_left (node_pointer ref_node) {
                node_pointer y = ref_node->right;
                ref_node->right = y->left;
                if (y->left != NULL)
                    y->left->parent = ref_node;
                y->parent = ref_node->parent;
                if (ref_node->parent == NULL)
                    _root = y;
                else if (ref_node == ref_node->parent->left)
                    ref_node->parent->left = y;
                else
                    ref_node->parent->right = y;
                y->left = ref_node;
                ref_node->parent = y;
            }

            void rotation_right (node_pointer ref_node) {
                node_pointer y = ref_node->left;
                ref_node->left = y->right;
                if (y->right != NULL)
                    y->right->parent = ref_node;
                y->parent = ref_node->parent;
                if (ref_node->parent == NULL)
                    _root = y;
                else if (ref_node == ref_node->parent->right)
                    ref_node->parent->right = y;
                else
                    ref_node->parent->left = y;
                y->right = ref_node;
                ref_node->parent = y;
            }

            void fixInsertRb (node_pointer new_node) {
                node_pointer y = NULL;
                while (new_node->parent->color == RED) {
                    if (new_node->parent == new_node->parent->parent->left) {
                        y = new_node->parent->parent->right;
                        if (y->color == RED) {
                            new_node->parent->color = BLACK;
                            y->color = BLACK;
                            new_node->parent->parent->color = RED;
                        }
                        else if (new_node == new_node->parent->right) {
                            new_node = new_node->parent;
                            rotation_left(new_node);
                            new_node->parent->color = BLACK;
                            new_node->parent->parent->color = RED;
                            rotation_right(new_node->parent->parent);
                        }
                    }
                    else {
                        y = new_node->parent->parent->left;
                        if (y->color == RED) {
                            new_node->parent->color = BLACK;
                            y->color = BLACK;
                            new_node->parent->parent->color = RED;
                        }
                        else if (new_node == new_node->parent->left) {
                            new_node = new_node->parent;
                            rotation_right(new_node);
                            new_node->parent->color = BLACK;
                            new_node->parent->parent->color = RED;
                            rotation_left(new_node->parent->parent);
                        }
                    }
                }
                _root->color = BLACK;
            }

            void clean_up (node_pointer curr) {
                if (curr == NULL)
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
                v->parent = u->parent;
            }

            node_pointer minimum (node_pointer relative_node) {
                if (relative_node == NULL)
                    return (relative_node);
                while (relative_node->left != NULL)
                    relative_node = relative_node->left;
                return (relative_node);
            }

            node_pointer maximum (node_pointer relative_node) {
                if (relative_node == NULL)
                    return (relative_node);
                while (relative_node->right != NULL)
                    relative_node = relative_node->right;
                return (relative_node);
            }

            void deleteFix (node_pointer x) {
                node_pointer w = NULL;
                while (x != _root && x->color == BLACK) {
                    if (x == x->parent->left) {
                        w = x->parent->right;
                        if (w->color == RED) {
                            w->color = BLACK;
                            x->parent->color = RED;
                            rotation_left(x->parent);
                            w = x->parent->right;
                        }
                        if (w->left->color == BLACK && w->right->color == BLACK) {
                            w->color = RED;
                            x = x->parent;
                        }
                        else if (w->right->color == BLACK) {
                            w->left->color = BLACK;
                            w->color = RED;
                            rotation_right(w);
                            w = x->parent->right;
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            w->right->color = BLACK;
                            rotation_left(x->parent);
                            x = _root;
                        }
                    }
                    else {
                        w = x->parent->left;
                        if (w->color == RED) {
                            w->color = BLACK;
                            x->parent->color = RED;
                            rotation_right(x->parent);
                            w = x->parent->left;
                        }
                        if (w->left->color == BLACK && w->right->color == BLACK) {
                            w->color = RED;
                            x = x->parent;
                        }
                        else if (w->left->color == BLACK) {
                            w->right->color = BLACK;
                            w->color = RED;
                            rotation_left(w);
                            w = x->parent->left;
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            w->left->color = BLACK;
                            rotation_right(x->parent);
                            x = _root;
                        }
                    }
                    x->color = BLACK;
                }
            }
    };
}

#endif
