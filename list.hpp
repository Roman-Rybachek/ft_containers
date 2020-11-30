/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 23:22:16 by rinne             #+#    #+#             */
/*   Updated: 2020/11/30 20:14:56 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <typeinfo>

namespace ft
{
	template < class T >
	class list
	{
		private:
			typedef struct		s_elem
			{
				struct s_elem	*left;
				struct s_elem	*right;
				T				content;
				bool			is_support;
			}					t_elem;

			size_t				length;
			t_elem				*first_elem;
			t_elem				*last_elem;
			t_elem				*supp_elem; 
			

			t_elem				*createElemet(	t_elem *set_left = NULL, \
												t_elem *set_right = NULL, \
												const T&val = T())
			{
				t_elem *new_elem;

				new_elem = new t_elem;
				new_elem->left = set_left;
				new_elem->right = set_right;
				new_elem->content = val;
				if (set_left != NULL)
					set_left->right = new_elem;
				if (set_right != NULL)
					set_right->left = new_elem;
				new_elem->is_support = false;
				return new_elem;
			}
			void 				createSupportElement()
			{
				supp_elem = createElemet();
				supp_elem->left = supp_elem;
				supp_elem->right = supp_elem;
				supp_elem->content = T();
				supp_elem->is_support = true;
			}
			void                increaseLength(size_t delta = 1)
			{
				length += delta;
			}
			void                decreaseLength(size_t delta = 1)
			{
				length -= delta;
			}
			size_t getSize()
			{
				t_elem *tmp = first_elem;
				size_t i = 0;
				while (tmp != supp_elem)
				{
					tmp = tmp->right;
					i++;
				}
				return (i);
			}
		public:
			list()
			{	
				first_elem = NULL; 
				last_elem = NULL; 
				length = 0;
				createSupportElement();
			}
			explicit list(size_t n, const T& val = T())
			{
				length = 0;
				first_elem = NULL;
				last_elem = NULL;
				createSupportElement();
				for (size_t i = 0; i < n; i++)
					push_back(val);
			}
			list (const list& copy)
			{
				length = 0;
				first_elem = NULL;
				last_elem = NULL;
				createSupportElement();
				if (copy.size() == 0)
					return ;
				for (const_iterator it = copy.begin(); it != copy.end(); it++)
					push_back(*it);
			}
			template <class InputIterator>
			list (InputIterator first, InputIterator last)
			{
				size_t n = last - first;
				if (last - 1 < first)
					throw std::exception();
				first_elem = NULL;
				last_elem = NULL;
				length = 0;
				createSupportElement();
				for (size_t i = 0; i <= n - 1; i++)
				{
					push_back(*(first + i));
				}
			}
			list& operator= (const list& copy)
			{
				size_t s = size();
				for (size_t i = 0; i < s; i++)
					pop_back();
				if (copy.size() == 0)
					return *this;
				for (const_iterator it = copy.begin(); it != copy.end(); it++)
					push_back(*it);
				return *this;
			}
			void push_back(const T& val)
			{
				if (first_elem == NULL)
				{
					first_elem = createElemet(supp_elem, supp_elem, val);
					last_elem = first_elem;
				}
				else
				{
					last_elem = createElemet(last_elem, supp_elem, val);
				}
				increaseLength();
			}
			void push_front(const T& val)
			{
				if (first_elem == NULL)
				{
					first_elem = createElemet(supp_elem, supp_elem, val);
					last_elem = first_elem;
				}
				else
				{
					first_elem = createElemet(supp_elem, first_elem, val);
				}
				increaseLength();	
			}
			void pop_back()
			{
				t_elem *tmp = last_elem;
				last_elem = last_elem->left;
				last_elem->right = supp_elem;
				supp_elem->left = last_elem;
				delete tmp;
				decreaseLength();
			}
			void pop_front()
			{
				t_elem *tmp;
				first_elem = first_elem->right;
				first_elem->left = supp_elem;
				supp_elem->right = first_elem;
				delete tmp;
				decreaseLength();
			}

			class iterator
			{
				public:
					t_elem	*p;
					iterator() //
					{	p = NULL;}
					iterator(const iterator &copy)//
					{	p = copy.p;}
					iterator(t_elem *set_p)//
					{	p = set_p;}
					virtual	T &operator*()//
					{	return(p->content);		}
					iterator &operator=(const iterator &copy)//
					{
						p = copy.p;
						return (*this);
					}
					iterator &operator++()//
					{	
						p = p->right;  
						return (*this);	
					}
					iterator &operator--()//
					{
						p = p->left; 
						return (*this);	
					}
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
			};
			class const_iterator : iterator
			{
				protected:
					t_elem	*p;
				public:
					const void* getAddr() const
					{
						return (p);
					}
					const_iterator() //
					{	p = NULL;}
					const_iterator(const const_iterator &copy)//
					{	p = copy.p;}
					const_iterator(const iterator &copy) : iterator(copy)//
					{	p = iterator::p;}
					const_iterator(t_elem *set_p)//
					{	p = set_p;}
					T &operator*() const//
					{	return(p->content);		}
					const_iterator &operator=(const const_iterator &copy)//
					{
						p = copy.p;
						return (*this);
					}
					const_iterator &operator++()//
					{	
						p = p->right;  
						return (*this);	
					}
					const_iterator &operator--()//
					{
						p = p->left; 
						return (*this);	
					}
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
					bool operator==(const_iterator const &other)
					{
						if (p == other.p)
							return (true);
						return false;
					}
					bool operator!=(const_iterator const &other)
					{
						if (p != other.p)
							return (true);
						return false;
					}
			};

			size_t size() const
			{
				return length;
			}
			bool empty() const
			{
				if (length == 0)
					return true;
				return false;
			}
			size_t max_size() const
			{
				return (-1 / sizeof(t_elem));
			}

			T& front()
			{
				return first_elem->content;
			}
			T& front() const
			{
				return first_elem->content;
			}
			T& back()
			{
				return last_elem->content;
			}
			T& back() const
			{
				return last_elem->content;
			}

			void clear()
			{
				size_t s = size();
				for (size_t i = 0; i < s; i++)
					pop_back();
			}
			void assign (size_t n, const T& val)
			{
				clear();
				for (size_t i = 0; i < n; i++)
					push_back(val);
			}
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)
			{
				clear();
				size_t n = last - first;
				if (last - 1 < first)
					throw std::exception();
				for (size_t i = 0; i <= n - 1; i++)
					push_back(*(first + i));
			}
			iterator insert (iterator position, const T& val)
			{
				createElemet(position.p->left, position.p, val);
				length++;
				return (--position);
			}
			void insert (iterator position, size_t n, const T& val)
			{
				for (size_t i = 0; i < n; i++)
				{
					createElemet(position.p->left, position.p, val);
					length++;
				}
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				size_t n = last - first - 1;
				if (last - 1 < first || last == first)
					throw std::exception();
				for (size_t i = 0; i <= n; i++)
				{
					createElemet(position.p->left, position.p, *(first + i));
					length++;
				}
			}
			iterator erase (iterator position)
			{
				t_elem *tmp = position.p;
				position--;
				tmp->left->right = tmp->right;
				tmp->right->left = tmp->left;
				delete tmp;
				decreaseLength();
				return (position);
			}
			iterator erase (iterator first, iterator last)
			{
				first.p->left->right = last.p;
				last.p->left = first.p->left;
				iterator it = first;
				while (it != last)
				{
					delete (it.p);
					it++;
					decreaseLength();
				}
				return last;
			}
			iterator begin()
			{	return (iterator(first_elem));	}
			iterator end()
			{	return (iterator(supp_elem));	}
			const_iterator begin() const
			{	return (const_iterator(first_elem));	}
			const_iterator end() const
			{	return (const_iterator(supp_elem));	}
			void swap(list &other)
			{
				list tmp;
				tmp = *this;
				*this = other;
				other = tmp;
			}
			void resize (size_t n, T val = T())
			{
				if (n < size())
				{
					while (n < size())
						pop_back();
				}
				else if (n > size())
				{
					while (n > size())
						push_back(val);
				}
			}
			
			void splice(iterator position, list &other)
			{
				iterator last = --other.end();
				iterator start = other.begin();

				position.p->left->right = start.p;
				start.p->left = position.p->left;

				position.p->left = last.p;
				last.p->right = position.p;
				other.supp_elem->left = other.supp_elem;
				other.supp_elem->right = other.supp_elem;
				length += other.length;
				other.length = 0;
				first_elem = supp_elem->right;
				last_elem = supp_elem->left;
			}
			void splice (iterator position, list& other, iterator i)
			{
				iterator last = --other.end();
				iterator start = i;

				start.p->left->right = other.supp_elem;
				other.supp_elem->left = start.p->left;
				other.last_elem = other.supp_elem->left;
				other.first_elem = other.supp_elem->right;
				
				position.p->left->right = start.p;
				start.p->left = position.p->left;

				position.p->left = last.p;
				last.p->right = position.p;

				other.length = other.getSize();
				first_elem = supp_elem->right;
				last_elem = supp_elem->left;
				length = getSize();
			}
			void splice (iterator position, list& other, iterator first, iterator set_last)
			{
				iterator last = --set_last;
				iterator start = first;

				start.p->left->right = other.supp_elem;
				other.supp_elem->left = start.p->left;
				other.last_elem = other.supp_elem->left;
				other.first_elem = other.supp_elem->right;
				
				position.p->left->right = start.p;
				start.p->left = position.p->left;

				position.p->left = last.p;
				last.p->right = position.p;

				other.length = other.getSize();
				first_elem = supp_elem->right;
				last_elem = supp_elem->left;
				length = getSize();
			}	
			void remove (const T& val)
			{
				iterator it = begin();
				while (it != end())
				{
					if (*it == val)
						it = erase(it);
					it++;
				}
			}
			template <class Predicate>
			void remove_if (Predicate pred)
			{
				iterator it = begin();
				while (it != end())
				{
					if (pred(it))
						it = erase(it);
					it++;
				}
			}
			void reverse()
			{
				t_elem *tmp;
				t_elem *tmp_supp_elem;

				while (first_elem != supp_elem)
				{
					tmp = first_elem->right;
					first_elem->right = first_elem->left;
					first_elem->left = tmp;
					tmp_supp_elem = first_elem;
					first_elem = first_elem->left;
				}
				tmp = supp_elem->left;
				supp_elem->left = supp_elem->right;
				supp_elem->right = tmp;
				first_elem = supp_elem->right->right;
				last_elem = supp_elem->left;
			}
			void unique()
			{
				iterator tmp;
				for (iterator it = begin(); it != end() ; it++)
				{
					tmp = (--it)++;
					if (*tmp == *it && tmp != end())
						it = erase(it);
				}
			}
	};
}
