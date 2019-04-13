class Stack {
private:
	class Node {				// класс для создания и работы с узлами
	public:
		Node * pDown;			// данные узла
		int data;				// указатель на нижний (следующий) узел
		Node(int data = int(), Node * pDown = nullptr) {
			this->data = data;	// переопреляем данные узла
			this->pDown = pDown; // переопреляем указатель на нижний (следующий) узел
		}
	};
	Node * head;				// указатель на узел-голову
	int size;					// кол-во узелов

	
public:
	Stack();
	~Stack();

	
	void push_up(int data);		// Добавление узла в вершину Стека
	void pop_up();				// Удаление узла с вершины Стека
	void pop_exactly(int num);	// Удаление узла выбранного места 
	void getSize();				// Кол-во узлов в данный момент 
	void clear();				// Удаление всех узлов сразу 
	void requests();			// Ввод запросов для "нормальной" работы со Стеком (не работает с "int& operator[](int num)")
	int& operator[](int num);	// Вывод выбранного элемента (как в массиве) 
	void Show();				// Ввод узлов на экран 
};


