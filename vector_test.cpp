/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:58:26 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/11 12:54:25 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

template <typename T>
void print_vector(ft::vector<T> v)
{
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << "\n";
}

int main()
{
	ft::vector<int> v;

	std::cout << "\nVector test:\n";
	std::cout << "Max size: " << v.max_size() << "\n";
	std::cout << "Size: " << v.size() << "\n";
	std::cout << "Capicity: " << v.capacity() << "\n";
	std::cout << "Is empty: " << v.empty() << "\n";
	v.reserve(5);
	std::cout << "\nReserve 5. Capicity: " << v.capacity() << "\n";

	v.resize(10);
	std::cout << "\nResize 10. Size: " << v.size() << " Capicity: " << v.capacity() << "\n";
	print_vector(v);
	v.resize(5);
	std::cout << "\nResize 5. Size: " << v.size() << " Capicity: " << v.capacity() << "\n";
	print_vector(v);
	std::cout << "Is empty: " << v.empty() << "\n";

	v.push_back(22);
	v[1] = 11;
	std::cout << "\nPush back 22 and change [1] element. Size: " << v.size() << " Capicity: " << v.capacity() << "\n";
	print_vector(v);
	std::cout << "At(1) = " << v.at(1) << "\n";

	ft::vector<int> v1(v); // copy
	std::cout << "\nAssign(3, 15) and copy constructor:\n";
	v1.assign(3, 15);
	print_vector(v1);
	

	std::cout << "\nAssign(other.begin(), other.end()):\n";
	ft::vector<int>::iterator it_begin = v.begin();
	ft::vector<int>::iterator it_end = v.end();
	v1.assign(it_begin, it_end);
	print_vector(v1);
	
	std::cout << "\nFront and back: \n";
	std::cout << v1.front() << " " << v1.back() << "\n";

	std::cout << "\n2x pop back: \n";
	v1.pop_back();
	v1.pop_back();
	print_vector(v1);

	std::cout << "\nSwap: \n";
	v.swap(v1);
	print_vector(v);
	print_vector(v1);

	print_vector(v);
	std::cout << "\nInsert: \n";
	it_end = v1.end();
	it_begin = v1.begin();
	// Они базируются на простом insert
	v.insert(v.begin(), (size_t)3, (int)33);
	print_vector(v);
	v.insert(v.begin(), it_begin, it_end);
	print_vector(v);

	std::cout << "\nErase: \n";
	v.erase(v.begin());
	print_vector(v);
	it_end = v.end() - 1;
	it_begin = v.begin() + 1;
	v.erase(it_begin, it_end);
	print_vector(v);

	std::cout << "\nRelations operators:\n";
	v.clear();
	v1.clear();
	v.assign(3, 33);
	v1.assign(3, 33);
	if (v == v1)
		std::cout << "==\n";
	v1.push_back(10);
	if (v != v1)
		std::cout << "!=\n";
	if (v <= v1)
		std::cout << "<=\n";
	if (v1 >= v)
		std::cout << ">=\n";
	if (v < v1)
		std::cout << "<\n";
	if (v1 > v)
		std::cout << ">\n";

	return (0);
}