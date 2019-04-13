// AVLTree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
struct AVLNode {
	int data;
	AVLNode * leftSon;
	AVLNode * rightSon;
	AVLNode * parent;
	int balance;
};
void treeRotateR(AVLNode *& node, AVLNode * item); // Добавление в левое поддерево левого сына опорного узла
void treeRotateL(AVLNode *& node, AVLNode * item); // Добавление в правое поддерево правое сына опорного узла
void treeRotateLR(AVLNode *& node, AVLNode * item); // Большой правый поворот
void treeRotateRL(AVLNode *& node, AVLNode * item); // Большой левый поворот

AVLNode * treeSuccessorNode(AVLNode *& node, AVLNode * item);
AVLNode * minItem(AVLNode * node);
AVLNode * maxItem(AVLNode * node);

void deleteNode(AVLNode *& node, AVLNode * item);

void show(AVLNode * node);
int insert(AVLNode *& node, int k);
int main()
{
	srand(time(NULL));
	AVLNode * tree = NULL;
	for (int i = 0; i < 10; i++) {
		int r = rand() % 100;
		std::cout << r << std::endl;
		insert(tree, r);
	}
	deleteNode(tree, tree->rightSon);
	show(tree);
}

AVLNode * minItem(AVLNode * node) { /* На вход подается дерево T, и возвращается узел с минимальным значением ключа в дереве. */
	while (node->leftSon != NULL) {
		node = node->leftSon;
	}
	return node;
}
AVLNode * maxItem(AVLNode * node) {
	while (node->rightSon != NULL) {
		node = node->rightSon;
	}
	return node;
}
AVLNode * treeSuccessorNode(AVLNode *& node, AVLNode * item) {
	if (item->rightSon != NULL) { /* Если у узла есть правое поддерево, то возвращаем САМЫЙ ЛЕВЫЙ узел ПРАВОГО поддерева. */
		return minItem(item->rightSon);
	}
	/* Если у узла нет правого поддерева, то поднимаемся по родителям наверх, пока не найдем того, для которого рассматриваемый
	узел – левый сын. */
	AVLNode * parent = item->parent;
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
/*
	item - узел у которого нарушен balance
	P и Q - поддеревья

	Вид поддерева, которое принимает ф-ия:
	 item
	/	\
   P 	rightSonItem
			/   \
		  Q 	созданный недавно элем., из-за которого нарушился баланс

	Вид поддерева, которое возвращает ф-ия:
		rightSonItem
		/			\
	item			созданный недавно элем.
	/  \
   P	Q
*/

void treeRotateL(AVLNode *& node, AVLNode * item) {
	AVLNode * rightSonItem = item->rightSon;

	/* Присваиваем правому поддереву левое поддерево rightSonItem и далаем item его родителем */
	item->rightSon = rightSonItem->leftSon;
	if (rightSonItem->leftSon != NULL) {
		rightSonItem->leftSon->parent = item;
	}

	/* Делаем левым поддеревом rightSonItem - узел item с его поддеревьями и перенастариваем указ. на родителя */
	rightSonItem->leftSon = item;
	rightSonItem->parent = item->parent;
	if (item->parent) { // если у item были родители, то находим в каком поддереве находился item, относительно его родителя и в ту ветку ставим узел rightSonItem
		if (item->parent->leftSon == item) {
			item->parent->leftSon = rightSonItem;
		}
		else {
			item->parent->rightSon = rightSonItem;
		}
	}
	else { // иначе, если нет родителей у item, то это был корень дерева и тогда корень дерева вместо item становится rightSonItem
		node = rightSonItem;
	}

	/* Делаем для item родителя rightSonItem */
	item->parent = rightSonItem;


	/*Расстановка баланса*/
	if (item->balance == 2 && rightSonItem->balance == 1) {
		item->balance = 0;
		rightSonItem->balance = 0;
	}
	else if (item->balance == 2 && rightSonItem->balance == 0) { 
		//std::cout << "Entered in RoteL with balance 2, 0" << std::endl;
		item->balance = 1;
		rightSonItem->balance = -1;
	}
}



/*
	item - узел у которого нарушен balance
	P и Q - поддеревья

	Вид поддерева, которое принимает ф-ия:
			item
			/	\
	leftSonItem	 P
		/	\
созданный	Q
недавно
элем.

	Вид поддерева, которое возвращает ф-ия:
		leftSonItem
		/			\
созданный недавно	item
	элем.			/	\
					Q	 P
*/

void treeRotateR(AVLNode *& node, AVLNode * item) {
	AVLNode * leftSonItem = item->leftSon;

	/* Присваиваем правому поддереву левое поддерево leftSonItem и далаем item его родителем */
	item->leftSon = leftSonItem->rightSon;
	if (leftSonItem->rightSon != NULL) {
		leftSonItem->rightSon->parent = item;
	}

	/* Делаем правым поддеревом leftSonItem - узел item с его поддеревьями и перенастариваем указ. на родителя */
	leftSonItem->rightSon = item;
	leftSonItem->parent = item->parent;
	if (item->parent) { // если у item были родители, то находим в каком поддереве находился item, относительно его родителя и в ту ветку ставим узел rightSonItem
		if (item->parent->leftSon == item) {
			item->parent->leftSon = leftSonItem;
		}
		else {
			item->parent->rightSon = leftSonItem;
		}
	}
	else { // иначе, если нет родителей у item, то это был корень дерева и тогда корень дерева вместо item становится rightSonItem
		node = leftSonItem;
	}

	/* Делаем для item родителя rightSonItem */
	item->parent = leftSonItem;


	/*Расстановка баланса*/
	if (item->balance == -2 && leftSonItem->balance == -1) {
		item->balance = 0;
		leftSonItem->balance = 0;
	}
	else if (item->balance == -2 && leftSonItem->balance == 0) {
		item->balance = -1;
		leftSonItem->balance = 1;
	}
}



/*
	item - узел у которого нарушен balance
	P, Q, R, S - поддеревья

	Вид поддерева, которое принимает ф-ия:
				item
				/	\
			leftSon	  P
			/	 \
			S	leftSon->rightSon
					/		\
					R		 Q

	Вид поддерева, которое возвращает ф-ия treeRotateL():
				item
				/	\
leftSon->rightSon	  P
		/	 \
	leftSon	  Q
	 /	 \
	S	  R

	Вид поддерева, которое возвращает ф-ия treeRotateR():
			leftSon->rightSon
			/			\
		leftSon			item
		/	\			  /	  \
	   S	 R			 Q	   P
*/

void treeRotateLR(AVLNode *& node, AVLNode * item) {
	/* Запоминаем старые балансы узлов, чтобы относительно них сделать новые былансы*/
	int balanceA = item->balance;
	int balanceB = item->leftSon->balance;
	int balanceC = item->leftSon->rightSon->balance;

	treeRotateL(node, item->leftSon);
	treeRotateR(node, item);

	/*Расстановка баланса*/

	item->balance = 0;
	item->parent->balance = 0;
	item->parent->leftSon->balance = 0;
	if (balanceA == -2 && balanceB == 1 && balanceC == -1) {
		item->balance = 1;
		item->parent->balance = 0;
		item->parent->leftSon->balance = 0;
	}
	else if (balanceA == -2 && balanceB == 1 && balanceC == 1) {
		item->balance = 0;
		item->parent->balance = 0;
		item->parent->leftSon->balance = -1;
	}
}


/*
	item - узел у которого нарушен balance
	P, Q, R, S - поддеревья

	Вид поддерева, которое принимает ф-ия:
				item
				/	\
				P	rightSon
					/		\
			rightSon->left	 S
				/		\
			   Q		 R

	Вид поддерева, которое возвращает ф-ия treeRotateR():
				item
				/	\
				P	rightSon->left
					/		\
					Q		 rightSon
								/	\
								R	 S

	Вид поддерева, которое возвращает ф-ия treeRotateL():
			rightSon->left
			/			\
		item			rightSon
		/	\			  /	  \
	   P	 Q			 R	   S
*/

void treeRotateRL(AVLNode *& node, AVLNode * item) {

	/* Запоминаем старые балансы узлов, чтобы относительно них сделать новые былансы*/
	int balanceA = item->balance;
	int balanceB = item->rightSon->balance;
	int balanceC = item->rightSon->leftSon->balance;
	treeRotateR(node, item->rightSon);
	treeRotateL(node, item);

	item->balance = 0;
	item->parent->balance = 0;
	item->parent->rightSon->balance = 0;
	/*Расстановка баланса*/
	if (balanceA == 2 && balanceB == -1 && balanceC == 1) {
		item->balance = -1;
		item->parent->balance = 0;
		item->parent->rightSon->balance = 0;
	}
	else if (balanceA == 2 && balanceB == -1 && balanceC == -1) {
		item->balance = 0;
		item->parent->balance = 0;
		item->parent->rightSon->balance = 1;
	}
}

int insert(AVLNode *& node, int k) {
	AVLNode * item = node;				// нынешний элемент узла
	AVLNode * itemParent = NULL;		// предыдущий элемент узла (родитель)
	if (node == nullptr) {				// если корень дерева пустой, то создаём его и обнуляем его родителя и его сыновей и баланс
		node = new AVLNode;
		node->data = k;
		node->leftSon = NULL;
		node->rightSon = NULL;
		node->parent = NULL;
		node->balance = 0;

	}
	else {
		while (item) { // спускаемся до нужного элемента
			itemParent = item;
			if (k < item->data) { // если добаляемый элемент меньше данных узла, то идём в левую ветвь
				item = item->leftSon;
			}
			else if (k > item->data) { // иначе в правую ветвь
				item = item->rightSon;
			}
			else {
				return 0;
			}
		}
		item = new AVLNode;						// найдя нужное место, выдяеляем там память под новый узел
		item->data = k;							// даём значение
		item->parent = itemParent;				// присваиваем родителя
		item->leftSon = item->rightSon = NULL;	// обнуляем указатели листа
		item->balance = 0;						// инициализируем баланс

		/*Узнаём в какой ветки относительно родителя наш элемент с ключом k и присваиваем соответствующий указатель родителя на наш элем.*/
		if (k < itemParent->data) {
			itemParent->leftSon = item;
		}
		else {
			itemParent->rightSon = item;
		}
		/*
			Постепенно поднимемся наверх и изменяем баланс родителей
			Если баланс отрицательный - левое поддерево больше правового
			Если баланс положительный - правое поддерево больше правового
		*/
		while (item->parent) {
			if (item->data < item->parent->data) {	// если вернулись с левого листа, то уменьшаем баланс родителя 
				item->parent->balance--;
			}
			else {									// если вернулись с левого листа, то увеличиваем баланс родителя 
				item->parent->balance++;
			}


			if (item->parent->balance == 0) { // если баланс не нарушен, то перестраивать не нужно
				break;
			}
			// иначе, если новый создный узел находится в самом низу правого поддерева  
			else if (item->parent->balance == 2 && item->balance == 1 /*|| item->parent->balance == 2 && item->balance == 0*/) {
				treeRotateL(node, item->parent);
				break;
			}
			// иначе, если новый создный узел находится в самом низу левого поддерева
			else if (item->parent->balance == -2 && item->balance == -1 /*|| item->parent->balance == 2 && item->balance == 0*/) {
				treeRotateR(node, item->parent);
				break;
			}
			else  if ( // если новый созданный узел находится или внизу слева или узел уже имеет хотя бы один лист 
				(item->parent->balance == 2 && item->balance == -1 && item->leftSon->balance == 0 ||
					item->parent->balance == 2 && item->balance == -1 && item->leftSon->balance == -1 ||
					item->parent->balance == 2 && item->balance == -1 && item->leftSon->balance == 1) &&
				item->leftSon
				)
			{
				treeRotateRL(node, item->parent);
				break;
			}
			else if ( // если новый созданный узел находится или внизу справа или узел уже имеет хотя бы один лист 
				(item->parent->balance == -2 && item->balance == 1 && item->rightSon->balance == 0 ||
					item->parent->balance == -2 && item->balance == 1 && item->rightSon->balance == -1 ||
					item->parent->balance == -2 && item->balance == 1 && item->rightSon->balance == 1) &&
				item->rightSon
				)
			{
				treeRotateLR(node, item->parent);
				break;
			}
			if (item->parent) { // если есть родитель есть, то переходим к нему для изменения его баланса
				item = item->parent;
			}
		}
	}
	return 1;
}

void deleteNode(AVLNode *& node, AVLNode * item) {
	AVLNode * removeNode = item;
	
	if (item->leftSon == NULL || item->rightSon == NULL) { // Если у узла есть хотя бы 1 потомок или нет ниодного
		AVLNode * tempParentRemoveNode = removeNode; // создаём указатель, для переход по узлам
		/* Пробегаемся от узла вверх по родителям и если мы пришли к родителя с левой ветки, то прибаляем 1 у родителя баланс, иначе вычитаем */
		while (tempParentRemoveNode->parent) { 
			if (tempParentRemoveNode->parent->leftSon == tempParentRemoveNode) {
				tempParentRemoveNode->parent->balance++;
			}
			else {
				tempParentRemoveNode->parent->balance--;
			}
			/* 
				Если после вычитания или прибаления баланс у родителя стал 1 или -1, т.е. у родителя сохранилась одна ветка с потомками,
				то дальше балан не меняем, т.к. о в общем не изменился
			*/
			if (tempParentRemoveNode->parent->balance == 1 || tempParentRemoveNode->parent->balance == -1) {
				break;
			}
			
			else if (tempParentRemoveNode->parent->balance == 2) {
				if (tempParentRemoveNode->parent->rightSon->balance == 1 || tempParentRemoveNode->parent->rightSon->balance == 0) {
					treeRotateL(node, tempParentRemoveNode->parent); // если баланс у родителя 2, а у прового сына родителя есть большая правая ветка или всё в балансе, то делаем поворот влево
				}else if (tempParentRemoveNode->parent->rightSon->balance == -1) {
					/* 
						если баланс у родителя 2, а у прового сына родителя есть большая левая ветка, т.е. стал вид

							A
						    \
							  B
							/	
							C	
						то делаем большой левый поворот
					*/
					treeRotateRL(node, tempParentRemoveNode->parent); 
				}

				/*
					Если после поворота балан узла стал 0, то мы поднимаемся на два узла вверх, от удаляемого, чтобы уже от корня поддерева,
					которое повернули начать восстанавливать баланс, т.к. при повоте в этой части поддерева баланас был восстановлен
				*/
				if (tempParentRemoveNode->balance == 0) {
					tempParentRemoveNode = tempParentRemoveNode->parent->parent;
					while (tempParentRemoveNode->parent) {
						if (tempParentRemoveNode->parent->rightSon == tempParentRemoveNode) {
							tempParentRemoveNode->parent->balance--;
						}
						else {
							tempParentRemoveNode->parent->balance++;
						}
						tempParentRemoveNode = tempParentRemoveNode->parent;
					}
				}
				break;
			}
			/* Если узел -2, то практически те же самые действия, что и для 2 */
			else if (tempParentRemoveNode->parent->balance == -2) {
				if (tempParentRemoveNode->parent->leftSon->balance == -1) {
					treeRotateR(node, tempParentRemoveNode->parent);
				}else if (tempParentRemoveNode->parent->leftSon->balance == 1 || tempParentRemoveNode->parent->rightSon->balance == 0) {
					treeRotateLR(node, tempParentRemoveNode->parent);
				}

				if (tempParentRemoveNode->balance == 0) {
					tempParentRemoveNode = tempParentRemoveNode->parent->parent;
					while (tempParentRemoveNode->parent) {
						if (tempParentRemoveNode->parent->rightSon == tempParentRemoveNode) {
							tempParentRemoveNode->parent->balance--;
						}
						else {
							tempParentRemoveNode->parent->balance++;
						}
						tempParentRemoveNode = tempParentRemoveNode->parent;
					}
				}
				break;
			}
			tempParentRemoveNode = tempParentRemoveNode->parent;
		}
		/* Если узел - лист, то его просто удалем и делаем указатеь на ветвь, где был удаляемы узел NULL */
		if (item->leftSon == NULL && item->rightSon == NULL) {
			if (item->parent->leftSon == item) {
				item->parent->leftSon = NULL;
			}
			else {
				item->parent->rightSon = NULL;
			}
		}
		else if (item->leftSon != NULL && item->rightSon == NULL) { // Если у узла есть один сын (левый)
			item->leftSon->parent = item->parent;	// деляем обзятельно перелинковку указателей на родителей (родитель левого сына элемента item должен быть не item, а родитель item)
			/* далаем потомком родителя слеующий элемент после удалаямого. И ссылкаемся на ту ветку, в которой находился удаляем узел */
			if (item->parent->leftSon == item) {
				item->parent->leftSon = item->leftSon;
			}
			else {
				item->parent->rightSon = item->leftSon;
			}
		}
		else if (item->leftSon == NULL && item->rightSon != NULL) { // Если у узла есть один сын (правый)

			item->rightSon->parent = item->parent;	// деляем обзятельно перелинковку указателей на родителей (родитель левого сына элемента item должен быть не item, а родитель item)
			if (item->parent->leftSon == item) {
				item->parent->leftSon = item->rightSon;
			}
			else {
				item->parent->rightSon = item->rightSon;
			}

		}



	}
	else {
		/*
			Если у узла два сына, то удаляемым узлом будет его последователь. У удаляемого узла может быть только правый сын, потому что
			это самый левый элемент правого поддерева узла. Таким образом, у удаляемого узла в любом случае только один сын.
		*/


		removeNode = minItem(item->rightSon);	// следующий элемент после item (это для узла с двумя листьями - MIN элем. в правом поддереве)
					
		AVLNode * tempParentRemoveNode = removeNode;  // создаём новый указатель, для прохода по дереву от MIN элем. в правом поддереве
		if (tempParentRemoveNode->parent) {
			/* Пока есть родитель, то если мы пришли из левого поддерева, то родителя прибавляем 1, иначе вычитаем 1 */
			while (tempParentRemoveNode->parent) {
				if (tempParentRemoveNode->parent->rightSon == tempParentRemoveNode) {
					tempParentRemoveNode->parent->balance--;
				}
				else {
					tempParentRemoveNode->parent->balance++;
				}
				/* 
					Если после вычитания или прибаления баланс у родителя стал 1 или -1,
					т.е. у родителя сохранилась одна ветка с потомками, то дальше балан не меняем, т.к. о в общем не изменился
				*/
				if (tempParentRemoveNode->parent->balance == 1 || tempParentRemoveNode->parent->balance == -1) {
					break;
				}

				if (tempParentRemoveNode->parent->balance == 2) {
					if (tempParentRemoveNode->parent->rightSon->balance == 1 || tempParentRemoveNode->parent->rightSon->balance == 0) {
						treeRotateL(node, tempParentRemoveNode->parent); // если баланс у родителя 2, а у прового сына родителя есть большая правая ветка или всё в балансе, то делаем поворот влево
					}else if (tempParentRemoveNode->parent->rightSon->balance == -1) {
						/*
						если баланс у родителя 2, а у прового сына родителя есть большая левая ветка, т.е. стал вид

							A
							\
							  B
							/
							C
						то делаем большой левый поворот
					*/
						treeRotateRL(node, tempParentRemoveNode->parent);
					}

					/*
						Если после поворота балан узла стал 0, то мы поднимаемся на два узла вверх, от удаляемого, чтобы уже от корня поддерева,
						которое повернули начать восстанавливать баланс, т.к. при повоте в этой части поддерева баланас был восстановлен
					*/
					tempParentRemoveNode = tempParentRemoveNode->parent->parent;
					if (tempParentRemoveNode->balance == 0) {
						while (tempParentRemoveNode->parent) {
							if (tempParentRemoveNode->parent->rightSon == tempParentRemoveNode) {
								tempParentRemoveNode->parent->balance--;
							}
							else {
								tempParentRemoveNode->parent->balance++;
							}
							tempParentRemoveNode = tempParentRemoveNode->parent;
						}
					}

					break;
				}
				/* Если узел -2, то практически те же самые действия, что и для 2 */
				else if (tempParentRemoveNode->parent->balance == -2) {
					if (tempParentRemoveNode->parent->leftSon->balance == -1 || tempParentRemoveNode->parent->leftSon->balance == 0) {
						treeRotateR(node, tempParentRemoveNode->parent);
					}else if (tempParentRemoveNode->parent->leftSon->balance == 1) {
						treeRotateLR(node, tempParentRemoveNode->parent);
					}

					tempParentRemoveNode = tempParentRemoveNode->parent->parent;
					if (tempParentRemoveNode->balance == 0) {
						while (tempParentRemoveNode->parent) {
							if (tempParentRemoveNode->parent->rightSon == tempParentRemoveNode) {
								tempParentRemoveNode->parent->balance--;
							}
							else {
								tempParentRemoveNode->parent->balance++;
							}
							tempParentRemoveNode = tempParentRemoveNode->parent;
						}
					}
					break;
				}
				tempParentRemoveNode = tempParentRemoveNode->parent;
			}
		}
		item->data = removeNode->data; // заменяем данные с элем., который идёт после item
		// если min элем. есть правое поддерево
		if (removeNode->rightSon != NULL) {

			// Узнаём, в какой ветви находится следующий элемент после item, по сравнению с его родителем, чтобы эту ветвь сделать NULL, для дальней корректной работы

			// Если данные родителя  min элем. больше данных самого  min элем. (т.е. min элем. в левой ветви родителя)

			if (removeNode->parent->data > removeNode->data) {
				removeNode->parent->leftSon = removeNode->rightSon;		// делаем указатель родителя его на левого сына - правое поддерево min элем. (т.к. мы точно знаем, что левого поддерева нет, т.к. это min элемент в левом поддереве)
				removeNode->rightSon->parent = removeNode->parent;		// деляем перелинковку указателей на родителей (родитель правого поддерева, относ. min элем. теперь не min элем, а родитель min элем.)
			}

			// min элем. в правой ветви родителя (т.е. этот элемент следующий в правой ветви относительно удаляемого узла)
			else {
				removeNode->parent->rightSon = removeNode->rightSon;	// указатель родителя его на правого сына - правое поддерево min элем.
				removeNode->rightSon->parent = removeNode->parent;		// деляем перелинковку указателей на родителей (родитель прового поддерева, относ. min элем. теперь не min элем, а родитель min элем.)

			}
		}

		// если нет правого поддерева, то узнаём в какой ветви относ. родителя находился min. элем. и указатель на эту ветвь делаем NULL для дальнейшей корректной работы
		else {
			if (removeNode->parent->data > removeNode->data) {
				removeNode->parent->leftSon = NULL;
			}
			else {
				removeNode->parent->rightSon = NULL;
			}
		}
	}

	delete removeNode;									// делаем удаление нужного узла
}



void show(AVLNode *tree) {
	if (tree != NULL)               //Пока не встретится пустое звено
	{
		show(tree->leftSon);               //Рекурсивная функция для вывода левого поддерева
		std::cout << tree->data << " ";
		show(tree->rightSon);               //Рекурсивная функци для вывода правого поддерева
	}
}