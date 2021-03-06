﻿
/*
	ПОЯСНЕНИЕ:
		Данный dictionary реализован на основе открытой реализции с помощью двойного хеширования.
		Данный метод сотоит в том, что мы прибегаем к помощи второй ВСПОМОГАТЕЛЬНОЙ хеш-функции, которая сложит "шагом" при коллизии от элемента 
		Двойное хеширование в отличие от линейного пробирования предостваляет отсутвсие "классетеров" (цепочек исследуемых элементов в массиве. Эта цепочка появляется, когда происходит коллизия),
		и получаемые перестановки максимально приближенны к случайным. Таким образом можно минизировать поиск пустого места для нового элемента.
		
		Если, к примеру, массив состоит из элеметов (N - NULL):
		0 1  2  3  4  5 6
		N 32 12 42 43 N N

		Пусть у нас случилась коллизия с элементом 32 и нам нужно найти пусто место для нового элеменат.
		При линейном пробировании мы будем последовательно идити через 12 -> 42 -> 43 -> N элемент.
		А при двойном хешировании(зависит от предоставленного пользователем ключа), к прмиеру key = 2, то вспомагательна хеш-функция = 2 % 5 + 1 = 3 - это шаг,
		но если в (h1 + i * h2) % size i начинается с 0, то сначала мы проверим следующий элемент, относитлеьно 32, а потом сделаем шаг 3, т.е 32 -> 12 -> N.
		Преимещество двойного хеширования ярко выражено в больших массивам.

*/

#include "pch.h"
#include "Dict.h"
#include <iostream>

int main()
{
	Dict * d = new Dict();
	d->add(new Item(23, "Kirill"));
	d->add(new Item(24, "Kirill"));
	d->add(new Item(0, "Kirill"));
	std::cout << d->search(23);
	d->remove(20);
}
