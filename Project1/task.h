#ifndef TASK_H_
#define TAKS_H_
#include <string>
#include <ctime>
#include <algorithm>
#include "list.h"

class Task
{
	std::string title;
	std::tm date;
	bool isroutine;
	bool isdone;
	bool isimportant;
	List<std::string> subtasks;

public:
	Task();
	Task(const std::string & t, bool isr = false, bool isd = false, bool isi = false);
	Task(const std::string & t, const std::tm & d, bool isr = false, bool isd = false, bool isi = false);
	~Task() {};

	bool operator==(const std::string & s) const;
	bool operator==(const Task & task) const;

	bool is_done() const { return isdone; } 
	bool is_routine() const { return isroutine; }
	bool is_important() const { return isimportant; }
	void change_done() { isdone = (isdone == true) ? false : true; }
	void change_routine() { isroutine = (isroutine == true) ? false : true; }
	void change_imporant() { isimportant = (isimportant == true) ? false : true; }
	void set_date(const std::tm & d) { date = d; }
	void set_title(const std::string & t) { title = t; };
	const std::string & get_title() const { return title; }
	const std::string & get_subtask(const int index) const { return subtasks[index]; }
	const std::tm & get_date() const { return date; }
	int get_num_elements() const { return subtasks.get_num_elements(); }
	void add_subtask(const std::string & task) { subtasks.add(task); };
	void add_subtask(const List<std::string> & tasks);
	bool remove_subtask(int index) { subtasks.remove(index); };
	bool remove_subtask(const std::string & t);

	friend std::ostream & operator<<(std::ostream & os, const Task & task);
	friend bool operator==(const std::string & s, const Task & task) { return task.operator==(s); }
	Task & operator=(const Task & task);
	const std::string & operator[](const int index) const { return subtasks[index]; }
};

#endif // !TASK_H_