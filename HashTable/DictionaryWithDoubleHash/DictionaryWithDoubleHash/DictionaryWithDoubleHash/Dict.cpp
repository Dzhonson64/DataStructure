#include "pch.h"
#include "Dict.h"


Dict::Dict()
{
	items.resize(size, NULL);
	deleted.resize(size);
}


Dict::~Dict()
{
}

void Dict::add(Item * item)
{
	int h1 = hash1(item->key);
	int h2 = hash2(item->key);
	for (int i = 0; i < size; i++) {
		if (items[h1] != NULL){					// если элемент с таким же ключом существует, то не добавляем новый элемент
			if (item->key == items[h1]->key) {
				return;
			}
		}
		
		if (items[h1] == NULL || deleted[h1]) { // если элемент пустой или для этой позиции флаг - true (на этой позиции был удалён элемент)
			items[h1] = item;					// присваиваем данной позиции переданный объект
			deleted[h1] = false;				// опускам флаг, говоря, что эта позиция занята
			return;
		}
		h1 = (h1 + i * h2) % size; // иначе делаем шаг
	}
	/* Можно также вместо вывода ошибки сделать увеличение массива */
	cout << "Overflow HashTable" << endl;
}

void Dict::remove(int key)
{
	int h1 = hash1(key);
	int h2 = hash2(key);
	for (int i = 0; i < size; i++) {
		if (items[h1] != NULL) {		// если элемент не пустой и ключи совпали, сам элемент не удаляем, а просто поднимаем флаг, говоря, что слот пустой
			if (items[h1]->key == key) {
				deleted[h1] = true;
			}
		}
		else {							// иначе, если мы обратились к пустому слоту, то вывыдим ошибку
			cout << "This element isn't in the dictionary";
			return;
		}
		h1 = (h1 + i * h2) % size;
	}
}

string Dict::search(int key)
{
	int h1 = hash1(key);
	int h2 = hash2(key);
	for (int i = 0; i < size; i++) {
		if (items[h1] != NULL) { // если слот не пустой и ключи совпали, и флаг опущен, то возвращаем значение слота
			if (items[h1]->key == key && !deleted[h1]) {
				return items[h1]->value;
			}
		}						// если слот пусто, то возвращаем ошибку
		else {
			return NULL;
		}
		h1 = (h1 + i * h2) % size;
	}
	return NULL;
}

int Dict::hash1(int key)
{
	return key % size;
}

int Dict::hash2(int key)
{
	return key % (size - 2) + 1;
}
