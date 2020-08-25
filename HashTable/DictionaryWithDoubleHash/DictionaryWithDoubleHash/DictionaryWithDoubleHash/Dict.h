#pragma once
#include <vector>
#include "Item.h"
using namespace std;
class Dict
{
private:
	vector<Item*> items;
	vector<bool> deleted;
	int size = 100;
public:
	Dict();
	~Dict();

	void add(Item * item);
	void remove(int key);
	string search(int key);

	int hash1(int key);
	int hash2(int key);
};

