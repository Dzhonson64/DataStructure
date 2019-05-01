#pragma once
#include "Node.h"

#include <iostream>
class RedBlackTree
{
private:
	Node * root;
	void rightRotate(Node * n);		// ������� ������
	void leftRotate(Node * n);		// ������� �����
	void fixInsertion(Node * n);	// ��������������� ������ ����� ���������� �������
	void fixDeleting(Node * n);		// ��������������� ������ ����� �������� ��������
public:
	
	RedBlackTree();
	~RedBlackTree();
	void insert(int value);		// ������� ��������
	Node* search(int value);	// ����� ��������
	void remove(int value);		// �������� ��������
	
};

