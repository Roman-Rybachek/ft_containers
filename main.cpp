/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/29 16:50:47 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <stack>
#include <list>
#include "list.hpp"

int		main(void)
{	
	ft::list<int> l1((size_t)5, (int)3);
	ft::list<int> l2((size_t)10, (int)4);
	l1.swap(l2);
	ft::list<int>::iterator it = l2.begin();

	for (size_t i = 0; i < l2.size(); i++)
	{
		std::cout << *it++ << " ";
	}
	return (0);
}
