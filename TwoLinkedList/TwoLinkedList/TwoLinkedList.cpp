// ToLinkedList.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "HeaderTwoLinkedList.h"
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	TwoLinkedList list;
	list.push_right(12);
	list.push_right(421);
	list.push_right(422);
	list.push_right(22);
	list.push_right(4);
	list.show();
	cout << endl;
	list.addAt(100, 4);
	list.show();
	cout << endl;
	list.removeAt(4);
	list.show();

	
	/*cout << endl;
	cout << list[0] << endl;*/
}