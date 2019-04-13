#include "pch.h"
#include "Header.h"

List::List()
{
	Size = 0;
	head = nullptr;
}



List::~List()
{
	clear();
}




void List::push_back(int data)
{
	if (head == nullptr)
	{
		head = new Node(data);
	}
	else
	{
		Node *current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node(data);

	}

	Size++;
}



int& List::operator[](const int index)
{
	int counter = 0;

	Node *current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

void List::pop_front() {
	Node *temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}

void List::push_front(int data)
{
	head = new Node(data, head);
	Size++;
}

void List::insert(int data, int index)
{
	if (index == 0) {
		push_front(data);
	}
	Node *previous = this->head;
	for (int i = 0; i < index - 1; i++) {
		previous = previous->pNext;
	}
	Node *newNode = new Node(data, previous->pNext);
	previous->pNext = newNode;
	Size++;
}

void List::removeAt(int index)
{
	if (index == 0) {
		pop_front();
	}
	Node *previous = this->head;
	for (int i = 0; i < index - 1; i++) {
		previous = previous->pNext;
	}
	Node *toDelete = previous->pNext;
	previous->pNext = toDelete->pNext;
	delete toDelete;
	Size--;
}

void List::pop_back()
{
	removeAt(Size - 1);
}

void List::clear()
{
	while (Size) {
		pop_front();
	}
}
