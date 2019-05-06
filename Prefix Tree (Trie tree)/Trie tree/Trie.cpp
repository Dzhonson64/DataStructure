#include "pch.h"
#include "Trie.h"
#include "Node.h"
#include <iostream>
#include <string>





void Trie::addNode(std::string key, int data, Node * node)
{
	if (key == "") {
		/* C����� ���������� */
		if (!node->isWord) {
			/* ��������� ������ �� ���������� */
			node->data = data;
			node->isWord = true; // ������ ��������� ������
		}
	}
	else {
		/* ������ �� ����������� */
		char symbol = key[0];
		Node * subNode = node->tryFind(symbol); // ���� �� ��������� ������� ���� ������ � �������, �� ��� ����������, ����� NULL
		if (subNode) {
			/* ��������� ����-������ � ������� */

			addNode(key.substr(1), data, subNode);
		}
		else {
			/* ��� � ������� ������ ����-������ */

			Node * newNode = new Node(symbol, data); // ������ ����� ������, ������� ������ ����� ����� � ��� ����� (data)
			node->subNodes->insert(std::pair<char, Node*>(symbol, newNode)); // ��������� � ���� ����� �����. ������, ������� ����� �������� ����� ����������
			addNode(key.substr(1), data, newNode); // �������� ������ ������ ������ � ������� � ������������ ����� ������
		}
	}
	
}

bool Trie::searchNode(std::string key, Node * node, int value)
{
	
	bool result = false;
	if (key == "") {
		/* C����� ���������� */

		if (node->isWord) {
			/* ��������� ������ ���������� */

			value =  node->data;
			result = true; // ����� �����������, ��������� �������
		}
	}
	else {
		/* C����� �� ���������� */

		Node * subNode = node->tryFind(key[0]); // ���� ����
		if (subNode != NULL) {
			/* ���� ����������� */

			result = searchNode(key.substr(1), subNode, value); // �������� ������ ������ ������ � ������� � ������������ ����� ������
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
