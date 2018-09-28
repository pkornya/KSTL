#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<typename T>
class LinkedList {
public:
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
