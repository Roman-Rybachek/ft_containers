/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 00:20:14 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/24 22:22:49 by jeldora          ###   ########.fr       */
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

			t_elem 				*l;
			size_t				len;
			
		public:
			list ()
			{	l = NULL; len = 0;	}
			explicit list(size_t n, const T& val = int())
			{
				t_elem *tmp;

				if (n == 0)
				{
					l = NULL;
					len = 0;
					return ;
				}
				l = new t_elem;
				l->content = val;
				l->right = NULL;
				l->left = NULL;
				tmp = l;
				for (size_t i = 0; i < n - 1; i++)
				{
					tmp->right = new t_elem;
					tmp->right->content = val;
					tmp->right->left = tmp;
					tmp->right->right = NULL;
					tmp = tmp->right;
				}
				len = n;
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
					ft::list<T>			*current;
				public:
					ft::list<T> *getCurrent() const
					{	return (current);	}
					iterator()
					{	current = NULL;		}
					iterator(const iterator &copy)
					{	current = copy.current; index = copy.index;		}
					
					iterator(ft::vector<T> *set_current, size_t set_index)
					{	
					current = set_current; index = set_index;	}
					virtual T &operator*()
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

			T& front()
			{
				return (l->content);
			}
			const T& front() const
			{
				return (l->content);
			}
	};
}