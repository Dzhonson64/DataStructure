#include "pch.h"
#include <iostream>
#include <string>
#include "HashTable.h"
#include "Person.h"
#include <malloc.h>



#define HASH_MUL 31
#define HASH_SIZE 128
using namespace std;
HashTable::HashTable()
{
	sizeArrPers = 10;
	arrPers = (Person **)malloc(sizeArrPers * sizeof(Person));
	for (int i = 0; i < 10; i++) {
		arrPers[i] = NULL;
	}
}


HashTable::~HashTable()
{
}
unsigned int HashTable::hash(std::string value)
{
	unsigned int h = 0;
	for (int i = 0; i != value.length(); i++)
		h = h * HASH_MUL + (unsigned int)value[i];
	return h;
}

unsigned int HashTable::ELFhash(char * value)
{
	unsigned int hash = 0;
	unsigned int test = 0;

	for (; *value; value++) {
		hash = (hash << 4) + (unsigned char)(*value);

		if ((test = hash & 0xf0000000) != 0) {
			hash = ((hash ^ (test >> 24)) & (0xfffffff));
		}
	}
	return hash;
}
unsigned int HashTable::getHash(std::string key) {
	return hash(key) % size();
}

void HashTable::push(std::string * name, std::string * surname, std::string * phone)
{
	int h = getHash(*name);	
	Person *pers = new Person(*name, *surname, *phone);
	Person *place = arrPers[h];
	if (arrPers[h] == NULL)
	{
		arrPers[h] = pers;
		return;
	}

	while (place->nextItem) {
		place = place->nextItem;
	}
	place->nextItem = pers;
}
void HashTable::remove(std::string * name)
{
	int h = getHash(*name);
	Person * temp = arrPers[h];
	delete temp;
	arrPers[h] = NULL;
}
Person * HashTable::find(std::string * name) {
	int h = getHash(*name);
	Person * item = NULL;
	if (arrPers[h] != NULL) {
		item = arrPers[h];
		return item;
	}
	else {
		cout << "This element is not found!" << endl;
		return 0;
	}
	
}
void HashTable::show()
{
	int sizeArr = size();
	cout << "[" << endl;
	for (int i = 0; i < sizeArr; i++) {
		
		if (arrPers[i]) {
			if (!arrPers[i]->nextItem) {
				cout << "\t[" << i << "] " << arrPers[i][0].name << ", " << arrPers[i][0].surname << " - " << arrPers[i][0].phone;
			}
			else {
				Person *place = arrPers[i];
				cout << "\t[" << i << "] " << "[" << arrPers[i][0].name << ", " << arrPers[i][0].surname << " - " << arrPers[i][0].phone << "]";
				while (place->nextItem) {
					cout << ", [" << place->nextItem->name << ", " << place->nextItem->surname << " - " << place->nextItem->phone << "]";
					place = place->nextItem;
				}
			}
			cout << endl;
		}
	}
	cout << "]" << endl;
}

void HashTable::show(Person * arrPers)
{
	int h = getHash(arrPers[0].name);
	if (arrPers != NULL) {
		cout << "\t" << "PRINT" << endl;
		cout << "\t[" << h << "] " << arrPers[0].name << ", " << arrPers[0].surname << " - " << arrPers[0].phone << endl;
	}
	else {
		cout << "This element is not found!" << endl;
	}
}

void HashTable::show(std::string * name)
{
	int h = getHash(*name);
	if (arrPers != NULL) {
		cout << "\t" << "PRINT" << endl;
		cout << "\t[" << h << "] " << arrPers[h][0].name << ", " << arrPers[h][0].surname << " - " << arrPers[h][0].phone << endl;
	}
	else {
		cout << "This element is not found!" << endl;
	}
}

int HashTable::size() {
	return sizeArrPers;
}

