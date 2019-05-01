#include "pch.h"
#include "Node.h"


Node::Node()
{
}

Node::Node(int value, char color, Node * left, Node * right)
{
	this->value = value;
	this->color = color;
	this->left = left;
	this->right = right;
}


Node::~Node()
{
}
