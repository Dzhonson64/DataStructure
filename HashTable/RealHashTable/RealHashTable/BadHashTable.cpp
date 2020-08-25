#include "pch.h"
#include "BadHashTable.h"


HashTable::HashTable(int size) {
	items.resize(size);
	for (int i = 0; i < size; i++) {
		items[i].resize(1);
	}
}


HashTable::~HashTable()
{
}

void HashTable::add(std::string item)
{
	int key = getHash(item);
	items[key][0] = item;
}

bool HashTable::search(std::string item)
{
	int key = getHash(item);
	if (items[key][0] != "" && items[key][0] == item) {
		return true;
	}
	return false;
}

int HashTable::getHash(std::string item) {
		return item.length() % items.size();
}
