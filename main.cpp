/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/25 02:08:27 by jeldora          ###   ########.fr       */
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
	ft::vector<int> a(5, 5);
	
	ft::vector<int>::iterator it = a.begin();
	ft::vector<int>::iterator en = a.end();
	en -= 3;
	for (ft::vector<int>::iterator i = it; i < en; i++)
	{
		std::cout << *i << " ";
	}
	
	return (0);
}
