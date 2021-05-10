#ifndef TASK_LIST_H_
#define TASK_LIST_H_
#include "task.h"
#include <algorithm>

class TaskList : List<Task>, public iSave
{
	std::string title;
	bool isdefalut;
public:
	TaskList(const std::string t = "no_title", bool isd = false);
	TaskList(const Task & task);
	TaskList(const std::string t, bool isd, const Task & task);
	TaskList(const TaskList & list);
	
	const Task & operator[](const int index) const { return List::operator[](index); }
	Task & operator[](const int index) { return List::operator[](index); }
	TaskList & operator=(const TaskList & list);
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
	void save(std::stringstream & sf);

	friend bool operator==(const std::string & s, const TaskList & list) { return (list == s); }
	friend std::ostream & operator<<(std::ostream & os, TaskList & list);
};

class TaskCategory : List<Task *>
{
	std::string title;
public:
	TaskCategory(const std::string & t = "no_title", bool isd = false);
	TaskCategory(Task * task);
	TaskCategory(const std::string & t, bool isd, Task* task);
	TaskCategory(const TaskCategory & list);

	Task & operator[](const int index) { return *(List::operator[](index)); }
	const Task & operator[](const int index) const { return *(List::operator[](index)); }
	TaskCategory & operator=(const TaskCategory & list);
	bool operator==(const std::string& s) const { return (title == s); }
	bool operator==(const TaskCategory& list) const { return (title == list.title); }


	void add(Task * item) { List::add(item); }
	void remove(int index = 0) { List::remove(index); }
	void remove(Task * t) { remove(find(t)); }
	int find(Task * item) const { return List::find(item); }
	int get_num_elements() const { return List::get_num_elements(); }
	void set_title(const std::string & t) { title = t; }
	const std::string & get_title() const { return title; };
	
	friend bool operator==(const std::string & s, const TaskCategory & list) { return (list == s); }
	friend std::ostream & operator<<(std::ostream & os, TaskCategory & list);
};


#endif
