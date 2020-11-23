/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:17:58 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/23 23:13:28 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> > 
	class stack
	{
		protected:
			Container c;
		public:
			explicit stack (const Container& cntr = Container())
			{	c = cntr;	}
			~stack(){}
			bool empty() const
			{	return (c.empty());		}
			size_t size() const
			{	return (c.size());	}
			T& top()
			{	return (c.back());	}
			T& top() const
			{	return (c.back());	}
			void push(const T& val)
			{	c.push_back(val);	}
			void pop()
			{	c.pop_back();	}

			friend bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{	return (lhs.c == rhs.c);	}
			friend bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{	return (lhs.c != rhs.c);	}
			friend bool operator< (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{	return (lhs.c < rhs.c);	}
			friend bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{	return (lhs.c <= rhs.c);	}
			friend bool operator> (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{	return (lhs.c > rhs.c);	}
			friend bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
			{	return (lhs.c != rhs.c);	}
	};
}