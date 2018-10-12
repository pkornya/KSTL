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

using namespace pkl;

int main(int argc, char *argv[])
{
	/*MyClass m(10, 23.10), m2(123, 34.0);
	LinkedList<int> list1 = { 1, 2, 3, 4, 5 };
	LinkedList<int> list2(list1);

	LinkedList<int> list3 = { 10, 20, 39 };

	list3 = std::move(list2);*/
	
	
	//unsigned int a = 0x55;
	//a = (a << 1) ^ (a << 1);


	/*int i = 3;
	int res = 0;

	while (i--)
		switch (i)
		{
		case 1:
			res += i * 3;
		case 2:
			res += i * 2;
		case 3:
			res += i * 1;
		default:
			res++;
		}
	printf("%d", res);*/

	LinkedList<int> list = { 1, 2, 3 };

	LinkedList<int> list2 = { 1, 2, 3, 4 };

	std::cout << (list == list2) << std::endl;

	std::cin.get();
	return 0;
}

/*int fun(int i)
{
	static int k = 8;
	static int l;
	int res;
	l = 8;

	res = k + l;
	l = i;
	k = i;
	return res;
}

int i = 3;

while (i--)
printf("%d\n", fun(i));
*/ ////// answer = 9;