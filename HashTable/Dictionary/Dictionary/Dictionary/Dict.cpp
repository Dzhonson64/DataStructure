#include "pch.h"
#include "Dict.h"
#include <functional>



int Dict::getHash(int key)
{
	double A = 0.618033;
	int h = size * fmod(key * A, 1);
	return h;
}

Dict::Dict()
{
	items.resize(size, NULL);
}


Dict::~Dict()
{
}

void Dict::add(Item * item)
{
	int hash = getHash(item->key);
	if (containsList(item->key)) return;	 // делаем проверку, а не существует ли в словаре уже такого ключа, если есть то ничего не добавляем
	if (items[hash] == NULL) {				 // если позиция массива с индексом hash свободная, то занимаем её обектом Item
		keys.push_back(item->key);
		items[hash] = item;
	}else{									 // иначе, если произошла коллизия
		bool placed = false;
		for (int i = hash; i < size; i++) {	 // проверям в правую строну

			/* Если элемент массива не пустой и ключ обекта в этом массиве равен принятому в ф-ию ключу, то его НЕ добаляем */
			if (items[i] != NULL && items[i]->key == item->key) { 
				std::cout << "Key " << item->key << " is in the dictionary." << std::endl;
				return;
			}
			
			if (items[i] == NULL) {			// иначе, если позиция пуста, то добавляем объект
				keys.push_back(item->key);
				items[i] = item;
				placed = true;				// поднимаем флаг, что элемент успешно добавлен
				break;
			}
		}
		if (!placed) {						// иначе, если флаг всё ещё опущен, проверям влевую строну (тоже самое проверяем, что и вправую сторону)
			for (int i = 0; i < hash; i++) {
				if (items[i] != NULL && items[i]->key == item->key) {
					std::cout << "Key " << item->key << "is in the dictionary" << std::endl;
					return;
				}
				if (items[i] == NULL) {
					keys.push_back(item->key);
					items[i] = item;
					placed = true;
					break;
				}
			}
		}
		if (!placed) { // если после двух проходов не оказалось пустого места, то выводим ошибку
			std::cout << "ERROR!" << std::endl;
		}
	}
}

void Dict::remove(int key)
{
	int hash = getHash(key);
	if (!containsList(key)) return;	// делаем проверку, а не существует ли в словаре уже такого ключа, то ничего не удаляем

	/*
		Если объект с идексом hash отсутствует, то возможно объект, который мы ищем для удаления существует с таким же хешом, но разрешение коллизии происходило с этого объекта, но этот объект удалён и с него дальше уже нельзя искать.
		Т.е. мы должны проверить во всём массиве обектов Item, а нет ли такого объекта с ключом, который мы ищем? Если есть, то удаляем из массива, делаем его NULL и удаляем этот ключ и списка.
	*/

	if (items[hash] == NULL) {
		for (std::vector<Item*>::iterator i = items.begin(); i < items.end(); i++) {
			if (*i != NULL && (*i)->key == key) {
				delete *i;
				*i = NULL;
				removeKey(key);
			}
		}
		return;
	}
	if (items[hash] != NULL && items[hash]->key == key) {		// если ключ объект массива с индексом hash равен принятом ф-ей ключу, то удаляем
		delete items[hash];
		items[hash] = NULL;
		removeKey(key);
	}
	else {										// иначе, если произошла коллизия, и ключи не равны, то проверяем справа от индекса hash, потом слева
		bool placed = false;
		for (int i = hash; i < size; i++) {
			if (items[i] != NULL && items[hash]->key == key) {	// если объект массива не пустой и ключи совпали, то удаляем этом объект
				delete items[hash];
				items[hash] = NULL;
				removeKey(key);
				return;
			}
			/* Если встретили пустой обект, значит дальше коллизий обекта с ключом hash нет, т.к. этот бы элем. занимал бы первое попавшиеся место, какое сейчас и нашли  */
			if (items[hash] == NULL) {
				return;
			}
		}
		if (!placed) {						// иначе, если флаг всё ещё опущен, проверям влевую строну (тоже самое проверяем, что и вправую сторону)
			for (int i = 0; i < hash; i++) {
				if (items[i] != NULL &&  items[hash]->key == key) {
					delete items[hash];
					items[hash] = NULL;
					removeKey(key);
					return;
				}

				if (items[hash] == NULL) {
					return;
				}
			}
		}
		if (!placed) { // если  после двух проходов не оказалось пустого места, то выводим ошибку
			std::cout << "ERROR!" << std::endl;
		}
	}
}

std::string Dict::search(int key)
{
	int hash = getHash(key);
	if (!containsList(key)) return "";	// делаем проверку, а не существует ли в словаре уже такого ключа, то ничего не удаляем

	/* 
		Если объект с идексом hash отсутствует, то возможно объект, который мы ищем существует с таким же хешом, но разрешение коллизии происходило с этого объекта.
		Т.е. мы должны проверить во всём массиве обектов Item, а нет ли такого объекта с ключом, который мы ищем? Если есть, то возвращаем его значение. 
	*/
	if (items[hash] == NULL) {			
		for (std::vector<Item*>::iterator i = items.begin(); i < items.end(); i++) {
			if (*i != NULL && (*i)->key == key) {
				return (*i)->value;
			}
		}
		return "This element isn't in the dictionary";
	}
	if (items[hash] != NULL && items[hash]->key == key) {		// если ключ обекта равен принятому ключу, то мы нашли нужный объект
		return items[hash]->value;
		
	}
	else {								// иначе, если произошла коллизия, и ключи не равны, то проверяем справа от индекса hash, потом слева
		bool placed = false;
		for (int i = hash; i < size; i++) {
			if (items[i] != NULL && items[i]->key == key) { // если ключ i-ого обекта равен принятому ключу, то мы нашли нужный объект
				return items[i]->value;
			}
			/* Если встретили пустой обект, значит дальше коллизий обекта с ключом hash нет, т.к. этот бы элем. занимал бы первое попавшиеся место, какое сейчас и нашли  */
			if (items[i] == NULL) {
				return "";
			}
		}
		if (!placed) {					// иначе, если флаг всё ещё опущен, проверям влевую строну (тоже самое проверяем, что и вправую сторону)	
			for (int i = 0; i < hash; i++) {
				if (items[i] != NULL && items[i]->key == key) {
					return items[i]->value;
				}

				if (items[i] == NULL) {
					return "";
				}
			}
		}
		if (!placed) { // если после двух проходов не оказалось пустого места, то выводим ошибку
			std::cout << "ERROR!" << std::endl;
		}
	}
	
}

bool Dict::containsList(int key)
{
	for (std::list<int>::iterator i = keys.begin(); i != keys.end(); i++) {
		if (*i == key) return true;
	}
	return false;
}
void Dict::removeKey(int key) {
	for (std::list<int>::iterator i = keys.begin(); i != keys.end(); i++) {
		if (*i == key) {
			keys.erase(i);
			return;
		}
	}
}
