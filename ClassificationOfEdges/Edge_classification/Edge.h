#pragma once
#include "Vertex.h"
class Edge
{
public:
	Edge();
	Edge(Vertex & from, Vertex & to);
	~Edge();
	Vertex * from;
	Vertex * to;
	std::string classification;
};

