/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 00:20:14 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/25 22:20:42 by jeldora          ###   ########.fr       */
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
			explicit list(size_t n, const T& val = int())
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
				for (size_t i = 0; i < n - 1; i++)
				{
					tmp->right = new t_elem;
					tmp->right->left = tmp;
					tmp = tmp->right;
					tmp->content = val;
					tmp->right = NULL;
				}
			}
	/*		template <class InputIterator>
			list (InputIterator first, InputIterator last)
			{
				t_elem *tmp = l;

				tmp = alloc.allocate(sizeof(t_elem));
				tmp->content = *first;
				tmp->left = NULL;
				tmp->right = NULL;
				for (InputIterator i = first + 1; i < last; i++)
				{
					tmp->right = alloc.allocate(sizeof(t_elem));
					tmp->right->left = tmp;
					tmp->right->right = NULL;
					tmp->right->content = *i;
					tmp = tmp->right;
				}
			}
			list (const list& x)
			{
				if (!x)
					throw std::exception();
				l = alloc.allocate(sizeof(t_elem));
				t_elem *tmp = l;
				t_elem &param = x;
				tmp->content = param.content;
				tmp->left = NULL;
				tmp->right = NULL;
				len = 1;
				while (param.right != NULL)
				{
					param = *param.right;
					tmp->right = alloc.allocate(sizeof(t_elem));
					tmp->right->content = param.content;
					tmp->right->left = tmp;
					tmp->right->right = NULL;
					tmp = tmp->right;
					len++;
				}
			}*/
			
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
							p = p->right; 
						return (*this);	
					}
					iterator &operator--()//
					{
						if (p->left != NULL)
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
			T& front()
			{
				return (c->content);
			}
			const T& front() const
			{
				return (c->content);
			}
	};
}