#pragma once
#include <iostream>
class Vertex
{
public:
	Vertex();
	Vertex(int number);
	Vertex(std::string str);
	~Vertex();
	int distance;
	int finish;
	char color;
	int number;
	std::string str;
	Vertex * predecessor;
};

