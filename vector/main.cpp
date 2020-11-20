/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/20 20:00:20 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.hpp"
#include <vector>
#include <iostream>
#include <memory>

class SimpleClass
{
	public:
		int a;
		SimpleClass(int set_a)
		{
			a = set_a;
		}
};


int		main(void)
{
	
	ft::vector<int> a(5, 5);
	for (int i = 0; i < 5; i++)
		a[i] = i;
	ft::vector<int>::iterator it = a.begin();
	std::cout << *it++ << "\n" << ++*it;
	// for (int i = 0; i < 5; i++)
	// {
	// 	std::cout << *it << "\n";
	// 	it++;
	// }

	return (0);
}