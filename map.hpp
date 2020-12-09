/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 00:06:59 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/09 07:51:11 by jeldora          ###   ########.fr       */
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
			std::less<T>			compare_value;
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
						end_elem->parent = *current;
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
			void	is_root(t_elem *old_root, t_elem *new_root)
			{
				if (old_root == root)
					root = new_root;
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
			t_elem *find_elem_or_next(const Key& k, t_elem *root_elem)
			{
				t_elem *ret = NULL;
				if (root_elem->content.first == k)
					return root_elem;
				else if (root_elem->left == NULL && root_elem->right == NULL)
				{
					iterator it(root_elem);
					it++;
					return (it->elem);
				}
				if (k > root_elem->content.first)
					ret = find_elem_or_next(k, root_elem->right);
				else if (k < root_elem->content.first)
					ret = find_elem_or_next(k, root_elem->left);
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
				length = 0;
			}
			t_elem *getMax(t_elem *elem)
			{
				t_elem *tmp = elem;
				while (tmp->right)
					tmp = tmp->right;
				return tmp;
			}
			t_elem *getMin(t_elem *elem)
			{
				t_elem *tmp = elem;
				while (tmp->left)
					tmp = tmp->left;
				return tmp;
			}
			bool	is_list(t_elem *elem)
			{
				if (elem->left == elem->right)
					return true;
				return false;
			}
			bool	is_left(t_elem *elem)
			{
				if (elem->parent->left == elem)
					return true;
				return false;
			}
			bool	delete_list(t_elem **elem)
			{
				if (is_list(*elem) == true)
				{
					if (is_left(*elem) && (*elem)->parent != NULL)
						(*elem)->parent->left = NULL;
					else if (!is_left(*elem) && (*elem)->parent != NULL)
						(*elem)->parent->right = NULL;
					delete *elem;
					*elem = NULL;
					length--;
					return true;
				}
				return false;
			}
			bool	delete_one_brench(t_elem **elem)
			{
				if ((*elem)->left != NULL && (*elem)->right == NULL )
				{
					(*elem)->content = (*elem)->left->content;
					t_elem *tmp = (*elem)->left;
					(*elem)->left = tmp->left;
					(*elem)->right = tmp->right;
					if (tmp->left != NULL)
						tmp->left->parent = *elem;
					if (tmp->right != NULL)
						tmp->right->parent = *elem;
					delete tmp;
					tmp = NULL;
					return true;
				}
				else if ((*elem)->left == NULL && (*elem)->right != NULL)
				{
					(*elem)->content = (*elem)->right->content;
					t_elem *tmp = (*elem)->right;
					(*elem)->left = tmp->left;
					if (tmp->left != NULL)
						tmp->left->parent = *elem;
					(*elem)->right = tmp->right;
					if (tmp->right != NULL)
						tmp->right->parent = *elem;
					delete tmp;
					tmp = NULL;
					return true;
				}
				return false;
			}
			bool	delete_if_right_min(t_elem **elem)
			{
				t_elem *min = getMin((*elem)->right);
				if (min == end_elem)
				{
					(*elem)->left->parent = (*elem)->parent;
					(*elem)->parent->right = (*elem)->left;
					delete *elem;
					*elem = NULL;
					return true;
				}
				if (is_list(min) == false)
				{
					(*elem)->content = min->content;
					min->parent->left = min->right;
					min->right->parent = min->parent;
					delete min;
					min = NULL;
					return true;
				}
				(*elem)->content = min->content;
				if (is_left(min))
					min->parent->left = NULL;
				else
					min->parent->right = NULL;
				delete min;
				return true;
			}
			void	add_end_elem()
			{
				if (end_elem->parent != NULL)
				{
					if (is_left(end_elem))
						end_elem->parent->left = NULL;
					else
						end_elem->parent->right = NULL;
				}
				t_elem *tmp = root;
				while (tmp->right != NULL)
					tmp = tmp->right;
				tmp->right = end_elem;
				tmp->right->parent = tmp;
			}
		public:
			map()
			{
				root = NULL;
				length = 0;
				end_elem = newElem(NULL, NULL, NULL);
				root = end_elem;
				max_value = 0;
			}
			template <class InputIterator>
			map (InputIterator first, InputIterator last)
			{
				if (last < first)
					throw std::exception();
				length = 0;
				max_value = 0;
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
				max_value = 0;
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
				protected:
					t_elem *end_elem;
				public:
					t_elem *elem;
					iterator()
					{
						elem = NULL;
						end_elem = NULL;
					}
					iterator(const iterator &copy)
					{
						elem = copy.elem;
						end_elem = copy.end_elem;
					}
					iterator(t_elem *set_elem, t_elem *set_end_elem)
					{
						elem = set_elem;
						end_elem = set_end_elem;
					}
					iterator &operator++()
					{
						if (elem == end_elem)
							return *this;
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
						if (elem->parent != NULL && elem == end_elem) // Если это правый лист
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
						end_elem = copy.end_elem;
						return *this;
					}
			};
			class const_iterator : public iterator
			{
				protected:
					t_elem *end_elem;
				public:
					t_elem *elem;
					const_iterator()
					{
						elem = NULL;
						end_elem = NULL;
					}
					const_iterator(const const_iterator &copy)
					{
						elem = copy.elem;
						end_elem = copy.end_elem;
					}
					const_iterator(t_elem *set_elem, t_elem *set_end_elem)
					{
						elem = set_elem;
						end_elem = set_end_elem;
					}
					const_iterator(const iterator &copy) : iterator(copy)
					{
						elem = iterator::elem;
						end_elem = iterator::end_elem;
					}
					const_iterator &operator++()
					{
						if (elem == end_elem)
							return *this;
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
					const_iterator &operator--()
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
						if (elem->parent != NULL && elem == end_elem) // Если это правый лист
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
					value_type &operator*() const
					{
						return (elem->content);
					}
					bool operator!=(const const_iterator &other) const
					{
						if (elem->content.first != other.elem->content.first)
							return true;
						return false;
					}
					const_iterator &operator=(const const_iterator &copy)
					{
						elem = copy.elem;
						end_elem = copy.end_elem;
						return *this;
					}
			};
			iterator begin()
			{
				iterator it(root, end_elem);
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
				iterator it(root, end_elem);
				t_elem *prew = NULL;
				while (it.elem != prew)
				{
					prew = it.elem;
					++it;
				}
				return it;
			}
			map& operator= (const map& copy)
			{
				delete_all(&root);
				for (iterator it = copy.begin(); it != copy.end(); it++)
					insert(*it);
				return *this;
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
				}
				else
				{
					inserted = false;
					delete new_elem;
				}
				iterator it(ins_elem, end_elem);
				return (std::pair<iterator, bool>(it, inserted));
			}
			iterator insert (iterator position, const value_type& val)
			{
				if (find(val.first) != end())
					return find(val.first);
				if ((*position).first > val.first && position.elem->left == NULL)
				{
					position.elem->left = newElem(position.elem, NULL, NULL, val);
					length++;
					balance(&position.elem->left);
				}
				if ((*position).first < val.first && position.elem->right == NULL)
				{
					position.elem->right = newElem(position.elem, NULL, NULL, val);
					length++;
					balance(&position.elem->right);
				}
				else
					return insert(val).first;
			}
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while ( first != last )
				{
					insert(*first);
					first++;
				}
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
					return (iterator(found, end_elem));
			}
			void erase (iterator position)
			{
				t_elem *to_erase = position.elem;

				if (position.elem == NULL)
					return ;
				position++;
				if (to_erase == end_elem)
					return ;
				else if (	delete_list(&to_erase) || \
							delete_one_brench(&to_erase) || \
							delete_if_right_min(&to_erase))
				{
					if (position.elem == end_elem)
						add_end_elem();
					length--;
					return ;
				}
			}
			size_t erase (const Key& k)
			{
				iterator to_erase = find(k);
				erase(to_erase);
				return 1;
			}
			void erase (iterator first, iterator last)
			{
				Key k[length];
				int i = 0;
				while (first != last)
				{
					k[i++] = (*first).first;
					first++;
				}
				while (i != 0)
					erase(k[--i]);
			}
			void clear()
			{
				delete_all(&root);
			}
			void swap (map& x)
			{
				map tmp = *this;
				*this = x;
				x = tmp;
			}
			size_t count (const Key& k) const
			{
				if (find(k) == end())
					return 0;
				return 1;
			}
			std::pair<iterator,iterator> equal_range (const Key& k)
			{
				t_elem *found = find_elem_or_next(k, root);
				iterator it(found);
				if ((*it).first == k)
					return std::pair<iterator, iterator>(it, it);
				++it;
				return std::pair<iterator, iterator>(it, it);
			}
			Compare key_comp() const
			{
				return compare;
			}
			std::less<T> value_comp() const
			{
				return (compare_value);
			}
			iterator lower_bound (const Key& k)
			{
				iterator it = find(k);
				if (--end() == it)
					return it;
				return ++it;
			}
			const_iterator lower_bound (const Key& k) const
			{
				const_iterator it = find(k);
				if (--end() == it)
					return it;
				return ++it;
			}
			iterator upper_bound (const Key& k)
			{
				iterator it = find(k);
				return ++it;
			}
			const_iterator upper_bound (const Key& k) const
			{
				const_iterator it = find(k);
				return ++it;
			}
	};
}

