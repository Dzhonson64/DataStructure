#pragma once
#include "Item.h"
#include "Person.h"
#include <vector>
class SuperHashTable
{
private:
	std::vector<Item>items;
public:
	SuperHashTable(int size);
	~SuperHashTable();
	int getHash(Person pers);
	void add(Person * pers);
	bool search(Person * pers);
};

