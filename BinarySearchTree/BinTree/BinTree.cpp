// BinTree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
using namespace std;
struct Node {
	int data;
	Node * leftSon;
	Node * rightSon;
	Node * parent;
};
void show(Node *tree);									// отображение ключей в консоли
void add(Node *&node, int item, Node * parent);			// добавление узла в дрерво
void removeTree(Node *& node);							// удаление всего дерева
int find(Node *& node, int item);						// поиск узла, по ключу
Node * minItem(Node * node);							// нахождение мин. элемента в поддереве
Node * maxItem(Node * node);							// нахождение макс. элемента в поддереве
Node * treeSuccessorNode(Node *& node, Node * item);	// поиск следующего элемента, после введённого item
Node * deleteNode(Node *& node, Node *& item);			// удаление узла item
int getHeight(Node *& node);
int main()
{
	

	Node * tree = NULL;
	add(tree, 45, tree);
	add(tree, 36, tree);
	add(tree, 31, tree);
	add(tree, 42, tree);
	add(tree, 40, tree);
	add(tree, 43, tree);
	add(tree, 44, tree);
	/*add(tree, 30, tree);
	add(tree, 83, tree);
	add(tree, 48, tree);
	add(tree, 89, tree);
	add(tree, 45, tree);
	add(tree, 64, tree);
	add(tree, 70, tree);
	add(tree, 41, tree);*/
	show(tree);
	cout << endl;
	deleteNode(tree, tree->leftSon->rightSon);
	/*deleteNode(tree, tree->rightSon->leftSon);
	deleteNode(tree, tree);
	deleteNode(tree, tree->leftSon);*/
}

void show(Node *tree) {
	if (tree != NULL)               //Пока не встретится пустое звено
	{
		show(tree->leftSon);               //Рекурсивная функция для вывода левого поддерева
		cout << tree->data << " ";              
		show(tree->rightSon);               //Рекурсивная функци для вывода правого поддерева
	}
}
/* ↑↑↑ Decription function show() ↑↑↑*/
/*
	С помощью show(tree->leftSon) мы сначала рекурсивно опускаемся по левой ветви, пока в его лепистке указатель на leftSon не будте NULL
	Если мы встретили NULL, то из-за того, что мы шли рекурсивно, то возвращаемся обратно. А обратно у нас встретится как раз сам leftSon. И опускаемся на одну опреция внизу и там происходит вывод нашего leftSon.
	Дальше идём к следующей опрециию. Это вызов show(tree->rightSon). Т.к. мы возвратились последний раз на элемент leftSon, который не NULL, по поэтому show(tree->rightSon) отталкивается от него.
	После вывода leftSon, который не NULL, tree->rightSon означает, что мы входим в левый лепесток leftSon, который не NULL. Он у leftSon NULL. Поэтому возвращемся назад из-за рекурсии.
	Т.к. операция show(tree->rightSon) была последняяв теле IF, то мы теперь начинаем занаво с show(tree->leftSon).
	Т.к. мы вернулись назад, то tree->leftSon - это корень лепестков tree->leftSon и tree->rightSon (но т.к.tree->rightSon == NULL, то отобразили только tree->leftSon).
	Т.к. tree->leftSon != NULL, то переходим к следующей ф-ии - это вывод, в данном случае, нашего корня лепистков.
	Потому преходим к show(tree->rightSon). tree->rightSon != NULL, поэтому снова начинаем IF занаво, т.к. show(tree->rightSon) последняя оперция в IF,то опять проходимся по левой ветке рекурсивно, пока не встретим на левой ветке NULL.
	Потом повторяем всё тоже самое, что и я писал в начале.
*/
void add(Node *&node, int item, Node * parent) {
	if (node == nullptr) {
		node = new Node;
		node->data = item;
		node->leftSon = nullptr;
		node->rightSon = nullptr;
		node->parent = parent;
	}
	else if (item < node->data) {
		Node * parent = node;
		add(node->leftSon, item, parent);
	}
	else if (item > node->data) {
		Node * parent = node;
		add(node->rightSon, item, parent);
	}

}
void removeTree(Node *& node) {
	if (node) {
		removeTree(node->leftSon);
		removeTree(node->rightSon);
		delete node;
	}
}
/* ↑↑↑ Decription function removeTree() ↑↑↑*/
/*
	С помощью ф-ий removeTree(node->leftSon) removeTree(node->rightSon) мы пробегаемся по левый и правым лепесткам каждого корня.
	Если у корня лепестки NULL, т.е. их нет, то мы можем спокойно этот лепесток удалить
*/

int find(Node *& node, int item) {
	if (node == NULL) {
		return NULL;
	}else if (item < node->data) {
		find(node->leftSon, item);
	}else if (item > node->data) {
		find(node->rightSon, item);
	}else if (node->data == item) {
		return node->data;
	}
	else {
		return NULL;
	}
}

Node * minItem(Node * node) { /* На вход подается дерево T, и возвращается узел с минимальным значением ключа в дереве. */
	while (node->leftSon != NULL) {
		node = node->leftSon;
	}
	return node;
}
Node * maxItem(Node * node) {
	while (node->rightSon != NULL) {
		node = node->rightSon;
	}
	return node;
}
Node * treeSuccessorNode(Node *& node, Node * item) {
	if (item->rightSon != NULL) { /* Если у узла есть правое поддерево, то возвращаем САМЫЙ ЛЕВЫЙ узел ПРАВОГО поддерева. */
		return minItem(item->rightSon);
	}
	/* Если у узла нет правого поддерева, то поднимаемся по родителям наверх, пока не найдем того, для которого рассматриваемый
	узел – левый сын. */
	Node * parent = item->parent;
	while (parent != NULL && parent->leftSon->data > item->data) {
		parent = parent->parent;
	}


	if (parent->data < item->data) {
		return NULL;
	}
	else {
		return parent;
	}	
}

Node * deleteNode(Node *& node, Node *& item) {

	int dataTemp = 0; // можно немного изменить, чтобы эта переменная хранила данные узла и выводила его перед удалением
	
			/*
				Если у узла нет сыновей или один сын, то удаляемым узлел
				будет он сам.
			*/

		if (item->leftSon == NULL && item->rightSon == NULL) {  // без сыновей
			Node * temp = item;									// сохраняю во временный указатель, чтобы потом с помощью него сделать удаление
			dataTemp = item->data;
			if (item->parent) {									// если у элемена есть родитель

				// узнаём, в какой ветви находится item, по сравнению с его родителем, чтобы эту ветвь сделать NULL, для дальней корректной работы
				if (item->parent->data > item->data) {  // и если данные родителя item больше данных самого item (т.е. item в левой ветви родителя), то обнуляем левую ветвь
					item->parent->leftSon = NULL; 
				}
				else {
					item->parent->rightSon = NULL;		// иначе правую ветвь обнуляем
				}
				delete temp;							// делаем удаление узла, после перестановки указателей
			}
			else { // если у элемента нет родителей, т.е. это корень дерева без сыновей, то удаляем узел и ... !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				delete temp;
				node = NULL;
				return node;
			}
		}
		else if (item->leftSon != NULL && item->rightSon == NULL) { // Если у узла есть один сын (левый)
			

			Node * temp = item;
			dataTemp = item->data;
			item->leftSon->parent = item->parent;	// деляем обзятельно перелинковку указателей на родителей (родитель левого сына элемента item должен быть не item, а родитель item)
			item = item->leftSon;					// на место item ставим его сына
			delete temp;							// удаляем выбранный элемент
		}
		else if (item->leftSon == NULL && item->rightSon != NULL) { // Если у узла есть один сын (правый)
			Node * temp = item;
			dataTemp = item->data;
			item->rightSon->parent = item->parent;	// деляем обзятельно перелинковку указателей на родителей (родитель правого сына элемента item должен быть не item, а родитель item)
			item = item->rightSon;					// на место item ставим его сына
			delete temp;							// удаляем выбранный элемент
		}
		else if (item->leftSon != NULL && item->rightSon != NULL) {
			/* 
				Если у узла два сына, то удаляемым узлом будет его последователь. У удаляемого узла может быть только правый сын, потому что
				это самый левый элемент правого поддерева узла. Таким образом, у удаляемого узла в любом случае только один сын.
			*/


			Node * temp = minItem(item->rightSon);	// следующий элемент после item (это для узла с двумя листьями - MIN элем. в правом поддереве)
			item->data = temp->data;				// заменяем данные с элем., который идёт после item


			// если min элем. есть правое поддерево
			if (temp->rightSon != NULL) { 

				// Узнаём, в какой ветви находится следующий элемент после item, по сравнению с его родителем, чтобы эту ветвь сделать NULL, для дальней корректной работы
				
				// Если данные родителя  min элем. больше данных самого  min элем. (т.е. min элем. в левой ветви родителя)
				if (temp->parent->data > temp->data) {	
					temp->parent->leftSon = temp->rightSon;		// делаем указатель родителя его на левого сына - правое поддерево min элем. (т.к. мы точно знаем, что левого поддерева нет, т.к. это min элемент в левом поддереве)
					temp->rightSon->parent = temp->parent;		// деляем перелинковку указателей на родителей (родитель правого поддерева, относ. min элем. теперь не min элем, а родитель min элем.)
				}

				// min элем. в правой ветви родителя (т.е. этот элемент следующий в правой ветви относительно удаляемого узла)
				else {
					temp->parent->rightSon = temp->rightSon;	// указатель родителя его на правого сына - правое поддерево min элем.
					temp->rightSon->parent = temp->parent;		// деляем перелинковку указателей на родителей (родитель прового поддерева, относ. min элем. теперь не min элем, а родитель min элем.)
				}
			}

			// если нет правого поддерева, то узнаём в какой ветви относ. родителя находился min. элем. и указатель на эту ветвь делаем NULL для дальнейшей корректной работы
			else { 
				if (temp->parent->data > temp->data) {
					temp->parent->leftSon = NULL;
				}
				else {
					temp->parent->rightSon = NULL;
				}
				delete temp;									// делаем удаление нужного узла
			}
		}
		return node;
}