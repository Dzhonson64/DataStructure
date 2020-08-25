#pragma once
#include <iostream>
class Item
{
public:
	int key;
	std::string value;
	Item();
	Item(int key, std::string value);
	~Item();
};

