class Stack {
private:
	class Node {				// ����� ��� �������� � ������ � ������
	public:
		Node * pDown;			// ������ ����
		int data;				// ��������� �� ������ (���������) ����
		Node(int data = int(), Node * pDown = nullptr) {
			this->data = data;	// ������������ ������ ����
			this->pDown = pDown; // ������������ ��������� �� ������ (���������) ����
		}
	};
	Node * head;				// ��������� �� ����-������
	int size;					// ���-�� ������

	
public:
	Stack();
	~Stack();

	
	void push_up(int data);		// ���������� ���� � ������� �����
	void pop_up();				// �������� ���� � ������� �����
	void pop_exactly(int num);	// �������� ���� ���������� ����� 
	void getSize();				// ���-�� ����� � ������ ������ 
	void clear();				// �������� ���� ����� ����� 
	void requests();			// ���� �������� ��� "����������" ������ �� ������ (�� �������� � "int& operator[](int num)")
	int& operator[](int num);	// ����� ���������� �������� (��� � �������) 
	void Show();				// ���� ����� �� ����� 
};


