/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/09 10:02:52 by jeldora          ###   ########.fr       */
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
	
	for (ft::map<int,int>::reverse_iterator i = m.rbegin() ; i != m.rend(); i++)
	{
		std::cout << (*i).first << " ";
	}
	

	return (0);
}
