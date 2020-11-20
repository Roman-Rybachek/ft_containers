/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:38:00 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/20 23:16:37 by jeldora          ###   ########.fr       */
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
			vector()	// Base 
			{	c = NULL; size = 0;		}
			explicit vector(size_t n, const T& val = 0)	// Fill [Узнать, почемy const]
			{
				c = alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					c[i] = val;
				size = n;
			}
			vector(const vector<T>& copy)	// Copy
			{
				alloc = copy.alloc;
				size = copy.size;
				c = alloc.allocate(size);
				for (size_t i = 0; i < size; i++)
					c[i] = copy.c[i];
			}

			template <class TemplateIterator>
			vector(TemplateIterator &first, TemplateIterator &last)
			{
				if (last < first)
					throw std::exception();
				size = last - first;
				c = alloc.allocate(size);
				for (size_t i = 0; i < size; i++)
					c[i] = *(first + i);
			}

			~vector()
			{alloc.deallocate(c, size);}	

			T&	operator[](size_t index)
			{return (c[index]);}

			class iterator
			{
				private:
					ft::vector<T>	*current;
					int				index;
				public:
					iterator()
					{	current = NULL; index = 0;	}
					iterator(const iterator &copy)
					{	current = copy.current; index = copy.index;		}
					iterator(ft::vector<T> *set_current, size_t set_index)
					{	current = set_current; index = set_index;	}
					T &operator*()
					{	return(current->c[index]);		}
					iterator &operator=(const iterator &copy)
					{
						current = copy.current;
						index = copy.index;
						return (*this);
					}
					iterator &operator++()
					{	index++; return (*this);	}
					iterator &operator--()
					{	index--; return (*this);	}
					iterator operator++(int)
					{	
						iterator tmp = *this;
						++(*this);
						return (tmp);	
					}
					iterator operator--(int)
					{	
						iterator tmp = *this;
						--(*this);
						return (tmp);	
					}
					iterator &operator+(int i)
					{
						index += i;
						return (*this);
					}
					iterator &operator-(int i)
					{
						index -= i;
						return (*this);
					}
					int operator-(const iterator &other)
					{
						int result;

						result = &(current->c[index]) - &(other.current->c[other.index]);
						return (result);
					}
					bool operator==(iterator const &other)
					{
						if (current == other.current && index == other.index)
							return (true);
						return false;
					}
					bool operator!=(iterator const &other)
					{
						if (current == other.current && index == other.index)
							return (false);
						return true;
					}
					bool operator>(iterator const &other)
					{
						if (current > other.current)
							return true;
						else if (current == other.current && index > other.index)
							return true;
						else
							return false;
					}
					bool operator<(iterator const &other)
					{
						if (current < other.current)
							return true;
						else if (current == other.current && index < other.index)
							return true;
						else
							return false;
					}
					bool operator<=(iterator const &other)
					{
						if (current < other.current)
							return true;
						else if (current == other.current && index <= other.index)
							return true;
						else
							return false;
					}
					bool operator>=(iterator const &other)
					{
						if (current > other.current)
							return true;
						else if (current == other.current && index >= other.index)
							return true;
						else
							return false;
					}
					iterator &operator+=(int value)
					{	index += value; return (*this);		}
					iterator &operator-=(int value)
					{	index -= value; return (*this);		}
			};
			iterator begin()
			{	return(iterator(this, 0));		}
			iterator end()
			{	return(iterator(this, size));		}
	};
}