#pragma once
#include <vector>
#include <iostream>
using namespace std;
class HeapTree
{
private:
	
	void siftDown(int currentIndex); // просеивание вниз интеративно
	void siftUp(int currentIndex);	 // просеивание вверх интеративно

	void siftDownRecursively(int currentIndex); // просеивание вниз рекурсивно
	void siftUpRecursively(int currentIndex);	// просеивание вверх рекурсивно
public:
	vector<int>tree; // массива элементов
	HeapTree();
	~HeapTree();
	
	void insert(int currentIndex);				// добавление элемента и просеивание его вверх интеративно	
	void insertRecursively(int currentIndex);	// добавление элемента и просеивание его вверх рекурсивно	


	int top(); // вовзращает корень дерева
	int pop(); // удаляет корень дерева
};

