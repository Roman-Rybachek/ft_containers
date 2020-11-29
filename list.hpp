/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 23:22:16 by rinne             #+#    #+#             */
/*   Updated: 2020/11/29 09:30:44 by jeldora          ###   ########.fr       */
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
			}
			void pop_front()
			{
				t_elem *tmp;
				first_elem = first_elem->right;
				first_elem->left = supp_elem;
				supp_elem->right = first_elem;
				delete tmp;
			}

			class iterator
			{
				protected:
					t_elem	*p;
				public:
					const void* getAddr() const
					{
						return (p);
					}
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

			iterator begin()
			{	return (iterator(first_elem));	}
			iterator end()
			{	return (iterator(supp_elem));	}
			const_iterator begin() const
			{	return (const_iterator(first_elem));	}
			const_iterator end() const
			{	return (const_iterator(supp_elem));	}
	};
}
