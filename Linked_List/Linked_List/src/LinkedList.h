#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iterator>
#include "ListException.h"

template <typename T>
class LinkedList 
{
public:
	template <typename T>
	class OwnIterator;

	typedef OwnIterator<T> iterator;
	typedef OwnIterator<const T> const_iterator;

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

	const_iterator cbegin() const { return const_iterator(pHead); }
	const_iterator cend() const { return const_iterator(nullptr); }

public:
	class Node;

	template <typename T>
	class OwnIterator : public std::iterator<std::forward_iterator_tag, T> 
	{
	public:
		OwnIterator(Node* pElement) :
			pCurrent(pElement) {}

		OwnIterator& operator++ (int) 
		{ 
			if (pCurrent == nullptr)
				throw ListException("It`s impossible to increment an iterator");
			OwnIterator temp(*this);
			pCurrent = pCurrent->pNext;
			return temp;
		}

		OwnIterator& operator++ () 
		{
			if (pCurrent == nullptr)
				throw ListException("It`s impossible to increment an iterator");
			pCurrent = pCurrent->pNext;
			return *this;
		}

		bool operator== (const OwnIterator& other) 
		{ 
			return pCurrent == other.pCurrent; 
		}

		bool operator!= (const OwnIterator& other) 
		{ 
			return pCurrent != other.pCurrent; 
		}

		T & operator* () 
		{ 
			if (pCurrent == nullptr)
				throw ListException("It`s impossible to dereference an iterator");
			return pCurrent->data; 
		}

	public:
		Node* pCurrent;
	};

private:
	class Node 
	{
	public:
		Node(T data = T(), Node* pNext = nullptr);

	public:
		T data;
		Node* pNext;
	};
	
private:
	Node* pHead;
	int Size;
};


#include "LinkedList.cpp"

#endif // !LINKEDLIST_H
