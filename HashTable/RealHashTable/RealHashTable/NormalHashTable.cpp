#include "pch.h"
#include <string>
#include "NormalHashTable.h"


NormalHashTable::NormalHashTable(int size)
{
	items.resize(size);
}


NormalHashTable::~NormalHashTable()
{
}
void NormalHashTable::add(int key, std::string value)
{
	int k = getHash(key);
	items[k].push_back(value);
}
bool NormalHashTable::search(int key, std::string value)
{
	int k = getHash(key);
	for (std::list<std::string>::iterator i = items[k].begin(); i != items[k].end(); i++) {
		if (*i == value) {
			return true;
		}
	}
	return false;
}

int NormalHashTable::getHash(int key) {
	std::string temp = std::to_string(key).substr(0, 1);
	return atoi(temp.c_str());
}