#include <iostream>
#include <fstream>
#include "task_manager.h"

int main(void)
{
	TaskManager tm{ "data.txt" };
	tm.get_command();
	return 0;
}