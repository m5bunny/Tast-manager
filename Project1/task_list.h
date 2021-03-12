#ifndef TASK_LIST_H_
#define TASK_LIST_H_
#include "task.h"
#include <algorithm>

class TaskList : List<Task>
{
	std::string title;
	bool isdefalut;
public:
	TaskList(const std::string t = "no_title", bool isd = false) : List() { title = t; isdefalut = isd; }
	TaskList(const Task & task) : List(task) { title = "no_title"; isdefalut = false; }
	TaskList(const std::string t, bool isd, const Task & task) : List(task) { title = t; isdefalut = isd; }
	TaskList(const TaskList & list) : List(list) { title = list.title; isdefalut = list.isdefalut; }
	
	const Task & operator[](const int index) const { return List::operator[](index); }
	Task & operator[](const int index) { return List::operator[](index); }
	TaskList & operator=(const TaskList & list) { List::operator=(list); title = list.title; isdefalut = list.isdefalut; return *this; }
	bool operator==(const std::string & s) const { return (title == s); }
	bool operator==(const TaskList & list) const { return (title == list.title); }

	void remove(Task & t) { remove(find(t)); }
	void remove(const std::string & t) { remove(find(t)); }
	void remove(int index = 0) { List::remove(index); }
	void add(const Task & item) { List::add(item); }
	int find(const Task & item) const { return List::find(item); }
	int get_num_elements() const { return List::get_num_elements(); }
	const std::string & get_title() const { return title; };
	void set_title(const std::string & t) { title = t; }
	bool is_defalut() const { return isdefalut; }

	friend bool operator==(const std::string & s, const TaskList & list) { return (list == s); }
	friend std::ostream & operator<<(std::ostream & os, TaskList & list) {  os << list.get_title() << " (" << list.get_num_elements() << ")"; return os; }
};

class TaskCategory : List<Task *>
{
	std::string title;
public:
	TaskCategory(const std::string & t = "no_title", bool isd = false) : List() { title = t; }
	TaskCategory(Task * task) : List(task) { title = "no_title"; }
	TaskCategory(const std::string & t, bool isd, Task* task) : List(task) { title = t; }
	TaskCategory(const TaskCategory & list) : List(list) { title = list.title; }

	Task & operator[](const int index) { return *(List::operator[](index)); }
	const Task & operator[](const int index) const { return *(List::operator[](index)); }
	TaskCategory & operator=(const TaskCategory& list) { List::operator=(list); title = list.title; return *this; }
	bool operator==(const std::string& s) const { std::string temp = title; std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);; return (temp == s); }
	bool operator==(const TaskCategory& list) const { return (title == list.title); }


	void add(Task * item) { List::add(item); }
	void remove(int index = 0) { List::remove(index); }
	void remove(Task * t) { remove(find(t)); }
	int find(Task * item) const { return List::find(item); }
	int get_num_elements() const { return List::get_num_elements(); }
	void set_title(const std::string & t) { title = t; }
	const std::string & get_title() const { return title; };
	
	friend bool operator==(const std::string & s, const TaskCategory & list) { return (list == s); }
	friend std::ostream & operator<<(std::ostream & os, TaskCategory & list) {  os << list.get_title() << " (" << list.get_num_elements() << ")"; return os; }
};
#endif
