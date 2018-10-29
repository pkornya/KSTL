#include <iostream>
#include "forward_list.h"
#include "vector.h"
#include "list.h"

#include <list>

using namespace pkl;

int main(int argc, char *argv[])
{
    
    std::list<int> li = { 10, 20, 30, 40, 50, 60, 79 };
   
    auto it1 = --li.end();
    it1--;

	std::cin.get();
	return 0;
}