#pragma once

#ifndef  OWNITERATOR_H
#define  OWNITERATOR_H

#include <iterator>

template <typename T>
class Node;

template <typename T>
class LinkedList;

template <typename T>
class OwnIterator : public std::iterator<std::forward_iterator_tag, T> 
{
	friend class LinkedList<T>;

public:
	OwnIterator(Node<T>* pElement);
	OwnIterator(const OwnIterator& another);
	OwnIterator& operator=(const OwnIterator& another);

	OwnIterator operator++ (int);
	OwnIterator& operator++ ();

	bool operator== (const OwnIterator& another);
	bool operator!= (const OwnIterator& another);

	T & operator* ();

private:
	Node<T>* pCurrent;
};

#include "OwnIterator.cpp"

#endif // ! OWNITERATOR_H
