// DynamicArray.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
using namespace std;
struct DArray {
	int index = 0;
	int capacity = 2;
	int * dynamicArray = new int[capacity];
}dArray;


void push(int item);
int getElemet(int id);
int size();
int pop();
void getIndex(int item);
int main()
{
	struct DArray * dArr = &dArray;
	for (int i = 0; i < 5; i++)
	{
		push(10);
	}
	push(25);
	//std::cout << pop();
	for (int i = 0; i < 6; i++) {
		cout << getElemet(i) << endl;
	}
}
void push(int item){
	struct DArray * dArr = &dArray;

	if (dArr->index == dArr->capacity) {
		int * arrayBuffer = new int[dArr->capacity * 2];
		for (int i = 0; i < dArr->capacity; i++)
		{
			arrayBuffer[i] = dArr->dynamicArray[i];
		}
		delete [] dArr->dynamicArray;
		
		dArr->dynamicArray = arrayBuffer;

		
	}
	cout << "dArr->capacity - " << dArr->capacity << endl;
	dArr->dynamicArray[dArr->index] = item;
	dArr->index++;
}
int getElemet(int id) {
	struct DArray * dArr = &dArray;
	return dArr->dynamicArray[id];
}
int size() {
	struct DArray * dArr = &dArray;
	return dArr->index;
}
int pop() {
	struct DArray * dArr = &dArray;
	int lastElem = dArr->dynamicArray[dArr->index - 1];
	dArr->index -= 1;
	return lastElem;
}
void getIndex(int item) {
	struct DArray * dArr = &dArray;
	
}