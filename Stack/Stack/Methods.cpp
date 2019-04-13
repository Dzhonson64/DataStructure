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
	if (head == nullptr) { // Если нет никаких элементов, то создаём его. И он становиться "головой"
		head = new Node(data);
	}
	else {
		Node *temp = head; // сохраняем предыдущый головной узел
		head = new Node(data, temp); // создаём новый узел-голову, и передаём данные и адресс предудущего узла-головы
	}
	size++;
}


void Stack::pop_up()
{
	Node *temp = head; // сохраняем старый узел-голову
	head = head->pDown; // обнолвяем узел-голову
	size--; // уменьшаем кол-во элементов в Стеке
	delete temp; // удалаём старый узел-голову
}


void Stack::pop_exactly(int num)
{
	Node *temp = head; // сохраняем старый узел-голову для того, что бы от неё переместиться к удаляемому узлу 
	Node *temp2 = head; // сохраняем старый узел-голову для того, что бы от неё переститься к узле, находящегося пред удаляемы улом
	if (num > 0) {
		for (int i = 0; i <= num - 1; i++) {
			temp = temp->pDown; // берём выбранынй узел для последущего удаления
		}

		/* Переносим указатели, что бы не потерялась связь в Стеке */
		while (temp2->pDown != temp) {
			temp2 = temp2->pDown; // берём узел перед удаляемым элементом
		}
		temp2->pDown = temp->pDown; // переносим указатель узла, находящегося после удаляемого узла, в узел перед удаляемым
		/**********/

		size--;
		delete temp; // удаляем выбранный узел
	}
	else if (num == 0) {
		pop_up(); // если элемент нулевой, то пользуемся методом, для удаления узла-головы
	}

}


void Stack::getSize()
{
	cout << "Кол-во элементов в стеке: " << size << endl;
}


void Stack::clear()
{
	while (size) {
		pop_up(); // Постепенно удаляем узел-голову, пока size != 0
	}
}


int & Stack::operator[](int num)
{
	Node *temp = head; // сохраняем узел-голову для последующего перемещения к выбранному элементу
	for (int i = 0; i < num; i++) {
		temp = temp->pDown;
	}
	return temp->data;
}


void Stack::Show() {
	Node *temp = head; // сохраняем узел-голову
	if (size == 1) {
		cout << temp->data; // если кол-во элеметов равно 1, то просто выводим данные узел-голову
	}
	else { // иначе выводи всё сразу, перемещаясь по указателям
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
		cout << "Введите число, которое хотите добавить в Стек: ";
		cin >> num;
		push_up(num);
		cout << "Элемент ДОБАВЛЕН" << endl;
		break;
	case 2:
		pop_up();
		cout << "Элемент УДАЛЁН с вершины Стека" << endl;
		break;
	case 3:
		cout << "Введите номер элемента, который хотите удалить из Стека: ";
		cin >> num;
		pop_exactly(num);
		cout << "Элемент под номером " << num << " УДАЛЁН с вершины Стека" << endl;
		break;
		/*case 4:
			cout << "Введите номер элемента, который хотите вывести из Стека: ";
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
		cout << "Стек УДАЛЁН" << endl;
		break;
	default:
		cout << "Вы ввели неправльный запрос" << endl;
		break;
	}
}