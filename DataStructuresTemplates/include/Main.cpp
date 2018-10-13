#include <iostream>
#include "forward_list.h"
#include "vector.h"
#include <vector>

class MyClass {
public:
	int a_ = 10;
	double b_ = 132;

public:
	MyClass() { a_ = 0; b_ = 0.0; }
	MyClass(int a, double b) : a_(a), b_(b) {}
};

using namespace pkl;

size_t func(size_t value)
{
    value++;

    return value;
}

int main(int argc, char *argv[])
{
    std::vector<int> v;
    v.reserve(6);
    v.push_back(123);
    v.push_back(123);
    v.push_back(123);
    v.push_back(123);
    v.push_back(123);

    std::cout << v.capacity() << std::endl;

    v.reserve(7);
    std::cout << v.capacity() << std::endl;

	std::cin.get();
	return 0;
}