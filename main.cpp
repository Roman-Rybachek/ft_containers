/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/08 18:55:48 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <memory>
#include <stack>
#include <list>
#include "list.hpp"
#include "map.hpp"
#include <map>

int		main(void)
{	


	ft::map<int, int> m;

	m.insert(std::pair<int, int>(1, 11));
	m.insert(std::pair<int, int>(2, 22));
	m.insert(std::pair<int, int>(3, 33));
	m.insert(std::pair<int, int>(4, 44));
	m.insert(std::pair<int, int>(5, 55));
	m.insert(std::pair<int, int>(6, 66));
	m.insert(std::pair<int, int>(7, 11));
	m.insert(std::pair<int, int>(8, 11));
	m.insert(std::pair<int, int>(9, 11));

	for (ft::map<int,int>::iterator i = m.begin() ; i != m.end(); i++)
	{
		std::cout << (*i).first << " ";
	}
	std::cout << "\n";
	ft::map<int,int>::iterator last = m.begin();
	m.erase(m.begin(), last);
	for (ft::map<int,int>::iterator i = m.begin() ; i != m.end(); i++)
	{
		std::cout << (*i).first << " ";
	}
	std::cout << "\n";


	return (0);
}
