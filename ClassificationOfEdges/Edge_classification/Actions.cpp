#include "pch.h"
#include "Actions.h"
#include <list>
#include "string"
Actions::Actions()
{
	start = NULL;
	vertexes = new list<Vertex*>;
	edges = new std::list<Edge>;

}


Actions::~Actions()
{
}
void Actions::DFS_algoritm(Actions & graph)
{
	/* �������������� ����� � ����� ���������� */
	time = 0;
	col = 1;
	/* ����������� ������ DFS �� �����, �������� ����� ��������� ������ � ��������� ����� ������, ���������������� � ������� �������� ������� ��������� */
	for (auto i : *vertexes) {

		if (i->color == 'W') {
			DFS_visit(graph, *i);
		}
	}


}

void Actions::DFS_visit(Actions & graph, Vertex & vertex)
{
	
	vertex.color = 'G';									// ������ ������� "����������"
	list<Vertex*> * vertexList = getVertexList(vertex); // �������� ������ ��������� ��� ������� vertex
	time++;	// ����������� ����� 
	vertex.distance = time;	// ��������� ����� ��������� � �������
	showEdges();
	std::cout << std::endl;
	for (auto i : *vertexList) {
		/* ������� �� ���� ���� ��������  */
		Edge * e = getEdge(vertex, *i);
		if (i->color == 'W') {
			/* ������� ��� �� ���� �������� */
			
			
			i->predecessor = &vertex;
			e->classification = "tree edge";
			DFS_visit(graph, *i);
		}
		else if (i->color == 'G') {
			e->classification = "back edges";
		}
		else if (i->color == 'B') {
			if (isChild(vertex, *i)) {
				e->classification = "forward edges";
			}
			else {
				e->classification = "cross edges";
			}
			
		}
	}
	/* � ������� ��� ������������ ������, ������� ��� �� �������� */
	vertex.color = 'B';			// ������ � �����������
	time++;
	vertex.finish = time;		// ����������� ����� ��������� �������
	showEdges();
	std::cout << std::endl;


}

void Actions::addVertex(Vertex & v)
{
	vertexes->push_back(&v);
}

void Actions::addEdge(Vertex & from, Vertex & to, bool oriented)
{
	Edge newEdge = Edge(from, to);
	edges->push_back(newEdge);
	if (oriented == false) {

		Edge newEdge_2 = Edge(to, from);
		edges->push_back(newEdge_2);
	}


}

list<Vertex*> * Actions::getVertexList(Vertex & vertex)
{
	list<Vertex*> * result = new list<Vertex*>;
	for (list<Edge>::iterator i = edges->begin(); i != edges->end(); i++) {
		if (i->from == &vertex) {
			/* ��������� ������� � ����� - ��� ������ ������� */
			result->push_back(i->to); // ���������� �������, ���� ��� ����� ���
		}
	}
	return result;
}

Edge * Actions::getEdge(Vertex & vertexFrom, Vertex & vertexTo)
{
	for (list<Edge>::iterator i = edges->begin(); i != edges->end(); i++) {
		if (i->to == &vertexTo && i->from == &vertexFrom) {
			/* ��������� ������� � ����� - ��� ������ ������� */
			return &*i;
		}
	}
	return nullptr;
}

bool Actions::isChild(Vertex & vertexParent, Vertex & vertexChild)
{
	Vertex * temp = &vertexChild;
	while (temp->predecessor) {
		if (temp->predecessor == &vertexParent) {
			return true;
		}
		temp = temp->predecessor;
	}
	return false;
}

void Actions::showEdges()
{
	for (list<Edge>::iterator i = edges->begin(); i != edges->end(); i++) {
		std::cout << i->from->number << " -> " << i->to->number << " (" << i->classification << ") " << std::endl;
	}
}
