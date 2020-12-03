/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 00:06:59 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/03 06:48:19 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <functional>

namespace ft
{

	

	template < class Key, class T, typename Compare = std::less<Key> >
	class map
	{

		private:
			typedef struct		s_elem
			{
				s_elem			*parent;
				s_elem 			*left;
				s_elem 			*right;
				Key				key;
				T				content;
			}					t_elem;

			t_elem				*root;
			size_t				length;
		public:
			map()
			{
				root = NULL;
				length = 0;
			}
			class iterator
			{
				private:
					t_elem *elem;
				public:
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
						if (elem->parent != NULL && elem->parent->key > elem->key) // Если это левый лист
						{
							elem = elem->parent;
							return (*this);
						}
						t_elem *tmp = elem;
						while (tmp->parent != NULL && tmp->parent->key < tmp->key) // Если это правый лист
							tmp = elem->parent;
						if (tmp->parent = NULL)
							return *this;
						else if (tmp->parent->key > tmp->key)
						{
							elem = tmp->parent;
							return *this;
						}
					}
			};
	};
}