#include "pch.h"
#include "Item.h"

Item::Item() {

}
Item::Item(int key, std::string value)
{
	this->key = key;
	this->value = value;
}


Item::~Item()
{
}
