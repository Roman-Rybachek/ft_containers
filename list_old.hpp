/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 00:20:14 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/27 04:18:54 by jeldora          ###   ########.fr       */
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
			list& operator= (const list& x)
			{
				while (size())
					this->pop_front();
				iterator x_it = x.begin();
				for (size_t i = 0; i < x.size(); i++)
					this->push_front(*x_it++);
				return (*this);
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
					const void* getAddr() const
					{
						return (p);
					}
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
			T& back()
			{
				t_elem tmp = c;
				while (tmp->right != NULL)
					tmp = tmp->right;
				return (tmp->content);
			}
			const T& back() const
			{
				t_elem tmp = c;
				while (tmp->right != NULL)
					tmp = tmp->right;
				return (tmp->content);
			}
			iterator begin()
			{	return (iterator(c));	}
			iterator end()
			{
				t_elem *tmp = c;
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

			void push_front (const T& val)
			{
				c->left = new t_elem;
				c->left->right = c;
				c->left->content = val;
				c->left->left = NULL;
				c = c->left;
				len++;
			}
			void pop_front()
			{
				if (c == NULL)
					return ;
				if (c->right != NULL)
				{
					c = c->right;
					delete c->left;
					c->left = NULL;
					len--;
					return ;
				}
				delete c;
				c = NULL;
				len--;
			}
			void push_back (const T& val)
			{
				t_elem tmp = c;
				if (c == NULL)
				{
					c = new t_elem;
					c->left = NULL;
					c->right = NULL;
					c->content = val;
					len++;
					return ;
				}
				while (tmp->right != NULL)
					tmp = tmp->right;
				tmp->right = new t_elem;
				tmp->right->left = tmp;
				tmp = tmp->right;
				tmp->right = NULL;
				tmp->content = val;
				len++;
			}
			void pop_back ()
			{
				t_elem *tmp = c;
				if (c == NULL)
					throw std::exception();
				if (c->right == NULL)
				{
					delete c;
					len--;
					return ;
				}
				while (tmp->right->right != NULL)
					tmp = tmp->right;
				delete tmp->right;
				len--;
			}
			void swap(list &copy)
			{
				ft::list<T> tmp;
				tmp = *this;
				*this = copy;
				copy = tmp;
			}
			
			iterator insert (iterator position, const T& val)
			{
				t_elem *tmp = c;

				while (tmp != NULL && tmp != position.getAddr())
					tmp = tmp->right;
				t_elem *new_elem = new t_elem;
				new_elem->content = val;
				new_elem->right = tmp;
				new_elem->left = tmp->left;
				tmp->left->right = new_elem;
				tmp->left = new_elem;
				len++;
				return (--position);
			}
			/*void insert (iterator position, size_type n, const value_type& val)
			{
				
			}*/
			/*template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);
			*/
	};
}