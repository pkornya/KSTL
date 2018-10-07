#pragma once

#ifndef NODE_H
#define NODE_H

template <typename T>
class LinkedList;

template <typename T>
class Iterator;

template <typename T>
class Node
{
	friend class LinkedList<T>;
	friend class Iterator<T>;

public:
	Node(T data = T(), Node<T>* pNext = nullptr);
	
private:
	T		 data;
	Node<T>* pNext;
};

#include "Node.cpp"

#endif // !NODE_H