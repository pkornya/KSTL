#include <iostream>
#include "LinkedList.h"

class MyClass {
public:
	int a_ = 10;
	double b_ = 132;
public:
	MyClass() { a_ = 0; b_ = 0.0; }
	MyClass(int a, double b) : a_(a), b_(b) {}


};

int main()
{
	MyClass m(10, 23.10), m2(123, 34.0);
	LinkedList<MyClass> list;
	
	list.push_front(m);
	list.push_back(m2);
	
	auto it = list.begin();
	std::cout << it->a_ << " " << it->b_ << std::endl;

	it++;

	std::cout << it->a_ << " " << it->b_ << std::endl;

	std::cin.get();
	return 0;
}

