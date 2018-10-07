#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <initializer_list>

template <typename T>
class Node;

template <typename T>
class Iterator;

template <typename T>
class LinkedList 
{
public:
	typedef Iterator<T> iterator;

	LinkedList();
	LinkedList(std::initializer_list<T> init_list);
	LinkedList(const LinkedList& another);
	~LinkedList();

	LinkedList& operator=(const LinkedList& another);
	T&			operator[](const int index);

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
	int  size() const { return Size; }
	void clear();

	iterator begin() { return iterator(pHead); }
	iterator end() { return iterator(nullptr); }
	
private:
	Node<T>*	pHead;
	int			Size;
};

#include "LinkedList.cpp"

#endif // !LINKEDLIST_H
