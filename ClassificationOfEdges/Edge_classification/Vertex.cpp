#include "pch.h"
#include "Vertex.h"


Vertex::Vertex() : distance(-1), color('W'), predecessor(nullptr), number(-1), finish(0)
{
}

Vertex::Vertex(int number) : distance(0), color('W'), predecessor(nullptr), number(number), finish(0)
{
}

Vertex::Vertex(std::string str) : distance(0), color('W'), predecessor(nullptr), str(str), finish(0)
{
}


Vertex::~Vertex()
{
}
