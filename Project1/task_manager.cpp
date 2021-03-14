#include "task_manager.h"

TaskManager::TaskManager(const std::string& t)
{
	category_list.add(TaskCategory{ "IMPORTANT" });
	category_list.add(TaskCategory{ "PLANNED" });
	category_list.add(TaskCategory{ "TODAY TASKS" });
	category_list.add(TaskCategory{ "OVERDUE" });
	data_file_title = t;
	contex = -1;
	std::time_t now = std::time(0);
	today_date = std::localtime(&now);
	today_date->tm_year += 1900;
	today_date->tm_mon += 1;

	initialization();
	if (base_list.get_num_elements() == 0)
	{
		base_list.add(TaskList{ "TASKS", true });
		base_list.add(TaskList{ "COMPLETED", true });
	}
}

TaskManager::~TaskManager()
{
	save();
}

void TaskManager::initialization()
{
	std::ifstream init_file;
	init_file.open(data_file_title);
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
				base_list.add(TaskList{ t, isd });
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
						Task & task = base_list[base_list.get_num_elements() - 1][base_list[base_list.get_num_elements() - 1].get_num_elements() - 1];
						if (init_file.get() == 't')
							task.change_routine();
						if (init_file.get() == 't')
							task.change_done();
						if (init_file.get() == 't')
						{
							task.change_imporant();
							if (!task.is_done())
								category_list[0].add(&task);
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
							task.set_date(date);
							add_task_to_date_categories(task);
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

void TaskManager::save()
{
	std::ofstream save_file;
	save_file.open(data_file_title);
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
					if (base_list[i][j].is_routine())
						save_file << 't';
					else
						save_file << 'f';
					if (base_list[i][j].is_done())
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
				save_file << ";" << std::endl;
			}
		}
	}
	save_file.close();
}

void TaskManager::help()
{
	system("cls");
	using std::cout;
	using std::endl;
	cout << "List of commands:\n\n"
		 << "'back' - go to the home screen;\n\n"
		 << "'show' \"list title\" - show the list with title \"list title\";\n\n"
		 << "'add':\n"
		 << " -'list' \"list title\" - add the list with title \"list title\";\n"
		 << " -'task' \"task title\" ('to' \"list title\") - add the task with title\n"
		 << "  \"task title\";\n"
		 << " -to \"TASKS\"(\"list title\");\n"
		 << " -'subtask' \"subtask title\" 'to' \"task title\" - add the subtask with title\n"
		 << "  \"subtask title\" to the task with title \"task title\";\n\n"
		 << "'remove':\n"
		 << " -'list' \"list title\" - remove the list with title \"list title\";\n"
		 << " -'task' \"task title\" ('from' \"list title\") - remove the task with title\n"
		 << "   \"task title\";\n"
		 << "  from \"TASKS\"(\"list title\");\n"
		 << " -'subtask' \"subtask title\" 'from' \"task title\" - remove the subtask with title\n"
		 << "  \"subtask title\" from the task with title \"task title\";\n\n"
		 << "'rename' \"list title\" \"new list title\" - change the title of list from\n"
		 << "\"list title\" to \"new list title\";\n\n"
		 << "'change' \"task title\":\n"
		 << " -'important' - set/unset important status to the task with the title\n"
		 << "  \"task title\";\n"
		 << " -'complete' - set/unset complete status to the task with the title\n"
		 << "  \"task title\";\n"
		 << " -'routine' - set/unset routine status to the task with the title \"task title\";\n"
		 << " -'title' \"new task tile\" - change the task title from \"task title\" to\n"
		 << "  \"new task title\";\n"
		 << " -'date' ('off') - set(unset) date to the task with the title \"task title\";\n\n"
		 << "'move' \"taks title\" ('from' \"from list title\") 'to' \"to list title\" - move task\n"
		 << "with title \"task title\" from context list(list with title \"from list title\") to list with title \"to list title\";\n\n";
} 

void TaskManager::add_task_to_date_categories(Task & task)
{
	std::tm task_date = task.get_date();
	if (task_date.tm_year != 0)
	{
		int yyyymmdd_task_date = task_date.tm_year * 10000 + task_date.tm_mon * 100 + task_date.tm_mday;
		int yyymmdd_today_date = today_date->tm_year * 10000 + today_date->tm_mon * 100 + today_date->tm_mday;
		if (yyymmdd_today_date > yyyymmdd_task_date && !(task.is_done()))
			category_list[3].add(&task);
		else if (!(task.is_done()))
		{
			category_list[1].add(&task);
			if (yyymmdd_today_date == yyyymmdd_task_date)
				category_list[2].add(&task);
		}
	}
}

void TaskManager::remove_task_from_date_categories(Task & task)
{
	std::tm task_date = task.get_date();
	if (task_date.tm_year != 0)
	{
		int yyyymmdd_task_date = task_date.tm_year * 10000 + task_date.tm_mon * 100 + task_date.tm_mday;
		int yyymmdd_today_date = today_date->tm_year * 10000 + today_date->tm_mon * 100 + today_date->tm_mday;
		if (yyymmdd_today_date > yyyymmdd_task_date && !(task.is_done()))
			category_list[3].remove(&task);
		else if (!(task.is_done()))
		{
			category_list[1].remove(&task);
			if (yyymmdd_today_date == yyyymmdd_task_date)
				category_list[2].remove(&task);
		}
	}
}

void TaskManager::add_list(const std::string & t)
{
	try 
	{
		if (base_list.find(t) != -1)
			throw "There is already a list with this title!\n";
		base_list.add(TaskList{ t });
	}
	catch (const char * massange)
	{
		std::cout << massange;
		return;
	}
	show(contex, base_list);
}
/*
void TaskManager::remove_list(const std::string & t)
{
	try
	{
		int index;
		if ((index = base_list.find(t)) == -1)
			throw "There is no any list with this title!";
		else if (base_list[index].is_defalut())
			throw "You can not remove the default list!";
		base_list.remove(index);
	}
	catch (const char * massange)
	{
		std::cout << massange;
		communicator();
	}
}

if (index > 0 && index <= 2)
			throw "You can not remove the default list!";
*/

void TaskManager::add_task(const std::string& t, int i)
{
	using std::cout;
	using std::cin;
	if (i != 1)
	{
		base_list[i].add(Task{ t });
		Task& task = base_list[i][base_list[i].get_num_elements() - 1];
		int year, month, day;
		cout << "Is the task important(y/n):";
		while (cin.get() != '\n');
		if (cin.get() == 'y')
		{
			task.change_imporant();
			category_list[0].add(&task);
		}
		while (cin.get() != '\n');
		cout << "Enter the date in format yyyy/mm/dd (n - to do not add the date):";
		if (cin >> year)
		{
			cin.get();
			cin >> month;
			cin.get();
			cin >> day;
			while (cin.get() != '\n');
			std::tm date;
			date.tm_year = year;
			date.tm_mon = month;
			date.tm_mday = day;
			task.set_date(date);
			add_task_to_date_categories(task);
			cout << "Is the task routine(y/n):";
			if (cin.get() == 'y')
				task.change_routine();
		}
		else
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		show(contex, base_list);
	}
	else
	{
		cout << "You can not add the task to the COMPLETED list!\n";
	}
}

void TaskManager::remove_list(const int index)
{
	try
	{
		if (index < 0 || index >= base_list.get_num_elements())
			throw "You entered a wrong number!";
		else if (base_list[index].is_defalut())
			throw "You can not remove the default list!";
		base_list.remove(index);
		show(contex, base_list);
	}
	catch (const char * massange)
	{
		std::cout << massange << std::endl;
	}
}
/*
void TaskManager::rename_list(const std::string & t, const std::string & nt)
{
	try
	{
		int index;
		if ((index = base_list.find(t)) == -1)
			throw "There is no any list with this title!";
		else if (base_list[index].is_defalut())
			throw "You can not rename the default list!";
		if (t == nt)
			throw "The new and the old title are the same!";
		base_list[index].set_title(nt);
	}
	catch (const char * massange)
	{
		std::cout << massange;
		communicator();
	}
}*/

void TaskManager::remove_task(const int list_index, const int task_index)
{
	Task & task = base_list[list_index][task_index];
	if (!task.is_done())
	{
		if (task.is_important())
			category_list[0].remove(&task);
		remove_task_from_date_categories(task);
	}
	base_list[list_index].remove(task_index);
	show(contex, base_list);
}

void TaskManager::move_task(const std::string & t, int f_index, int t_index)
{
	if (f_index != 1 && t_index != 1)
	{
		int task_index = base_list[f_index].find(t);
		if (task_index != -1)
		{
			base_list[t_index].add(base_list[f_index][task_index]);
			Task & new_task = base_list[t_index][base_list[t_index].get_num_elements() - 1];
			if (new_task.is_important())
				category_list[0].add(&new_task);
			add_task_to_date_categories(new_task);
			remove_task(f_index, task_index);
		}
		else
			std::cout << "There is not task with this title in " << base_list[f_index].get_title() << "!" << std::endl;
	}
	else
	{
		std::cout << "You can not move tasks from or to the COMPLETED list!\n";
	}
}

void TaskManager::rename_list(int index, const std::string & nt)
{
	try
	{
		if (index < 0 || index >= base_list.get_num_elements())
			throw "You entered a wrong number!";
		else if (base_list[index].is_defalut())
			throw "You can not rename the default list!";
		else if (base_list[index].get_title() == nt)
			throw "The new and the old title are the same!";
		base_list[index].set_title(nt);
		show(contex, base_list);
	}
	catch (const char * massange)
	{
		std::cout << massange << std::endl;
	}
}

void TaskManager::show_home()
{
	system("cls");
	contex = -1;
	using std::cout;
	using std::endl;
	cout << "Categories:" << endl;
	for (int i{}; i < category_list.get_num_elements(); ++i)
		cout << category_list[i] << endl;
	cout << endl << "Lists: " << endl;
	for (int i{}; i < base_list.get_num_elements(); ++i)
		cout << base_list[i] << endl;
	cout << endl;
}

void TaskManager::get_command()
{
	show_home();
	using std::cout;
	using std::cin;
	using std::endl;
	std::string title;
	std::string command;
	int index;
	cout << "Enter command (\"Q\" to quite):";
	while (reed_command(command) && command != "q")
	{
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);
		if (command == "show")
		{
			if (reed_title(title, true))
			{
				if ((index = category_list.find(title)) != -1)
					show(index, category_list);
				else if ((index = base_list.find(title)) != -1)
					show(index, base_list);
				else
					cout << "There is not list with this title!\n";
			}
		}
		else if (command == "add")
		{
			reed_command(command);
			if (command == "list")
			{
				reed_title(title, true);
				add_list(title);
			}
			else if (command == "task")
			{
				std::string task_title;
				reed_title(task_title, false);
				index = (contex == -1) ? 0 : contex;
				while (char c = cin.peek() != '\n')
					if (c != ' ')
					{
						reed_command(command);
						break;
					}
				if (command == "to")
				{
					reed_title(title, true);
					index = base_list.find(title);
				}
				if (index != -1)
					add_task(task_title, index);
				else
					cout << "There is not list with this title!\n";
			}
			else if (command == "subtask")
			{
				if (contex != -1)
				{
					std::string sub_title;
					reed_title(sub_title, false);
					while (char c = cin.peek() != '\n')
						if (c != ' ')
						{
							reed_command(command);
							break;
						}
					if (command == "to")
					{
						reed_title(title, false);
						index = base_list[contex].find(title);
					}
					else
						cout << "You have to enter \"to\" and title of tasks you want to add subtaks to!\n";
					if (index != -1)
					{
						base_list[contex][index].add_subtask(sub_title);
						show(contex, base_list);
					}
					else
						cout << "There is not task with this title!\n";
				}
				else
				{
					while (cin.get() != '\n');
					cout << "You have to be in list to add the subtasks!\n";
				}
					
			}
			else
			{
				cout << "You have to enter \"list\" if you want to add the list, or \"taks\" if you want to add the task!\n";
			}
		}
		else if (command == "remove")
		{
			reed_command(command);
			if (command == "list")
			{
				reed_title(title, true);
				if ((index = base_list.find(title)) != -1)
					remove_list(index);
				else
					cout << "There is not list with this title!\n";
			}
			else if (command == "task")
			{
				std::string task_title;
				reed_title(task_title, false);
				index = (contex == -1) ? 0 : contex;
				while (char c = cin.peek() != '\n')
					if (c != ' ')
					{
						reed_command(command);
						break;
					}
				if (command == "from")
				{
					reed_title(title, true);
					index = base_list.find(title);
				}
				if (index != -1)
				{
					std::transform(task_title.begin(), task_title.end(), task_title.begin(), ::tolower);
					int task_index = base_list[index].find(task_title);
					if (task_index != -1)
						remove_task(index, task_index);
					else
						cout << "There is not task with this title in " << base_list[index].get_title() << "!" << endl;
				}
				else
					cout << "There is not list with this title!\n";
			}
			else if (command == "subtask")
			{
				if (contex != -1)
				{
					std::string sub_title;
					reed_title(sub_title, false);
					while (char c = cin.peek() != '\n')
						if (c != ' ')
						{
							reed_command(command);
							break;
						}
					if (command == "from")
					{
						reed_title(title, false);
						index = base_list[contex].find(title);
					}
					else
						cout << "You have to enter \"from\" and title of tasks you want to remove subtaks from!\n";
					if (index != -1)
					{
						if (base_list[contex][index].remove_subtask(sub_title))
							show(contex, base_list);
					}
					else
						cout << "There is not task with this title!\n";
				}
				else
				{
					while (cin.get() != '\n');
					cout << "You have to be in list to remove the subtasks!\n";
				}
			}
			else
			{
				cout << "You have to enter \"list\" if you want to remove the list, or \"taks\" if you want to remove the task!\n";
			}
		}
		else if (command == "rename")
		{
			reed_title(title, true);
			if ((index = base_list.find(title)) != -1)
			{
				if (reed_title(title, true))
					rename_list(index, title);
			}
			else
			{
				while (cin.get() != '\n');
				cout << "There is not list with this title!\n";
			}
		}
		else if (command == "change")
		{	
			if (contex != -1)
			{
				if (reed_title(title, false))
				{
					index = base_list[contex].find(title);
					if (index != -1)
					{
						Task & task = base_list[contex][index];
						reed_command(command);
						if (command == "important")
						{
							if (task.is_important() && !task.is_done())
							{
								category_list[0].remove(&task);
							}
							else
							{
								category_list[0].add(&task);
							}
							task.change_imporant();
							show(contex, base_list);
						}
						else if (command == "complete")
						{
							if (!task.is_done())
							{
								if (task.is_routine())
								{
									base_list[contex].add(task);
									Task & new_task = base_list[contex][base_list[contex].get_num_elements() - 1];
									std::tm new_task_date = new_task.get_date();
									if (new_task_date.tm_mon + 1 <= 12)
										++new_task_date.tm_mon;
									else
									{
										++new_task_date.tm_year;
										new_task_date.tm_mon = 1;
									}
									new_task.set_date(new_task_date);
									if (new_task.is_important())
										category_list[0].add(&new_task);
									add_task_to_date_categories(new_task);
								}
								if (task.is_important())
									category_list[0].remove(&task);
								remove_task_from_date_categories(task);
								task.change_done();
								base_list[1].add(task);
								base_list[contex].remove(task);
								show(contex, base_list);
							}
							else
							{
								base_list[0].add(task);
								Task & new_task = base_list[0][base_list[0].get_num_elements() - 1];
								new_task.change_done();
								if (new_task.is_important())
									category_list[0].add(&new_task);
								add_task_to_date_categories(new_task);
								base_list[1].remove(task);
								show(contex, base_list);
							}
						}
						else if (command == "routine")
						{
							if (task.get_date().tm_year != 0)
							{
								task.change_routine();
								show(contex, base_list);
							}
							else
								cout << "You can not set routine to task without date!\n";
						}
						else if (command == "title")
						{
							if (reed_title(title, false))
							{
								task.set_title(title);
								show(contex, base_list);
							}
						}
						else if (command == "date")
						{
							char c;
							int year, month, day;
							while ((c = cin.peek()) != '\n')
							{
								if (c != ' ')
								{
									reed_command(command);
									break;
								}
								else 
									cin.get();
							}
							if (command == "off")
							{
								if (task.get_date().tm_year != 0)
								{
									remove_task_from_date_categories(task);
									std::tm date;
									date.tm_year = 0;
									date.tm_mon = 0;
									date.tm_mday = 0;
									task.set_date(date);
									if (task.is_routine())
										task.change_routine();
									show(contex, base_list);
								}
								else
									cout << "This task is already without date!\n";
							}
							else
							{
								cout << "Enter the date in format yyyy/mm/dd:";
								if (cin >> year)
								{
									cin.get();
									cin >> month;
									cin.get();
									cin >> day;
									while (cin.get() != '\n');
									std::tm date;
									date.tm_year = year;
									date.tm_mon = month;
									date.tm_mday = day;
									task.set_date(date);
									add_task_to_date_categories(task);
									show(contex, base_list);
								}
								else
								{
									cout << "You have to enter date like YYYY/MM/DD!\n";
									cin.clear();
									cin.ignore(256, '\n');
								}
							}
						}
						else
						{
							while (cin.get() != '\n');
							cout << "You can change date, important, complete, title and routine!\n";
						}
					}
					else 
						cout << "There is not task with this title!\n";
				}
			}
			else
			{
				while (cin.get() != '\n');
				cout << "You have to be in list to change the task!\n";
			}

		}
		else if (command == "move")
		{
			std::string task_title;
			reed_title(task_title, false);
		 	int from_index = (contex == -1) ? 0 : contex;
			int to_index;
			while (char c = cin.peek() != '\n')
				if (c != ' ')
				{
					reed_command(command);
					break;
				}
			if (command == "from")
			{
				reed_title(title, true);
				from_index = base_list.find(title);
				reed_command(command);
				if (command == "to")
				{
					reed_title(title, true);
					to_index = base_list.find(title);
					if (from_index != to_index)
					{
						std::transform(task_title.begin(), task_title.end(), task_title.begin(), ::tolower);
						if (from_index != -1 && to_index != -1)
							move_task(task_title, from_index, to_index);
						else
							cout << "There is not list with this title!\n";
					}
					else
						cout << "The from list and the to list are the same!\n";
				}
				else
					cout << "You have to enter \"to\" and the title of the list to move the task!\n";
			}
			else if (command == "to")
			{
				reed_title(title, true);
				to_index = base_list.find(title);
				if (from_index != to_index)
				{
					std::transform(task_title.begin(), task_title.end(), task_title.begin(), ::tolower);
					if (from_index != -1 && to_index != -1)
						move_task(task_title, from_index, to_index);
					else
						cout << "There is not list with this title!\n";
				}
				else
					cout << "The from list and the to list are the same!\n";
			}
			else
			{
				while (cin.get() != '\n');
				cout << "You have to enter \"to\" and the title of the list to move the task!\n";
			}
		}
		else if (command == "help")
		{
			help();
		}
		else if (command == "back")
		{
			show_home();
		}
		else
		{
			while (cin.get() != '\n');
			cout << "There is no such command, enter \"help\" to see the list of commands!\n";
		}
		cout << ":";
	}
}

bool TaskManager::reed_title(std::string & title, bool islist)
{
	using std::cout;
	using std::cin;
	using std::endl;
	title = "";
	try
	{
		char read_char;
		while ((read_char = cin.get()) != '\n')
			if (read_char == '"')
				break;
		if (read_char == '\n')
		{
			throw "You have to enter title of list/task (\"List/task title\")!";
		}
		while ((read_char = cin.get()) != '\n')
		{
			if (read_char == '"')
				break;
			title += read_char;
		}
		if (read_char == '\n')
		{
			throw "You have to enter title of list/task (\"List/task title\")!";
		}
		if (islist)
			std::transform(title.begin(), title.end(), title.begin(), ::toupper);
		return true;
	}
	catch (const char * massange)
	{
		cout << massange << endl;
		return false;
	}
}

bool TaskManager::reed_command(std::string & command)
{
	if (std::cin >> command)
	{
		std::transform(command.begin(), command.end(), command.begin(), ::tolower);
		return true;
	}
	return false;
}

template<typename Item>
void TaskManager::show(int index, Item & list)
{
	if (index != -1)
	{
		system("cls");
		using std::cout;
		using std::endl;
		cout << list[index] << ":" << endl;
		for (int i{}; i < list[index].get_num_elements(); ++i)
		{
			cout << "+" << list[index][i] << endl;
			for (int j{}; j < list[index][i].get_num_elements(); ++j)
			{
				if (i != list[index].get_num_elements() - 1)
					cout << "+";
				else
					cout << " ";
				cout << "  +--" << list[index][i][j] << endl;
			}
		}
		cout << endl;
		if (typeid(list) == typeid(List<TaskList>))
			contex = index;
	}
	else
		show_home();
}