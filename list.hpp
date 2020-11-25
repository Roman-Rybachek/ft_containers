/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 00:20:14 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/26 00:05:54 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>

namespace ft
{
	template < class T >
	class list
	{
		private:
			typedef struct 		s_elem
			{
				struct s_elem	*left;
				struct s_elem	*right;
				T				content;
			}					t_elem;

			t_elem 				*c;
			size_t				len;
			
		public:
			list ()
			{	c = NULL; len = 0;	}
			explicit list(size_t n, const T& val = T())
			{
				if (n == 0)
				{
					c = NULL;
					len = 0;
					return ;
				}
				c = new t_elem;
				t_elem *tmp = c;
				tmp->left = NULL;
				tmp->right = NULL;
				tmp->content = val;
				for (size_t i = 0; i < n; i++)
				{
					tmp->right = new t_elem;
					tmp->right->left = tmp;
					tmp = tmp->right;
					tmp->content = val;
					tmp->right = NULL;
				}
				len = n;
			}
			template <class InputIterator>
			list (InputIterator first, InputIterator last)
			{
				if (last < first)
					throw std::exception();
				size_t n = last - first;
				if (n == 0)
				{	len = 0; c = NULL;	return ;}
				c = new t_elem;
				t_elem *tmp = c;
				tmp->right = NULL;
				tmp->left = NULL;
				tmp->content = *first;
				for (size_t i = 1; i < n + 1; i++)
				{
					tmp->right = new t_elem;
					tmp->right->left = tmp;
					tmp = tmp->right;
					tmp->right = NULL;
					if (i == n)
						tmp->content = 0;
					else
						tmp->content = first + n;
				}
				len = n;	
			}
			list(const list& copy)
			{
				len = copy.len;
				const_iterator it = copy.begin();
				c = new t_elem;
				t_elem *tmp = c;
				tmp->right = NULL;
				tmp->left = NULL;
				tmp->content = *it;
				for (size_t i = 1; i < len; i++)
				{
					tmp->right = new t_elem;
					tmp->right->left = tmp;
					tmp = tmp->right;
					tmp->right = NULL;
					tmp->content = *(it + i);
				}
			}
			~list()
			{
				if (c == NULL)
					return ;
				t_elem *tmp = c;
				while (tmp->right != NULL)
				{
					tmp = tmp->right;
					delete c;
					c = tmp;
				}
			}
			
			bool empty() const
			{
				if (len == 0)
					return true;
				return false;
			}
			size_t size() const
			{	return (len);	}
			size_t max_size() const
			{	return (-1 / sizeof(t_elem) / 2);	}
			
			class iterator
			{
				protected:
					t_elem *p;
				public:
					iterator() //
					{	p = NULL;		}
					iterator(const iterator &copy)//
					{	p = copy.p;	}
					iterator(t_elem *set_p)//
					{	p = set_p;	}
					virtual	T &operator*()//
					{	return(p->content);		}
					iterator &operator=(const iterator &copy)//
					{
						p = copy.p;
						return (*this);
					}
					iterator &operator++()//
					{	
						if (p->right != NULL)
							std::exception();
						p = p->right;  
						return (*this);	
					}
					iterator &operator--()//
					{
						if (p->left != NULL)
							std::exception();
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
							return (false);
						return true;
					}
			};
			class const_iterator : public iterator
			{
				protected:
					t_elem *p;
				public:
					const_iterator() : iterator()
					{	p = NULL;		}
					const_iterator(const iterator &copy) : iterator(copy)
					{	p = iterator::p;	}
					const_iterator(const const_iterator &copy) : iterator(copy)
					{	p = copy.p;	}
					const_iterator(t_elem *set_p) : iterator(set_p)
					{	p = set_p;	}
					const T &operator*() const
					{	return(p->content);		}
					const_iterator &operator=(const const_iterator &copy)//
					{
						p = copy.p;
						return (*this);
					}
					const_iterator &operator++()//
					{	
						if (p->right != NULL)
							std::exception();
						p = p->right;  
						return (*this);	
					}
					const_iterator &operator--()//
					{
						if (p->left != NULL)
							std::exception();
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
							return (false);
						return true;
					}
			};	
			T& front()
			{
				return (c->content);
			}
			const T& front() const
			{
				return (c->content);
			}
			iterator begin()
			{	return (iterator(c));	}
			iterator end()
			{
				t_elem tmp = c;
				while (tmp->right != NULL)
					tmp = tmp->right;
				return (iterator(tmp->right));
			}
			const_iterator begin() const
			{	return (const_iterator(c));	}
			const_iterator end() const
			{
				t_elem tmp = c;
				while (tmp->right != NULL)
					tmp = tmp->right;
				return (const_iterator(tmp->right));
			}

	};
}