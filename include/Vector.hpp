/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:37:42 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/27 21:57:40 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <limits>
#include <memory>
#include <stdexcept>
#include "random_access_iterator.hpp"
#include "algorithm.hpp"
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
            vector  (void) :
                _data(NULL),
                _size(0),
                _capacity(0),
                _allocator(Allocator()) {}

            explicit vector( const Allocator& alloc ) :
                _data(NULL),
                _size(0),
                _capacity(0),
                _allocator(Allocator()) {}

            explicit vector( size_type count,
                    const T& value = T(),
                    const Allocator& alloc = Allocator()) :
                _allocator(alloc),
                _size(count),
                _capacity(count),
                _data(alloc.allocate(count)) {
                    assign(count, value);
            }

            template< class InputIt >
            vector( InputIt first,
                    InputIt last,
                    const Allocator& alloc = Allocator()) :
                _allocator(alloc),
                _size(first - last),
                _capacity(first - last),
                _data(alloc.allocate(first - last)) {
                    assign(first, last);
            }

            vector  (const vector &other) :
                _data(other.allocator.allocate(other._capacity)),
                _size(other._size),
                _capacity(other._capacity),
                _allocator(other.allocator) {
                    for (size_t i = 0; i < other._size; i++)
                        _allocator.construct(_data + i, *(other._data + i));
            }
            // Construtors end######

            // Get allocator #####
            allocator_type  getAllocator(void) {
                return (_allocator);
            }
            // Get allocator end##

            // Destructor###############
            ~vector (void) {
                clear();
                _allocator.deallocate(_data, _capacity);
            }
            // Destructor end###########

            // Copy assign and assign#######
            vector  &operator=(const vector &other) {
                _data = other._data;
                _capacity = other._capacity;
                _size = other._size;
                _allocator = other._allocator;
            }

            void assign( size_type count, const T& value ) {
                for (size_type i = 0; i < count; i++)
                    _allocator.construct(_data + i, value);
            }

            template< class InputIt >
            void assign( InputIt first, InputIt last ) {
                for (size_type offset = 0; (first + offset) < last; offset++)
                    _allocator.construct(_data + offset, *(first + offset));
            }
            // Copy assign and assign end###

             // Iterator ###############
             iterator begin(void) {
                 return (iterator(_data));
             }

             const_iterator begin(void) const {
                 return (const_iterator(_data));
             }

             iterator end(void) {
                 return (iterator(_data + _size));
             }

             const_iterator end(void) const {
                 return (const_iterator(_data + _size));
             }

             reverse_iterator rbegin(void) {
                 return (reverse_iterator(end()));
             }

             const_reverse_iterator rbegin(void) const {
                 return (const_reverse_iterator(end()));
             }

             reverse_iterator rend(void) {
                 return (reverse_iterator(begin()));
             }

             const_reverse_iterator rend(void) const {
                 return (const_reverse_iterator(begin()));
             }
             // Iterator end############

             // Accessors ##############
             reference at(size_type pos) {
                 if (!(pos < size()))
                     throw std::out_of_range("Out of range");
                 return (*(_data + pos));
             }

             const_reference at( size_type pos ) const {
                 if (!(pos < size()))
                     throw std::out_of_range("Out of range");
                 const_reference const_ref = *(_data + pos);
                 return (const_ref);
             }

             reference operator[] (size_type idx) {
                 return (_data[idx]);
             }

             const_reference operator[] (size_type idx) const {
                 return (_data[idx]);
             }

             reference front( void ) {
                 return (*(begin()));
             }

             const_reference front ( void ) const {
                 return (*(begin()));
             }

             reference back( void ) {
                 return (*(end() - 1));
             }

             const_reference back (void ) const {
                 return (*(end() - 1));
             }

             pointer data(void) {
                 if (_size == 0)
                     return (NULL);
                 return (begin());
             }

             const pointer data(void) const {
                 if (_size == 0)
                     return (NULL);
                 return (begin());
             }
             // Accessors end ##########
             
             // Capacity ###############
             bool empty(void) {
                 if (size() == 0)
                     return (true);
                 return (false);
             }

             size_type size(void) const {
                 return (_size);
             }

             size_type capacity(void) const {
                 return (_capacity);
             }

             size_type max_size(void) const {
                 return (std::numeric_limits<difference_type>::max());
             }

             void reserve (size_type new_cap) {
                 if (new_cap > max_size())
                     throw std::length_error("Max size exceeded");
                 if (new_cap < capacity())
                     return ;
                 resize(new_cap);
             }
             // Capacity end ###########

             // Member functions#########
             iterator erase( iterator first, iterator last ) {
                 for (iterator curr = first; curr < last; curr++)
                     erase(curr);
                 return (last);
             }

             iterator erase( iterator pos ) {
                 if (_size == 0)
                     return (begin());
                 _allocator.destroy(pos);
                 _size -= 1;
                 return (pos);
             }

             iterator insert( const_iterator pos, const T& value ) {
                 if (_size + 1 > _capacity)
                     resize(_capacity * 2);
                 copy_offset(pos, end() - pos, 1);
                 _allocator.destroy(pos);
                 _allocator.construct(pos, value);
                 _size++;
             }

             iterator insert( const_iterator pos, size_type count, const T& value ) {
                 if (_size + count > _capacity)
                     resize(_capacity * 2);
                 copy_offset(pos, end() - pos, count);
                 for (size_type i = 0; i < count; i++) {
                    _allocator.destroy(pos + i);
                    _allocator.construct(pos + i, value);
                 }
                 _size += count;
             }

             template< class InputIt >
             iterator insert( const_iterator pos, InputIt first, InputIt last ) {
                 if (_size + (first - last) > _capacity)
                     resize(_capacity * 2);
                 copy_offset(pos, end() - pos, last - first);
                 for (size_type i = 0; (first + i) != last; i++) {
                    _allocator.destroy(pos + i);
                    _allocator.construct(pos + i, *(first + i));
                 }
                 _size += last - first;
             }

             void clear( void ) {
                 for (iterator curr = begin(); curr < end(); curr++)
                     erase(curr);
             }

             void push_back( const T& value ) {
                try {
                    if (_size + 1 > _capacity)
                        resize(_capacity * 2);
                    _allocator.destroy(_data + _size);
                    _allocator.construct(_data + _size, value);
                }
                catch (std::out_of_range &e) {}
             }

             void pop_back( void ) {
                 if (_size == 0)
                     return ;
                 erase(_data + _size - 1);
             }

             void resize ( size_type count ) {
                 if (count > max_size())
                     throw std::length_error("Max size exceeded");
                 pointer tmp = _allocator.allocate(count);

                 if (count < _size)
                    copy(tmp, begin(), begin() + count);
                 else
                    copy(tmp, begin(), begin() + _size);

                 clear();
                 _allocator.deallocate(_data, _capacity);
                 _capacity = count;
                 _data = tmp;
                 if (count < _size)
                     _size = count;
             }

             void resize( size_type count, T value = T() ) {
                 if (count > max_size())
                     throw std::length_error("Max size exceeded");
                 pointer tmp = _allocator.allocate(count);

                 if (count < _size)
                    copy(tmp, begin(), begin() + count);
                 else {
                    copy(tmp, begin(), begin() + _size);
                    fill(tmp, count - _size, value);
                 }

                 clear();
                 _allocator.deallocate(_data, _capacity);
                 _capacity = count;
                 _data = tmp;
                 if (count < _size)
                     _size = count;
             }

             void swap( vector& other ) {
                 pointer tmp = _data;
                 size_type tmp_size = _size;
                 size_type tmp_capacity = _capacity;

                 _data = other._data;
                 _size = other._size;
                 _capacity = other._capacity;

                 other._data = tmp;
                 other._size = tmp_size;
                 other._capacity = tmp_capacity;
             }
             // Member functions end#####

        private:
             void copy(pointer buff, iterator first, iterator last) {
                 for (size_type offset = 0 ; (first + offset) < last; offset++)
                     _allocator.construct((buff + offset), *(first + offset));
             }

             void copy_offset (pointer pos, size_type total_steps, size_type offset) {
                 pointer positionWithOffset = pos + offset;
                 for (size_type step = 0; step < total_steps; step++) {
                     _allocator.destroy(positionWithOffset + step);
                     _allocator.construct((positionWithOffset + step), *(pos + step));
                 }
             }

             void fill(pointer buff, size_type count, T value) {
                 for (size_type offset = 0; offset < count; offset++)
                     *(buff + offset) = value;
             }
    };

    template< class T, class Alloc >
    bool operator==( const ft::vector<T,Alloc>& lhs,
                     const ft::vector<T,Alloc>& rhs ) {
        return ((lhs.size() == rhs.size())
                && ft::equal(lhs.begin(), lhs.end(),
                    rhs.begin(), rhs.end()));
    }

    template< class T, class Alloc >
    bool operator!=( const ft::vector<T,Alloc>& lhs,
                     const ft::vector<T,Alloc>& rhs ) {
        return (!(lhs == rhs));
    }

    template< class T, class Alloc >
    bool operator<( const ft::vector<T,Alloc>& lhs,
                    const ft::vector<T,Alloc>& rhs ) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
                    rhs.begin(), rhs.end()));
    }

    template< class T, class Alloc >
    bool operator>( const ft::vector<T,Alloc>& lhs,
                    const ft::vector<T,Alloc>& rhs ) {
        return (!(lhs < rhs));
    }

    template< class T, class Alloc >
    bool operator<=( const ft::vector<T,Alloc>& lhs,
                     const ft::vector<T,Alloc>& rhs ) {
        return (lhs < rhs || lhs == rhs);
    }

    template< class T, class Alloc >
    bool operator>=( const ft::vector<T,Alloc>& lhs,
                     const ft::vector<T,Alloc>& rhs ) {
        return (lhs > rhs || lhs == rhs);
    }

    template< class T, class Alloc >
    void swap( ft::vector<T,Alloc>& lhs,
               ft::vector<T,Alloc>& rhs ) {
        lhs.swap(rhs);
    }
}

#endif
