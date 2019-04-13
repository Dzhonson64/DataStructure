#include "pch.h"
#include <iostream>
#include "Header.h"
using namespace std;
Stack::Stack() {
	head = nullptr;
	size = 0;
}

Stack::~Stack() {
	clear();
}


void Stack::push_up(int data) {
	if (head == nullptr) { // ���� ��� ������� ���������, �� ������ ���. � �� ����������� "�������"
		head = new Node(data);
	}
	else {
		Node *temp = head; // ��������� ���������� �������� ����
		head = new Node(data, temp); // ������ ����� ����-������, � ������� ������ � ������ ����������� ����-������
	}
	size++;
}


void Stack::pop_up()
{
	Node *temp = head; // ��������� ������ ����-������
	head = head->pDown; // ��������� ����-������
	size--; // ��������� ���-�� ��������� � �����
	delete temp; // ������ ������ ����-������
}


void Stack::pop_exactly(int num)
{
	Node *temp = head; // ��������� ������ ����-������ ��� ����, ��� �� �� �� ������������� � ���������� ���� 
	Node *temp2 = head; // ��������� ������ ����-������ ��� ����, ��� �� �� �� ����������� � ����, ������������ ���� �������� ����
	if (num > 0) {
		for (int i = 0; i <= num - 1; i++) {
			temp = temp->pDown; // ���� ��������� ���� ��� ����������� ��������
		}

		/* ��������� ���������, ��� �� �� ���������� ����� � ����� */
		while (temp2->pDown != temp) {
			temp2 = temp2->pDown; // ���� ���� ����� ��������� ���������
		}
		temp2->pDown = temp->pDown; // ��������� ��������� ����, ������������ ����� ���������� ����, � ���� ����� ���������
		/**********/

		size--;
		delete temp; // ������� ��������� ����
	}
	else if (num == 0) {
		pop_up(); // ���� ������� �������, �� ���������� �������, ��� �������� ����-������
	}

}


void Stack::getSize()
{
	cout << "���-�� ��������� � �����: " << size << endl;
}


void Stack::clear()
{
	while (size) {
		pop_up(); // ���������� ������� ����-������, ���� size != 0
	}
}


int & Stack::operator[](int num)
{
	Node *temp = head; // ��������� ����-������ ��� ������������ ����������� � ���������� ��������
	for (int i = 0; i < num; i++) {
		temp = temp->pDown;
	}
	return temp->data;
}


void Stack::Show() {
	Node *temp = head; // ��������� ����-������
	if (size == 1) {
		cout << temp->data; // ���� ���-�� �������� ����� 1, �� ������ ������� ������ ����-������
	}
	else { // ����� ������ �� �����, ����������� �� ����������
		while (temp != nullptr) {
			cout << temp->data << endl;
			temp = temp->pDown;
		}
	}

}

void Stack::requests() {
	int request, num;
	cin >> request;
	switch (request)
	{
	case 1:
		cout << "������� �����, ������� ������ �������� � ����: ";
		cin >> num;
		push_up(num);
		cout << "������� ��������" << endl;
		break;
	case 2:
		pop_up();
		cout << "������� ���˨� � ������� �����" << endl;
		break;
	case 3:
		cout << "������� ����� ��������, ������� ������ ������� �� �����: ";
		cin >> num;
		pop_exactly(num);
		cout << "������� ��� ������� " << num << " ���˨� � ������� �����" << endl;
		break;
		/*case 4:
			cout << "������� ����� ��������, ������� ������ ������� �� �����: ";
			cin >> num;
			operator[](num);
			break;*/
	case 5:
		Show();
		break;
	case 6:
		getSize();
		break;
	case 7:
		clear();
		cout << "���� ���˨�" << endl;
		break;
	default:
		cout << "�� ����� ����������� ������" << endl;
		break;
	}
}