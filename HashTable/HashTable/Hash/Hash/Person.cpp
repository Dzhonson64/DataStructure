#include "pch.h"
#include <iostream>
#include <string>
#include "Person.h"

Person::Person(){

}
Person::Person(std::string name, std::string surname, std::string phone) {
	this->name = name;
	this->surname = surname;
	this->phone = phone;
}


Person::~Person()
{
	if (name != "") {
		delete this;
	}
	
}
void Person::getPerson() {
	std::cout << name << ", " << surname << " " << phone;
}
