#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<typename T>
class LinkedList {
public:
	class Iterator;

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

	Iterator begin() { return Iterator(pHead); }
	Iterator end() { return Iterator(nullptr); }

public:
	template <typename T>
	class Node;

	class Iterator {
	private:
		Node<T>* pCurrent;

	public:
		Iterator(Node<T>* pElement) : 
			pCurrent(pElement) {}

		Iterator& operator++ (int) { 
			Iterator temp(*this);
			pCurrent = pCurrent->pNext;
			return temp;
		}

		Iterator& operator++ () {
			pCurrent = pCurrent->pNext;
			return *this;
		}

		bool operator== (const Iterator& other) { return pCurrent == other.pCurrent; }
		bool operator!= (const Iterator& other) { return pCurrent != other.pCurrent; }

		T& operator* () { return pCurrent->data; }
	};

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

#endif // !LINKEDLIST_H
