#pragma once

#ifndef LISTEXCEPTION_CPP
#define LISTEXCEPTION_CPP

#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList()
{
	pHead = nullptr;
	Size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}

template <typename T>
void LinkedList<T>::push_back(T data)
{
	if (pHead == nullptr) {
		pHead = new Node(data, pHead);
		Size++;
		return;
	}

	Node* pTemp = pHead;

	while (pTemp->pNext != nullptr)
		pTemp = pTemp->pNext;

	pTemp->pNext = new Node(data);

	Size++;
}

template <typename T>
T & LinkedList<T>::operator[](const int index)
{
	if (pHead == nullptr)
		throw ListException("List is empty. It`s impossible get an element.");


	if (index >= Size || index < 0) {
		throw ListException("Out of range error!!!");
	}

	Node* pTemp = pHead;
	int counter = 0;

	while (pTemp != nullptr) {
		if (counter == index)
			return pTemp->data;

		pTemp = pTemp->pNext;
		counter++;
	}
}

template <typename T>
void LinkedList<T>::push_front(T data)
{
	pHead = new Node(data, pHead);
	Size++;
}

template <typename T>
void LinkedList<T>::clear()
{
	while (Size) {
		pop_front();
	}
}

template <typename T>
void LinkedList<T>::pop_front()
{
	if (pHead == nullptr)
		throw ListException("List is empty. It`s impossible to pop a front element.");

	Node* pTemp = pHead;
	pHead = pHead->pNext;

	delete pTemp;
	Size--;
}

template <typename T>
void LinkedList<T>::pop_back()
{
	remove_at(Size - 1);
}

template <typename T>
void LinkedList<T>::insert(const int index, T data)
{
	if (index > Size || index < 0)
		throw ListException("Out of range error!!!");

	if (index == 0) {
		push_front(data);
		return;
	}

	Node* pPrevious = pHead;

	for (int i = 0; i < index - 1; i++)
		pPrevious = pPrevious->pNext;

	Node* pNode = new Node(data, pPrevious->pNext);
	pPrevious->pNext = pNode;

	Size++;
}

template <typename T>
bool LinkedList<T>::empty()
{
	return Size == 0 ? true : false;
}

template <typename T>
void LinkedList<T>::remove_at(const int index)
{
	if (pHead == nullptr)
		throw ListException("List is empty. It`s impossible to remove an element.");

	if (index >= Size || index < 0)
			throw ListException("Out of range error!!!");

	if (index == 0) {
		pop_front();
		return;
	}

	Node* pPrevious = pHead;

	for (int i = 0; i < index - 1; i++)
		pPrevious = pPrevious->pNext;

	Node* pDelete = pPrevious->pNext;
	pPrevious->pNext = pDelete->pNext;

	delete pDelete;
	Size--;
}

template <typename T>
T LinkedList<T>::front()
{
	if (pHead == nullptr) {
		throw ListException("List is empty. It`s impossible to get the front element.");
	}

	return pHead->data;
}

template <typename T>
T LinkedList<T>::back()
{
	if (pHead == nullptr) {
		throw ListException("List is empty. It`s impossible to get the last element.");
	}

	Node* pTemp = pHead;

	while (pTemp->pNext != nullptr)
		pTemp = pTemp->pNext;

	return pTemp->data;
}

template <typename T>
T LinkedList<T>::value_at(const int index)
{
	return this->operator[](index);
}

template <typename T>
void LinkedList<T>::remove_value(const int value)
{
	Node* pTemp = pHead;
	int index = 0;

	while (pTemp != nullptr) {
		if (pTemp->data == value) {
			pTemp = pTemp->pNext;
			remove_at(index);
		}
		else
			pTemp = pTemp->pNext;
		index++;
	}
}

template<typename T>
LinkedList<T>::Node::Node(T data, Node * pNext)
{
	this->data = data;
	this->pNext = pNext;
}

#endif // !LISTEXCEPTION_CPP