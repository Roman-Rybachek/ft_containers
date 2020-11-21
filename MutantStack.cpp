/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeldora <jeldora@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:48:28 by jeldora           #+#    #+#             */
/*   Updated: 2020/11/09 23:54:30 by jeldora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <exception>

template <typename T>
MutantStack<T>::iterator::iterator(MutantStack<T> &current, unsigned int index) : m_current(current)
{
	if (index > m_current.size())
		throw std::exception();
	m_index = index;
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin()
{
	return (iterator(*this, 0));
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end()
{
	return (iterator(*this, this->size()));
}

template <typename T>
typename MutantStack<T>::iterator &MutantStack<T>::iterator::operator++()
{
	if (m_index < m_current.size())
		m_index++;
	else
		throw std::exception();
	return (*this);
}

template <typename T>
typename MutantStack<T>::iterator &MutantStack<T>::iterator::operator--()
{
	if (m_index > 0)
		m_index--;
	else
		throw std::exception();
	return (*this);
}

template <typename T>
bool MutantStack<T>::iterator::operator== (const MutantStack<T>::iterator &any)
{
	return (m_index == any.m_index);
}

template <typename T>
bool MutantStack<T>::iterator::operator!= (const MutantStack<T>::iterator &any)
{
	return (m_index != any.m_index);
}

template <typename T>
T &MutantStack<T>::iterator::operator*()
{return (m_current.c[m_index]);}

template <typename T>
MutantStack<T>::iterator::iterator(iterator const &copy) : m_current(copy.m_current)
{
	m_index = copy.m_index;
}

template <typename T>
MutantStack<T>::MutantStack()
{
}

template <typename T>
MutantStack<T>::~MutantStack()
{
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T> &copy)
{
	copy.size();
}

template <typename T>
MutantStack<T>	&MutantStack<T>::operator=(const MutantStack<T> &copy)
{
	*this = copy;
	return (*this);
}

template <typename T>
MutantStack<T>::iterator::iterator()
{
}

template <typename T>
MutantStack<T>::iterator::~iterator()
{
}