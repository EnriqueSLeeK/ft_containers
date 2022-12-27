/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:37:42 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/26 19:01:56 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

    template < typename T, class Allocator = std::allocator<T> >
    class vector {

        private:
            typedef T                                               value_type;
            typedef T                                               &reference;
            typedef const T                                         &const_reference;
            typedef std::size_t                                     size_type;
            typedef std::ptrdiff_t                                  difference_type;
            typedef Allocator                                       allocator_type;
            typedef typename Allocator::pointer                     pointer;
            typedef typename Allocator::const_pointer               const_pointer;
            typedef ft::random_access_iterator<value_type>          iterator;
            typedef ft::random_access_iterator<const value_type>    const_iterator;
            typedef ft::reverse_iterator<iterator>                  reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;

        private:
            pointer         _data;
            size_type       _size;
            size_type       _capacity;
            allocator_type  _allocator;

        public:
            // Construtors##########
            vector  (void) : _data(NULL), _size(0), _capacity(0), _allocator(Allocator()) {}
            explicit vector( const Allocator& alloc ) : _data(NULL), _size(0), _capacity(0), _allocator(Allocator()) {}
            explicit vector( size_type count,
                             const T& value = T(),
                             const Allocator& alloc = Allocator());
            template< class InputIt >
            vector( InputIt first, InputIt last,
                    const Allocator& alloc = Allocator() );

            vector  (const vector &vector);
            // Construtors end######

            // Get allocator #####
            allocator_type  getAllocator(void);
            // Get allocator end##

            // Destructor###############
            ~vector (void);
            // Destructor end###########

            // Copy assign and assign#######
            vector  &operator=(const vector &vector);
            void assign( size_type count, const T& value );
            template< class InputIt >
            void assign( InputIt first, InputIt last );
            // Copy assign and assign end###

             // Iterator ###############
             iterator begin(void);
             const_iterator begin(void) const;
             iterator end(void);
             const_iterator end(void) const;
             reverse_iterator rbegin(void);
             const_reverse_iterator rbegin(void) const;
             reverse_iterator rend(void);
             const_reverse_iterator rend(void) const;
             // Iterator end############

             // Member functions#########
             iterator erase( iterator first, iterator last );
             iterator erase( iterator pos );
             iterator insert( const_iterator pos, const T& value );
             iterator insert( const_iterator pos, size_type count, const T& value );
             template< class InputIt >
             iterator insert( const_iterator pos, InputIt first, InputIt last );
             void clear( void );
             void push_back( const T& value );
             void pop_back( void );
             void resize( size_type count, T value = T() );
             void swap( vector& other );
             // Member functions end#####
    };

    template< class T, class Alloc >
    bool operator==( const ft::vector<T,Alloc>& lhs,
                     const ft::vector<T,Alloc>& rhs );

    template< class T, class Alloc >
    bool operator!=( const ft::vector<T,Alloc>& lhs,
                     const ft::vector<T,Alloc>& rhs );

    template< class T, class Alloc >
    bool operator<=( const ft::vector<T,Alloc>& lhs,
                     const ft::vector<T,Alloc>& rhs );

    template< class T, class Alloc >
    bool operator<( const ft::vector<T,Alloc>& lhs,
                    const ft::vector<T,Alloc>& rhs );

    template< class T, class Alloc >
    bool operator>( const ft::vector<T,Alloc>& lhs,
                    const ft::vector<T,Alloc>& rhs );

    template< class T, class Alloc >
    bool operator>=( const ft::vector<T,Alloc>& lhs,
                     const ft::vector<T,Alloc>& rhs );

    template< class T, class Alloc >
    void swap( ft::vector<T,Alloc>& lhs,
               ft::vector<T,Alloc>& rhs );
}

#endif
