#ifndef EXCEPTION_H_
#define EXECPTION_H_
#include <iostream>

class Exeption
{
	std::string mMsg;
public:
	Exeption(const std::string& m) : mMsg(m) {}
	void what() 
	{ 
		while (std::cin.get() != '\n'); 
		std::cout << mMsg << std::endl; 
	}
};

#endif // !EXCEPTION_H_

