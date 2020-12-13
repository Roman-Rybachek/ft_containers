/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/12/13 19:32:34 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.hpp"
#include "list.hpp"
#include <deque>
#include <list>
#include <iostream>

template <typename T, class Containers>
void push(ft::queue<T, Containers> s)
{
	for (int i = 0; i < 5; i++)
	{
		s.push(i);
	}
}

template <typename T, class Containers>
void pop(ft::queue<T, Containers> s)
{
	for (size_t i = 0; i < 5; i++)
	{
		s.pop();
	}
}

template <typename T, class Containers>
void	push_pop(ft::queue<T, Containers> s)
{
	std::cout << "Push elemnet 1 to 5\n";
	for (size_t i = 0; i < 5; i++)
	{
		s.push(i);
		std::cout << "Last: " << s.back() << "; ";
	}
	std::cout << "\nSize: " << s.size() << "\n";

	std::cout << "Pop elemnets\n";
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << "First: " << s.front() << "; ";
		s.pop();
	}
	std::cout << "\n\n";
}

int		main(void)
{	
	std::cout << "\nQueue test: \n\n";
	ft::queue<int> s1;
	push_pop(s1);
	ft::queue<int, ft::list<int> > s2;
	push_pop(s2);
	ft::queue<int, std::deque<int> > s3;
	push_pop(s3);

	ft::queue<int, std::list<int> > s6;
	ft::queue<int, std::list<int> > s7;

	std::cout << "Relation operators:\n";
	push<int, std::list<int> >(s6);
	push<int, std::list<int> >(s7);
	if (s6 == s7)
		std::cout << "==\n";
	s6.push(10);
	if (s7 != s6)
		std::cout << "!=\n";
	if (s7 <= s6)
		std::cout << "<=\n";
	if (s6 >= s7)
		std::cout << ">=\n";
	if (s7 < s6)
		std::cout << "<\n";
	if (s6 > s7)
		std::cout << ">\n";
	return (0);
}
