#include "pch.h"
#include "RedBlackTree.h"





void RedBlackTree::rightRotate(Node * n)
{
	Node * oldLeft = n->left; // родитель элемента
	n->left = oldLeft->right; // правой ветвью становится левый сын рассматриваемого узла
	if (oldLeft->right) { // если есть у левого сына родитель, то его новым родителем становится родитель рассматриваемого элемента !!! ВОЗМОЖНО УСЛОВИЕ МОЖНО УБРАТЬ !!!
		oldLeft->right->parent = n;
	}

	oldLeft->parent = n->parent;
	if (n->parent) { // если у родителя рассматриваемого элемента был родитель,то определяем в какой ветки был он, и в этому ветку вставляем рассматриваемый элемент
		if (n->parent->right == n) {
			n->parent->right = oldLeft;
		}
		else {
			n->parent->left = oldLeft;
		}
	}
	else { // если не было родителей, то это корень
		root = oldLeft;
	}

	oldLeft->right = n;
	n->parent = oldLeft;

}

void RedBlackTree::leftRotate(Node * n)
{
	Node * oldRight = n->right; // родитель элемента
	n->right = oldRight->left; // правой ветвью становится левый сын рассматриваемого узла
	if (oldRight->left) { // если есть у левого сына родитель, то его новым родителем становится родитель рассматриваемого элемента !!! ВОЗМОЖНО УСЛОВИЕ МОЖНО УБРАТЬ !!!
		oldRight->left->parent = n;
	}

	oldRight->parent = n->parent;
	if (n->parent) { // если у родителя рассматриваемого элемента был родитель,то определяем в какой ветки был он, и в этому ветку вставляем рассматриваемый элемент
		if (n->parent->left == n) {
			n->parent->left = oldRight;
		}
		else {
			n->parent->right = oldRight;
		}
	}
	else { // если не было родителей, то это корень
		root = oldRight;
	}

	oldRight->left = n;
	n->parent = oldRight;
}

RedBlackTree::RedBlackTree()
{
	
}

RedBlackTree::~RedBlackTree()
{
}

void RedBlackTree::insert(int value)
{
	Node * n = new Node(value, 'R', NULL, NULL); // создаём красный узел со значение value
	if (root == NULL) {
		/* Корня нет, то дерева превоначально не было, значит создаём корень */
		root = n;
		n->parent = NULL;
	}
	else {
		/* Если корень */
		Node * tempParentNode = root; // указывает на предыдщий узел tempNode
		Node * tempNode = root; // будет указывать на NULL лист, куда будем вставлять узел n
		while (tempNode != NULL) {
			tempParentNode = tempNode; // запоминаем предыдущий узел
			if (tempNode->value > n->value) {
				/* Значение меньше значения узла */

				tempNode = tempNode->left;
			}
			else if (tempNode->value < n->value){
				/* Значение больше значения узла */

				tempNode = tempNode->right;
			}
			else {
				/* Значение уже есть в дереве */
				return;
			}
		}
		n->parent = tempParentNode; // родителем нового узла tempParentNode

		if (tempParentNode->value < n->value) {
			/* Значение нового узла больше */

			tempParentNode->right = n;
		}
		else {
			/* Значение нового узла меньше */

			tempParentNode->left = n;
		}
		fixInsertion(n); // проверяем, не нарушены ли свойства красно-черного дерева
	}
	
}

void RedBlackTree::fixInsertion(Node * n)
{
	Node * dad = NULL;
	Node * grandpa = NULL;
	Node * uncle = NULL;

	while (n != root && n->parent->parent != NULL && n->parent->color == 'R') { // пока отец красный
		if (n->parent == n->parent->parent->left) {
			/* Отец находится в левой ветки */

			uncle = n->parent->parent->right;   // запоминаем "дядю" элемента
			dad = n->parent;					// запоминаем "отца"
			grandpa = n->parent->parent;		// запоминаем "дедушку"

			if (uncle != NULL && uncle->color == 'R') {
				/* Дядя имеет красный цвет */

				/* Меняем цевета */
				dad->color = 'B';
				uncle->color = 'B';
				grandpa->color = 'R';
				n = grandpa;			// переходим для дальшейшего рассмотрения к дедушке
			}
			else {
				/* Дядя имеет чёрный цвет (его не существует в поддереве)*/

				if (n == dad->right){
					/* Элемент в правой ветви */
					n = dad;
					leftRotate(n); // делаем левый поворт, относительно родителя
				}
				dad->color = 'B';		// после этого бывший отец  - чёрный
				grandpa->color = 'R';   // бывший дедушка - красный
				rightRotate(grandpa);   // поворот вправо, относительно дедушки
			}
		}
		else {
			/* Отец в правой ветки */

			uncle = n->parent->parent->left; // запоминаем "дядю" элемента
			dad = n->parent;				 // запоминаем "отца"
			grandpa = n->parent->parent;	 // запоминаем "дедушку"

			if (uncle != NULL && uncle->color == 'R') {
				/* Дядя имеет красный цвет */

				/* Меняем цевета */
				dad->color = 'B';
				uncle->color = 'B';
				grandpa->color = 'R';
				n = grandpa; // переходи для дальнейшего рассмотрения к дедушке
			}
			else { 
				/* Дядя имеет чёрный цвет (его не существует в поддереве)*/

				if (n == dad->left) {
					/* Элемент в левой ветви */

					//n = n->parent;
					rightRotate(dad); // делаем правый поворт, относительно родителя
				}
				dad->color = 'B';		// отце - чёрный
				grandpa->color = 'R';	// дедушка - красыный
				leftRotate(grandpa);	// делаем левый поворот относительно дедушки
			}		
		}
	}
	root->color = 'B'; // поправлям корень, делая его чёрным
}

Node* RedBlackTree::search(int value)
{
	Node * item = root;
	while (item != NULL) {
		if (value < item->value) {
			item = item->left;
		}
		else if (value > item->value) {
			item = item->right;
		}
		else {
			return item;
		}
	}
	
	std::cout << "This element didn't find" << std::endl;
	return NULL;
}

void RedBlackTree::remove(int value)
{
	Node * item = root;

	
	while (item != NULL) {
		/* Поиск элемента */

		if (value < item->value) {
			item = item->left;
		}
		else if (value > item->value) {
			item = item->right;
		}
		else if (item->value == value){
			break;
		}
	}

	if (item->left == NULL && item->right == NULL) {
		/* Если у удаляемого элемента нет сыновей */

		Node * deleteItem = item; // запоминаю удаляемый элемент
		int dataDeleteItem = item->value; // запоминаю значение удаляемого элемента
		if (deleteItem->color == 'B') fixDeleting(deleteItem);
		if (deleteItem->parent) {
			/* Родитель удалямого элемента есть */

			if (deleteItem->parent->left == deleteItem) {
				/* Удаляемый элемент влево ветви родителя */
				deleteItem->parent->left = NULL;
			}
			else {
				/* Удаляемый элемент вправой ветви родителя */
				deleteItem->parent->right = NULL;
			}
		}
		else {	
			/* Нет родителя и нет листей, то это корень */
			root = NULL;
		}
		
		delete deleteItem;
	}
	else if (item->left == NULL && item->right) {
		/* Есть правый сын */

		Node * deleteItem = item;
		int dataDeleteItem = item->value;

		/* Присваивание родителю нового сына и изменения родителя сына */
		item->parent->right = item->right;
		item->right->parent = item->parent;
		if (deleteItem->color == 'B') fixDeleting(deleteItem);
		delete deleteItem;
	}
	else if (item->left && item->right == NULL) {
		/* Есть левый сын */

		Node * deleteItem = item;
		int dataDeleteItem = item->value;

		/* Присваивание родителю нового сына и изменения родителя сына */
		item->parent->left = item->left;
		item->left->parent = item->parent;
		if (deleteItem->color == 'B') fixDeleting(deleteItem);
		delete deleteItem;
	}
	else {
		/* Есть и правый, и левый ребёнок */

		Node * replaceItem = item; // запоминаю удаляемый элемент, значение которого будет заменено на значение следующего элмента
		Node * nextItem = item->right; // элемент хранящий узел с значением следующего элмента 

		while (nextItem->left) nextItem = nextItem->left; // если есть левая ветвь, то ищем в ней следующий элемент
		int dataDeleteItem = item->value; // запоминаем значение удаляемого элемента

		if (nextItem->right) {
			/* Есть правая ветвь */

			if (nextItem->parent->left == nextItem) {
				/* nextItem в левой ветви  */

				/* Присваиваем левому сыну родителя правой поддерево  nextItem*/
				nextItem->parent->left = nextItem->right;
				nextItem->right->parent = nextItem->parent;
			}
			else {
				/* nextItem в левой ветви, т.е у nextItem нет левого сына, иначе бы это был следующим элементом */

				/* Присваиваем левому сыну родителя правой поддерево  nextItem*/
				nextItem->parent->right = nextItem->right;
				nextItem->right->parent = nextItem->parent;
			}
			replaceItem->value = nextItem->value; // "удаляемому" узлу присваиваем новое значение
			if (nextItem->color == 'B') fixDeleting(nextItem);
			delete nextItem; // удаляем следующий элемент по значению после удаляемого
		}
		else {
			/* Нет правой ветви */

			if (nextItem->color == 'B') fixDeleting(nextItem);

			/* Удаляем как узел без сыновей */
			if (nextItem->parent->left == nextItem) {
				nextItem->parent->left = NULL;
			}
			else {
				nextItem->parent->right = NULL;
			}
			replaceItem->value = nextItem->value; // "удаляемому" узлу присваиваем новое значение
			
			delete nextItem;
		}
	}
}

void RedBlackTree::fixDeleting(Node * n)
{
	while (n != root && n->color == 'B') {
		/* Пока рассматриваемый узёл чёрный и не корень */

		if (n == n->parent->left) {
			/* Рассматриваемый узел левый ребёнок */

			Node * brother = n->parent->right; // запоминаем брата
			if (brother && brother->color == 'R') {
				/* Брат красный */

				brother->color = 'B';
				n->parent->color = 'R';
				leftRotate(n->parent);
				//brother = n->parent->right;
			}
			if (brother->left &&  brother->right && brother->left->color == 'B' && brother->right->color == 'B') {
				/* у брата чёрный дети */

				brother->color = 'R';
				//n = n->parent;
			}
			else {
				/* У брата есть красные дети */

				if (brother->right && brother->right->color == 'B') {
					/* Правый ребёнок чёрный */

					brother->left->color == 'B';
					brother->color = 'R';
					rightRotate(brother);
					//brother = n->parent->right;
				}
			}
			brother->color = n->parent->color;
			n->parent->color = 'B';
			if (brother->right) brother->right->color = 'B';
			leftRotate(brother->parent);
			n = root;
		}
		else {
			/* Рассматриваемый узел правый ребёнок */

			Node * brother = n->parent->left;
			if (brother && brother->color == 'R') {
				/* Брат красный */

				brother->color = 'B';
				n->parent->color = 'R';
				rightRotate(n->parent);
				//brother = n->parent->left;
			}
			if (brother->right && brother->left && brother->right->color == 'B' && brother->left->color == 'B') {
				/* у брата чёрный дети */

				brother->color = 'R';
				n = n->parent;
			}
			else {
				/* у брата чёрный дети */

				if (brother->left && brother->left->color == 'B') {
					/* Правый ребёнок чёрный */

					brother->right->color == 'B';
					brother->color = 'R';
					leftRotate(brother);
					//brother = n->parent->left;
				}
				brother->color = n->parent->color;
				n->parent->color = 'B';
				if (brother->left) brother->left->color = 'B';
				rightRotate(brother->parent);
				n = root;
			}
		}
	}
	n->color = 'B';
}
