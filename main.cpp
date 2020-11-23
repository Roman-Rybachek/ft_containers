/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:57:46 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/24 01:03:11 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "stack.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <stack>
#include <list>
#include "queue.hpp"

int		main(void)
{
	ft::vector<int> v1(1, 4);
	ft::vector<int> v2(1, 4);

	std::cout << (v1 <= v2);
	std::cout << (v1 >= v2);
	
	return (0);
}