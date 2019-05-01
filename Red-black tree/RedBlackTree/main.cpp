

#include "pch.h"
#include "RedBlackTree.h"
#include <iostream>

int main()
{
	RedBlackTree t;
	t.insert(2);
	t.insert(1);
	t.insert(4);
	t.insert(3);
	t.insert(5);
	t.insert(6);
	t.insert(7);
	t.insert(8);
	//t.remove(2);
	std::cout << t.search(10)->value << std::endl;
	/*t.insert(11);
	t.insert(1);
	t.insert(100);*/
}

