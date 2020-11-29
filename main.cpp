/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/29 14:35:35 by jeldora          ###   ########.fr       */
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
	ft::list<int> l((size_t)5, (int)3);
	std::vector<int> v((size_t)0, (int)4);
	ft::list<int>::iterator it = l.begin();

	it++;
	it++;
	l.insert(it, v.begin(), v.end());
	it = l.begin();
	for (size_t i = 0; i < l.size(); i++)
	{
		std::cout << *it++ << " ";
	}
	
   
	return (0);
}
