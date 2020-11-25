/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/25 03:10:48 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <stack>
#include <list>
#include "queue.hpp"


int		main(void)
{
	ft::vector<int> a(5, 3);
	a[0] = 9;
	a[1] = 10;
	a[2] = 11;
	a[3] = 12;
	a[4] = 13;
	//ft::vector<int>::iterator it = a.begin();
	ft::vector<int>::const_iterator c_it = a.begin();
	ft::vector<int>::const_iterator it = a.end() -1;
	c_it += 3;
	c_it = it;
	c_it -= 1;
	std::cout << *c_it << " ";

	return (0);
}
