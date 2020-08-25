#pragma once
#include <string>
#include <iostream>
class Item
{
public:
	Item(int key, std::string value);
	Item();
	~Item();

	int key;
	std::string value;
};

