#pragma once
#include <vector>
#include <iostream>
#include <list>
#include "Item.h"
class Dict
{
private:
	std::vector<Item*> items;
	int size = 5;
	int getHash(int key);
	std::list<int> keys;
	
public:
	Dict();
	~Dict();
	void add(Item * item); /* ���������� �� ������ ������ "��������� ������������" */
	void remove(int key); /* P.S. �������� ����� ����� ���� ������� �� ������ ������ ����� �������, ����� �������� ��������, ����� ���� �� ����� NULL (��� vector �-��� erase())*/
	std::string search(int key);

	/* ��� ����������� ��� ��� ��� �-�� ��������� � ��������� ����� */
	bool containsList(int key); /* ����� ����� � ������ */
	void removeKey(int key); /* ����� � �������� ����� */
};

