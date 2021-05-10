#include "task_list.h"

TaskList::TaskList(const std::string t, bool isd) : List(), title(t), isdefalut(isd) {}

TaskList::TaskList(const Task & task) : List(task), title("no_title"), isdefalut(false) {}

TaskList::TaskList(const std::string t, bool isd, const Task & task) : List(task), title(t), isdefalut(isd) {}

TaskList::TaskList(const TaskList & list) : List(list), title(list.title), isdefalut(list.isdefalut) {}

TaskList & TaskList::operator=(const TaskList & list) 
{ 
	List::operator=(list); 
	title = list.title; 
	isdefalut = list.isdefalut; 
	return *this; 
}

void TaskList::save(std::stringstream & sf)
{
	sf << 'L' << title << std::endl;
	if (isdefalut)
		sf << 't';
	else
		sf << 'f';
	if (get_num_elements() == 0)
		sf << ";" << std::endl;
	else
	{
		sf << ":" << std::endl;
		iSave* ptr;
		for (int i{}; i < get_num_elements(); ++i)
		{
			ptr = &(this->operator[](i));
			ptr->save(sf);
			if (i < get_num_elements() - 1)
				sf << "," << std::endl;
		}
	}
}

std::ostream & operator<<(std::ostream & os, TaskList& list) 
{  
	os << list.get_title() << " (" << list.get_num_elements() << ")"; 
	return os; 
}

TaskCategory::TaskCategory(const std::string& t, bool isd) : List(), title(t) {}

TaskCategory::TaskCategory(Task * task) : List(task), title("no_title") {}

TaskCategory::TaskCategory(const std::string & t, bool isd, Task * task) : List(task), title(t) {}

TaskCategory::TaskCategory(const TaskCategory & list) : List(list), title(list.title) {}

TaskCategory & TaskCategory::operator=(const TaskCategory & list) 
{ 
	List::operator=(list); 
	title = list.title; 
	return *this; 
}

std::ostream & operator<<(std::ostream & os, TaskCategory & list) 
{ 
	os << list.get_title() << " (" << list.get_num_elements() << ")"; 
	return os; 
}