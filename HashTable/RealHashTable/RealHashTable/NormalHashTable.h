#pragma once
#include <iostream>
#include <vector>
#include <list>
class NormalHashTable
{
private:
	int getHash(int key);
public:
	std::vector <std::list<std::string>> items;
	NormalHashTable(int size);
	~NormalHashTable();
	void add(int key, std::string value);
	bool search(int key, std::string value);
};

