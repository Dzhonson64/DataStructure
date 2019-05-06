#include "pch.h"
#include "Node.h"
#include <iostream>
#include <map>


Node::Node(int data)
{
	this->data = data;
}

Node::Node(char symbol, int data)
{
	this->symbol = symbol;
	this->data = data;
	this->subNodes = new std::map<char, Node*>();
}



Node::~Node()
{
}

Node::Node()
{
}

Node * Node::tryFind(char symbol)
{
	std::map<char, Node*>::iterator i = subNodes->find(symbol);
	if (i != subNodes->end()) {
		/* "Value" с "key" symbol есть*/

		return &*i->second; // возвращаем "value"
	}
	else {
		return NULL;
	}
	
}
