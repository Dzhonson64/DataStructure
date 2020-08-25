// Dictionary.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


/*
	ПОЯСНЕНИЕ:
		Данный алгоритм реализует словарь. Отличие Dictionary от HashTable - не существует элементов с одинаковыми ключами.
		Dictionary постороен на основе метода "Открытая адресация". Т.е. здесь нет массива списков, а только массив, тем самым плюс этого метода - это отсутствие указателей

*/
#include "pch.h"
#include <iostream>
#include "Dict.h"
#include "Item.h"
#include <string>

int main()
{
	Dict * dict = new Dict();
	Item * item = new Item(1, "One");
	dict->add(item);
	dict->add(new Item(6, "Six"));
	dict->add(new Item(5, "Five"));
	dict->add(new Item(3, "Three"));
	dict->add(new Item(4, "Four"));
	dict->remove(4);
	std::cout << dict->search(6) << std::endl;
	dict->add(new Item(10, "Six"));
}