/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:48:28 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/09 23:53:47 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP
# include <iostream>
# include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
	public:
		class iterator
		{
			private:
				MutantStack		&m_current;
				unsigned int	m_index;
				iterator();

			public:
				iterator(MutantStack &current, unsigned int index);
				iterator(iterator const &copy);
				iterator &operator++();
				iterator &operator--();
				bool operator==(iterator const &other);
				bool operator!=(iterator const &other);
				T &operator*();

				~iterator();
		};

		iterator	begin();
		iterator	end();
		MutantStack();
		~MutantStack();

	private:
		MutantStack(const MutantStack &copy);
		MutantStack &operator=(const MutantStack &copy);
};

#endif
