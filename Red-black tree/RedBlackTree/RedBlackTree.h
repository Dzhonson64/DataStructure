#pragma once
#include "Node.h"

#include <iostream>
class RedBlackTree
{
private:
	Node * root;
	void rightRotate(Node * n);		// поворот вправо
	void leftRotate(Node * n);		// поворот влево
	void fixInsertion(Node * n);	// корректирование дерева после добавляеня элмента
	void fixDeleting(Node * n);		// корректирование дерева после удаления элемента
public:
	
	RedBlackTree();
	~RedBlackTree();
	void insert(int value);		// вставка элемента
	Node* search(int value);	// поиск элемента
	void remove(int value);		// удаления элемента
	
};

