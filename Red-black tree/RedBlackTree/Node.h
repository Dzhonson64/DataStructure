#pragma once
class Node
{
public:
	char color;
	int value;
	Node * left;
	Node * right;
	Node * parent;
	Node();
	Node(int value, char color, Node * left, Node * right);
	~Node();
};

