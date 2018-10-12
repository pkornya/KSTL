#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <initializer_list>
#include <exception>
//#include <iterator>




///////////// Node /////////////
// 

namespace pkl
{




	template <typename T>
	struct Node
	{
		T		 data;
		Node<T>* pNext;

		Node(T data = T(), Node<T>* pNext = nullptr);
	};




	///////////// ListException /////////////
	// 

	class ListException : public std::exception
	{
	public:
		ListException(const char* what_arg) : std::exception(what_arg) {}
		ListException(const char* what_arg, const int value) : std::exception(what_arg, value) {}
		~ListException() {}
	};




	///////////// Iterator /////////////
	// 

	template <typename T, typename Pointer, typename Reference>
	struct Iterator //: public std::iterator<std::forward_iterator_tag, T>
	{
		typedef Iterator<T, Pointer, Reference>		this_type;
		typedef Iterator<T, T*, T&>					iterator;
		typedef Iterator<T, const T*, const T&>		const_iterator;
		typedef T									value_type;
		typedef Node<T>								node_type;
		typedef Pointer                             pointer;
		typedef Reference                           reference;

	public:

		Iterator();
		Iterator(const this_type& another) = default;
		Iterator(node_type* pElement);

		this_type&	operator++();
		this_type	operator++(int);

		bool		operator==(const this_type& another) const;
		bool		operator!=(const this_type& another) const;

		reference	operator*() const;
		pointer		operator->() const;

	public:
		node_type* pCurrent;
	};




	///////////// LinkedList /////////////
	// 

	template <typename T>
	class LinkedList
	{
		typedef LinkedList<T>	this_type;

	public:
		typedef T									value_type;
		typedef T*									pointer;
		typedef const T*							const_pointer;
		typedef T&									reference;
		typedef const T&							const_reference;
		typedef Node<T>								node_type;
		typedef Iterator<T, T*, T&>					iterator;
		typedef Iterator<T, const T*, const T&>		const_iterator;

	public:
		LinkedList();
		LinkedList(std::initializer_list<value_type> init_list);
		explicit LinkedList(size_t quantity, value_type value);

		LinkedList(const this_type & another);
		LinkedList(this_type && another);

		this_type& operator=(const this_type& another);
		this_type& operator=(this_type&& another);
		this_type& operator=(std::initializer_list<value_type> init_list);

		~LinkedList();

		void swap(this_type& another);

		void push_back(value_type data);
		void push_front(value_type data);
		void insert(const size_t index, value_type data);

		void pop_back();
		void pop_front();
		void remove_at(const size_t index);
		void remove_value(const size_t value);

		reference		back();
		const_reference back() const;

		reference		front();
		const_reference front() const;

		reference value_at(const size_t index);
		reference operator[](const size_t index);

		bool empty() const;
		size_t  size() const;
		void clear();

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;

		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

	private:
		node_type*	pHead;
		size_t		mSize;
	};




	///////////// Node /////////////
	// 

	template<typename T>
	Node<T>::Node(T data = T(), Node<T>* pNext = nullptr)
	{
		this->data = data;
		this->pNext = pNext;
	}




	///////////// Iterator /////////////
	//

	template <typename T, typename Pointer, typename Reference>
	Iterator<T, Pointer, Reference>::Iterator() :
		pCurrent(nullptr)
	{

	}

	template <typename T, typename Pointer, typename Reference>
	Iterator<T, Pointer, Reference>::Iterator(node_type* pElement) :
		pCurrent(pElement)
	{

	}

	template <typename T, typename Pointer, typename Reference>
	typename Iterator<T, Pointer, Reference>::this_type&
		Iterator<T, Pointer, Reference>::operator++()
	{
		if (pCurrent == nullptr)
			throw ListException("It`s impossible to increment an iterator");
		pCurrent = pCurrent->pNext;
		return *this;
	}

	template <typename T, typename Pointer, typename Reference>
	typename Iterator<T, Pointer, Reference>::this_type
		Iterator<T, Pointer, Reference>::operator++(int)
	{
		if (pCurrent == nullptr)
			throw ListException("It`s impossible to increment an iterator");
		Iterator temp(*this);
		++(*this);
		return temp;
	}

	template <typename T, typename Pointer, typename Reference>
	typename Iterator<T, Pointer, Reference>::reference
		Iterator<T, Pointer, Reference>::operator* () const
	{
		if (pCurrent == nullptr)
			throw ListException("It`s impossible to dereference an iterator");
		return pCurrent->data;
	}

	template <typename T, typename Pointer, typename Reference>
	typename Iterator<T, Pointer, Reference>::pointer
		Iterator<T, Pointer, Reference>::operator->() const
	{
		if (pCurrent == nullptr)
			throw ListException("It`s impossible to dereference an iterator");
		return &pCurrent->data;
	}

	template <typename T, typename Pointer, typename Reference>
	bool Iterator<T, Pointer, Reference>::operator == (const this_type& other) const
	{
		return pCurrent == other.pCurrent;
	}

	template <typename T, typename Pointer, typename Reference>
	bool Iterator<T, Pointer, Reference>::operator != (const this_type& other) const
	{
		return !(pCurrent == other.pCurrent);
	}




	///////////// LinkedList /////////////
	//

	template <typename T>
	LinkedList<T>::LinkedList() :
		pHead(nullptr), mSize(0)
	{

	}

	template<typename T>
	LinkedList<T>::LinkedList(size_t quantity, value_type value) :
		pHead(nullptr), mSize(0)
	{
		while (quantity) {
			push_front(value);
			quantity--;
		}
	}

	template<typename T>
	LinkedList<T>::LinkedList(const this_type& another) :
		pHead(nullptr), mSize(0)
	{
		node_type* pTempAnother = another.pHead;
		node_type* pTemp;

		while (pTempAnother != nullptr) {
			if (mSize == 0) {
				push_front(pTempAnother->data);
				pTemp = pHead;
				pTempAnother = pTempAnother->pNext;
			}
			else {
				pTemp->pNext = new node_type(pTempAnother->data);
				pTempAnother = pTempAnother->pNext;
				pTemp = pTemp->pNext;
				mSize++;
			}
		}
	}

	template<typename T>
	LinkedList<T>::LinkedList(this_type&& another) :
		pHead(nullptr), mSize(0)
	{
		swap(another);
	}

	template<typename T>
	void LinkedList<T>::swap(this_type& another)
	{
		std::swap(pHead, another.pHead);
		std::swap(mSize, another.mSize);
	}

	template<typename T>
	LinkedList<T>::LinkedList(std::initializer_list<T> init_list) :
		pHead(nullptr), mSize(0)
	{
		node_type* pTemp;

		for (auto it = init_list.begin(); it != init_list.end(); ++it) {
			if (mSize == 0) {
				push_front(*it);
				pTemp = pHead;
			}
			else {
				pTemp->pNext = new node_type(*it);
				pTemp = pTemp->pNext;
				mSize++;
			}
		}
	}

	template<typename T>
	typename LinkedList<T>::this_type&
		LinkedList<T>::operator=(const this_type& another)
	{

		if (this != &another) {
			clear();
			this_type(another).swap(*this); // 1. LinkedList temp(another); 2. temp.swap(*this); 
		}
		return *this;
	}

	template<typename T>
	typename LinkedList<T>::this_type&
		LinkedList<T>::operator=(this_type&& another)
	{
		if (this != &another) {
			clear();
			swap(another);
		}
		return *this;
	}

	template<typename T>
	typename LinkedList<T>::this_type&
		LinkedList<T>::operator=(std::initializer_list<value_type> init_list)
	{
		clear();

		node_type* pTemp;

		for (auto it = init_list.begin(); it != init_list.end(); ++it) {
			if (mSize == 0) {
				push_front(*it);
				pTemp = pHead;
			}
			else {
				pTemp->pNext = new node_type(*it);
				pTemp = pTemp->pNext;
				mSize++;
			}
		}

		return *this;
	}

	template <typename T>
	LinkedList<T>::~LinkedList()
	{
		clear();
	}

	template <typename T>
	void LinkedList<T>::push_back(value_type data)
	{
		if (pHead == nullptr) {
			pHead = new node_type(data, pHead);
			mSize++;
			return;
		}

		node_type* pTemp = pHead;

		while (pTemp->pNext != nullptr)
			pTemp = pTemp->pNext;

		pTemp->pNext = new node_type(data);

		mSize++;
	}

	template <typename T>
	typename LinkedList<T>::reference
		LinkedList<T>::operator[](const size_t index)
	{
		if (pHead == nullptr)
			throw ListException("List is empty. It`s impossible to get an element.");


		if (index >= mSize || index < 0) {
			throw ListException("Out of range error!!!");
		}

		node_type* pTemp = pHead;
		int counter = 0;

		while (pTemp != nullptr) {
			if (counter == index)
				return pTemp->data;

			pTemp = pTemp->pNext;
			counter++;
		}
	}

	template <typename T>
	void LinkedList<T>::push_front(value_type data)
	{
		pHead = new node_type(data, pHead);
		mSize++;
	}

	template <typename T>
	void LinkedList<T>::clear()
	{
		while (mSize) {
			pop_front();
		}
	}

	template <typename T>
	void LinkedList<T>::pop_front()
	{
		if (pHead == nullptr)
			throw ListException("List is empty. It`s impossible to pop a front element.");

		node_type* pTemp = pHead;
		pHead = pHead->pNext;

		delete pTemp;
		mSize--;
	}

	template <typename T>
	void LinkedList<T>::pop_back()
	{
		remove_at(mSize - 1);
	}

	template <typename T>
	void LinkedList<T>::insert(const size_t index, value_type data)
	{
		if (index > mSize || index < 0)
			throw ListException("Out of range error!!!");

		if (index == 0) {
			push_front(data);
			return;
		}

		node_type* pPrevious = pHead;

		for (int i = 0; i < index - 1; i++)
			pPrevious = pPrevious->pNext;

		node_type* pNode = new node_type(data, pPrevious->pNext);
		pPrevious->pNext = pNode;

		mSize++;
	}

	template <typename T>
	bool LinkedList<T>::empty() const
	{
		return mSize == 0 ? true : false;
	}

	template<typename T>
	size_t LinkedList<T>::size() const
	{
		return mSize;
	}

	template <typename T>
	void LinkedList<T>::remove_at(const size_t index)
	{
		if (pHead == nullptr)
			throw ListException("List is empty. It`s impossible to remove an element.");

		if (index >= mSize || index < 0)
			throw ListException("Out of range error!!!");

		if (index == 0) {
			pop_front();
			return;
		}

		node_type* pPrevious = pHead;

		for (int i = 0; i < index - 1; i++)
			pPrevious = pPrevious->pNext;

		node_type* pDelete = pPrevious->pNext;
		pPrevious->pNext = pDelete->pNext;

		delete pDelete;
		mSize--;
	}

	template <typename T>
	typename LinkedList<T>::reference
		LinkedList<T>::front()
	{
		if (pHead == nullptr) {
			throw ListException("List is empty. It`s impossible to get the front element.");
		}

		return pHead->data;
	}

	template<typename T>
	typename LinkedList<T>::const_reference
		LinkedList<T>::front() const
	{
		if (pHead == nullptr) {
			throw ListException("List is empty. It`s impossible to get the front element.");
		}

		return pHead->data;
	}

	template <typename T>
	typename LinkedList<T>::reference
		LinkedList<T>::back()
	{
		if (pHead == nullptr) {
			throw ListException("List is empty. It`s impossible to get the last element.");
		}

		node_type* pTemp = pHead;

		while (pTemp->pNext != nullptr)
			pTemp = pTemp->pNext;

		return pTemp->data;
	}

	template<typename T>
	typename LinkedList<T>::const_reference
		LinkedList<T>::back() const
	{
		if (pHead == nullptr) {
			throw ListException("List is empty. It`s impossible to get the last element.");
		}

		node_type* pTemp = pHead;

		while (pTemp->pNext != nullptr)
			pTemp = pTemp->pNext;

		return pTemp->data;
	}

	template <typename T>
	typename LinkedList<T>::reference
		LinkedList<T>::value_at(const size_t index)
	{
		return this->operator[](index);
	}

	template <typename T>
	void LinkedList<T>::remove_value(const size_t value)
	{
		node_type* pTemp = pHead;
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
	typename LinkedList<T>::iterator
		LinkedList<T>::begin()
	{
		return iterator(pHead);
	}

	template<typename T>
	typename LinkedList<T>::const_iterator
		LinkedList<T>::begin() const
	{
		return const_iterator(pHead);
	}

	template<typename T>
	typename LinkedList<T>::const_iterator
		LinkedList<T>::cbegin() const
	{
		return const_iterator(pHead);
	}

	template<typename T>
	typename LinkedList<T>::iterator
		LinkedList<T>::end()
	{
		return iterator(nullptr);
	}

	template<typename T>
	typename LinkedList<T>::const_iterator
		LinkedList<T>::end() const
	{
		return const_iterator(nullptr);
	}

	template<typename T>
	typename LinkedList<T>::const_iterator
		LinkedList<T>::cend() const
	{
		return const_iterator(nullptr);
	}

	template <typename T>
	bool operator==(const LinkedList<T>& a, const LinkedList<T>& b)
	{
		typename LinkedList<T>::const_iterator ia = a.begin();
		typename LinkedList<T>::const_iterator ib = b.begin();
		typename LinkedList<T>::const_iterator enda = a.end();

		if (a.size() == b.size())
		{
			while ((ia != enda) && (*ia == *ib))
			{
				++ia;
				++ib;
			}
			return (ia == enda);
		}
		return false;
	}

	template <typename T>
	bool operator!=(const LinkedList<T>& a, const LinkedList<T>& b)
	{
		return !(a == b);
	}
}
#endif // !LINKEDLIST_H
