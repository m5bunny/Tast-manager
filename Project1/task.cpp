#include "task.h"

Task::Task()
{
	title = "no_title";
	date.tm_year = 0;
	date.tm_mon = 0;
	date.tm_yday = 0;
	isroutine = 0;
	isdone = 0;
}

Task::Task(const std::string & t)
{
	title = t;
	date.tm_year = 0;
	date.tm_mon = 0;
	date.tm_yday = 0;
	isroutine = 0;
	isdone = 0;
}

Task::Task(const std::string & t, const std::tm & d, bool isr, bool isd)
{
	title = t;
	date = d;
	isroutine = isr;
	isdone = isd;
}

void Task::add_subtask(const List<std::string> & tasks)
{
	for (int i{}; i < tasks.get_num_elements(); ++i)
		subtasks.add(tasks[i]);
}

bool Task::remove_subtask(const std::string & t)
{
	int index { subtasks.find(t) };
	if (index != -1)
	{
		subtasks.remove(index);
		return true;
	}
	std::cout << "There is no such a subtask!\n";
	return false;
}

std::ostream & operator<<(std::ostream & os, Task & task)
{
	os << "--" << task.title;
	if (task.date.tm_year != 0)
	{
		os << " " << task.date.tm_mday << "." << task.date.tm_mon << "." << task.date.tm_year;
	}
	if (task.isdone == true)
		os << " *";
	if (task.isroutine == true)
		os << " r";
	os << std::endl;
	for (int i{}; i < task.subtasks.get_num_elements(); ++i)
		os << "  +--" << task.subtasks[i] << std::endl;
	return os;
}