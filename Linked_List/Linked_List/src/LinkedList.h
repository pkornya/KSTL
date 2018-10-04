#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class Node;

template <typename T>
class OwnIterator;

template <typename T>
class LinkedList 
{
public:

	typedef OwnIterator<T> iterator;
	//typedef OwnIterator<const T> const_iterator;

	LinkedList();
	~LinkedList();

	void push_back(T data);
	void push_front(T data);
	void insert(const int index, T data);

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

	iterator begin() { return iterator(pHead); }
	iterator end() { return iterator(nullptr); }

	//const_iterator cbegin() const { return const_iterator(pHead); }
	//const_iterator cend() const { return const_iterator(nullptr); }
	
private:
	Node<T>* pHead;
	int Size;
};

#include "LinkedList.cpp"

#endif // !LINKEDLIST_H
