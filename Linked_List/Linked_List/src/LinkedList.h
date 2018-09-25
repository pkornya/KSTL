#pragma once

#include <iostream>

template<typename T>
class LinkedList {
public:
	LinkedList();
	~LinkedList();

	void push_back(T data);
	void push_front(T data);
	void insert(int index, T data);

	void pop_back();
	void pop_front();
	void remove_at(const int index);
	void remove_value(const int value);

	T back();
	T front();
	T value_at(const int index);

	bool empty();
	int size() const { return Size; }
	void clear();

	T & operator[](const int index);

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
	int Size;
};




template<typename T>
LinkedList<T>::LinkedList()
{
	pHead = nullptr;
	Size = 0;
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
		Size++;
		return;
	}

	Node<T>* pTemp = pHead;

	while (pTemp->pNext != nullptr)
		pTemp = pTemp->pNext;

	pTemp->pNext = new Node<T>(data);

	Size++;
}

template<typename T>
T & LinkedList<T>::operator[](const int index)
{
	if (index >= Size || index < 0) {
		std::cerr << "Out of bounds error!!!" << std::endl;
		exit(EXIT_FAILURE);
	}

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
	Size++;
}

template<typename T>
void LinkedList<T>::clear()
{
	while (Size) {
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
	Size--;
}

template<typename T>
void LinkedList<T>::pop_back()
{
	remove_at(Size - 1);
}

template<typename T>
void LinkedList<T>::insert(int index, T data)
{
	if (index > Size)
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

	Size++;
}

template<typename T>
bool LinkedList<T>::empty()
{
	return Size == 0 ? true : false;
}

template<typename T>
void LinkedList<T>::remove_at(const int index)
{
	if (pHead == nullptr)
		return;

	if (index >= Size)
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
	Size--;
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

template<typename T>
T LinkedList<T>::value_at(const int index)
{
	return this->operator[](index);
}

// TODO 
// Think about while (?)
template<typename T>
void LinkedList<T>::remove_value(const int value)
{
	if (pHead == nullptr) {
		std::cerr << "List is empty!!!" << std::endl;
		exit(EXIT_FAILURE);
	}

	Node<T>* pTemp = pHead;
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
