#include <iostream>
#include "todolist.h"
#include "task_category.h"

int main(void)
{
	using std::cout;
 	Task tre{ "This" };
	Task zalupa{ "this" };
	ToDoList list;
	TaskCategory category;

	list.add(tre);
	category.add(&list[0]);
	category[0]->change_done();
	category[0]->set_title("taklsjd");
    cout << *category[0];
	cout << list[0];
	zalupa.add_subtask("ad");
}