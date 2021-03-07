#ifndef LIST_H_
#define LIST_H_
#include <iostream>

template<typename Item>
class List
{
	struct List_element
	{
		Item data;
		List_element * next;
	};
	List_element * first_element;
	List_element * last_element;
	int num_elements;
	List_element * get_i_element(int index) const
	{
		List_element * temp = first_element;
		for (int i{}; i < index; ++i)
			temp = temp->next;
		return temp;
	}

public:
	List() { first_element = last_element = nullptr; num_elements = 0; }
	List(const Item & item);
	List(const List & list);
	virtual ~List();

	Item & operator[] (const int index);
	const Item & operator[](const int index) const;
	List & operator=(const List & list);

	void add(const Item & item);
	void remove(int index = 0);
	int find(const Item & item) const;
	int get_num_elements() const { return num_elements; }
};

template<typename Item>
List<Item>::List(const Item & item)
{
	first_element = new List_element;
	first_element->data = item;
	first_element->next = nullptr;
	last_element = first_element;
	num_elements = 1;
}

template<typename Item>
List<Item>::List(const List & list) : List(list.first_element->data)
{
	for (int i{ 1 }; i < list.get_num_elements(); ++i)
		this->add(list[i]);
}

template<typename Item>
List<Item>::~List()
{
	List_element * temp;
	while (first_element != nullptr)
	{
		temp = first_element;
		first_element = first_element->next;
		delete temp;
	}
}

template<typename Item>
const Item & List<Item>::operator[](const int index) const
{
	try
	{
		if (index < 0 || index >= num_elements)
			throw "ERROR: out of range!\n";
		List_element * temp = first_element;
		for (int i{}; i < index; ++i)
			temp = temp->next;
		return temp->data;
	}
	catch (const char * massange)
	{
		std::cout << massange;
		exit(EXIT_FAILURE);
	}
}

template<typename Item>
Item & List<Item>::operator[](const int index)
{
	try
	{
		if (index < 0 || index >= num_elements)
			throw "ERROR: out of range!\n";
		List_element * temp = first_element;
		for (int i{}; i < index; ++i)
			temp = temp->next;
		return temp->data;
	}
	catch (const char * massange)
	{
		std::cout << massange;
		exit(EXIT_FAILURE);
	}
}

template<typename Item>
List<Item> & List<Item>::operator=(const List & list)
{
	if (&list == this)
		return *this;
	List_element * temp;
	while (first_element != nullptr)
	{
		temp = first_element;
		first_element = first_element->next;
		delete temp;
	}
	if (list.get_num_elements() != 0)
	{
		first_element = new List_element;
		first_element->data = list.first_element->data;
		first_element->next = nullptr;
		last_element = first_element;
		num_elements = 1;
		for (int i{ 1 }; i < list.get_num_elements(); ++i)
			this->add(list[i]);
	}
	return *this;
}

template<typename Item>
void List<Item>::add(const Item & item)
{
	if (first_element == nullptr)
		*this = List(item);
	else
	{
		last_element->next = new List_element;
		last_element = last_element->next;
		last_element->data = item;
		last_element->next = nullptr;
		++num_elements;
	}
}


template<typename Item>
void List<Item>::remove(int index)
{
	try
	{
		if (index < 0 || index >= num_elements)
			throw "ERROR: out of range!\n";
		List_element * temp = this->get_i_element(index);
		if (index == 0)
			first_element = first_element->next;
		else
		{
			this->get_i_element(index - 1)->next = temp->next;
		}
		delete temp;
		--num_elements;
	}
	catch (const char * massange)
	{
		std::cout << massange;
		exit(EXIT_FAILURE);
	}
};

template<typename Item>
int List<Item>::find(const Item & item) const
{
	int result_index{ -1 };
	for (int i{}; i < this->get_num_elements(); ++i)
		if (this->get_i_element(i)->data == item)
		{
			result_index = i;
			break;
		}
	return result_index;
}
#endif 