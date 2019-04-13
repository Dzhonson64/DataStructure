#include "pch.h"
class TwoLinkedList {
private:
	class Node {
	public:
		Node *pNext;
		Node *pPrev;
		int data;
		Node(int data = int(), Node *pPrev = nullptr, Node *pNext = nullptr) {
			this->pNext = pNext;
			this->pPrev = pPrev;
			this->data = data;
		};
		//~Node();
		
	};
	Node *head;
	Node *end;
	int size;
public:
	TwoLinkedList();
	~TwoLinkedList();
	
	

	void push_right(int data);
	void push_left(int data);
	void addAt(int data, int index);
	void removeAt(int index);
	void removeAll();
	int & operator[](int index);
	int & getSize();
	void show();
	void showEnd();

};
