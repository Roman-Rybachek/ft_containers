/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:55:34 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/11 14:30:29 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.hpp"
#include <iostream>

template <typename T>
void print_list(ft::list<T> v)
{
	for (typename ft::list<T>::iterator i = v.begin(); i != v.end(); i++)
		std::cout << *i << " ";
	std::cout << "\n";
}

int main()
{
	ft::list<int> v;

	std::cout << "\nList test: \n";
	std::cout << "Max size: " << v.max_size() << "\n";
	std::cout << "Size: " << v.size() << "\n";
	std::cout << "Is empty: " << v.empty() << "\n";

	v.resize(10);
	std::cout << "\nResize 10. Size: " << v.size() << "\n";
	print_list(v);
	
	std::cout << "\nAssign:\n";
	v.assign((size_t)5, (int)5);
	print_list(v);
	std::cout << "\nAssign(other.begin(), other.end()) and constructor:\n";
	ft::list<int> v1((size_t)3, (int)3);
	ft::list<int>::iterator it_begin = v1.begin();
	ft::list<int>::iterator it_end = v1.end();
	v.assign(it_begin, it_end);
	print_list(v);

	v.push_back(22);
	v.push_front(11);
	std::cout << "\nPush back 22 and push front 11" << "\n";
	print_list(v);
	std::cout << "\nFront and back: \n";
	std::cout << v.front() << " " << v.back() << "\n";

	std::cout << "\nErase: \n";
	v.erase(v.begin());
	print_list(v);
	it_end = --v.end();
	it_begin = ++v.begin();
	v.erase(++it_begin, it_end);
	print_list(v);

	return 0;
}