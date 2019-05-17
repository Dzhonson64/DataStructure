#pragma once
#include "Vertex.h"
class Edge
{
private:
	
public:
	Vertex * from; // указатель на вершину из которой выходит ребро
	Vertex * to; // указатель на вершину в которую выходит ребро
	Edge();
	Edge(Vertex & from, Vertex & to);
	~Edge();
	
};

