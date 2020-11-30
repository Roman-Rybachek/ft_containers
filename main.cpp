/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/30 06:02:22 by jeldora          ###   ########.fr       */
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
	ft::list<int> l1((size_t)10, (int)0);
	ft::list<int>::iterator it = l1.end();
	for (size_t i = 1; i < l1.size() + 1; i++)
	{
		*it = i;
		std::cout << *it << " ";
		it++;
	}
	std::cout << "\n";
	l1.reverse();
	it = l1.begin();
	for (size_t i = 0; i < l1.size() + 3; i++)
	{
		std::cout << *it++ << " ";
	}
	std::cout << "\n" << *it;
	return (0);
}
