/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 00:06:59 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/05 15:37:51 by jeldora          ###   ########.fr       */
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
		Делаем поворот, перекрашиваем дядю и батю
	2. Если он красный:
		Перекрашиваем дядю, батю и деда. Запускаем балансировку для деда.
*/
			void smallRotate(t_elem **elem)
			{
				t_elem *place_for_parent;
				t_elem *place_for_null;
				
				if ((*elem) == (*elem)->parent->right)
				{
					place_for_parent = (*elem)->left;
					place_for_null = (*elem)->parent->right;
				}
				else
				{
					place_for_parent = (*elem)->right;
					place_for_null = (*elem)->parent->left;
				}
				place_for_parent = (*elem)->parent;
				t_elem *grandparent = getGrandparent((*elem));
				place_for_null = NULL;
				(*elem)->parent->parent = (*elem);
				(*elem)->parent = grandparent;
			}
			void rotateLeft(t_elem **elem)
			{
				t_elem *new_root = (*elem)->parent;
				t_elem *grandparent = getGrandparent(*elem);
				new_root->is_red = !new_root->is_red;
				grandparent->is_red = !grandparent->is_red;
				new_root->left = grandparent;
				new_root->parent = grandparent->parent;
				grandparent->parent = new_root;
				grandparent->right = NULL;
			}
			// забыл изменить цвета при повороте
			void rotateRight(t_elem **elem)
			{
				t_elem *new_root = (*elem)->parent;
				t_elem *grandparent = getGrandparent(*elem);
				new_root->is_red = !new_root->is_red;
				grandparent->is_red = !grandparent->is_red;
				new_root->right = grandparent;
				new_root->parent = grandparent->parent;
				grandparent->parent = new_root;
				grandparent->left = NULL;
			}
			void rotate(t_elem **elem)
			{
				if (getGrandparent(*elem)->left == (*elem)->parent)
				{
					if ((*elem) == (*elem)->parent->right)
						smallRotate(elem);
					rotateRight(elem);
				}
				else
				{
					if ((*elem) == (*elem)->parent->left)
						smallRotate((elem));
					rotateLeft(elem);
				}
			}
			void balance(t_elem **elem)
			{
				if ((*elem)->parent == NULL || (*elem)->parent->is_red == false)
					return ;
				if (getGrandparent(*elem) == NULL)
				{
					(*elem)->parent->is_red = !(*elem)->parent->is_red;
					return ;
				}
				if (getUncle(*elem)->is_red == false)
					rotate(elem);
				else
				{
					getUncle(*elem)->is_red = !getUncle(*elem)->is_red;
					getGrandparent(*elem)->is_red = !getGrandparent(*elem)->is_red;
					(*elem)->parent->is_red = !(*elem)->parent->is_red;
					t_elem *gr = getGrandparent(*elem);
					balance(&gr);
					return ;
				}
			}
			t_elem *find_elem(const Key& k, t_elem *root_elem)
			{
				t_elem *ret = NULL;
				if (root_elem->content.first == k)
					return root_elem;
				else if (root_elem->left == NULL && root_elem->right == NULL)
					return NULL;
				if (k > root_elem->content.first)
					ret = find_elem(k, root_elem->right);
				else if (k < root_elem->content.first)
					ret = find_elem(k, root_elem->left);
				return ret;
			}
			void delete_all(t_elem **elem)
			{
				if ((*elem)->left != NULL)
					delete_all(&(*elem)->left);
				if ((*elem)->right != NULL)
					delete_all(&(*elem)->right);
				delete *elem;
				*elem = NULL;
			}
		public:
			map()
			{
				root = NULL;
				length = 0;
				end_elem = newElem(NULL, NULL, NULL);
				root = end_elem;
			}
			template <class InputIterator>
			map (InputIterator first, InputIterator last)
			{
				if (last < first)
					throw std::exception();
				length = 0;
				root = NULL;
				end_elem = newElem(NULL, NULL, NULL);
				while (first != last)
				{
					insert(*first);
					first++;
				}
			}
			map (const map& copy)
			{
				length = 0;
				root = NULL;
				for (iterator it = copy.begin(); it != copy.end(); it++)
					insert(*it);
			}
			~map()
			{
				delete_all(&root);
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
			std::pair<iterator, bool> insert (const value_type& val)
			{
				t_elem	*new_elem = newElem(NULL, NULL, NULL, val);
				t_elem	*ins_elem = paste(&root, NULL, new_elem);
				bool	inserted;
				if (new_elem == ins_elem)
				{
					inserted = true;
					length++;
					balance(&ins_elem);
				}
				else
				{
					inserted = false;
					delete new_elem;
				}
				iterator it(ins_elem);
				return (std::pair<iterator, bool>(it, inserted));
			}
			T& operator[] (const Key& k)
			{
				t_elem *found = find_elem(k, root);
				if (found != NULL)
					return (found->content.second);
				iterator ret = insert(value_type(k, T())).first;
				return ((*ret).second);
			}

			iterator find (const Key& k)
			{
				t_elem *found = find_elem(k, root);
				if (found == NULL)
					return end();
				else
					return (iterator(found));
			}
	};
}

