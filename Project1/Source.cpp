#include <iostream>
#include "list.h"

int main(void)
{
	 List<int> list;
	int y = 1;
	list.add(y);
	list.add(2);
	list.add(3);
	list.remove();
	std::cout << list[2] << std::endl;
	
}