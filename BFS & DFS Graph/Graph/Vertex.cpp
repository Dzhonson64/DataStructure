#include "pch.h"
#include "Vertex.h"
#include <iostream>


Vertex::Vertex(): distance(-1), color('W'), predecessor(NULL), number(-1), finish(0)
{
}

Vertex::Vertex(int number) : distance(0), color('W'), predecessor(NULL), number(number), finish(0)
{
}


Vertex::~Vertex()
{
}
