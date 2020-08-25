// RealHashTable.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
//#include "BadHashTable.h"
//#include "NormalHashTable.h"
#include "SuperHashTable.h"
#include "Person.h"
/* 
	! Реализиця хеш-функция может быть любая, тут я не зацикливался на них !
	Реализация HashTable 3-х видов по сложности и унивесальность:

	BadHashTable:
		состоит из двумерного динамич. массива строк;
		не продумана реализиция разрешений коллизий;

	NormalHashTable:
		состоит из динамич. массива списков, хранящих строки;
		присутствует реализиция разрешений коллизий (в виде списка)

	SuperHashTable
		состоит их массивов объектов Item, каждый из которых хранит список людей в виде обектов Person;
		присутствует рализация разрешения коллизий (в виде списка)
		т.к. у нас элементы массива хранит объекты Person, то мы можем споконо изменять содержимое объектов и не завязаны только на строковых переменных
		P.S.1 не получается при поиске элемента сравнивать адрес элемента в списке и полученных обектом, хотя пережаются по одному указателю, поэтому сравниваются имена
		P.S.2 можно продумать как взаимодействовать с ключом в элементе Item, чтобы оптимизировать

*/
int main()
{
	/*HashTable * badHashTable = new HashTable(100);
	badHashTable->add("5");
	badHashTable->add("18");
	badHashTable->add("777");

	std::cout << badHashTable->search("777") << std::endl;
	std::cout <<  badHashTable->search("18") << std::endl;
	std::cout <<  badHashTable->search("10") << std::endl;*/

	/*NormalHashTable * hashTable = new NormalHashTable(100);
	hashTable->add(5, "Привет");
	hashTable->add(18, "Мир");
	hashTable->add(777, "Здравствуй");
	hashTable->add(788, "Программист");


	std::cout << hashTable->search(777, "Здравствуй") << std::endl;
	std::cout << hashTable->search(6, "Программист") << std::endl;
	std::cout << hashTable->search(788, "Программис") << std::endl;*/

	SuperHashTable * hashTable = new SuperHashTable(100);
	Person * person = new Person("Kirill", "Chugunov", 18);
	hashTable->add(person);
	hashTable->add(new Person("Leonid", "Valco", 38));
	std::cout << hashTable->search(person) << std::endl;
	std::cout << hashTable->search(new Person("Leonid", "Valco", 38)) << std::endl;
	 
}