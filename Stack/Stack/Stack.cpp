// Stack.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Header.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	Stack stack;
	cout << "Выберите требумое действие: \n1 - добавить элемент в вершину Стека, \n2 - удаление элемента с вершины Стека, \n3 - удаление узла выбранного места, \n5 - вывод всего Стека, \n6 - узнать кол-во элементов в Стеке, \n7 - удалить весь Стек" << endl;
	while (true)
	{
		stack.requests();
		cout << "\nВыберите требумое действие: ";
	}
}
