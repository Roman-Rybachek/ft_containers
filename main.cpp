/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/03 18:47:51 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <memory>
#include <stack>
#include <list>
#include "list.hpp"
#include "map.hpp"


int		main(void)
{	


	ft::map<int, int> m;

	m.insert(std::pair<int, int>(4, 44));
	m.insert(std::pair<int, int>(6, 66));
	m.insert(std::pair<int, int>(2, 22));
	m.insert(std::pair<int, int>(3, 33));
	m.insert(std::pair<int, int>(1, 11));
	m.insert(std::pair<int, int>(5, 55));
	m.end();
	for (ft::map<int, int>::iterator i = m.begin(); i != m.end(); i++)
	{
		std::cout << (*i).first << " ";
	}
	

	return (0);
}
