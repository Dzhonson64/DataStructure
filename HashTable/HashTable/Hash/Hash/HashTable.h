#pragma once

#include <vector>
#include "Person.h"
class HashTable
{
public:
	Person ** arrPers;
	int sizeArrPers;
	HashTable();
	~HashTable();
	
	
	unsigned int hash(std::string value);
	unsigned int ELFhash(char * value);
	unsigned int getHash(std::string key);
	void push(std::string * name, std::string * surname, std::string * phone);
	void remove(std::string * name);
	Person * find(std::string * name);
	void show();
	void show(Person * arrPers);
	void show(std::string * name);

	int size();
};


