// Graph.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "GraphActions.h"
#include "Vertex.h" 
#include "Edge.h"

int main()
{
	GraphActions graph;
	/* Создание вершин */
	Vertex & v1 = *new Vertex(1);
	Vertex & v2 = *new Vertex(2);
	Vertex & v3 = *new Vertex(3);
	Vertex & v4 = *new Vertex(4);
	Vertex & v5 = *new Vertex(5);
	Vertex & v6 = *new Vertex(6);
	Vertex & v7 = *new Vertex(7);
	Vertex & v8 = *new Vertex(8);

	/* Добавления вершин в общий список */
	graph.addVertex(v1);
	graph.addVertex(v2);
	graph.addVertex(v3);
	graph.addVertex(v4);
	graph.addVertex(v5);
	graph.addVertex(v6);
	graph.addVertex(v7);
	graph.addVertex(v8);

	/* Установление связей (рёбер) между вершинами */
	graph.addEdge(v1, v2);
	graph.addEdge(v1, v3);
	graph.addEdge(v3, v8);
	graph.addEdge(v2, v4);
	graph.addEdge(v2, v5);
	graph.addEdge(v4, v6);
	graph.addEdge(v5, v6);
	graph.addEdge(v5, v7);
	graph.addEdge(v6, v7);

	graph.BFS(graph, v1);
	cout << "Path: ";
	graph.getPath(graph, v1, v7);

	graph.DFS(graph);

}