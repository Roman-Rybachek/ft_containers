/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 00:06:59 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/03 12:55:52 by jeldora          ###   ########.fr       */
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
												value_type content = pair<Key, T>(Key(), T()))
			{
				t_elem *new_elem = new t_elem;
				new_elem->parent = parent;
				new_elem->left = left;
				new_elem->right = right;
				new_elem->content = content;
				return new_elem;
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
						if (tmp->parent = NULL)
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
						if (tmp->parent = NULL)
							return *this;
						else if (tmp->parent->content.first < tmp->content.first)
						{
							elem = tmp->parent;
							return *this;
						}
					}
					value_type &operator*()
					{
						return (elem->content);
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
			/*value_type insert (const value_type& val)
			{
				if (root == NULL)
				{
					root = newElem(NULL, NULL, NULL, val);
					value_type ret(); // добавить итератор
				}
			};*/
	};
}