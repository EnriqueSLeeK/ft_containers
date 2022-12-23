/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:37:42 by ensebast          #+#    #+#             */
/*   Updated: 2022/12/22 18:16:07 by ensebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>

namespace ft {

    template < typename T, class Allocator = std::allocator<T> >
    class Vector {
        private:
            typedef T                                           value_type;
            typedef T                                           &reference;
            typedef const T                                     &const_reference;
            typedef std::size_t                                 size_type;
            typedef std::ptrdiff_t                              difference_type;
            typedef Allocator                                   allocator_type;
        public:
            Vector  (void);
            Vector  (const Vector &vector);
            Vector  &operator=(const Vector &vector);
            ~Vector (void);
    };
}

#endif
