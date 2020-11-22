/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/22 18:58:51 by jeldora          ###   ########.fr       */
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
	ft::vector<int> a(15, 10);
	for (size_t i = 0; i < a.size(); i++)
		a[i] = i;
	ft::vector<int>::iterator it = a.begin();
	a.erase(it + 5, it + 10);
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << " ";	
	std::cout << "\n";	
	return (0);
}