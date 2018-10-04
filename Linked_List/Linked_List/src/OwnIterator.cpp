#pragma once

#ifndef OWNITERATOR_CPP
#define OWNITERATOR_CPP

#include "OwnOterator.h"
#include "ListException.h"

template <typename T>
OwnIterator<T>::OwnIterator(Node<T>* pElement) :
	pCurrent(pElement)
{

}

template <typename T>
OwnIterator<T>::OwnIterator(const OwnIterator & another) :
	pCurrent(another.pCurrent)
{
	
}

template <typename T>
void OwnIterator<T>::operator=(const OwnIterator & another)
{
	pCurrent = another.pCurrent;
}

template <typename T>
OwnIterator<T> OwnIterator<T>::operator++(int)
{
	if (pCurrent == nullptr)
		throw ListException("It`s impossible to increment an iterator");
	OwnIterator temp(*this);
	++(*this);
	return temp;
}

template <typename T>
OwnIterator<T> & OwnIterator<T>::operator++()
{
	if (pCurrent == nullptr)
		throw ListException("It`s impossible to increment an iterator");
	pCurrent = pCurrent->pNext;
	return *this;
}
template <typename T>
bool OwnIterator<T>::operator== (const OwnIterator& other)
{
	return pCurrent == other.pCurrent;
}

template <typename T>
bool OwnIterator<T>::operator!= (const OwnIterator& other)
{
	return pCurrent != other.pCurrent;
}
template <typename T>
T & OwnIterator<T>::operator* ()
{
	if (pCurrent == nullptr)
		throw ListException("It`s impossible to dereference an iterator");
	return pCurrent->data;
}

#endif // !OWNITERATOR_CPP