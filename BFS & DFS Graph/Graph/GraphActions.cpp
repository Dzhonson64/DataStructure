#include "pch.h"
#include "GraphActions.h"
#include "Vertex.h"
#include "Edge.h"
#include <queue> 
#include <list> 
#include <iostream> 

using namespace std;
GraphActions::GraphActions()
{
	start = NULL;
	vertexes = new list<Vertex*>;
	pendingVertexes = new queue<Vertex*>;
	edges = new std::list<Edge>;
	time = 0;
}


GraphActions::~GraphActions()
{
}

void GraphActions::BFS(GraphActions & graph, Vertex & start)
{
	/*
		Если вершина имеет цвет:
		WHITE (W) - вершина ещё не рассматривалась и её нет в очереди для дальнейшего рассмотрения
		GRAY (G) - вершина уже есть в очереди и её повторно ну нужно рассматривать
		BLACK (B) - вершина уже была рассмотрена
	*/

	start.color = 'G';			// делаем начальную вершину "рассматриваемой"
	start.distance = 0;			// расстояние от нач. вершины ноль
	start.predecessor = NULL;	// нет выршины из который мы пришли в нач. вершину
	pendingVertexes->push(&start);	// добавляем её в очередь
	list<Vertex*> * vertexList;		// список смежности 
	while (!pendingVertexes->empty()) {
		/* Очередь не пуста */

		Vertex * temp = pendingVertexes->front();	// берём вершину из очереди
		pendingVertexes->pop();
		vertexList = getVertexList(*temp);			// узнаём для неё список смежности
		
		for (auto i : *vertexList) {
			/* проходимся по всем вершинам из списка смежности */

			if (i->color == 'W') {
				/* Вершина не рассматривалась */

				i->color = 'G';						// делаем её рассматриваемой
				i->distance = temp->distance + 1;	// дистанцию увелиличваем, относительно дистанции "родительской" вершины
				i->predecessor = temp;				// запоминаем из какой вершины мы пришли 
				pendingVertexes->push(i);			// добавляем в очередь вершину из списка смежности
			}
		}
		temp->color = 'B';	// после добавления в очередь всех нерассматриваемых смежных вершин, данную аершину помечаем, как рассмотренную
	}
}

void GraphActions::DFS(GraphActions & graph)
{
	time = 0;
	
	for (auto i : *vertexes) {
		/* Проходимся по всем вершинам графа */
		if (i->color == 'W') {
			/* Вершина белая => переходм к её исследованию */
			DFS_visit(graph, *i);
		}
	}
}

void GraphActions::DFS_visit(GraphActions & graph, Vertex & vertex)
{
	time++;
	vertex.distance = time;
	vertex.color = 'G';									// помечаем её, как иследоваемую
	list<Vertex*> * vertexList = getVertexList(vertex); // запоминаем список смежности для вершины vertex
	for (auto i : *vertexList) {
		/* Проходим по всем смежным вершинам */
		if (i->color == 'W') {
			/* Вершина неисследованная */
			i->predecessor = &vertex;	// запоминаем из какой вершины пришли
			DFS_visit(graph, *i);		// рассматриваем уже смежную вершину
		}
	}
	/* Все смежные вершины серые, то начинаем помечать уже исслдованные вершины */
	vertex.color = 'B';
	time++;
	vertex.finish = time;
}

void GraphActions::getPath(GraphActions & graph, Vertex & begin, Vertex & end)
{
	
	if (&begin == &end) {
		/* Вершина  begin является вершиной end => просто выводим последнюю вершину */
		cout << begin.number << ", ";
	}
	else if (end.predecessor == NULL){
		/* У последней вершины нет вершины, из которой можно придти в вершину end */
		cout << "ERROR: This path is not found" << endl;
	}
	else {
		getPath(graph, begin, *end.predecessor); // переходим на "родельскую" вершину
		cout << end.number << ", ";
	}
}

void GraphActions::addVertex(Vertex & v)
{
	vertexes->push_back(&v);
}

void GraphActions::addEdge(Vertex & from, Vertex & to, bool oriented)
{
	Edge newEdge = Edge(from, to); // создаём ребро из двух вершин: из какой вершины выходит ребро и в какую вершину
	edges->push_back(newEdge);		// добавляем в список рёбер
	if (oriented == false) {
		/* Граф неориетиованный => делаем тоже самое, но меняем местами вершины */
		Edge newEdge_2 = Edge(to, from);
		edges->push_back(newEdge_2);
	}
		
	
}

list<Vertex*> * GraphActions::getVertexList(Vertex & vertex)
{
	list<Vertex*> * result = new list<Vertex*>; // результирующий список смежности для вершины vertex
	for (list<Edge>::iterator i = edges->begin(); i != edges->end(); i++) {
		if (i->from == &vertex) {
			/* В списке рёбер есть вершина vertex, которая указывает вершину, из которой ВЫХОДИТ ребро*/
			result->push_back(i->to); // но в список смежности добавляем вершину, в которой ВХОДИТ ребро
		}
	}
	return result;
}
