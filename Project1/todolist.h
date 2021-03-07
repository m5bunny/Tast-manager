#ifndef TODOLIST_H_
#define TODOLIST_H_
#include "task.h"

class ToDoList : List<Task>
{
	std::string title;
	bool isdefalut;
public:
	ToDoList(const std::string t = "no_title", bool isd = false) : List() { title = t; isdefalut = isd; }
	ToDoList(const Task & task) : List(task) { title = "no_title"; isdefalut = false; }
	ToDoList(const std::string t, bool isd, const Task & task) : List(task) { title = t; isdefalut = isd; }
	ToDoList(const ToDoList & list) : List(list) { title = list.title; isdefalut = list.isdefalut; }
	
	const Task & operator[](const int index) const { return List::operator[](index); }
	Task& operator[](const int index) { return List::operator[](index); }
	ToDoList & operator=(const ToDoList & list) { List::operator=(list); title = list.title; isdefalut = list.isdefalut; return *this; }
	bool operator==(const std::string & s) const { return (title == s); }
	bool operator==(const ToDoList & list) const { return (title == list.title); };

	void remove(Task & t) { remove(find(t)); }
	void add(const Task & item) { List::add(item); };
	void remove(int index = 0) { List::remove(index); };
	int find(const Task & item) { return List::find(item); };
	int get_num_elements() const { return List::get_num_elements(); }
	void set_title(std::string & t) { title = t; };

	friend bool operator==(const std::string & s, const ToDoList & list) { return (list == s); }
};

class TaskCategory : List<Task *>
{
	std::string title;
public:
	TaskCategory(const std::string & t = "no_title", bool isd = false) : List() { title = t; }
	TaskCategory(Task * task) : List(task) { title = "no_title"; }
	TaskCategory(const std::string & t, bool isd, Task* task) : List(task) { title = t; }
	TaskCategory(const TaskCategory & list) : List(list) { title = list.title; }

	Task * operator[](const int index) { return List::operator[](index); }
	const Task * operator[](const int index) const { return List::operator[](index); }
	TaskCategory & operator=(const TaskCategory& list) { List::operator=(list); title = list.title; return *this; }

	void add(Task * item) { List::add(item); };
	void remove(int index = 0) { List::remove(index); };
	void remove(Task * t) { remove(find(t)); }
	int find(Task * item) { return List::find(item); };
	int get_num_elements() const { return List::get_num_elements(); }
	void set_title(std::string & t) { title = t; };
};
#endif