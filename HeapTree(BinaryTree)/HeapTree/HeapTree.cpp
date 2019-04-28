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
	int leftIndex;	// указатель на позицию элемента влевом узле
	int rightIndex; // указатель на позицию элемента вправом узле
	int maxIndex = currentIndex;
	int count = tree.size();
	while (currentIndex < count) {
		
		leftIndex = 2 * currentIndex + 1;	// вычисляем позицию левого элемента
		rightIndex = 2 * currentIndex + 2;	// вычисляем позицию правого элемента

		if (leftIndex < count && tree[leftIndex] > tree[maxIndex]) { // если не вышли за границу и влевом узле элемент больше чем i-ый, то присваиваем maxIndex
			maxIndex = leftIndex;
			
		}
		if (rightIndex < count && tree[rightIndex] > tree[maxIndex]) { // если не вышли за границу и ещё и впрвом уезле элемент больше чем i-ый, то присваиваем maxIndex
			maxIndex = rightIndex;
		}
		if (maxIndex == currentIndex) { // если все два сына меньше i-ого элемента, то прекращаем цикл
			break;
		}
		/* делаем заменту элементов */
		int temp = tree[currentIndex];
		tree[currentIndex] = tree[maxIndex];
		tree[maxIndex] = temp;

		currentIndex = maxIndex;
	}
}


void HeapTree::siftUp(int i)
{
	while (i > 0 && tree[i] > tree[i / 2]) { // пока массив не закончился и родитель меньше рассматриваемого элемента
		swap(tree[i], tree[i / 2]);			 // меняем их местами
		i = i / 2;
	}
}

void HeapTree::insert(int num)
{
	tree.push_back(num);						// добавлем элемент в массив

	int currentIndex = tree.size() - 1;			// запоминаем индекс последнего элемента
	int parentIndex = (currentIndex - 1) / 2;	// запоминаем его родителя

	while (currentIndex > 0 && tree[parentIndex] < tree[currentIndex]) { // пока массив не закончился и родитель меньше рассматриваемого элемента
		/* меняем их местами */
		int temp = tree[currentIndex];
		tree[currentIndex] = tree[parentIndex];
		tree[parentIndex] = temp;

		currentIndex = parentIndex;				// рассматриваем элементом теперь становится элемент на месте родителя
		parentIndex = (currentIndex - 1) / 2;	// теперь берём родителя относительно нового элемента
	}
	// или вместо while можно заменить на siftUp(tree.size());
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
		swap(tree[currentIndex], tree[currentIndex / 2]); // меняем их местами
		currentIndex = currentIndex / 2;
	}
	return;
}

void HeapTree::insertRecursively(int currentIndex)
{
	tree.push_back(currentIndex);		// добавлем элемент в массив
	siftUpRecursively(tree.size() - 1); // делаем просев вверх
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
	int result = tree[0];				// запоминаем корневой элемент
	tree[0] = tree[tree.size() - 1];	// на место корневого ставим последний элемент массива
	//tree.erase(tree.begin() + (tree.size() - 1));
	tree.pop_back();	// удаляем последний элемет массива
	siftDown(0);		// делаем просев нового корня вниз
	return result;		// возвращяем старый корень
}
