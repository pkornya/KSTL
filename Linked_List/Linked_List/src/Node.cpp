#pragma once

#ifndef NODE_CPP
#define NODE_CPP

#include "Node.h"

template<typename T>
Node<T>::Node(T data = T(), Node<T>* pNext = nullptr)
{
	this->data = data;
	this->pNext = pNext;
}

#endif // !NODE_H