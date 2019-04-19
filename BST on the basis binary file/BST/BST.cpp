// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
using namespace std;
void add(FILE * f, int value); // добавление элемента в дерево
void read(FILE * f); // вывод в 16-ой сс данных с указателями на "узлы"
void show(FILE * f, int type); // вывод только данных, в той последовательности, как и хранятся в файле (если type == 10 - в 10 сс, если type == 16 - в 16 сс)
int main()
{
	FILE * f;
	if (fopen_s(&f,"input.txt", "w+b") == 0) {
		add(f, 7);
		add(f, 3);
		add(f, 10);
		add(f, 1);
		add(f, 9);
		add(f, 100);
		add(f, 100);
		add(f, 50);
		read(f);
		printf("\n");
		show(f, 16);
	}
	else {
		printf("Error: Your file didn't open");
	}
	fclose(f);
}
void add(FILE * f, int value) {
	int ptrItem = -1;	// обозначение пустого указателя
	int sizeTree = ftell(f); // кол-во байте в файле
	int flag = 1; // флаг для обозначения того, что дошли до листа дерева
	
	if (sizeTree == 0) {	// если дерево пусто, то создаём корень
		fwrite(&value, sizeof(int), 1, f);
		fwrite(&ptrItem, sizeof(int), 1, f);
		fwrite(&ptrItem, sizeof(int), 1, f);
	}
	else {	// иначе, с самого начала спускаемся от корня к листу
		fseek(f, 0, SEEK_SET);
		while (flag) {
			int item;
			fread(&item, sizeof(int), 1, f); // счяитываем элемент, который хранится в узле

			fseek(f, 0, SEEK_CUR);	// без вызова этого fseek() возникает конфликт между fread() и последующим fwrite()
			int ptrLeft;
			int ptrRight;
			fread(&ptrLeft, sizeof(int), 1, f);  // запоминаем левый указатель узла
			fread(&ptrRight, sizeof(int), 1, f); // запоминаем правый указатель узла

			/* Если заначение больше, чем значание узла */
			if (value > item) { 

				/* Рассматриваем два случая: 
					1) когда после данного узла есть другой узел, но его значение меньше. К примеру узел хранится узелы со значение 7 , 3. 
					В этом случае нужно добвить новый узел после узла со значение 3.

					2) когда после того узла, на котором находимся, нет другого узла.
					В этом случае нужно добвить новый узел после того узла, на котором находимся.
				*/
				if (ptrRight == -1) { // если правый указатель пустой
					flag = 0; // поднимаем флаг, т.к. нашли место для нового узла
					
					if (ptrLeft == -1) { //  если после того узла, на котором находимся, нет узла 
						int posNewItem = ftell(f); // т.к. мы считали уже и левый указатель и правый указатель узла, т.е указатель файла уже указывает на то место, куда нужно вставить, то это и есть отсутуп в байтах 
						fseek(f, -1 * (int)sizeof(int), SEEK_CUR); // передвигаемся на позицию влево, где находится указатель, указывающий на правую ветвь, 
						fwrite(&posNewItem, sizeof(int), 1, f); // записываем этот этот указатель
					}
					else { // если после того узла, на котором находимся, есть ещё узел
						int posNewItem = ftell(f) + 3 * (int)sizeof(int); // отсутуп равен нынешнему кол-ву байт + размер следующего узла (12 байт)
						fseek(f, -1 * (int)sizeof(int), SEEK_CUR); // передвигаемся на позицию влево, где находится указатель, указывающий на правую ветвь, 
						fwrite(&posNewItem, sizeof(int), 1, f);// записываем этот этот указатель
						fseek(f, 3 * (int)sizeof(int), SEEK_CUR); // перепрыгиваем через узел, размером 12 байт
					}
					fwrite(&value, sizeof(int), 1, f); // заносим новое значение нового узла
					fwrite(&ptrItem, sizeof(int), 1, f); // создаём левый левый укзатель узла
					fwrite(&ptrItem, sizeof(int), 1, f); // создаём правый левый укзатель узла
				}
				else { // если правый указатель НЕ пустой
					fseek(f, ptrRight, SEEK_SET); // перемещаемся на ptrRight-байт от начала файла
				}
			}
			/* Если заначение меньше, чем значание узла (дальше все те же 2 случая, как в предыдущем условии)*/
			else if (value < item){
				if (ptrLeft == -1) { 
					flag = 0;

					if (ptrRight == -1) {
						int posNewItem = ftell(f);
						fseek(f, -2 * (int)sizeof(int), SEEK_CUR);
						fwrite(&posNewItem, sizeof(int), 1, f);
						fseek(f, sizeof(int), SEEK_CUR);
					}
					else {
						int posNewItem = ftell(f) + 3 * (int)sizeof(int);
						fseek(f, -1 * (int)sizeof(int), SEEK_CUR);

						fwrite(&posNewItem, sizeof(int), 1, f);
						fseek(f, 3 * (int)sizeof(int), SEEK_CUR);
					}
					fwrite(&value, sizeof(int), 1, f);
					fwrite(&ptrItem, sizeof(int), 1, f);
					fwrite(&ptrItem, sizeof(int), 1, f);
				}
				else { // если правый указатель НЕ пустой
					fseek(f, ptrLeft, SEEK_SET); // перемещаемся на ptrRight-байт от начала файла
				}
			}
			else { // если число уже есть в дереве, то выходим из цикла
				break;
			}
		}
	}
	
}
void read(FILE * f) {
	int sizeTree = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (sizeTree == 0) {
		printf("ERROR read(): Tree is empty");
	}
	else {
		fseek(f, 0, SEEK_END);
		int size = ftell(f); // узнаём размер данных

		fseek(f, 0, SEEK_SET); // переходим в самое начала файла

		int temp[1000]; // массив в котором хранятся данные файла
		fread(&temp, sizeof(int), 1000, f);
		for (int i = 0; i < size / sizeof(int); i++) {
			printf("%X ", temp[i]);
			if ((i + 1) % 3 == 0) {
				printf(" %c  ", '|');
			}
		}
	}
	
	
}

void show(FILE * f, int type) {
	int sizeTree = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (sizeTree == 0){
		printf("ERROR show(): Tree is empty");
	}
	else {
		if (type == 10) {
			/* Сначала считываем значение корня, потом других узлов */
			int item;
			fread(&item, sizeof(int), 1, f); 
			printf("%i ", item);
			int len = sizeTree / (3 * sizeof(int)); // перевод из кол-ва байт в кол-во значение узлов
			for (int i = 0; i < len - 1; i++) {
				fseek(f, 2 * sizeof(int), SEEK_CUR);
				fread(&item, sizeof(int), 1, f);
				printf("%i ", item);
			}
		}
		else if (type == 16) {
			int item;
			fread(&item, sizeof(int), 1, f);
			printf("%X ", item);
			int len = sizeTree / (3 * sizeof(int));
			for (int i = 0; i < len - 1; i++) {
				fseek(f, 2 * sizeof(int), SEEK_CUR);
				fread(&item, sizeof(int), 1, f);
				printf("%X ", item);
			}
		}
		else {
			printf("ERROR: You entered the wrong type");
		}
	}
}