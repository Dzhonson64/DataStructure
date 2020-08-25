#pragma once
class Person
{
public:
	std::string name;
	std::string surname;
	std::string phone;
	Person * nextItem;
	Person();
	Person(std::string name, std::string surname, std::string phone);
	~Person();
	void getPerson();
};

