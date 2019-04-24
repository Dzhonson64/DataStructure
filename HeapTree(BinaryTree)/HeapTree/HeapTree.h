#pragma once
#include <vector>
#include <iostream>
using namespace std;
class HeapTree
{
private:
	
	void siftDown(int currentIndex); // ����������� ���� �����������
	void siftUp(int currentIndex);	 // ����������� ����� �����������

	void siftDownRecursively(int currentIndex); // ����������� ���� ����������
	void siftUpRecursively(int currentIndex);	// ����������� ����� ����������
public:
	vector<int>tree; // ������� ���������
	HeapTree();
	~HeapTree();
	
	void insert(int currentIndex);				// ���������� �������� � ����������� ��� ����� �����������	
	void insertRecursively(int currentIndex);	// ���������� �������� � ����������� ��� ����� ����������	


	int top(); // ���������� ������ ������
	int pop(); // ������� ������ ������
};

