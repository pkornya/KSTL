#pragma once

#ifndef OWNITERATOR_CPP
#define OWNITERATOR_CPP

#include "Iterator.h"
#include "ListException.h"

template <typename T>
Iterator<T>::Iterator() :
	pCurrent(nullptr) 
{

}

template <typename T>
Iterator<T>::Iterator(Node<T>* pElement) :
	pCurrent(pElement)
{

}

template <typename T>
Iterator<T> Iterator<T>::operator++(int)
{
	if (pCurrent == nullptr)
		throw ListException("It`s impossible to increment an iterator");
	Iterator temp(*this);
	++(*this);
	return temp;
}

template <typename T>
Iterator<T> & Iterator<T>::operator++()
{
	if (pCurrent == nullptr)
		throw ListException("It`s impossible to increment an iterator");
	pCurrent = pCurrent->pNext;
	return *this;
}

template <typename T>
bool Iterator<T>::operator== (const Iterator& other) const
{
	return pCurrent == other.pCurrent;
}

template <typename T>
bool Iterator<T>::operator!= (const Iterator& other) const
{
	return pCurrent != other.pCurrent;
}

template <typename T>
T & Iterator<T>::operator* () const
{
	if (pCurrent == nullptr)
		throw ListException("It`s impossible to dereference an iterator");
	return pCurrent->data;
}

template<typename T>
T* Iterator<T>::operator->() const
{
	if (pCurrent == nullptr)
		throw ListException("It`s impossible to dereference an iterator");
	return &pCurrent->data;
}

#endif // !OWNITERATOR_CPP