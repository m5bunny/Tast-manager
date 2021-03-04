#ifndef TASK_CATEGORY_H_
#define TASK_CATEGORY_H_
#include "task.h"

class TaskCategory : List<Task*>
{
	std::string title;
public:
	TaskCategory(const std::string& t = "no_title", bool isd = false) : List() { title = t; }
	TaskCategory(Task* task) : List(task) { title = "no_title"; }
	TaskCategory(const std::string& t, bool isd, Task* task) : List(task) { title = t; }
	TaskCategory(const TaskCategory& list) : List(list) { title = list.title; }

	Task* operator[](const int index) { return List::operator[](index); }
	const Task* operator[](const int index) const { return List::operator[](index); }
	TaskCategory& operator=(const TaskCategory& list) { List::operator=(list); title = list.title; return *this; }

	void add(Task* item) { List::add(item); };
	void remove(int index = 0) { List::remove(index); };
	void remove(Task* t) { remove(find(t)); }
	int find(Task* item) { return List::find(item); };
	int get_num_elements() const { return List::get_num_elements(); }
	void set_title(std::string& t) { title = t; };
};

#endif