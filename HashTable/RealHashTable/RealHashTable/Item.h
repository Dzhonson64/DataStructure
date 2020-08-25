#pragma once
#include <list>
#include "Person.h"
class Item
{
public:
	Item();
	Item(int key);
	~Item();

	int key;
	std::list<Person> nodes;

};

