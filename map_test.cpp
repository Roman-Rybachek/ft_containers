/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 10:00:27 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/12 10:20:25 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"
#include <iostream>

template <typename T, typename Key, typename map = ft::map<Key, T> >
void print_map(map v)
{
	for (typename map::iterator i = v.begin(); i != v.end(); i++)
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

	std::cout << "Insert: \n";
	v.insert(std::pair<int, int>(1, 100));
	v.insert(std::pair<int, int>(2, 200));
	v.insert(std::pair<int, int>(3, 300));
	v.insert(std::pair<int, int>(4, 400));
	v.insert(std::pair<int, int>(5, 500));
	print_map<int, int>(v);

	return 0;
}