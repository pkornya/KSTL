#pragma once

#ifndef  OWNITERATOR_H
#define  OWNITERATOR_H

#include <iterator>

template <typename T>
class Node;

template <typename T>
class LinkedList;

template <typename T>
class Iterator : public std::iterator<std::forward_iterator_tag, T> 
{
	friend class LinkedList<T>;

public:
	Iterator();
	Iterator(const Iterator& another) = default;
	Iterator(Node<T>* pElement);
	
	Iterator&	operator=(const Iterator& another) = default;

	Iterator	operator++ (int);
	Iterator&	operator++ ();

	bool		operator== (const Iterator& another) const;
	bool		operator!= (const Iterator& another) const;

	T&			operator* () const;
	T*			operator-> () const;

private:
	Node<T>* pCurrent;
};

#include "Iterator.cpp"

#endif // ! OWNITERATOR_H
