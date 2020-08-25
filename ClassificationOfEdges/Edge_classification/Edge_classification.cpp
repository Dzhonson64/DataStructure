// Edge_classification.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "string"
#include "Actions.h"

int main()
{

	/* 
		КЛАССИФИКАЦИЯ РЕБЕР (ДУГ) ГРАФА.
			Ребрами дерева (дугами дерева для ориентированного графа) (tree edge) являются ребра, ведущие к вершинам, которые раньше не посещались. Они формируют для заданного графа глубинныйостовный лес. (Это те рёбра, по которым прозодится алгоритм DFS)
				Это всегда ребро с вершиной с белым цветом.

			Обратными ребра/дуги (back edge) - дуги, идущие от потомков к предкам. Дуга, идущая из вершины в саму себя, считается обратной.
				Это всегда ребро с вершиной с серым цветом. Т.к. сервые вершины у нас образуют нисходяще, то получается, что уже образованная серая вершина - это точно предок

			Прямыми рёбрами (forward edge) - дуги, идущие от предков к собственным потомкам, но которые не являются дугами дерева.
				Это всегда ребро с чёрной вершиной, но нужно проверить, является ли не черная вершина предком
			Перекрестными дугами (cross edge) - ребра, соединяющие вершины, не являющиеся ни предками, ни потомками.
				Это всегда ребро с чёрной вершиной, но нужно проверить, не является ли не черная вершина предком
	*/
	Actions dfsGraph;

	/* Создание вершин */
	Vertex & v1 = *new Vertex(1);
	Vertex & v2 = *new Vertex(2);
	Vertex & v3 = *new Vertex(3);
	Vertex & v4 = *new Vertex(4);
	Vertex & v5 = *new Vertex(5);
	Vertex & v6 = *new Vertex(6);
	Vertex & v7 = *new Vertex(7);
	Vertex & v8 = *new Vertex(8);
	Vertex & v9 = *new Vertex(9);

	/* Добавления вершин в общий список */
	dfsGraph.addVertex(v1);
	dfsGraph.addVertex(v2);
	dfsGraph.addVertex(v3);
	dfsGraph.addVertex(v4);
	dfsGraph.addVertex(v5);
	dfsGraph.addVertex(v6);
	dfsGraph.addVertex(v7);
	dfsGraph.addVertex(v8);
	dfsGraph.addVertex(v9);

	/* Установление связей (рёбер) между вершинами */
	dfsGraph.addEdge(v1, v2, false);
	dfsGraph.addEdge(v1, v5, false);
	dfsGraph.addEdge(v1, v8, false);
	dfsGraph.addEdge(v2, v3, false);
	dfsGraph.addEdge(v3, v4, false);
	dfsGraph.addEdge(v4, v2, false);
	dfsGraph.addEdge(v5, v6, false);
	dfsGraph.addEdge(v6, v7, false);
	dfsGraph.addEdge(v6, v8, false);
	dfsGraph.addEdge(v6, v3, false);
	dfsGraph.addEdge(v9, v9, false);


	dfsGraph.DFS_algoritm(dfsGraph);
	dfsGraph.showEdges();
}
