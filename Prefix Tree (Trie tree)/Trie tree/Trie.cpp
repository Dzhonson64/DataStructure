#include "pch.h"
#include "Trie.h"
#include "Node.h"
#include <iostream>
#include <string>





void Trie::addNode(std::string key, int data, Node * node)
{
	if (key == "") {
		/* Cтрока закочилась */
		if (!node->isWord) {
			/* Окончание строки не поставлено */
			node->data = data;
			node->isWord = true; // ставим окончание строки
		}
	}
	else {
		/* Строка не закончилась */
		char symbol = key[0];
		Node * subNode = node->tryFind(symbol); // если по заданному символу есть объект в словаре, то его возвращает, иначе NULL
		if (subNode) {
			/* Сущесвует узел-объект в словаре */

			addNode(key.substr(1), data, subNode);
		}
		else {
			/* Нет в словаре такого узла-обекта */

			Node * newNode = new Node(symbol, data); // создаём новый объект, помещая первую букву слова и вес слова (data)
			node->subNodes->insert(std::pair<char, Node*>(symbol, newNode)); // добавляем в узер новый ассоц. массив, который будет являться новым поддеревом
			addNode(key.substr(1), data, newNode); // отрезаем первый символ строки и переход к рассмотрению новой строки
		}
	}
	
}

bool Trie::searchNode(std::string key, Node * node, int value)
{
	
	bool result = false;
	if (key == "") {
		/* Cтрока закочилась */

		if (node->isWord) {
			/* Окончание строки поставлено */

			value =  node->data;
			result = true; // слово закончилось, результат успешен
		}
	}
	else {
		/* Cтрока не закочилась */

		Node * subNode = node->tryFind(key[0]); // берём узел
		if (subNode != NULL) {
			/* Узел сущетствует */

			result = searchNode(key.substr(1), subNode, value); // отрезаем первый символ строки и переход к рассмотрению новой строки
		}
	}
	return result;
}

void Trie::add(std::string key, int data)
{
	addNode(key, data, root);
}

void Trie::remove(std::string key)
{
	removeNode(key, root);
}

void Trie::removeNode(std::string key, Node * node)
{
	if (key == "") {
		if (node->isWord) {
			node->isWord = false;
		}
	}
	else {
		Node * subNode = node->tryFind(key[0]);
		if (subNode != NULL) {
			removeNode(key.substr(1), subNode);
		}		
	}
}

bool Trie::trySerch(std::string key)
{
	return searchNode(key, root, value);
}

Trie::Trie(int data)
{
	root = new Node('\0', data);
	this->count = 1;
}

Trie::Trie()
{
	root = new Node('\0', NULL);
	this->count = 1;
}

Trie::~Trie()
{
}
