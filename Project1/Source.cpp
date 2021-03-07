#include <iostream>
#include <fstream>
#include "todolist.h"

void initialization(List<ToDoList> & base_list, TaskCategory & important, TaskCategory & planned);

int main(void)
{
	TaskCategory important{ "Important" };
	TaskCategory planned{ "Planned" };
	List<ToDoList> base_list;
	initialization(base_list, important, planned);
	std::cout << base_list.get_num_elements();
	return 0;
}

void initialization(List<ToDoList> & base_list, TaskCategory & important, TaskCategory & planned)
{
	std::ifstream init_file;
	init_file.open("data.txt");
	if (init_file)
	{
		while (!init_file.eof())
		{
			if (init_file.get() == 'L')
			{
				std::string t;
				bool isd;
				std::getline(init_file, t);
				if (init_file.get() == 't')
					isd = true;
				else
					isd = false;
				base_list.add(ToDoList{ t, isd });
				if (init_file.get() == ';')
				{

					continue;
				}
				else
				{
					do
					{
						init_file.get();
						std::getline(init_file, t);
						base_list[base_list.get_num_elements() - 1].add(Task{ t });
						if (init_file.get() == 't')
							base_list[base_list.get_num_elements() - 1][base_list[base_list.get_num_elements() - 1].get_num_elements() - 1].change_routine();
						if (init_file.get() == 't')
							base_list[base_list.get_num_elements() - 1][base_list[base_list.get_num_elements() - 1].get_num_elements() - 1].change_done();
						if (init_file.get() == 't')
						{
							base_list[base_list.get_num_elements() - 1][base_list[base_list.get_num_elements() - 1].get_num_elements() - 1].change_imporant();
							important.add(&(base_list[base_list.get_num_elements() - 1][base_list[base_list.get_num_elements() - 1].get_num_elements() - 1]));
						}
						if (init_file.get() == 't')
						{
							tm date;
							int year, month, day;
							init_file >> year;
							init_file.get();
							init_file >> month;
							init_file.get();
							init_file >> day;
							date.tm_year = year;
							date.tm_mon = month;
							date.tm_mday = day;
							base_list[base_list.get_num_elements() - 1][base_list[base_list.get_num_elements() - 1].get_num_elements() - 1].set_date(date);
							planned.add(&(base_list[base_list.get_num_elements() - 1][base_list[base_list.get_num_elements() - 1].get_num_elements() - 1]));
						}
						if (init_file.get() == ':')
						{
							do
							{
								init_file.get();
								std::getline(init_file, t);
								base_list[base_list.get_num_elements() - 1][base_list[base_list.get_num_elements() - 1].get_num_elements() - 1].add_subtask(t);
							} while (init_file.get() == ',');
						}
					} while (init_file.get() == ',');
				}
			}
		}
	}
	init_file.close();
}