/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:38:00 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/22 02:36:28 by jeldora          ###   ########.fr       */
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
			size_t	len;
			size_t	space;
		public:
			vector()	// Base 
			{	c = NULL; len = 0;	space = 0;	}
			explicit vector(size_t n, const T& val = 0)	// Fill [Узнать, почемy const]
			{
				c = alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					c[i] = val;
				len = n; space = n;
			}
			vector(const vector<T>& copy)	// Copy
			{
				alloc = copy.alloc;
				len = copy.len;
				space = copy.space;
				c = alloc.allocate(space);
				for (size_t i = 0; i < len; i++)
					c[i] = copy.c[i];
			}
			template <class TemplateIterator>
			vector(TemplateIterator &first, TemplateIterator &last)
			{
				if (last < first)
					throw std::exception();
				len = last - first;
				space = len;
				c = alloc.allocate(space);
				for (size_t i = 0; i < len; i++)
					c[i] = *(first + i);
			}
			~vector()
			{
				if (c != NULL)
					alloc.deallocate(c, space);
			}

			T&	operator[](size_t index)
			{return (c[index]);}
			vector &operator=(const vector &copy)
			{
				if (c != NULL)
					alloc.deallocate(c, space);
				len = copy.len;
				space = copy.space;
				c = alloc.allocate(space);
				for(size_t i = 0; i < len; i++)
					c[i] = copy.c[i];
				return (*this);
			}	

			size_t size() const
			{	return len;		}
			size_t max_size() const
			{	return (-1 / sizeof(ft::vector<T>));	}
			void resize (size_t n, const T& val = 0)
			{
				if (n <= len)
				{
					for (size_t i = n; i < len; i++)
						c[i] = 0;
					return ;
				}
				else
				{
					if (n > space)
						reserve(n);
					for (size_t i = len; i < space; i++)
						c[i] = val;
					len = n;
				}
			}
			void reserve (size_t n)
			{
				if (n <= space)
					return ;
				if (n > max_size())
					throw std::bad_alloc();
				vector<T> tmp(*this);
				alloc.deallocate(c, space);
				c = alloc.allocate(n);
				for (size_t i = 0; i < len; i++)
					c[i] = tmp[i];
				space = n;
			}
			size_t capacity()
			{	return (space);		}


			class iterator
			{
				protected:
					ft::vector<T>	*current;
					int				index;
				public:
					ft::vector<T> *getCurrent() const
					{	return (current);	}
					ft::vector<T> &getIndex() const
					{	return (index);		}
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
					iterator operator+(int i)
					{
						iterator tmp = iterator(*this);
						tmp.index = index + i;
						return (tmp);
					}
					iterator operator-(int i)
					{
						iterator tmp = iterator(*this);
						tmp.index = index - i;
						return (tmp);
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
			{	return(iterator(this, len));		}
	};
}