/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/30 04:01:55 by jeldora          ###   ########.fr       */
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
	ft::list<int> l2((size_t)3, (int)4);
	ft::list<int>::iterator it = l1.end();
	ft::list<int>::iterator it2 = l2.begin();
	l1.splice(it, l2, it2);
	it = l1.begin();
	for (size_t i = 0; i < l1.size() + 1; i++)
	{
		std::cout << *it++ << " ";
	}
	return (0);
}
