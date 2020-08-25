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
	void add(Item * item); /* добавление на основе метода "линейного пробирования" */
	void remove(int key); /* P.S. удаление можно также было сделать на основе сдвига всего массива, после удаления элемента, чтобы уйти от меток NULL (для vector ф-ией erase())*/
	std::string search(int key);

	/* Для идеальности вот эти две ф-ии перенести в отдельный класс */
	bool containsList(int key); /* Поиск ключа в списке */
	void removeKey(int key); /* Поиск и удаления ключа */
};

