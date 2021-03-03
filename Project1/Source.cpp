#include <iostream>
#include "task.h"

int main(void)
{
	using namespace std;
	tm date;
	date.tm_year = 2020;
	date.tm_mday = 11;
	date.tm_mon = 03;
	Task task{"Do some shit", date};
	task.change_done();
	task.change_routine();
	task.add_subtask("Govno");
	task.add_subtask("Zalupa");
	task.add_subtask("Gomosek");
	cout << "Not a list:" << endl;
	cout << task;
	Task task2("Zalupa 2");
	cout << task2;
	cout << task;
}