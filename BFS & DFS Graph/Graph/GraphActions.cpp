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
		���� ������� ����� ����:
		WHITE (W) - ������� ��� �� ��������������� � � ��� � ������� ��� ����������� ������������
		GRAY (G) - ������� ��� ���� � ������� � � �������� �� ����� �������������
		BLACK (B) - ������� ��� ���� �����������
	*/

	start.color = 'G';			// ������ ��������� ������� "���������������"
	start.distance = 0;			// ���������� �� ���. ������� ����
	start.predecessor = NULL;	// ��� ������� �� ������� �� ������ � ���. �������
	pendingVertexes->push(&start);	// ��������� � � �������
	list<Vertex*> * vertexList;		// ������ ��������� 
	while (!pendingVertexes->empty()) {
		/* ������� �� ����� */

		Vertex * temp = pendingVertexes->front();	// ���� ������� �� �������
		pendingVertexes->pop();
		vertexList = getVertexList(*temp);			// ����� ��� �� ������ ���������
		
		for (auto i : *vertexList) {
			/* ���������� �� ���� �������� �� ������ ��������� */

			if (i->color == 'W') {
				/* ������� �� ��������������� */

				i->color = 'G';						// ������ � ���������������
				i->distance = temp->distance + 1;	// ��������� ������������, ������������ ��������� "������������" �������
				i->predecessor = temp;				// ���������� �� ����� ������� �� ������ 
				pendingVertexes->push(i);			// ��������� � ������� ������� �� ������ ���������
			}
		}
		temp->color = 'B';	// ����� ���������� � ������� ���� ����������������� ������� ������, ������ ������� ��������, ��� �������������
	}
}

void GraphActions::DFS(GraphActions & graph)
{
	time = 0;
	
	for (auto i : *vertexes) {
		/* ���������� �� ���� �������� ����� */
		if (i->color == 'W') {
			/* ������� ����� => �������� � � ������������ */
			DFS_visit(graph, *i);
		}
	}
}

void GraphActions::DFS_visit(GraphActions & graph, Vertex & vertex)
{
	time++;
	vertex.distance = time;
	vertex.color = 'G';									// �������� �, ��� ������������
	list<Vertex*> * vertexList = getVertexList(vertex); // ���������� ������ ��������� ��� ������� vertex
	for (auto i : *vertexList) {
		/* �������� �� ���� ������� �������� */
		if (i->color == 'W') {
			/* ������� ��������������� */
			i->predecessor = &vertex;	// ���������� �� ����� ������� ������
			DFS_visit(graph, *i);		// ������������� ��� ������� �������
		}
	}
	/* ��� ������� ������� �����, �� �������� �������� ��� ������������ ������� */
	vertex.color = 'B';
	time++;
	vertex.finish = time;
}

void GraphActions::getPath(GraphActions & graph, Vertex & begin, Vertex & end)
{
	
	if (&begin == &end) {
		/* �������  begin �������� �������� end => ������ ������� ��������� ������� */
		cout << begin.number << ", ";
	}
	else if (end.predecessor == NULL){
		/* � ��������� ������� ��� �������, �� ������� ����� ������ � ������� end */
		cout << "ERROR: This path is not found" << endl;
	}
	else {
		getPath(graph, begin, *end.predecessor); // ��������� �� "����������" �������
		cout << end.number << ", ";
	}
}

void GraphActions::addVertex(Vertex & v)
{
	vertexes->push_back(&v);
}

void GraphActions::addEdge(Vertex & from, Vertex & to, bool oriented)
{
	Edge newEdge = Edge(from, to); // ������ ����� �� ���� ������: �� ����� ������� ������� ����� � � ����� �������
	edges->push_back(newEdge);		// ��������� � ������ ����
	if (oriented == false) {
		/* ���� ��������������� => ������ ���� �����, �� ������ ������� ������� */
		Edge newEdge_2 = Edge(to, from);
		edges->push_back(newEdge_2);
	}
		
	
}

list<Vertex*> * GraphActions::getVertexList(Vertex & vertex)
{
	list<Vertex*> * result = new list<Vertex*>; // �������������� ������ ��������� ��� ������� vertex
	for (list<Edge>::iterator i = edges->begin(); i != edges->end(); i++) {
		if (i->from == &vertex) {
			/* � ������ ���� ���� ������� vertex, ������� ��������� �������, �� ������� ������� �����*/
			result->push_back(i->to); // �� � ������ ��������� ��������� �������, � ������� ������ �����
		}
	}
	return result;
}
