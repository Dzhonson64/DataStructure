/* Реализация Двоичной(Бинарной) кучи */
#include "pch.h"
#include <iostream>
#include "HeapTree.h"

int main()
{
	HeapTree * ht = new HeapTree();
	ht->insertRecursively(20);
	ht->insertRecursively(11);
	ht->insertRecursively(17);
	ht->insertRecursively(7);
	ht->insertRecursively(4);
	ht->insertRecursively(13);
	ht->insertRecursively(15);
	ht->insertRecursively(14);
	/* Вывод элементов в порядке возрастания */
	while (ht->tree.size() > 0) {
		cout << ht->pop() << " ";
	}
}