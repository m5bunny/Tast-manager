#include "task.h"

Task::Task()
{
	title = "no_title";
	date.tm_year = 0;
	date.tm_mon = 0;
	date.tm_yday = 0;
	isroutine = false;
	isdone = false;
	isimportant = false;
}

Task::Task(const std::string & t, bool isr, bool isd, bool isi)
{
	title = t;
	date.tm_year = 0;
	date.tm_mon = 0;
	date.tm_yday = 0;
	isroutine = isr;
	isdone = isd;
	isimportant = isi;
}

Task::Task(const std::string & t, const std::tm & d, bool isr, bool isd, bool isi)
{
	title = t;
	date = d;
	isroutine = isr;
	isdone = isd;
	isdone = isi;
}

void Task::add_subtask(const List<std::string> & tasks)
{
	for (int i{}; i < tasks.get_num_elements(); ++i)
		subtasks.add(tasks[i]);
}

bool Task::remove_subtask(const std::string & t)
{
	int index{ subtasks.find(t) };
	if (index != -1)
	{
		subtasks.remove(index);
		return true;
	}
	std::cout << "There is no such a subtask!\n";
	return false;
} 

bool Task::operator==(const std::string & s) const
{
	return (title == s);
}

bool Task::operator==(const Task & task) const
{
	return (title == task.title);
}

std::ostream & operator<<(std::ostream & os, const Task & task)
{
	os << "--" << task.title;
	if (task.date.tm_year != 0)
	{
		os << " " << task.date.tm_mday << "." << task.date.tm_mon << "." << task.date.tm_year;
	}
	if (task.isdone == true)
		os << " c";
	if (task.isroutine == true)
		os << " r";
	if (task.isimportant == true)
		os << " *";
	os << std::endl;
	for (int i{}; i < task.subtasks.get_num_elements(); ++i)
		os << "  +--" << task.subtasks[i] << std::endl;
	return os;
}

Task & Task::operator=(const Task & task)
{
	title = task.title;
	date = task.date;
	isroutine = task.isroutine;
	isdone = task.isdone;
	isimportant = task.isimportant;
	if (task.subtasks.get_num_elements() != 0)
		subtasks = task.subtasks;
	return *this;
}