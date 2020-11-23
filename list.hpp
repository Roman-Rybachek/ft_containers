/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 00:20:14 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/24 01:51:14 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class list
	{
		private:
			typedef struct 		s_elem
			{
				struct s_elem	*left;
				struct s_elem	*right;
				T				content;
			}					t_elem;

			t_elem 				*list;
			size_t				len;


		public:

	};
}