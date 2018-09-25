#include <iostream>
#include "LinkedList.h"

int main()
{
	LinkedList<int> list;

	list.push_front(10);
	list.push_front(20);
	list.insert(200, 2);
	list.insert(135, 2);
	list.insert(-5, 2);
	list.insert(25, 1);

	for (int i = 0; i < list.size(); i++)
		std::cout << list[i] << " ";

	std::cout << std::endl;

	list.remove_at(0);
	list.pop_back();

	for (int i = 0; i < list.size(); i++)
		std::cout << list[i] << " ";

	std::cin.get();
	return 0;
}