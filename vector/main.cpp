/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/22 06:05:41 by jeldora          ###   ########.fr       */
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
	for (int j = 0; j < 7; j++)
	{
		ft::vector<int> a(7, 7);
		// std::vector<int> b(10, 22);
		// std::vector<int>::iterator bb = b.begin();
		// std::vector<int>::iterator be = b.end();

		ft::vector<int>::iterator it = a.begin();

		it += j;
		a.insert(it, (size_t)15, (int)44);
		for (size_t i = 0; i < a.size(); i++)
			std::cout << a[i] << " ";
		std::cout << "\n";
		it -= j;
	}
	
	return (0);
}