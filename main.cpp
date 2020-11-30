/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/30 20:16:02 by jeldora          ###   ########.fr       */
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
	ft::list<int> l1((size_t)10, (int)5);
	ft::list<int>::iterator it = l1.begin();
	*it++ = 1;
	*it++ = 1;
	*it++ = 2;
	*it++ = 2;
	*it++ = 3;
	*it++ = 3;
	l1.unique();
	it = l1.begin();
	for (size_t i = 0; i < l1.size(); i++)
	{
		std::cout << *it++ << " ";
	}
	return (0);
}
