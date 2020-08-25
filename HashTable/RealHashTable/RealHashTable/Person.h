#pragma once
#include <iostream>
class Person
{
public:
	Person(std::string name, std::string surname, int age);
	~Person();

	std::string name;
	std::string surname;
	int age;
	
};

