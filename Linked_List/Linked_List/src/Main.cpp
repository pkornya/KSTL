#include <iostream>
#include "LinkedList.h"
#include "LinkedList.cpp"

int main()
{
	LinkedList<int> list;

	list.push_front(10);
	list.push_front(20);
	list.insert(2, 200);
	list.insert(2, 135);
	list.insert(2, -5);
	list.insert(1, 25);

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