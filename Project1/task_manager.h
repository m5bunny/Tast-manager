#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_
#include <typeinfo>
#include <fstream>
#include <algorithm>
#include "task_list.h"

class TaskManager 
{
	std::string data_file_title;
	List<TaskList> base_list;
	List<TaskCategory> category_list;
	int contex;
	std::tm * today_date;
	void initialization();
	void save();
	bool reed_title(std::string & title, bool islist);
	void add_task_to_date_categories(Task & task);
	void remove_task_from_date_categories(Task& task);
	bool reed_command(std::string & command);
public:
	TaskManager(const std::string & t);
	~TaskManager();

	void show_home();
	template<typename Item>
	void show(int index, Item & list);
	void get_command();

	void add_list(const std::string & t);
	void add_task(const std::string & t, int i);
	//void remove_list(const std::string & t);
	void remove_list(const int index);
	void remove_task(const int list_index, const int task_index);
	void move_task(const std::string& t, int f_index, int t_index);
	void help();

	//void rename_list(const std::string & t, const std::string & nt);
	void rename_list(const int index, const std::string & nt);
	//void add_task(const int index, const Task & task);
	//void remove_task(const int list_index, const int task_index);
	//void rename_task(const int list_index, const int task_index, const Task & task);
};

#endif // !TASK_MANAGER_H_
