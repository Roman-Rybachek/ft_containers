/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:38:00 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/19 23:27:04 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <memory>
#include <cstdlib>
#include <iostream>

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{	
		private:
			Alloc	alloc;
			T		*c;
			size_t	size;
		public:
			//////////////////
			// Constructors //
			//////////////////

			explicit vector()	// Base 
			{c = NULL;}

			explicit vector(size_t n, \
							const T& val = 0)	// Fill [Узнать, почемy const]
			{
				c = alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					c[i] = val;
			}

			vector(const vector& copy)	// Copy
			{
				alloc = copy.alloc;
				size = copy.size;
				c = alloc.allocate(size);
				for (int i = 0; i < size; i++)
					c[i] = copy.c[i];
			}

			// --- Range constructor

			/////////////////
			//  Destructor //
			/////////////////

			~vector()
			{alloc.deallocate(c, size);}	
	};
}