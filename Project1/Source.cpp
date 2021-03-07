#include <iostream>
#include <fstream>
#include "todolist.h"

void initialization(List<ToDoList> & base_list, TaskCategory & important, TaskCategory & planned);
void save(const List<ToDoList> & base_list);

int main(void)
{
	TaskCategory important{ "IMPORTANT" };
	TaskCategory planned{ "PLANED" };
	List<ToDoList> base_list;
	initialization(base_list, important, planned);
	std::cout << base_list.get_num_elements();
	save(base_list);
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

void save(const List<ToDoList> & base_list)
{
	std::ofstream save_file;
	save_file.open("data.txt");
	if (save_file)
	{
		for (int i{}; i < base_list.get_num_elements(); ++i)
		{
			save_file << 'L' << base_list[i].get_title() << std::endl;
			if (base_list[i].is_defalut())
				save_file << 't';
			else
				save_file << 'f';
			if (base_list[i].get_num_elements() == 0)
				save_file << ";" << std::endl;
			else
			{
				save_file << ":" << std::endl;
				for (int j{}; j < base_list[i].get_num_elements(); ++j)
				{
					save_file << base_list[i][j].get_title() << std::endl;
					if (base_list[i][j].is_done())
						save_file << 't';
					else
						save_file << 'f';
					if (base_list[i][j].is_routine())
						save_file << 't';
					else
						save_file << 'f';
					if (base_list[i][j].is_important())
						save_file << 't';
					else
						save_file << 'f';
					std::tm date = base_list[i][j].get_date();
					if (date.tm_year != 0)
						save_file << 't' << date.tm_year << " " << date.tm_mon << " " << date.tm_mday;
					else
						save_file << 'f';
					if (base_list[i][j].get_num_elements() == 0)
					{
						save_file << ';';
						if (j < base_list[i].get_num_elements() - 1)
							save_file << "," << std::endl;
					}
					else
					{
						save_file << ':' << std::endl;
						for (int k{}; k < base_list[i][j].get_num_elements(); ++k)
						{
							save_file << base_list[i][j][k] << std::endl;
							if (k < base_list[i][j].get_num_elements() - 1)
								save_file << "," << std::endl;
						}
						if (j < base_list[i].get_num_elements() - 1)
							save_file << ";," << std::endl;
					}
				}
				save_file << std::endl  << ";" << std::endl;
			}
		}
	}
	save_file.close();
}