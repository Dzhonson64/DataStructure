#include "pch.h"

class List
{
public:
	List();
	~List();

	//добавление элемента в конец списка
	void push_back(int data);
	// получить количество елементов в списке
	int GetSize() { return Size; }
	// перегруженный оператор [] 
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

		Node(int data = int(), Node *pNext = nullptr) /*int data = int()::здесь вызывается конструктор по умолчанию "этого" типа данных, и инициализирует переменную data "своими нулями".
													  Что бы проще было понять, можешь попробовать, например, такую конструкцию: int a = int(); - здесь в переменную "а" запендюрится его интовый 0*/
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

	int Size;
	Node *head;
};