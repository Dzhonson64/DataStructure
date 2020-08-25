#include "pch.h"
#include "Person.h"


Person::Person(std::string name, std::string surname, int age)
{
	this->name = name;
	this->surname = surname;
	this->age = age;
}


Person::~Person()
{
}
