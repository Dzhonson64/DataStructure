#include "pch.h"

class List
{
public:
	List();
	~List();

	//���������� �������� � ����� ������
	void push_back(int data);
	// �������� ���������� ��������� � ������
	int GetSize() { return Size; }
	// ������������� �������� [] 
	int& operator[](const int index);

	void pop_front();
	void push_front(int data);
	void insert(int data, int index);
	void removeAt(int index);
	void pop_back();
	void clear();

	

private:
	
	class Node
	{
	public:
		Node * pNext;
		int data;

		Node(int data = int(), Node *pNext = nullptr) /*int data = int()::����� ���������� ����������� �� ��������� "�����" ���� ������, � �������������� ���������� data "������ ������".
													  ��� �� ����� ���� ������, ������ �����������, ��������, ����� �����������: int a = int(); - ����� � ���������� "�" ������������ ��� ������� 0*/
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

	int Size;
	Node *head;
};