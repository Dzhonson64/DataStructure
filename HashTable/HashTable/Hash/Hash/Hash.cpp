// Hash.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "HashTable.h"
#include "Person.h"

int main()
{	HashTable m;
	std::string s_name;
	std::string s_surname;
	std::string s_phone;

	std::string tempName = "Kirill";
	int count = 2;
	for (int i = 0; i < count; i++) {
		std::cout << "Type the name: ";
		std::cin >> s_name;
		std::cout << "Type the surname: ";
		std::cin >> s_surname;
		std::cout << "Type the phone: ";
		std::cin >> s_phone;
		m.push(&s_name, &s_surname, &s_phone);
		
		std::cout << std::endl;
	}
	m.remove(&tempName);
	m.show();
}
