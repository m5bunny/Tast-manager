#ifndef TODOLIST_H_
#define TODOLIST_H_
#include "task.h"

class ToDoList : List<Task>
{
	std::string title;
	bool isdefalut;
public:
	ToDoList(std::string t = "no_title", bool isd = false) : List() { title = t; isdefalut = isd; }
	ToDoList(Task & task) : List(task) { title = "no_title"; isdefalut = false; }
	ToDoList(std::string t, bool isd, Task & task) : List(task) { title = t; isdefalut = isd; }
	ToDoList(ToDoList & list) : List(list) { title = list.title; isdefalut = list.isdefalut; }
	
	const Task & operator[](const int index) const { return List::operator[](index); }
	ToDoList & operator=(const ToDoList & list) { List::operator=(list); title = list.title; isdefalut = list.isdefalut; return *this; }

	void add(const Task & item) { List::add(item); };
	void remove(int index = 0) { List::remove(index); };
	int find(const Task& item) { return List::find(item); };
	int get_num_elements() const { return List::get_num_elements(); }
};

#endif