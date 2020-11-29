/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 23:22:16 by rinne             #+#    #+#             */
/*   Updated: 2020/11/29 02:53:23 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template < class T >
	class list
	{
		private:
			typedef struct		s_elem
			{
				struct s_elem	*left;
				struct s_elem	*right;
				T				content;
			}					t_elem;

			size_t				length;
			t_elem				*first_elem;
			t_elem				*last_elem;
			t_elem				*supp_elem; 
			

			t_elem				*createElemet(	t_elem *set_left = NULL, \
												t_elem *set_right = NULL, \
												const T&val = T())
			{
				t_elem *new_elem;

				new_elem = new t_elem;
				new_elem->left = set_left;
				new_elem->right = set_right;
				new_elem->content = val;
				if (set_left != NULL)
					set_left->right = new_elem;
				if (set_right != NULL)
					set_right->left = new_elem;
				return new_elem;
			}
            void                increaseLength(size_t delta = 1)
            {
                length += delta;
                try
				{
					T conv = length;
                    supp_elem->content = conv;
				}
                catch(...)
                {}
            }
			void                decreaseLength(size_t delta = 1)
            {
                length -= delta;
                try
				{
					T conv = length;
                    supp_elem->content = conv;
				}
                catch(...)
                {}
            }
		public:
			list()
			{	
				first_elem = NULL; 
				last_elem = NULL; 
				length = 0;
				supp_elem = createElemet();
				supp_elem->left = supp_elem;
				supp_elem->right = supp_elem;
				supp_elem->content = 0;
			}
			explicit list(size_t n, const T& val = T())
			{
				length = 0;
				for (size_t i = 0; i < n; i++)
					push_back(val);
			}
			void push_back(const T& val)
			{
				if (first_elem == NULL)
				{
					first_elem = createElemet(supp_elem, supp_elem, val);
					last_elem = first_elem;
				}
				else
				{
					last_elem = createElemet(last_elem, supp_elem, val);
				}
				increaseLength();
			}
			void push_front(const T& val)
			{
				if (first_elem == NULL)
				{
					first_elem = createElemet(supp_elem, supp_elem, val);
					last_elem = first_elem;
				}
				else
				{
					first_elem = createElemet(supp_elem, first_elem, val);
				}
				increaseLength();	
			}
			
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
						p = p->right;  
						return (*this);	
					}
					iterator &operator--()//
					{
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
			iterator begin()
			{	return (iterator(first_elem));	}
			iterator end()
			{	return (iterator(last_elem));	}
	};
}
