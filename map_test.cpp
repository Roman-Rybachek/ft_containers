/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 10:00:27 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/12 18:33:31 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <iostream>

void print_map(ft::map<int, int> &v)
{
	for (ft::map<int, int>::iterator i = v.begin(); i != v.end(); i++)
		std::cout << (*i).first << ":" << (*i).second << " ";
	std::cout << "\n";
}

int		main()
{
	ft::map<int, int> v;

	std::cout << "\nMap test: \n";
	std::cout << "Size: " << v.size() << "\n";
	std::cout << "Is empty: " << v.empty() << "\n";
	std::cout << "Max size: " << v.max_size() << "\n";


	std::cout << "\nInsert: \n";
	v.insert(std::pair<int, int>(1, 100));
	v.insert(std::pair<int, int>(2, 200));
	v.insert(std::pair<int, int>(3, 300));
	v.insert(std::pair<int, int>(4, 400));
	v.insert(std::pair<int, int>(5, 500));
	print_map(v);
	ft::map<int, int>::iterator it = v.begin();
	it++;
	it++;
	it++;
	it++;
	it++;
	v.insert(it, std::pair<int, int>(6, 600));
	print_map(v);

	ft::map<int, int> v1;
	v1.insert(std::pair<int, int>(7, 700));
	v1.insert(std::pair<int, int>(8, 800));
	v1.insert(std::pair<int, int>(9, 900));
	v1.insert(std::pair<int, int>(10, 1000));
	v.insert(v1.begin(), v1.end());
	print_map(v);
	std::cout << "Find 9: ";
	if (v.find(9) != v.end())
		std::cout << "true\n";
	else
		std::cout << "false\n";

	std::cout << "\nErase: \n";
	v.erase(v.begin());
	print_map(v);
	v.erase(9);
	print_map(v);
	it = v.begin();
	it++; it++; it++;
	v.erase(it, v.end());
	print_map(v);

	std::cout << "\nSwap: \n";
	print_map(v);
	print_map(v1);
	v.swap(v1);
	print_map(v);
	print_map(v1);
	return 0;
}