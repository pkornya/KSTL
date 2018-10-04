#include <iostream>
#include "LinkedList.h"

int main()
{
	LinkedList<int> list;

	list.push_front(10);
	list.push_front(20);
	list.push_front(30);

	LinkedList<int>::iterator it = list.begin();
	auto it2 = list.end();

	it2 = it;

	it++;
	std::cout << *it << std::endl;

	std::cin.get();
	return 0;
}

