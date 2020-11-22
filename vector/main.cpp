/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/22 10:56:03 by jeldora          ###   ########.fr       */
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
	ft::vector<int> a(15, 7);
	for (size_t i = 0; i < a.size(); i++)
		a[i] = i;
	ft::vector<int>::iterator it = a.begin();
	it += 10;
	a.erase(it);
	a.erase(it);
	a.erase(it);
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << "\n";	
	return (0);
}