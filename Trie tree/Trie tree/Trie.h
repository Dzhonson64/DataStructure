#pragma once
#include "Node.h"
class Trie
{
private:
	
	void addNode(std::string key, int data, Node * node);
	Node * root;
	bool searchNode(std::string key, Node * node, int value);
	void removeNode(std::string key, Node * node);
	int value;
public:
	int count;
	void add(std::string key, int data);
	void remove(std::string key);
	bool trySerch(std::string key);
	Trie(int data);
	Trie();
	~Trie();
};

