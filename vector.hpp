/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:38:00 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/25 02:35:03 by jeldora          ###   ########.fr       */
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

			class iterator
			{
				protected:
					T *p;
				public:
					iterator()
					{	p = NULL;		}
					iterator(const iterator &copy)
					{	p = copy.p;	}
					iterator(T *set_p)
					{	p = set_p;	}
					T &operator*()
					{	return(*p);		}
					iterator &operator=(const iterator &copy)
					{
						p = copy.p;
						return (*this);
					}
					iterator &operator++()
					{	p++; return (*this);	}
					iterator &operator--()
					{	p--; return (*this);	}
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
						tmp.p = p + i;
						return (tmp);
					}
					iterator operator-(int i)
					{
						iterator tmp = iterator(*this);
						tmp.index = p - i;
						return (tmp);
					}
					int operator-(const iterator &other)
					{
						int result;

						result = p - other.p;
						return (result);
					}
					bool operator==(iterator const &other)
					{
						if (p == other.p)
							return (true);
						return false;
					}
					bool operator!=(iterator const &other)
					{
						if (p != other.p)
							return (false);
						return true;
					}
					bool operator>(iterator const &other)
					{
						if (p > other.p)
							return true;
						else
							return false;
					}
					bool operator<(iterator const &other)
					{
						if (p < other.p)
							return true;
						else
							return false;
					}
					bool operator<=(iterator const &other)
					{
						if (p <= other.p)
							return true;
						else
							return false;
					}
					bool operator>=(iterator const &other)
					{
						if (p >= other.p)
							return true;
						else
							return false;
					}
					iterator &operator+=(int value)
					{	p += value; return (*this);		}
					iterator &operator-=(int value)
					{	p -= value; return (*this);		}
			};
			class const_iterator
			{
				protected:
					T *p;
				public:
					const_iterator()
					{	p = NULL;		}
					const_iterator(const const_iterator &copy)
					{	p = copy.p;	}
					const_iterator(const iterator &copy)
					{	p = &(*copy);	}
					const_iterator(T *set_p)
					{	p = set_p;	}
					const T &operator*() const
					{	return(*p);		}
					const_iterator &operator=(const const_iterator &copy)
					{
						p = copy.p;
						return (*this);
					}
					const_iterator &operator++()
					{	p++; return (*this);	}
					const_iterator &operator--()
					{	p--; return (*this);	}
					const_iterator operator++(int)
					{	
						const_iterator tmp = *this;
						++(*this);
						return (tmp);	
					}
					const_iterator operator--(int)
					{	
						const_iterator tmp = *this;
						--(*this);
						return (tmp);	
					}
					const_iterator operator+(int i)
					{
						const_iterator tmp = const_iterator(*this);
						tmp.p = p + i;
						return (tmp);
					}
					const_iterator operator-(int i)
					{
						const_iterator tmp = const_iterator(*this);
						tmp.index = p - i;
						return (tmp);
					}
					int operator-(const const_iterator &other)
					{
						int result;

						result = p - other.p;
						return (result);
					}
					bool operator==(const_iterator const &other)
					{
						if (p == other.p)
							return (true);
						return false;
					}
					bool operator!=(const_iterator const &other)
					{
						if (p != other.p)
							return (false);
						return true;
					}
					bool operator>(const_iterator const &other)
					{
						if (p > other.p)
							return true;
						else
							return false;
					}
					bool operator<(const_iterator const &other)
					{
						if (p < other.p)
							return true;
						else
							return false;
					}
					bool operator<=(const_iterator const &other)
					{
						if (p <= other.p)
							return true;
						else
							return false;
					}
					bool operator>=(const_iterator const &other)
					{
						if (p >= other.p)
							return true;
						else
							return false;
					}
					const_iterator &operator+=(int value)
					{	p += value; return (*this);		}
					const_iterator &operator-=(int value)
					{	p -= value; return (*this);		}
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
			iterator erase (iterator position)
			{
				if (position.getIndex() >= len || position.getIndex() < 0)
					throw std::exception();
				for (size_t i = position.getIndex(); i < len - 1; i++)
					c[i] = c[i + 1];
				c[len - 1] = 0;
				len -= 1;
				return (position);
			}
			iterator erase (iterator first, iterator last)
			{
				if (last < first || last > end() || first < begin())
					throw std::exception();
				int n = last - first;
				iterator it_end = end();
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
			iterator begin()
			{	return(iterator(&c[0]));		}
			iterator end()
			{	return(iterator(&c[len]));		}
			const_iterator begin() const
			{	return(const_iterator(&c[0]));		}
			const_iterator end() const
			{	return(const_iterator(&c[len]));		}

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
	
	
}
