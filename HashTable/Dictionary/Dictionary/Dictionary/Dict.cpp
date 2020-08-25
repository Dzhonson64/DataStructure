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
	if (containsList(item->key)) return;	 // ������ ��������, � �� ���������� �� � ������� ��� ������ �����, ���� ���� �� ������ �� ���������
	if (items[hash] == NULL) {				 // ���� ������� ������� � �������� hash ���������, �� �������� � ������� Item
		keys.push_back(item->key);
		items[hash] = item;
	}else{									 // �����, ���� ��������� ��������
		bool placed = false;
		for (int i = hash; i < size; i++) {	 // �������� � ������ ������

			/* ���� ������� ������� �� ������ � ���� ������ � ���� ������� ����� ��������� � �-�� �����, �� ��� �� �������� */
			if (items[i] != NULL && items[i]->key == item->key) { 
				std::cout << "Key " << item->key << " is in the dictionary." << std::endl;
				return;
			}
			
			if (items[i] == NULL) {			// �����, ���� ������� �����, �� ��������� ������
				keys.push_back(item->key);
				items[i] = item;
				placed = true;				// ��������� ����, ��� ������� ������� ��������
				break;
			}
		}
		if (!placed) {						// �����, ���� ���� �� ��� ������, �������� ������ ������ (���� ����� ���������, ��� � ������� �������)
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
		if (!placed) { // ���� ����� ���� �������� �� ��������� ������� �����, �� ������� ������
			std::cout << "ERROR!" << std::endl;
		}
	}
}

void Dict::remove(int key)
{
	int hash = getHash(key);
	if (!containsList(key)) return;	// ������ ��������, � �� ���������� �� � ������� ��� ������ �����, �� ������ �� �������

	/*
		���� ������ � ������� hash �����������, �� �������� ������, ������� �� ���� ��� �������� ���������� � ����� �� �����, �� ���������� �������� ����������� � ����� �������, �� ���� ������ ����� � � ���� ������ ��� ������ ������.
		�.�. �� ������ ��������� �� ��� ������� ������� Item, � ��� �� ������ ������� � ������, ������� �� ����? ���� ����, �� ������� �� �������, ������ ��� NULL � ������� ���� ���� � ������.
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
	if (items[hash] != NULL && items[hash]->key == key) {		// ���� ���� ������ ������� � �������� hash ����� �������� �-�� �����, �� �������
		delete items[hash];
		items[hash] = NULL;
		removeKey(key);
	}
	else {										// �����, ���� ��������� ��������, � ����� �� �����, �� ��������� ������ �� ������� hash, ����� �����
		bool placed = false;
		for (int i = hash; i < size; i++) {
			if (items[i] != NULL && items[hash]->key == key) {	// ���� ������ ������� �� ������ � ����� �������, �� ������� ���� ������
				delete items[hash];
				items[hash] = NULL;
				removeKey(key);
				return;
			}
			/* ���� ��������� ������ �����, ������ ������ �������� ������ � ������ hash ���, �.�. ���� �� ����. ������� �� ������ ���������� �����, ����� ������ � �����  */
			if (items[hash] == NULL) {
				return;
			}
		}
		if (!placed) {						// �����, ���� ���� �� ��� ������, �������� ������ ������ (���� ����� ���������, ��� � ������� �������)
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
		if (!placed) { // ����  ����� ���� �������� �� ��������� ������� �����, �� ������� ������
			std::cout << "ERROR!" << std::endl;
		}
	}
}

std::string Dict::search(int key)
{
	int hash = getHash(key);
	if (!containsList(key)) return "";	// ������ ��������, � �� ���������� �� � ������� ��� ������ �����, �� ������ �� �������

	/* 
		���� ������ � ������� hash �����������, �� �������� ������, ������� �� ���� ���������� � ����� �� �����, �� ���������� �������� ����������� � ����� �������.
		�.�. �� ������ ��������� �� ��� ������� ������� Item, � ��� �� ������ ������� � ������, ������� �� ����? ���� ����, �� ���������� ��� ��������. 
	*/
	if (items[hash] == NULL) {			
		for (std::vector<Item*>::iterator i = items.begin(); i < items.end(); i++) {
			if (*i != NULL && (*i)->key == key) {
				return (*i)->value;
			}
		}
		return "This element isn't in the dictionary";
	}
	if (items[hash] != NULL && items[hash]->key == key) {		// ���� ���� ������ ����� ��������� �����, �� �� ����� ������ ������
		return items[hash]->value;
		
	}
	else {								// �����, ���� ��������� ��������, � ����� �� �����, �� ��������� ������ �� ������� hash, ����� �����
		bool placed = false;
		for (int i = hash; i < size; i++) {
			if (items[i] != NULL && items[i]->key == key) { // ���� ���� i-��� ������ ����� ��������� �����, �� �� ����� ������ ������
				return items[i]->value;
			}
			/* ���� ��������� ������ �����, ������ ������ �������� ������ � ������ hash ���, �.�. ���� �� ����. ������� �� ������ ���������� �����, ����� ������ � �����  */
			if (items[i] == NULL) {
				return "";
			}
		}
		if (!placed) {					// �����, ���� ���� �� ��� ������, �������� ������ ������ (���� ����� ���������, ��� � ������� �������)	
			for (int i = 0; i < hash; i++) {
				if (items[i] != NULL && items[i]->key == key) {
					return items[i]->value;
				}

				if (items[i] == NULL) {
					return "";
				}
			}
		}
		if (!placed) { // ���� ����� ���� �������� �� ��������� ������� �����, �� ������� ������
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
