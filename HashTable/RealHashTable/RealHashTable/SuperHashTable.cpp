#include "pch.h"
#include "SuperHashTable.h"
#include "Person.h"


SuperHashTable::SuperHashTable(int size)
{
	items.resize(size);

}


SuperHashTable::~SuperHashTable()
{
}

int SuperHashTable::getHash(Person pers)
{
	/*int N = items.size();
	double A = 0.618033;
	int h = N * fmod(pers.name.length()*A, 1);*/
	return pers.name.length() % items.size();
}
void SuperHashTable::add(Person * pers) {
	int key = getHash(*pers);
	items[key].key = key;
	items[key].nodes.push_back(*pers);
}

bool SuperHashTable::search(Person * pers)
{
	int key = getHash(*pers);
	for (std::list<Person>::iterator i = items[key].nodes.begin(); i != items[key].nodes.end(); i++) {
		Person * temp = &*i;
		if (i->name == pers->name){
			return true;
		}
	}
	return false;
}
