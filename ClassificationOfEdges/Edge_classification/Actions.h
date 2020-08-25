#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <queue> 
#include <list>
#include <map>
using namespace std;
class Actions
{
private:
	Vertex * start;
	int time;	// время прохождения графа, отоносительно него узнаются время вхождения в вершину и его окончание
	int col;	// номер компоненты связанности
public:
	Actions();
	~Actions();
	void DFS_algoritm(Actions & graph); // общий метод, содержащий два DFS
	void DFS_visit(Actions & graph, Vertex & vertex); // DFS, который обходит граф первым для вычисления времени окончания для вершины
	list<Vertex*> * vertexes;						// список вершин графа
	list<Edge> * edges;								// список рёбер
	void addVertex(Vertex & v);						// добавление новой вершины
	void addEdge(Vertex & from, Vertex & to, bool oriented = false); // добавление нового ребра (oriented = false - граф неориетированный, oriented = true - оринетированный)
	list<Vertex*>* getVertexList(Vertex & vertex);	// получение списка смежности для вершины vertex
	Edge * getEdge(Vertex & vertexFrom, Vertex & vertexTo);
	bool isChild(Vertex & vertexParent, Vertex & vertexChild);
	void showEdges();
};

