/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/22 19:26:42 by jeldora          ###   ########.fr       */
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
	ft::vector<int> a(2, 2);
	ft::vector<int> b(0, 0);
	a.swap(b);
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";
	std::cout << "\n";	
	for (size_t i = 0; i < b.size(); i++)
		std::cout << b[i] << " ";

	std::cout << "\n";	
	return (0);
}