/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/02 10:51:23 by jeldora          ###   ########.fr       */
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
	ft::list<int> l1;
	l1.push_back(5);
	l1.push_back(4);
	l1.push_back(9);
	l1.push_back(2);
	l1.push_back(1);

	ft::list<int> l2;
	l2.push_back(5);
	l2.push_back(4);
	l2.push_back(9);
	l2.push_back(2);
	l2.push_back(1);

	if (l2 > l1)
		std::cout << "gsdfgsdfg";

	l1.sort();
	for (ft::list<int>::iterator it = l1.begin(); it != l1.end(); it++)
	{
		std::cout << *it << " ";
	}
	// ft::list<int>::iterator it = l1.begin();
	// for (size_t i = 0; i < l1.size(); i++)
	// {
	// 	std::cout << *it++ << " ";
	// }
	return (0);
}
