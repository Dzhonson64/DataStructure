#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <queue> 
#include <list>
using namespace std;
class GraphActions
{
private:
	Vertex * start; // указатель на стартовую вершину
	int time;
public:
	GraphActions();
	~GraphActions();
	void BFS(GraphActions & graph, Vertex & start); // обход в ширину
	void DFS(GraphActions & graph); // обход в глубину
	void DFS_visit(GraphActions & graph, Vertex & vertex); // обход в глубину
	void getPath(GraphActions & graph, Vertex & begin, Vertex & end);
	queue<Vertex*> * pendingVertexes;				// очередь вершин для дальнейшего их рассмотрения
	list<Vertex*> * vertexes;						// список всех вершин
	list<Edge> * edges;								// список рёбер
	void addVertex(Vertex & v);						// добавление вершины
	void addEdge(Vertex & from, Vertex & to, bool oriented = false); // добавление ребра (oriented = false - граф неориентированный, oriented = true - ориентированный)
	list<Vertex*>* getVertexList(Vertex & vertex);	// получение списка смежности для вершины vertex
};

