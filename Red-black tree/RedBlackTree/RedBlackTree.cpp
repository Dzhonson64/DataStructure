#include "pch.h"
#include "RedBlackTree.h"





void RedBlackTree::rightRotate(Node * n)
{
	Node * oldLeft = n->left; // �������� ��������
	n->left = oldLeft->right; // ������ ������ ���������� ����� ��� ���������������� ����
	if (oldLeft->right) { // ���� ���� � ������ ���� ��������, �� ��� ����� ��������� ���������� �������� ���������������� �������� !!! �������� ������� ����� ������ !!!
		oldLeft->right->parent = n;
	}

	oldLeft->parent = n->parent;
	if (n->parent) { // ���� � �������� ���������������� �������� ��� ��������,�� ���������� � ����� ����� ��� ��, � � ����� ����� ��������� ��������������� �������
		if (n->parent->right == n) {
			n->parent->right = oldLeft;
		}
		else {
			n->parent->left = oldLeft;
		}
	}
	else { // ���� �� ���� ���������, �� ��� ������
		root = oldLeft;
	}

	oldLeft->right = n;
	n->parent = oldLeft;

}

void RedBlackTree::leftRotate(Node * n)
{
	Node * oldRight = n->right; // �������� ��������
	n->right = oldRight->left; // ������ ������ ���������� ����� ��� ���������������� ����
	if (oldRight->left) { // ���� ���� � ������ ���� ��������, �� ��� ����� ��������� ���������� �������� ���������������� �������� !!! �������� ������� ����� ������ !!!
		oldRight->left->parent = n;
	}

	oldRight->parent = n->parent;
	if (n->parent) { // ���� � �������� ���������������� �������� ��� ��������,�� ���������� � ����� ����� ��� ��, � � ����� ����� ��������� ��������������� �������
		if (n->parent->left == n) {
			n->parent->left = oldRight;
		}
		else {
			n->parent->right = oldRight;
		}
	}
	else { // ���� �� ���� ���������, �� ��� ������
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
	Node * n = new Node(value, 'R', NULL, NULL); // ������ ������� ���� �� �������� value
	if (root == NULL) {
		/* ����� ���, �� ������ ������������� �� ����, ������ ������ ������ */
		root = n;
		n->parent = NULL;
	}
	else {
		/* ���� ������ */
		Node * tempParentNode = root; // ��������� �� ��������� ���� tempNode
		Node * tempNode = root; // ����� ��������� �� NULL ����, ���� ����� ��������� ���� n
		while (tempNode != NULL) {
			tempParentNode = tempNode; // ���������� ���������� ����
			if (tempNode->value > n->value) {
				/* �������� ������ �������� ���� */

				tempNode = tempNode->left;
			}
			else if (tempNode->value < n->value){
				/* �������� ������ �������� ���� */

				tempNode = tempNode->right;
			}
			else {
				/* �������� ��� ���� � ������ */
				return;
			}
		}
		n->parent = tempParentNode; // ��������� ������ ���� tempParentNode

		if (tempParentNode->value < n->value) {
			/* �������� ������ ���� ������ */

			tempParentNode->right = n;
		}
		else {
			/* �������� ������ ���� ������ */

			tempParentNode->left = n;
		}
		fixInsertion(n); // ���������, �� �������� �� �������� ������-������� ������
	}
	
}

void RedBlackTree::fixInsertion(Node * n)
{
	Node * dad = NULL;
	Node * grandpa = NULL;
	Node * uncle = NULL;

	while (n != root && n->parent->parent != NULL && n->parent->color == 'R') { // ���� ���� �������
		if (n->parent == n->parent->parent->left) {
			/* ���� ��������� � ����� ����� */

			uncle = n->parent->parent->right;   // ���������� "����" ��������
			dad = n->parent;					// ���������� "����"
			grandpa = n->parent->parent;		// ���������� "�������"

			if (uncle != NULL && uncle->color == 'R') {
				/* ���� ����� ������� ���� */

				/* ������ ������ */
				dad->color = 'B';
				uncle->color = 'B';
				grandpa->color = 'R';
				n = grandpa;			// ��������� ��� ����������� ������������ � �������
			}
			else {
				/* ���� ����� ������ ���� (��� �� ���������� � ���������)*/

				if (n == dad->right){
					/* ������� � ������ ����� */
					n = dad;
					leftRotate(n); // ������ ����� ������, ������������ ��������
				}
				dad->color = 'B';		// ����� ����� ������ ����  - ������
				grandpa->color = 'R';   // ������ ������� - �������
				rightRotate(grandpa);   // ������� ������, ������������ �������
			}
		}
		else {
			/* ���� � ������ ����� */

			uncle = n->parent->parent->left; // ���������� "����" ��������
			dad = n->parent;				 // ���������� "����"
			grandpa = n->parent->parent;	 // ���������� "�������"

			if (uncle != NULL && uncle->color == 'R') {
				/* ���� ����� ������� ���� */

				/* ������ ������ */
				dad->color = 'B';
				uncle->color = 'B';
				grandpa->color = 'R';
				n = grandpa; // �������� ��� ����������� ������������ � �������
			}
			else { 
				/* ���� ����� ������ ���� (��� �� ���������� � ���������)*/

				if (n == dad->left) {
					/* ������� � ����� ����� */

					//n = n->parent;
					rightRotate(dad); // ������ ������ ������, ������������ ��������
				}
				dad->color = 'B';		// ���� - ������
				grandpa->color = 'R';	// ������� - ��������
				leftRotate(grandpa);	// ������ ����� ������� ������������ �������
			}		
		}
	}
	root->color = 'B'; // ��������� ������, ����� ��� ������
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
		/* ����� �������� */

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
		/* ���� � ���������� �������� ��� ������� */

		Node * deleteItem = item; // ��������� ��������� �������
		int dataDeleteItem = item->value; // ��������� �������� ���������� ��������
		if (deleteItem->color == 'B') fixDeleting(deleteItem);
		if (deleteItem->parent) {
			/* �������� ��������� �������� ���� */

			if (deleteItem->parent->left == deleteItem) {
				/* ��������� ������� ����� ����� �������� */
				deleteItem->parent->left = NULL;
			}
			else {
				/* ��������� ������� ������� ����� �������� */
				deleteItem->parent->right = NULL;
			}
		}
		else {	
			/* ��� �������� � ��� ������, �� ��� ������ */
			root = NULL;
		}
		
		delete deleteItem;
	}
	else if (item->left == NULL && item->right) {
		/* ���� ������ ��� */

		Node * deleteItem = item;
		int dataDeleteItem = item->value;

		/* ������������ �������� ������ ���� � ��������� �������� ���� */
		item->parent->right = item->right;
		item->right->parent = item->parent;
		if (deleteItem->color == 'B') fixDeleting(deleteItem);
		delete deleteItem;
	}
	else if (item->left && item->right == NULL) {
		/* ���� ����� ��� */

		Node * deleteItem = item;
		int dataDeleteItem = item->value;

		/* ������������ �������� ������ ���� � ��������� �������� ���� */
		item->parent->left = item->left;
		item->left->parent = item->parent;
		if (deleteItem->color == 'B') fixDeleting(deleteItem);
		delete deleteItem;
	}
	else {
		/* ���� � ������, � ����� ������ */

		Node * replaceItem = item; // ��������� ��������� �������, �������� �������� ����� �������� �� �������� ���������� �������
		Node * nextItem = item->right; // ������� �������� ���� � ��������� ���������� ������� 

		while (nextItem->left) nextItem = nextItem->left; // ���� ���� ����� �����, �� ���� � ��� ��������� �������
		int dataDeleteItem = item->value; // ���������� �������� ���������� ��������

		if (nextItem->right) {
			/* ���� ������ ����� */

			if (nextItem->parent->left == nextItem) {
				/* nextItem � ����� �����  */

				/* ����������� ������ ���� �������� ������ ���������  nextItem*/
				nextItem->parent->left = nextItem->right;
				nextItem->right->parent = nextItem->parent;
			}
			else {
				/* nextItem � ����� �����, �.� � nextItem ��� ������ ����, ����� �� ��� ��� ��������� ��������� */

				/* ����������� ������ ���� �������� ������ ���������  nextItem*/
				nextItem->parent->right = nextItem->right;
				nextItem->right->parent = nextItem->parent;
			}
			replaceItem->value = nextItem->value; // "����������" ���� ����������� ����� ��������
			if (nextItem->color == 'B') fixDeleting(nextItem);
			delete nextItem; // ������� ��������� ������� �� �������� ����� ����������
		}
		else {
			/* ��� ������ ����� */

			if (nextItem->color == 'B') fixDeleting(nextItem);

			/* ������� ��� ���� ��� ������� */
			if (nextItem->parent->left == nextItem) {
				nextItem->parent->left = NULL;
			}
			else {
				nextItem->parent->right = NULL;
			}
			replaceItem->value = nextItem->value; // "����������" ���� ����������� ����� ��������
			
			delete nextItem;
		}
	}
}

void RedBlackTree::fixDeleting(Node * n)
{
	while (n != root && n->color == 'B') {
		/* ���� ��������������� ��� ������ � �� ������ */

		if (n == n->parent->left) {
			/* ��������������� ���� ����� ������ */

			Node * brother = n->parent->right; // ���������� �����
			if (brother && brother->color == 'R') {
				/* ���� ������� */

				brother->color = 'B';
				n->parent->color = 'R';
				leftRotate(n->parent);
				//brother = n->parent->right;
			}
			if (brother->left &&  brother->right && brother->left->color == 'B' && brother->right->color == 'B') {
				/* � ����� ������ ���� */

				brother->color = 'R';
				//n = n->parent;
			}
			else {
				/* � ����� ���� ������� ���� */

				if (brother->right && brother->right->color == 'B') {
					/* ������ ������ ������ */

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
			/* ��������������� ���� ������ ������ */

			Node * brother = n->parent->left;
			if (brother && brother->color == 'R') {
				/* ���� ������� */

				brother->color = 'B';
				n->parent->color = 'R';
				rightRotate(n->parent);
				//brother = n->parent->left;
			}
			if (brother->right && brother->left && brother->right->color == 'B' && brother->left->color == 'B') {
				/* � ����� ������ ���� */

				brother->color = 'R';
				n = n->parent;
			}
			else {
				/* � ����� ������ ���� */

				if (brother->left && brother->left->color == 'B') {
					/* ������ ������ ������ */

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
