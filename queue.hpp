/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 22:25:12 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/24 00:20:30 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <list>

namespace ft
{
	template <typename T, typename Container = std::list<T> >
	class queue
	{
		private:
			Container c;
		public:
			explicit queue (const Container& ctnr = Container())
			{	c = ctnr;	}
			~queue(){}
			bool empty() const
			{	return (c.empty());		}
			size_t size() const
			{	return (c.size());	}
			T& front()
			{
				return (c.front());
			}
			const T& front() const
			{
				return (c.front());
			}
			T& back()
			{
				return (c.back());
			}
			const T& back() const
			{
				return (c.back());
			}
			void push (const T& val)
			{
				c.push_back(val);
			}
			void pop()
			{
				c.pop_front();
			}

			friend bool operator== (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
			{	return (lhs.c == rhs.c);	}
			friend bool operator!= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
			{	return (lhs.c != rhs.c);	}
			friend bool operator< (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
			{	return (lhs.c < rhs.c);	}
			friend bool operator<= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
			{	return (lhs.c <= rhs.c);	}
			friend bool operator> (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
			{	return (lhs.c > rhs.c);	}
			friend bool operator>= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
			{	return (lhs.c != rhs.c);	}


	};
}