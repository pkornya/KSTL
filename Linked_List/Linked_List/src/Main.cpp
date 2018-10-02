#include <iostream>
#include "LinkedList.h"

int main()
{
	LinkedList<int> list;

	list.push_front(10);
	list.push_front(20);
	list.push_front(30);


	std::cin.get();
	return 0;
}

