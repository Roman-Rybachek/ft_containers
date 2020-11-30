/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/30 23:21:49 by jeldora          ###   ########.fr       */
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
	l1.push_back(1);
	l1.push_back(3);
	l1.push_back(5);
	ft::list<int> l2;
	l2.push_back(2);
	l2.push_back(4);

	l1.merge(l2);
	for (ft::list<int>::iterator it = l1.begin(); it != l1.end(); it++)
	{
		std::cout << *it << " ";
	}

	return (0);
}
