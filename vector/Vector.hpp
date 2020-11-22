/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:38:00 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/22 06:05:22 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <memory>
#include <cstdlib>
#include <iostream>
#include <exception>

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
			bool empty() const
			{
				if (len == 0)
					return true;
				return false;
			}
			T& at(size_t n)
			{
				if (n < 0 || n > len)
					throw std::exception();
				return (c[n]);
			}
			T& at(size_t n) const
			{
				if (n < 0 || n > len)
					throw std::exception();
				return (c[n]);
			}
			T& front()
			{	return (c[0]);		}
			T& front() const
			{	return (c[0]);		}
			T& back()
			{	return (c[len - 1]);		}
			T& back() const
			{	return (c[len - 1]);		}
			template <class TemplateIterator>
			void assign(TemplateIterator &first, TemplateIterator &last)
			{
				if (c != NULL)
					alloc.deallocate(c, space);
				if (last < first)
					throw std::exception();
				len = last - first;
				space = len;
				c = alloc.allocate(space);
				for (size_t i = 0; i < len; i++)
					c[i] = *(first + i);
			}
			void assign(size_t n, const T& val = 0)
			{
				if (c != NULL)
					alloc.deallocate(c, space);
				c = alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					c[i] = val;
				len = n; space = n;
			}
			void push_back (const T& val)
			{
				if (len < space)
					c[len++] = val;
				else
					resize(len + 1, val);
			}
			void pop_back()
			{	c[len--] = 0;	}

			class iterator
			{
				protected:
					ft::vector<T>	*current;
					size_t				index;
				public:
					ft::vector<T> *getCurrent() const
					{	return (current);	}
					const size_t &getIndex() const
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

			iterator insert (iterator position, const T& val)
			{
				if (position.getCurrent() != this || \
					position.getIndex() > len || \
					position.getIndex() < 0 || \
					size() == 0)
					throw std::exception();
				reserve(len + 1);
				for (size_t i = len; i != position.getIndex(); i--)
					c[i] = c[i - 1];
				c[position.getIndex()] = val;
				len++;
				return (iterator(this, position.getIndex()));
			}
			void insert (iterator position, size_t n, const T& val)
			{
				if (position.getCurrent() != this || \
					position.getIndex() > len || \
					position.getIndex() < 0 || \
					size() == 0)
					throw std::exception();
				reserve(len + n);
				for (size_t i = len + n - 1; i >= position.getIndex() + n; i--)
					c[i] = c[i - n];
				for (long long i = (long long)position.getIndex() + n - 1; i >= (long long)position.getIndex(); i--)
					c[i] = val;
				len += n;
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				if (position.getCurrent() != this || \
					position.getIndex() > len || \
					position.getIndex() < 0 || \
					size() == 0 || \
					last < first)
					throw std::exception();

				size_t n = last - first;
				reserve(len + n);
				for (size_t i = len + n - 1; i >= position.getIndex() + n; i--)
					c[i] = c[i - n];
				size_t n_copy = n;
				for (long long i = (long long)position.getIndex() + n - 1; i >= (long long)position.getIndex(); i--)
					c[i] = *(first + --n_copy);
				len += n;
			}
			iterator begin()
			{	return(iterator(this, 0));		}
			iterator end()
			{	return(iterator(this, len));		}
	};
}