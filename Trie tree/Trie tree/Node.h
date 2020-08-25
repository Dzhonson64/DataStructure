#pragma once
#include <map>
class Node
{
public:
	Node(int data);
	Node(char symbol, int data);
	~Node();
	Node();
	int data;
	bool isWord;
	char symbol;
	std::string prefix;
	Node * tryFind(char symbol);
	std::map<char, Node*> * subNodes;
};

