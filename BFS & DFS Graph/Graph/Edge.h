#pragma once
#include "Vertex.h"
class Edge
{
private:
	
public:
	Vertex * from; // ��������� �� ������� �� ������� ������� �����
	Vertex * to; // ��������� �� ������� � ������� ������� �����
	Edge();
	Edge(Vertex & from, Vertex & to);
	~Edge();
	
};

