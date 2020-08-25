#include "pch.h"
#include "HeaderTwoLinkedList.h"
#include <iostream>
using namespace std;

TwoLinkedList::TwoLinkedList() {
	head = nullptr;
	end = nullptr;
	size = 0;
}

TwoLinkedList::~TwoLinkedList() {
	removeAll();
}

void TwoLinkedList::push_right(int data) {
	if (head == nullptr && end == nullptr) { // ���� ��� �������� ��������, �� ������ ���. �� � ������, � �����
		head = new Node(data);
		end = head;
	}
	else if (size > 0) {
		end->pNext = new Node(data, end, nullptr); // ����� ������� � ������, ������� ��������� �� ��������� �������, �������� ����� ������ ��������
		end = end->pNext; // ����� ������� ���������� �������
	}
	size++;
}

void TwoLinkedList::push_left(int data) // �� ����� �����, ��� � � push_right, ������ ������ ��� �� � ������, � � ������
{
	if (head == nullptr && end == nullptr) {
		head = new Node(data);
		end = head;
	}
	else if (size > 0) {
		head->pPrev = new Node(data, nullptr, head);
		end = head->pPrev;
	}
	size++;
}

void TwoLinkedList::addAt(int data, int index)
{
	if (index == 0) {
		push_left(data);
		size++;
	}
	else if (index == this->size + 1) {
		push_right(data);
		size++;
	}
	else if (index <= this->size / 2 && index > 0) {
		Node *temp = head;
		for (int i = 0; i < index; i++) {
			temp = temp->pNext;
		}
		temp->pPrev->pNext = new Node(data, temp->pPrev, temp->pPrev->pNext);
		temp->pPrev = temp->pPrev->pNext;
		size++;
	}
	else if (index > this->size / 2 && index < this->size && index > 0) {
		Node *temp = end;
		for (int i = this->size; i > index; i--) {
			temp = temp->pPrev;
		}
		temp->pPrev->pNext = new Node(data, temp->pPrev, temp->pPrev->pNext);
		temp->pPrev = temp->pPrev->pNext;
		size++;
	}
	else {
		cout << "ERROR: ������ ����� � ������ ���" << endl;
	}
}

void TwoLinkedList::removeAt(int index)
{
	if (index == 0) {
		Node *temp = head;
		head = temp->pNext;
		head->pPrev = nullptr;
		delete temp;
		size--;
	}
	else if (index == size) {
		Node *temp = end;
		end = temp->pPrev;
		end->pNext = nullptr;
		delete temp;
		size--;
	}
	else if (index <= this->size / 2 && index > 0) {
		Node *temp = head;
		for (int i = 0; i < index; i++) {
			temp = temp->pNext;
		}

		temp->pPrev->pNext = temp->pNext;
		temp->pNext->pPrev = temp->pPrev;

		delete temp;
		size--;
	}
	else if (index > this->size / 2 && index < this->size && index > 0) {
		Node *temp = end;
		for (int i = this->size; i > index + 1; i--) {
			temp = temp->pPrev;
		}

		temp->pPrev->pNext = temp->pNext;
		temp->pNext->pPrev = temp->pPrev;

		delete temp;
		size--;
	}
	else {
		cout << "ERROR: ������ ����� � ������ ���" << endl;
	}
	
	
	
	//cout << "ERROR: ������ ����� � ������ ���" << endl;
}

void TwoLinkedList::removeAll()
{
	Node * temp = head;
	while (temp != nullptr) {
		temp = temp->pNext;
		delete temp;
		size--;
	}	
	
}

int & TwoLinkedList::operator[](int index)
{
	if (index <= size / 2) { // ��������� ������ �� ��� �����, ���� ��� ����� �������� (�� ������� ��������), �� ���� �������� ��� ������� index
		Node *tempHead = head;
		for (int i = 0; i < index; i++) {
			tempHead = tempHead->pNext;
		}
		return tempHead->data;
	}
	else {
		Node *tempEnd = end;
		for (int i = 0; i < index; i++) {
			tempEnd = tempEnd->pNext;
		}
		return tempEnd->data;
	}

}

int & TwoLinkedList::getSize()
{
	return this->size;
}

void TwoLinkedList::show() {
	Node *tempHead = head;
	if (size == 1) {
		cout << tempHead->data << endl;
	}
	else {
		while (tempHead != nullptr) {
			cout << tempHead->data << endl;
			tempHead = tempHead->pNext;
		}
	}


}

void TwoLinkedList::showEnd()
{
	cout << end->data << endl;
}
