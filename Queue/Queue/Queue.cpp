
#include "pch.h"
#include "Header.h"
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");


	List lst;
	lst.push_back(5);
	lst.push_back(7);
	lst.push_back(101);
	for (int i = 0; i < lst.GetSize(); i++)
	{
		std::cout << lst[i] << std::endl;
	}
	cout << endl;
	lst.removeAt(1);
	for (int i = 0; i < lst.GetSize(); i++)
	{
		std::cout << lst[i] << std::endl;
	}
	return 0;
}