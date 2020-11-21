/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:38:00 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/21 21:20:42 by jeldora          ###   ########.fr       */
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
				len = copy.sizelen;
				c = alloc.allocate(len);
				for (size_t i = 0; i < len; i++)
					c[i] = copy.c[i];
			}
			template <class TemplateIterator>
			vector(TemplateIterator &first, TemplateIterator &last)
			{
				if (last < first)
					throw std::exception();
				len = last - first;
				c = alloc.allocate(len);
				for (size_t i = 0; i < len; i++)
					c[i] = *(first + i);
			}
			~vector()
			{
				if (c != NULL)
					alloc.deallocate(c, len);
			}

			T&	operator[](size_t index)
			{return (c[index]);}
			vector &operator=(const vector &copy)
			{
				if (c != NULL)
					alloc.deallocate(c, len);
				len = copy.len;
				c = alloc.allocate(len);
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
				T		tmp[len];
				
				for (size_t i = 0; i < len; i++)
					tmp[i] = c[i];
				alloc.deallocate(c, len);
				c = alloc.allocate(n);
				for(size_t i = 0; i < len && i < n; i++)
					c[i] = tmp[i];
				for(size_t i = len; i < n; i++)
					c[i] = val;
				len = n;
			}
			void reserve (size_t n)
			{

			}



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