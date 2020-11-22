/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/22 03:26:02 by jeldora          ###   ########.fr       */
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
	ft::vector<int> a(7, 5);
	a.reserve(10);
	std::cout << a.capacity() << "\n";
	a.push_back(3);
	std::cout << a.capacity() << "\n";
	std::cout << a.size() << "\n";
	a.push_back(3);
	a.push_back(3);
	std::cout << a.size() << "\n";
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << "\n";
	
	
	return (0);
}