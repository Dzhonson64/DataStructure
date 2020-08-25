#pragma once
#include <iostream>
#include <vector>
class HashTable
{
private:
	
	int getHash(std::string item);
public:
	std::vector<std::vector<std::string>>items;
	HashTable(int size);
	~HashTable();
	void add(std::string item);
	bool search(std::string item);

};

