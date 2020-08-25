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
		if (items[h1] != NULL){					// ���� ������� � ����� �� ������ ����������, �� �� ��������� ����� �������
			if (item->key == items[h1]->key) {
				return;
			}
		}
		
		if (items[h1] == NULL || deleted[h1]) { // ���� ������� ������ ��� ��� ���� ������� ���� - true (�� ���� ������� ��� ����� �������)
			items[h1] = item;					// ����������� ������ ������� ���������� ������
			deleted[h1] = false;				// ������� ����, ������, ��� ��� ������� ������
			return;
		}
		h1 = (h1 + i * h2) % size; // ����� ������ ���
	}
	/* ����� ����� ������ ������ ������ ������� ���������� ������� */
	cout << "Overflow HashTable" << endl;
}

void Dict::remove(int key)
{
	int h1 = hash1(key);
	int h2 = hash2(key);
	for (int i = 0; i < size; i++) {
		if (items[h1] != NULL) {		// ���� ������� �� ������ � ����� �������, ��� ������� �� �������, � ������ ��������� ����, ������, ��� ���� ������
			if (items[h1]->key == key) {
				deleted[h1] = true;
			}
		}
		else {							// �����, ���� �� ���������� � ������� �����, �� ������� ������
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
		if (items[h1] != NULL) { // ���� ���� �� ������ � ����� �������, � ���� ������, �� ���������� �������� �����
			if (items[h1]->key == key && !deleted[h1]) {
				return items[h1]->value;
			}
		}						// ���� ���� �����, �� ���������� ������
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
