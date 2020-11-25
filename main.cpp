/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/25 04:06:15 by jeldora          ###   ########.fr       */
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
	ft::vector<int>::iterator it = a.end();
	ft::vector<int>::reverse_iterator r_it(it);
	std::cout << *r_it << " ";

	return (0);
}
