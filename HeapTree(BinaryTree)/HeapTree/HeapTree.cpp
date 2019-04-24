#include "pch.h"
#include "HeapTree.h"


HeapTree::HeapTree()
{
}


HeapTree::~HeapTree()
{
}


void HeapTree::siftDown(int currentIndex)
{
	int leftIndex;	// ��������� �� ������� �������� ������ ����
	int rightIndex; // ��������� �� ������� �������� ������� ����
	int maxIndex = currentIndex;
	int count = tree.size();
	while (currentIndex < count) {
		
		leftIndex = 2 * currentIndex + 1;	// ��������� ������� ������ ��������
		rightIndex = 2 * currentIndex + 2;	// ��������� ������� ������� ��������

		if (leftIndex < count && tree[leftIndex] > tree[maxIndex]) { // ���� �� ����� �� ������� � ������ ���� ������� ������ ��� i-��, �� ����������� maxIndex
			maxIndex = leftIndex;
			
		}
		if (rightIndex < count && tree[rightIndex] > tree[maxIndex]) { // ���� �� ����� �� ������� � ��� � ������ ����� ������� ������ ��� i-��, �� ����������� maxIndex
			maxIndex = rightIndex;
		}
		if (maxIndex == currentIndex) { // ���� ��� ��� ���� ������ i-��� ��������, �� ���������� ����
			break;
		}
		/* ������ ������� ��������� */
		int temp = tree[currentIndex];
		tree[currentIndex] = tree[maxIndex];
		tree[maxIndex] = temp;

		currentIndex = maxIndex;
	}
}


void HeapTree::siftUp(int i)
{
	while (i > 0 && tree[i] > tree[i / 2]) { // ���� ������ �� ���������� � �������� ������ ���������������� ��������
		swap(tree[i], tree[i / 2]);			 // ������ �� �������
		i = i / 2;
	}
}

void HeapTree::insert(int num)
{
	tree.push_back(num);						// �������� ������� � ������

	int currentIndex = tree.size() - 1;			// ���������� ������ ���������� ��������
	int parentIndex = (currentIndex - 1) / 2;	// ���������� ��� ��������

	while (currentIndex > 0 && tree[parentIndex] < tree[currentIndex]) { // ���� ������ �� ���������� � �������� ������ ���������������� ��������
		/* ������ �� ������� */
		int temp = tree[currentIndex];
		tree[currentIndex] = tree[parentIndex];
		tree[parentIndex] = temp;

		currentIndex = parentIndex;				// ������������� ��������� ������ ���������� ������� �� ����� ��������
		parentIndex = (currentIndex - 1) / 2;	// ������ ���� �������� ������������ ������ ��������
	}
	// ��� ������ while ����� �������� �� siftUp(tree.size());
}

void HeapTree::siftDownRecursively(int currentIndex)
{
	int leftIndex = 2 * currentIndex + 1;
	int rightIndex = 2 * currentIndex + 2;
	int maxIndex = currentIndex;
	if (leftIndex < tree.size() && tree[leftIndex] >  tree[currentIndex]) {
		maxIndex = leftIndex;
	}
	if (rightIndex < tree.size() && tree[rightIndex] >  tree[currentIndex]) {
		maxIndex = rightIndex;
	}
	if (currentIndex == maxIndex) {
		return;
	}
	siftDownRecursively(maxIndex);

}

void HeapTree::siftUpRecursively(int currentIndex)
{
	if (currentIndex > 0 && tree[currentIndex] > tree[currentIndex / 2]) {
		swap(tree[currentIndex], tree[currentIndex / 2]); // ������ �� �������
		currentIndex = currentIndex / 2;
	}
	return;
}

void HeapTree::insertRecursively(int currentIndex)
{
	tree.push_back(currentIndex);		// �������� ������� � ������
	siftUpRecursively(tree.size() - 1); // ������ ������ �����
}

int HeapTree::top()
{
	if (!tree.empty()) {
		return tree.front();
	}
	else {
		cout << "List is empty" << endl;
	}
	
}

int HeapTree::pop()
{
	int result = tree[0];				// ���������� �������� �������
	tree[0] = tree[tree.size() - 1];	// �� ����� ��������� ������ ��������� ������� �������
	//tree.erase(tree.begin() + (tree.size() - 1));
	tree.pop_back();	// ������� ��������� ������ �������
	siftDown(0);		// ������ ������ ������ ����� ����
	return result;		// ���������� ������ ������
}
