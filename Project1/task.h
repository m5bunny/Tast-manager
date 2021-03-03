#ifndef TASK_H_
#define TAKS_H_
#include <string>
#include <ctime>
#include "list.h"

class Task
{
	std::string title;
	std::tm date;
	bool isroutine;
	bool isdone;
	List<std::string> subtasks;

public:
	Task();
	Task(const std::string & t);
	Task(const std::string & t, const std::tm & d, bool isr = false, bool isd = false);
	~Task() {};

	bool is_done() const { return isdone; } 
	bool is_routine() const { return isroutine; }
	void change_done() { isdone = (isdone == true) ? false : true; }
	void change_routine() { isroutine = (isroutine == true) ? false : true; }
	void set_date(std::tm & d) { date = d; }
	void set_title(std::string & t) { title = t; };
	const std::string & get_title() { return title; }
	const std::tm & get_date() { return date; }
	void add_subtask(const std::string & task) { subtasks.add(task); };
	void add_subtask(const List<std::string> & tasks);
	bool remove_subtask(int index) { subtasks.remove(index); };
	bool remove_subtask(const std::string & t);

	friend std::ostream & operator<<(std::ostream & os, Task & task);
	
};

#endif // !TASK_H_
