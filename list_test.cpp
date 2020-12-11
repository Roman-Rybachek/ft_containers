/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:55:34 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/11 18:20:39 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.hpp"
#include <list>
#include <iostream>

template <typename T, typename list = ft::list<T> >
void print_list(list v)
{
	for (typename list::iterator i = v.begin(); i != v.end(); i++)
		std::cout << *i << " ";
	std::cout << "\n";
}

template <typename T>
bool predicate(T x, T y)
{
	if (x == y)
		return true;
	return false;
}

template <typename T>
bool predicate1(T x)
{
	if (x == 4)
		return true;
	return false;
}


template <typename T>
bool compare(T x, T y)
{
	if (x > y)
		return true;
	return false;
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
	print_list<int>(v);
	
	std::cout << "\nAssign:\n";
	v.assign((size_t)5, (int)5);
	print_list<int>(v);
	std::cout << "\nAssign(other.begin(), other.end()) and constructor:\n";
	ft::list<int> v1((size_t)3, (int)3);
	ft::list<int>::iterator it_begin = v1.begin();
	ft::list<int>::iterator it_end = v1.end();
	v.assign(it_begin, it_end);
	print_list<int>(v);



	v.push_back(22);
	v.push_front(11);
	std::cout << "\nPush back 22 and push front 11" << "\n";
	print_list<int>(v);
	std::cout << "\nFront and back: \n";
	std::cout << v.front() << " " << v.back() << "\n";

	std::cout << "\nErase: \n";
	v.erase(v.begin());
	print_list<int>(v);
	it_end = v.end();
	it_begin = ++v.begin();
	v.erase(++it_begin, it_end);
	print_list<int>(v);

	std::cout << "\nSwap: \n";
	v1.assign((size_t)5, (int)5);
	v.swap(v1);
	print_list<int>(v);
	print_list<int>(v1);

	std::cout << "\nInsert: \n";
	it_end = v1.end();
	it_begin = v1.begin();
	v.insert(v.begin(), (size_t)3, (int)33);
	print_list<int>(v);
	v.insert(v.begin(), it_begin, it_end);
	print_list<int>(v);

	std::cout << "\nUnique: \n";
	v1 = v;
	v.unique();
	print_list<int>(v);
	v = v1;
	v.unique(predicate<int>);
	print_list<int>(v);

	std::cout << "\nSplice: \n";
	v1.assign((size_t)4, (int)4);
	v.assign((size_t)5, (int)5);
	v.splice(v.begin(), v1);
	print_list<int>(v);

	v.assign((size_t)5, (int)5);
	v1.assign((size_t)4, (int)4);
	v.splice(v.begin(), v1, v1.begin());
	print_list<int>(v);

	v.assign((size_t)5, (int)5);
	v1.assign((size_t)4, (int)4);
	v.splice(v.begin(), v1, v1.begin(), v1.end());
	print_list<int>(v);

	std::cout << "\nRemove 4: \n";
	v1 = v;
	v.remove(4);
	print_list<int>(v);
	v1.remove_if(predicate1<int>);
	print_list<int>(v1);

	std::cout << "\nSort: \n";
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	print_list<int>(v);
	v.sort();
	print_list<int>(v);

	std::cout << "\nReverse and sort\n";
	v.reverse();
	print_list<int>(v);
	v.sort(compare<int>);
	print_list<int>(v);

	std::cout << "\nMerge: \n";
	v.clear();
	v.push_back(1);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	v1.clear();
	v.push_back(2);
	v.push_back(4);
	v.push_back(6);
	v.push_back(8);
	v.merge(v1);
	print_list<int>(v);

	std::list<int> l;
	std::list<int> l1;

	l.clear();
	l.push_back(1);
	l.push_back(3);
	l.push_back(5);
	l.push_back(7);
	l1.clear();
	l.push_back(2);
	l.push_back(4);
	l.push_back(6);
	l.push_back(8);
	l.merge(l1);
	print_list<int, std::list<int> >(l);

	v.clear();
	v.push_back(1);
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);
	v1.clear();
	v.push_back(2);
	v.push_back(4);
	v.push_back(6);
	v.push_back(8);
	v.merge(v1, compare<int>);
	print_list<int>(v);

	l.clear();
	l.push_back(1);
	l.push_back(3);
	l.push_back(5);
	l.push_back(7);
	l1.clear();
	l.push_back(2);
	l.push_back(4);
	l.push_back(6);
	l.push_back(8);
	l.merge(l1, compare<int>);
	print_list<int, std::list<int> >(l);

	std::cout << "\nRelations operators:\n";
	v.clear();
	v1.clear();
	v.assign((size_t)3, (int)33);
	v1.assign((size_t)3, (int)33);
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



	return 0;
}