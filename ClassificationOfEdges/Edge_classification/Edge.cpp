#include "pch.h"
#include "Edge.h"


Edge::Edge()
{
}

Edge::Edge(Vertex & from, Vertex & to) :from(&from), to(&to)
{
}


Edge::~Edge()
{
}
