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
    std::vector<int> vec(10, 2);

    std::cout << vec.capacity() << std::endl;
    std::cout << vec.size() << std::endl;

    vec.resize(15, 10);

    std::cout << &vec[10] << std::endl;
    std::cout << vec.size() << std::endl;


	std::cin.get();
	return 0;
}