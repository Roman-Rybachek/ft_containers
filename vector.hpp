/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:38:00 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/24 23:29:05 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <memory>
#include <cstdlib>
#include <iostream>
#include <exception>

namespace ft
{


	template <typename T>
	class iterator_vector;

/*
	template <typename T>
	class const_iterator_vector : public iterator_vector
	{
		public:
			const_iterator_vector() : iterator_vector()
			{}
			const_iterator_vector(const iterator_vector &copy)
			{	current = copy.current; index = copy.index;		}
			const_iterator_vector(ft::vector<T> *set_current, size_t set_index)
			{	current = set_current; index = set_index;	}
			const T &operator*() const
			{	return(current->c[index]);	}
	};
*/

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
			explicit vector(size_t n, const T& val = T())	// Fill [Узнать, почемy const]
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
			T&	operator[](size_t index) const
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
			void resize (size_t n, const T& val = T())
			{
				if (n <= len)
				{
					for (size_t i = n; i < len; i++)
						c[i] = 0;
					len = n;
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
			void assign(size_t n, const T& val = T())
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
			{
				if (len != 0)
					c[--len] = 0;	
			}

					// class const_iterator_vector : public iterator_vector
			// {
			// 	public:
			// 		const_iterator_vector() : iterator_vector() {}
			// 		const_iterator_vector(const iterator_vector &copy)
			// 		{
			// 			current = copy.current;
			// 			index = copy.index;
			// 		}
			// 		const_iterator_vector(ft::vector<T> *set_current, size_t set_index)
			// 		{	current = set_current; index = set_index;	}

			// 		const T &operator*()
			// 		{	return(current->c[index]);		}
			// };

			iterator_vector<T> insert (iterator_vector<T> position, const T& val)
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
				return (iterator_vector<T>(this, position.getIndex()));
			}
			void insert (iterator_vector<T> position, size_t n, const T& val)
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
			void insert (iterator_vector<T> position, InputIterator first, InputIterator last)
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
			iterator_vector<T> erase (iterator_vector<T> position)
			{
				if (position.getIndex() >= len || position.getIndex() < 0)
					throw std::exception();
				for (size_t i = position.getIndex(); i < len - 1; i++)
					c[i] = c[i + 1];
				c[len - 1] = 0;
				len -= 1;
				return (position);
			}
			iterator_vector<T> erase (iterator_vector<T> first, iterator_vector<T> last)
			{
				if (last < first || last > end() || first < begin())
					throw std::exception();
				int n = last - first;
				iterator_vector<T> it_end = end();
				for (size_t i = first.getIndex(); i <= it_end.getIndex(); i++)
					c[i] = c[i + n + 1];
				for (size_t i = it_end.getIndex() - 1; i >= it_end.getIndex() -1 - n; i--)
					c[i] = 0;
				len -= n + 1;
				return (first);
			}
			void swap (ft::vector<T>& x)
			{
				vector<T> tmp = *this;
				*this = x;
				x = tmp;
			}
			void clear()
			{
				for (int i = 0; i < size(); i++)
					c[i] = 0;
				len = 0;
			}
			iterator_vector<T> begin()
			{	return(iterator_vector<T>(this, 0));		}
			iterator_vector<T> end()
			{	return(iterator_vector<T>(this, len));		}

			friend bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				for (size_t i = 0; i < lhs.size(); i++)
					if (lhs[i] != rhs[i])
						return (false);
				return true;
			}
			friend bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				if (lhs.size() == rhs.size())
					return false;
				for (size_t i = 0; i < lhs.size(); i++)
					if (lhs[i] == rhs[i])
						return (false);
				return true;
			}
			friend bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				for (size_t i = 0; i < lhs.size(); i++)
				{
					if (lhs[i] > rhs[i])
						return (true);
					if (lhs.size() == rhs.size())
						continue ;
					if (i == rhs.size() - 1)
						return (true);
				}
				return false;
			}
			friend bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				for (size_t i = 0; i < rhs.size(); i++)
				{
					if (lhs[i] < rhs[i])
						return (true);
					if (lhs.size() == rhs.size())
						continue ;
					if (i == lhs.size() - 1)
						return (true);
				}
				return false;
			}
			friend bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				for (size_t i = 0; i < rhs.size(); i++)
				{
					if (lhs[i] < rhs[i])
						return (false);
					if (lhs.size() == rhs.size())
						continue ;
					if (i == lhs.size() - 1)
						return (false);
				}
				return true;
			}
			friend bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
			{
				for (size_t i = 0; i < lhs.size(); i++)
				{
					if (lhs[i] > rhs[i])
						return (false);
					if (lhs.size() == rhs.size())
						continue ;
					if (i == rhs.size() - 1)
						return (false);
				}
				return true;
			}
	};

	template <class T, class Alloc>
  	void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{
		vector<T, Alloc> tmp = x;
		x = y;
		y = tmp;
	}
	
	template <typename T>
	class iterator_vector
	{
		protected:
			ft::vector<T>	*current;
			size_t				index;
		public:
			ft::vector<T> *getCurrent() const
			{	return (current);	}
			const size_t &getIndex() const
			{	return (index);		}
			iterator_vector()
			{	current = NULL; index = 0;	}
			iterator_vector(const iterator_vector &copy)
			{	current = copy.current; index = copy.index;		}
			iterator_vector(ft::vector<T> *set_current, size_t set_index)
			{	current = set_current; index = set_index;	}
			virtual T &operator*()
			{	return(current[index]);		}
			iterator_vector &operator=(const iterator_vector &copy)
			{
				current = copy.current;
				index = copy.index;
				return (*this);
			}
			iterator_vector &operator++()
			{	index++; return (*this);	}
			iterator_vector &operator--()
			{	index--; return (*this);	}
			iterator_vector operator++(int)
			{	
				iterator_vector tmp = *this;
				++(*this);
				return (tmp);	
			}
			iterator_vector operator--(int)
			{	
				iterator_vector tmp = *this;
				--(*this);
				return (tmp);	
			}
			iterator_vector operator+(int i)
			{
				iterator_vector tmp = iterator_vector(*this);
				tmp.index = index + i;
				return (tmp);
			}
			iterator_vector operator-(int i)
			{
				iterator_vector tmp = iterator_vector(*this);
				tmp.index = index - i;
				return (tmp);
			}
			int operator-(const iterator_vector &other)
			{
				int result;

				result = &(current[index]) - &(other.current[other.index]);
				return (result);
			}
			bool operator==(iterator_vector const &other)
			{
				if (current == other.current && index == other.index)
					return (true);
				return false;
			}
			bool operator!=(iterator_vector const &other)
			{
				if (current == other.current && index == other.index)
					return (false);
				return true;
			}
			bool operator>(iterator_vector const &other)
			{
				if (current > other.current)
					return true;
				else if (current == other.current && index > other.index)
					return true;
				else
					return false;
			}
			bool operator<(iterator_vector const &other)
			{
				if (current < other.current)
					return true;
				else if (current == other.current && index < other.index)
					return true;
				else
					return false;
			}
			bool operator<=(iterator_vector const &other)
			{
				if (current < other.current)
					return true;
				else if (current == other.current && index <= other.index)
					return true;
				else
					return false;
			}
			bool operator>=(iterator_vector const &other)
			{
				if (current > other.current)
					return true;
				else if (current == other.current && index >= other.index)
					return true;
				else
					return false;
			}
			iterator_vector &operator+=(int value)
			{	index += value; return (*this);		}
			iterator_vector &operator-=(int value)
			{	index -= value; return (*this);		}
	};
}
