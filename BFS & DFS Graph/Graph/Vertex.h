#pragma once
class Vertex
{
private:

public:
	Vertex();
	Vertex(int number);
	~Vertex();
	int distance;			// min ���������� �� ��������� �������
	int finish;				// ��� ������ � �������
	char color;				// ���� �������
	int number;				// ����� �������
	Vertex * predecessor;	// ��������� �� �������, �� ������� ������ � ������ �������
};

