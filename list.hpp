/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 23:22:16 by rinne             #+#    #+#             */
/*   Updated: 2020/11/29 01:08:31 by jeldora          ###   ########.fr       */
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
			t_elem				*c;
			t_elem				*first_elem;
			t_elem				*last_elem;
			// создается один раз, хранит в себе длину листа. Указывает на первый и на последний элемент и наоборот
			t_elem				*supp_elem; 
			

			t_elem				*createElemet(	const t_elem *set_left = NULL, \
												const t_elem *set_right = NULL, \
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
            void                increaseLength(const size_t& delta = 1)
            {
                length += delta;
                try
                    supp_element->content = delta;
                catch(const std::exception& e)
                {}
            }
			void                decreaseLength(const size_t& delta = 1)
            {
                length -= delta;
                try
                    supp_element->content = delta;
                catch(const std::exception& e)
                {}
            }
		public:
			list()
			{	
				c = NULL; 
				first_elem = NULL; 
				last_elem = NULL; 
				length = 0;
				supp_elem = createElemet();
				supp_elem->content = 0;
			}
			void push_back(const T& val)
			{
				if (c == NULL)
				{
					c = createElemet(supp_elem, supp_elem, val);
					last_elem = c;
					first_elem = c;
				}
				else
				{
					last_elem = createElemet(last_elem, supp_elem, val);
					increaseLength();	
				}
			}
			void push_front(const T& val)
			{
				if (c == NULL)
				{
					c = createElemet(supp_elem, supp_elem, val);
					last_elem = c;
					first_elem = c;
				}
				else
				{
					first_elem = createElemet(supp_elem, first_elem, val);
					increaseLength();	
				}
			}
	};
}
