#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <queue> 
#include <list>
using namespace std;
class GraphActions
{
private:
	Vertex * start; // ��������� �� ��������� �������
	int time;
public:
	GraphActions();
	~GraphActions();
	void BFS(GraphActions & graph, Vertex & start); // ����� � ������
	void DFS(GraphActions & graph); // ����� � �������
	void DFS_visit(GraphActions & graph, Vertex & vertex); // ����� � �������
	void getPath(GraphActions & graph, Vertex & begin, Vertex & end);
	queue<Vertex*> * pendingVertexes;				// ������� ������ ��� ����������� �� ������������
	list<Vertex*> * vertexes;						// ������ ���� ������
	list<Edge> * edges;								// ������ ����
	void addVertex(Vertex & v);						// ���������� �������
	void addEdge(Vertex & from, Vertex & to, bool oriented = false); // ���������� ����� (oriented = false - ���� �����������������, oriented = true - ���������������)
	list<Vertex*>* getVertexList(Vertex & vertex);	// ��������� ������ ��������� ��� ������� vertex
};

