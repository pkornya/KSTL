#pragma once

#include <iostream>

template<typename T>
class LinkedList {
public:
	LinkedList();
	~LinkedList();

	void push_back(T data);
	void push_front(T data);
	void pop_back();
	void pop_front();
	T front();
	T back();
	void insert(int index, T data);
	void clear();
	bool isEmpty();
	int getSize() const { return size; }
	T & operator[](const int index);
	void removeAt(const int index);

private:
	template<typename T>
	class Node {
	public:
		T data;
		Node* pNext;

		Node(T data = T(), Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};

private:
	Node<T>* pHead;
	int size;
};




template<typename T>
LinkedList<T>::LinkedList()
{
	pHead = nullptr;
	size = 0;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}

template<typename T>
void LinkedList<T>::push_back(T data)
{
	if (pHead == nullptr) {
		pHead = new Node<T>(data, pHead);
		size++;
		return;
	}

	Node<T>* pTemp = pHead;

	while (pTemp->pNext != nullptr)
		pTemp = pTemp->pNext;

	pTemp->pNext = new Node<T>(data);

	size++;
}

template<typename T>
T & LinkedList<T>::operator[](const int index)
{
	Node<T>* pTemp = pHead;
	int counter = 0;

	while (pTemp != nullptr) {
		if (counter == index)
			return pTemp->data;

		pTemp = pTemp->pNext;
		counter++;
	}
}

template<typename T>
void LinkedList<T>::push_front(T data)
{
	pHead = new Node<T>(data, pHead);
	size++;
}

template<typename T>
void LinkedList<T>::clear()
{
	while (size) {
		pop_front();
	}
}

template<typename T>
void LinkedList<T>::pop_front()
{
	if (pHead == nullptr)
		return;

	Node<T>* pTemp = pHead;
	pHead = pHead->pNext;

	delete pTemp;
	size--;
}

template<typename T>
void LinkedList<T>::pop_back()
{
	removeAt(size - 1);
}

template<typename T>
void LinkedList<T>::insert(int index, T data)
{
	if (index > size)
		return;

	if (index == 0) {
		push_front(data);
		return;
	}

	Node<T>* pPrevious = pHead;

	for (int i = 0; i < index - 1; i++)
		pPrevious = pPrevious->pNext;

	Node<T>* pNode = new Node<T>(data, pPrevious->pNext);
	pPrevious->pNext = pNode;

	size++;
}

template<typename T>
bool LinkedList<T>::isEmpty()
{
	return size == 0 ? true : false;
}

template<typename T>
void LinkedList<T>::removeAt(const int index)
{
	if (pHead == nullptr)
		return;

	if (index >= size)
		return;

	if (index == 0) {
		pop_front();
		return;
	}

	Node<T>* pPrevious = pHead;

	for (int i = 0; i < index - 1; i++)
		pPrevious = pPrevious->pNext;

	Node<T>* pDelete = pPrevious->pNext;
	pPrevious->pNext = pDelete->pNext;

	delete pDelete;
	size--;
}

template<typename T>
T LinkedList<T>::front()
{
	if (pHead == nullptr) {
		std::cerr << "List is empty" << std::endl;
		exit(EXIT_FAILURE);
	}

	return pHead->data;
}

template<typename T>
T LinkedList<T>::back()
{
	if (pHead == nullptr) {
		std::cerr << "List is empty" << std::endl;
		exit(EXIT_FAILURE);
	}

	Node<T>* pTemp = pHead;

	while (pTemp->pNext != nullptr)
		pTemp = pTemp->pNext;

	return pTemp->data;
}
