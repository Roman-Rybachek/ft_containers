/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:38:00 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/11 09:36:21 by jeldora          ###   ########.fr       */
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
	class vector
	{	
		private:
			T		*c;
			size_t	len;
			size_t	space;
		public:
			vector()	// Base 
			{	c = NULL; len = 0;	space = 0;	}
			explicit vector(size_t n, const T& val = T())	// Fill [Узнать, почемy const]
			{
				c = new T[n];
				for (size_t i = 0; i < n; i++)
					c[i] = val;
				len = n; space = n;
			}
			vector(const vector<T>& copy)	// Copy
			{
				len = copy.len;
				space = copy.space;
				c = new T[space];
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
				c = new T[space];
				for (size_t i = 0; i < len; i++)
					c[i] = *(first + i);
			}
			~vector()
			{
				if (c != NULL)
					delete[] c;
			}

			T&	operator[](size_t index)
			{return (c[index]);}
			T&	operator[](size_t index) const
			{return (c[index]);}
			vector &operator=(const vector &copy)
			{
				if (c != NULL)
					delete[] c; 
				len = copy.len;
				space = copy.space;
				c = new T[space];
				for(size_t i = 0; i < len; i++)
					c[i] = copy.c[i];
				return (*this);
			}	

			size_t size() const
			{	return len;		}
			size_t max_size() const
			{	return (-1 / sizeof(T));	}
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
				delete[] c;
				c = new T[n];
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
					delete[] c;
				if (last < first)
					throw std::exception();
				len = last - first;
				space = len;
				c = new T[space];
				for (size_t i = 0; i < len; i++)
					c[i] = *(first + i);
			}
			void assign(size_t n, const T& val = T())
			{
				if (c != NULL)
					delete[] c;
				c = new T[n];
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
				public:
					T *p;
					iterator()
					{	p = NULL;		}
					iterator(const iterator &copy)
					{	p = copy.p;	}
					iterator(T *set_p)
					{	p = set_p;	}
					virtual	T &operator*()
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
						tmp.p = p - i;
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
							return (true);
						return false;
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
			class const_iterator : public iterator
			{
				public:
					T *p;
					const_iterator() : iterator()
					{	p = NULL;}
					const_iterator(const const_iterator &copy) : iterator(copy)
					{	p = iterator::p;	}
					const_iterator(const iterator &copy) : iterator(copy)
					{	p = iterator::p;	}
					const_iterator(T *set_p) : iterator(set_p)
					{	p = iterator::p;	}
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
			class reverse_iterator
			{
				protected:
					iterator it;
				public:
					reverse_iterator(){}
					explicit reverse_iterator (iterator set_it)
					{	it = set_it;	}
					reverse_iterator(const reverse_iterator& copy)
					{	it = copy.it;	}
					T &operator*()
					{	return(*it);		}
					reverse_iterator &operator++()
					{	it--; return (*this);	}
					reverse_iterator &operator--()
					{	it++; return (*this);	}
					reverse_iterator operator++(int)
					{	
						reverse_iterator tmp = *this;
						--(*this);
						return (tmp);	
					}
					reverse_iterator operator--(int)
					{	
						reverse_iterator tmp = *this;
						++(*this);
						return (tmp);	
					}
					reverse_iterator operator+(int i)
					{
						reverse_iterator tmp = reverse_iterator(*this);
						tmp.p = it - i;
						return (tmp);
					}
					reverse_iterator operator-(int i)
					{
						reverse_iterator tmp = reverse_iterator(*this);
						tmp.p = it + i;
						return (tmp);
					}
					int operator-(const reverse_iterator &other)
					{
						int result;

						result = it + other.it;
						return (result);
					}
					bool operator==(reverse_iterator const &other)
					{
						if (it == other.it)
							return (true);
						return false;
					}
					bool operator!=(reverse_iterator const &other)
					{
						if (it != other.it)
							return (false);
						return true;
					}
					bool operator>(reverse_iterator const &other)
					{
						if (it < other.it)
							return true;
						else
							return false;
					}
					bool operator<(reverse_iterator const &other)
					{
						if (it > other.it)
							return true;
						else
							return false;
					}
					bool operator<=(reverse_iterator const &other)
					{
						if (it >= other.it)
							return true;
						else
							return false;
					}
					bool operator>=(reverse_iterator const &other)
					{
						if (it <= other.it)
							return true;
						else
							return false;
					}
					reverse_iterator &operator+=(int value)
					{	it -= value; return (*this);		}
					reverse_iterator &operator-=(int value)
					{	it += value; return (*this);		}
					T* operator->() const
					{	return(&(*it));	}
					T& operator[](size_t n) const
					{
						return (*(it - n));
					}
					friend reverse_iterator operator+(size_t n, const reverse_iterator& rev_it)
					{
						reverse_iterator tmp(rev_it);
						tmp.it -= n;
						return (tmp);
					}
					friend reverse_iterator operator-(size_t n, const reverse_iterator& rev_it)
					{
						reverse_iterator tmp(rev_it);
						tmp.it += n;
						return (tmp);
					}
			};
			class const_reverse_iterator
			{
				protected:
					const_iterator it;
				public:
					const_reverse_iterator(){}
					explicit const_reverse_iterator (const_iterator set_it)
					{	it = set_it;	}
					const_reverse_iterator(const const_reverse_iterator& copy)
					{	it = copy.it;	}
					const T &operator*() const
					{	return(*it);		}
					const_reverse_iterator &operator++()
					{	it--; return (*this);	}
					const_reverse_iterator &operator--()
					{	it++; return (*this);	}
					const_reverse_iterator operator++(int)
					{	
						const_reverse_iterator tmp = *this;
						--(*this);
						return (tmp);	
					}
					const_reverse_iterator operator--(int)
					{	
						const_reverse_iterator tmp = *this;
						++(*this);
						return (tmp);	
					}
					const_reverse_iterator operator+(int i)
					{
						const_reverse_iterator tmp = const_reverse_iterator(*this);
						tmp.p = it - i;
						return (tmp);
					}
					const_reverse_iterator operator-(int i)
					{
						const_reverse_iterator tmp = const_reverse_iterator(*this);
						tmp.p = it + i;
						return (tmp);
					}
					int operator-(const const_reverse_iterator &other)
					{
						int result;

						result = it + other.it;
						return (result);
					}
					bool operator==(const_reverse_iterator const &other)
					{
						if (it == other.it)
							return (true);
						return false;
					}
					bool operator!=(const_reverse_iterator const &other)
					{
						if (it != other.it)
							return (false);
						return true;
					}
					bool operator>(const_reverse_iterator const &other)
					{
						if (it < other.it)
							return true;
						else
							return false;
					}
					bool operator<(const_reverse_iterator const &other)
					{
						if (it > other.it)
							return true;
						else
							return false;
					}
					bool operator<=(const_reverse_iterator const &other)
					{
						if (it >= other.it)
							return true;
						else
							return false;
					}
					bool operator>=(const_reverse_iterator const &other)
					{
						if (it <= other.it)
							return true;
						else
							return false;
					}
					const_reverse_iterator &operator+=(int value)
					{	it -= value; return (*this);		}
					const_reverse_iterator &operator-=(int value)
					{	it += value; return (*this);		}
					T* operator->() const
					{	return(&(*it));	}
					T& operator[](size_t n) const
					{
						return (*(it - n));
					}
					friend const_reverse_iterator operator+(size_t n, const const_reverse_iterator& rev_it)
					{
						const_reverse_iterator tmp(rev_it);
						tmp.it -= n;
						return (tmp);
					}
					friend const_reverse_iterator operator-(size_t n, const const_reverse_iterator& rev_it)
					{
						const_reverse_iterator tmp(rev_it);
						tmp.it += n;
						return (tmp);
					}
			};

			iterator insert (iterator position, const T& val)
			{
				reserve(len + 1);

				for (iterator it_end = end(); it_end > position; it_end--)
					*it_end = *(it_end - 1);
				*position.p = val;
				len++;
				return (iterator(position.p));
			}
			void insert (iterator position, size_t n, const T& val)
			{
				for (size_t i = 0; i < n; i++)
				{
					position = insert(position, val);
					position++;
				}
			}
			/*template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				if (size() == 0 || last < first)
					throw std::exception();

				while (first != last)
				{
					insert(position, *first);
					first++;
				}
			}*/
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

			reverse_iterator rbegin()
			{	return(reverse_iterator(end()));		}
			reverse_iterator rend()
			{	return(reverse_iterator(begin()));		}
			const_reverse_iterator rbegin() const
			{	return(const_reverse_iterator(end()));		}
			const_reverse_iterator rend() const
			{	return(const_iterator(begin()));		}

			friend bool operator== (const vector<T >& lhs, const vector<T >& rhs)
			{
				if (lhs.size() != rhs.size())
					return false;
				for (size_t i = 0; i < lhs.size(); i++)
					if (lhs[i] != rhs[i])
						return (false);
				return true;
			}
			friend bool operator!= (const vector<T >& lhs, const vector<T >& rhs)
			{
				if (lhs.size() == rhs.size())
					return false;
				for (size_t i = 0; i < lhs.size(); i++)
					if (lhs[i] == rhs[i])
						return (false);
				return true;
			}
			friend bool operator> (const vector<T >& lhs, const vector<T >& rhs)
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
			friend bool operator< (const vector<T >& lhs, const vector<T >& rhs)
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
			friend bool operator>= (const vector<T >& lhs, const vector<T >& rhs)
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
			friend bool operator<= (const vector<T >& lhs, const vector<T >& rhs)
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

	template <class T>
  	void swap (ft::vector<T >& x, ft::vector<T >& y)
	{
		vector<T> tmp = x;
		x = y;
		y = tmp;
	}
	
	
}
