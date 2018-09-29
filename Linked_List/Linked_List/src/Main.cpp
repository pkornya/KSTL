#include <iostream>
#include "LinkedList.h"
#include "LinkedList.cpp"

int main()
{
	LinkedList<int> list;

	list.push_front(10);
	list.push_front(20);
	list.push_front(30);

	LinkedList<int>::Iterator it = list.begin();
	
	auto it2 = it++;


	std::cin.get();
	return 0;
}