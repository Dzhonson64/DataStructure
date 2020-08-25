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
	int time;	// ����� ����������� �����, ������������� ���� �������� ����� ��������� � ������� � ��� ���������
	int col;	// ����� ���������� �����������
public:
	Actions();
	~Actions();
	void DFS_algoritm(Actions & graph); // ����� �����, ���������� ��� DFS
	void DFS_visit(Actions & graph, Vertex & vertex); // DFS, ������� ������� ���� ������ ��� ���������� ������� ��������� ��� �������
	list<Vertex*> * vertexes;						// ������ ������ �����
	list<Edge> * edges;								// ������ ����
	void addVertex(Vertex & v);						// ���������� ����� �������
	void addEdge(Vertex & from, Vertex & to, bool oriented = false); // ���������� ������ ����� (oriented = false - ���� ����������������, oriented = true - ���������������)
	list<Vertex*>* getVertexList(Vertex & vertex);	// ��������� ������ ��������� ��� ������� vertex
	Edge * getEdge(Vertex & vertexFrom, Vertex & vertexTo);
	bool isChild(Vertex & vertexParent, Vertex & vertexChild);
	void showEdges();
};

