/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 00:06:59 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/05 06:40:58 by jeldora          ###   ########.fr       */
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
		typedef std::pair<Key, T> value_type;

		public:
			class iterator;
		private:
			typedef struct			s_elem
			{
				s_elem				*parent;
				s_elem 				*left;
				s_elem 				*right;
				value_type			content;
				bool				is_red;
			}						t_elem;

			Compare					compare;
			t_elem					*root;
			t_elem					*end_elem;
			Key						max_value;
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
				new_elem->is_red = true;
				return new_elem;
			}
			t_elem *paste(t_elem **current, t_elem *parent, t_elem *new_elem)
			{
				t_elem *ins_elem = NULL;

				if (*current == NULL || *current == end_elem)
				{
					*current = new_elem;
					(*current)->parent = parent;
					ins_elem = *current;
					if ((*current)->content.first > max_value)
					{
						max_value = (*current)->content.first;
						(*current)->right = end_elem;
					}
				}
				else if (compare((*current)->content.first, new_elem->content.first))
					ins_elem = paste(&(*current)->right, *current, new_elem);
				else if (compare(new_elem->content.first, (*current)->content.first))
					ins_elem = paste(&(*current)->left, *current, new_elem);
				else
					return (ins_elem);
				return (ins_elem);
			}
			t_elem *getGrandparent(t_elem *elem)
			{
				if ((elem != NULL) && (elem->parent != NULL))
					return elem->parent->parent;
				return NULL;
			}
			t_elem *getUncle(t_elem *elem)
			{
				t_elem *grandparent = getGrandparent(elem);
				if ( grandparent == NULL)
					return NULL;
				if (elem->parent == grandparent->left)
					return grandparent->right;
				else
					return grandparent->right;
			}
/*
1) Вставляем узел, смотрим кто его батя. Если батя черный - все норм. Если батя красный - включаем балансеровку.
2) Смотрим, кто у нас дядя:
	1. Если он черный:
		Делаем поворот влево, перекрашиваем дядю и батю
	2. Если он красный:
		Перекрашиваем дядю, батю и деда. Запускаем балансировку для деда.
*/
			void smallRotate(t_elem *elem)
			{
				t_elem *place_for_parent;
				t_elem *place_for_null;
				
				if (elem = elem->parent->right)
				{
					place_for_parent = elem->left;
					place_for_null = elem->parent->right;
				}
				else
				{
					place_for_parent = elem->right;
					place_for_null = elem->parent->left;
				}
				place_for_parent = elem->parent;
				t_elem *grandparent = getGrandparent(elem);
				place_for_null = NULL;
				elem->parent->parent = elem;
				elem->parent = grandparent;
			}

			rotateLeft(t_elem *elem)
			{
				
			}

			iterator rotate(t_elem *elem)
			{
				if (getGrandparent(elem)->left = elem->parent)
				{
					if (elem = elem->parent->right)
						smallRotate(elem);
					rotateRight();
				}
				else
				{
					if (elem = elem->parent->left)
						smallRotate(elem);
					rotateLeft();
				}
			}

			iterator balance(t_elem *elem)
			{
				if (elem->parent == NULL || elem->parent->is_red == false)
					return (iterator(elem));
				if (getUncle(elem).is_red == false)
					// rotate
				else
				{
					getUncle()->is_red = !getUncle()->is_red;
					getGrandparent()->is_red = !getGrandparent()->is_red;
					elem->parent->is_red = !elem->parent->is_red;
					return (iterator(elem));
				}
				
			}
		public:
			map()
			{
				root = NULL;
				length = 0;
				end_elem = newElem(NULL, NULL, NULL);
				root = end_elem;
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
							while (elem->left != NULL)
								elem = elem->left;
							return (*this);
						}
						if (elem->parent != NULL && elem->parent->content.first > elem->content.first) // Если это левый лист
						{
							elem = elem->parent;
							return (*this);
						}
						t_elem *tmp = elem;
						while (tmp->parent != NULL && tmp->parent->content.first < tmp->content.first) // Если это правый лист
							tmp = tmp->parent;
						if (tmp->parent == NULL)
							return *this;
						else if (tmp->parent->content.first > tmp->content.first)
						{
							elem = tmp->parent;
							return *this;
						} 
						return *this;
					}
					iterator &operator--()
					{
						if (elem->left != NULL) // Если есть слево элемент
						{
							elem = elem->left;
							while (elem->right != NULL)
								elem = elem->right;
							return (*this);
						}
						if (elem->parent != NULL && elem->parent->content.first < elem->content.first) // Если это правый лист
						{
							elem = elem->parent;
							return (*this);
						}
						t_elem *tmp = elem;
						while (tmp->parent != NULL && tmp->parent->content.first > tmp->content.first) // Если это левый лист
							tmp = tmp->parent;
						if (tmp->parent == NULL)
							return *this;
						else if (tmp->parent->content.first < tmp->content.first)
						{
							elem = tmp->parent;
							return *this;
						}
						return *this;
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
					iterator &operator=(const iterator &copy)
					{
						elem = copy.elem;
						return *this;
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
				t_elem	*ins_elem = paste(&root, NULL, new_elem);
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

