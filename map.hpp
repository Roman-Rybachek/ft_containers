/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 00:06:59 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/03 14:27:37 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <functional>
#include <utility>

namespace ft
{

	template < class Key, class T, typename Compare = std::less<Key> >
	class map
	{
		typedef std::pair<const Key, T> value_type;

		private:
			typedef struct			s_elem
			{
				s_elem				*parent;
				s_elem 				*left;
				s_elem 				*right;
				value_type			content;
			}						t_elem;

			t_elem					*root;
			size_t					length;
			t_elem 					*newElem(	t_elem *parent = NULL, \
												t_elem *left = NULL, \
												t_elem *right = NULL, \
												value_type content = value_type(Key(), T()))
			{
				t_elem *new_elem = new t_elem;
				new_elem->parent = parent;
				new_elem->left = left;
				new_elem->right = right;
				new_elem->content = content;
				return new_elem;
			}
			t_elem *paste(t_elem *current, t_elem *parent, t_elem *new_elem)
			{
				if (current == NULL)
				{
					current = new_elem;
					current->parent = parent;
				}
				else if (Compare(current->content.first, new_elem->content.first))
					paste(current->right, parent, new_elem);
				else if (Compare(new_elem->content.first, current->content.first))
					paste(current->left, parent, new_elem);
				else
					return (current);
				return (current);
			}
		public:
			map()
			{
				root = NULL;
				length = 0;
			}

			class iterator
			{
				public:
					t_elem *elem;
					iterator()
					{
						elem = NULL;
					}
					iterator(t_elem *set_elem)
					{
						elem = set_elem;
					}
					iterator &operator++()
					{
						if (elem->right != NULL) // Если есть справа элемент
						{
							elem = elem->right;
							return (*this);
						}
						if (elem->parent != NULL && elem->parent->content.first > elem->content.first) // Если это левый лист
						{
							elem = elem->parent;
							return (*this);
						}
						t_elem *tmp = elem;
						while (tmp->parent != NULL && tmp->parent->content.first < tmp->content.first) // Если это правый лист
							tmp = elem->parent;
						if (tmp->parent == NULL)
							return *this;
						else if (tmp->parent->content.first > tmp->content.first)
						{
							elem = tmp->parent;
							return *this;
						}
					}
					iterator &operator--()
					{
						if (elem->left != NULL) // Если есть слево элемент
						{
							elem = elem->left;
							return (*this);
						}
						if (elem->parent != NULL && elem->parent->content.first < elem->content.first) // Если это правый лист
						{
							elem = elem->parent;
							return (*this);
						}
						t_elem *tmp = elem;
						while (tmp->parent != NULL && tmp->parent->content.first > tmp->content.first) // Если это левый лист
							tmp = elem->parent;
						if (tmp->parent == NULL)
							return *this;
						else if (tmp->parent->content.first < tmp->content.first)
						{
							elem = tmp->parent;
							return *this;
						}
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
					value_type &operator*()
					{
						return (elem->content);
					}
					bool operator!=(const iterator &other) const
					{
						if (elem->content.first != other.elem->content.first)
							return true;
						return false;
					}
			};
			iterator begin()
			{
				iterator it(root);
				t_elem *prev = NULL;
				while (it.elem != prev)
				{
					prev = it.elem;
					--it;
				}
				return it;
			}
			iterator end()
			{
				iterator it(root);
				t_elem *next = NULL;
				while (it.elem != next)
				{
					next = it.elem;
					++it;
				}
				return it;
			}
			
			std::pair<iterator, bool> insert (const value_type& val)
			{
				t_elem	*new_elem = newElem(NULL, NULL, NULL, val);
				t_elem	*ins_elem = paste(root, NULL, new_elem);
				bool	inserted;
				if (new_elem == ins_elem)
					inserted = true;
				else
				{
					inserted = false;
					delete new_elem;
				}
				iterator it(ins_elem);
				return (std::pair<iterator, bool>(it, inserted));
			}
	};
}