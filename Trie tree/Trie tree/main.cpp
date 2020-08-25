// Trie tree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Trie.h"

int main()
{
	Trie * trie = new Trie();
	trie->add("привет", 50);
	trie->add("мир", 100);
	trie->add("приз", 200);
	trie->add("мирный", 50);
	trie->add("подарок", 200);
	trie->add("проект", 2000);
	trie->add("прапорщик", 200);
	trie->add("правый", 200);
	trie->add("год", 200);
	trie->add("герой", 200);
	trie->add("голубь", 200);

	trie->remove("правый");
	trie->remove("мир");

	std::cout << trie->trySerch("мирный") << std::endl;
}
