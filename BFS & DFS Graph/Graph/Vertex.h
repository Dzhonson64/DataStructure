#pragma once
class Vertex
{
private:

public:
	Vertex();
	Vertex(int number);
	~Vertex();
	int distance;			// min расстояние от начальной вершины
	int finish;				// для обхода в глубину
	char color;				// цвет вершины
	int number;				// номер вершины
	Vertex * predecessor;	// указатель на вершину, из которой пришли в данную вершину
};

