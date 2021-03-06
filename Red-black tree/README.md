Двоичное дерево поиска является красно-чёрным, если обладает следующими ***свойствами***:
  1) Каждый узел промаркирован красным или чёрным цветом
  2) Корень - чёрный
  3) Конечные узлы (листья NULL) дерева — чёрные
  4) У красного узла родительский узел — чёрный
  5) Все простые пути из любого узла x до листьев содержат одинаковое количество чёрных узлов
  6 (дополнительное) Чёрный узел может иметь чёрного родителя
    
Количество черных узлов на ветви от корня до листа называется черной высотой дерева. Перечисленные свойства гарантируют, что самая длинная ветвь от корня к листу не более чем вдвое длиннее любой другой ветви от корня к листу. К примеру, кратчайшее возможное расстояние от корня до листа равно двум - когда оба узла чёрные. Длиннейшее расстояние от корня до листа равно четырем - узлы при этом покрашены (от корня к листу) так: красный, черный, красный, черный.

![](https://i.imgur.com/hdvnGbc.png)

**(a)** Узел z после вставки. Посколько и z и его родитель красные, наблюдается нарушение св-ва 4. Т.к. "дядя" узла z, узел y, красный, срабатывает случай 1. Мы перекрашиваем узлы и пермещаем указатель z вверх по дереву, получая результат, показанный в части

**(б)** Вновь z и его родитель красные, но теперь "дядя" z, узел y, чёрный. Т.к. z является правым дочерним узлом по отношению к родителю z применим случай 2. Мы выполним левый поворот, и полученное в результате дерево показано в части (в)

**(в)** Теперь z является левым дочерним узлом своего родителя, так что применим случай 3. Перекрашивание и правый поворот дают показанное в части

**(г)** Корректное красно-чёрное дерево

### Вставка (восстановление св-в RBT)
***
![](https://i.imgur.com/f4dOv6n.png)

1. "Дядя" этого узла тоже красный. Тогда, чтобы сохранить свойства 4 и 5, просто перекрашиваем "отца" и "дядю" в чёрный цвет, а "деда" — в красный. В таком случае черная высота в этом поддереве одинакова для всех листьев и у всех красных вершин "отцы" черные. В предпринимем одни и теже действи в рис. пунктах  **(а)** и **(б)** Проверяем, не нарушена ли балансировка. Если в результате этих перекрашиваний мы дойдём до корня, то в нём в любом случае ставим чёрный цвет, чтобы дерево удовлетворяло свойству 2.
Цикл **while** прожолжает с "дедом" узла ***z*** в качестве нового узла ***z***.
![](https://i.imgur.com/16osyIl.png)

2, 3. "Дядя" чёрный, и ***z*** - правый потомок; "Дядя" чёрный, и ***z*** - левый потомок. Отличие только в размещении узла ***z***. Если выполнить только перекрашивание, то может нарушиться постоянство чёрной высоты дерева по всем ветвям. Поэтому выполняем поворот. Если добавляемый узел был правым потомком, то необходимо сначала выполнить левое вращение, которое сделает его левым потомком. Так как узел ***z*** и его родитель красные то при повороте чёрная высота неизменится Таким образом, свойство 4 и постоянство черной высоты сохраняются. Дальше тело цилка **while** не выполняется, т.к. узел родитель ***z*** чёрный
### Удаление (восстановление св-в RBT)
***
***Удаление самого элемента такое же как и в обыночно Binary Search Tree***
![](https://i.imgur.com/XqCXYmk.png)

***Чёрный узел - color равен BLACK***

***Светлый узел - color равен RED***

***Серый узел - color предствален значениям c и c', который могу быть равны RED и BLACK***

Цикл повторяется в случае 2

**(а)** ***Случай 1*** преобразует в случай 2, 3 или 4 путём измененя цвета узлов B и D и выполенения левого поворота

**(б)** В ***случае 2*** дополнительная чернота, представленная узахателем ***x***, перемещается вверх по дереву путём окраски узла D в красный цвет и утановки ***x*** указывающим на узел B. Если мы попадаем в случай 2 из случая 1, цикл **while** завершается, т.к. новый узел ***x*** - чёрно-красный, и, следовательно, значение c его атрибута ***color*** равне RED

**(в)** ***Случай 3*** преобразеутся в слуай 4 путём обмена цветов узлов C и D и выполненя правого поворота

**(г)** ***Случай 4*** убирает дополнитеьную черноту, представленную ***x***, путём изменения некоторых цветов и выполнения левого поворота (без нарушения красно-чёрных свойств), после чего цикл завершается.
#### Случай 1. Брат ***w*** узла ***x*** - красный
Поскольку ***w*** узел должен иметь черные потомки, можно обменять цвета ***w*** и ***родителя x***, а затем выполнить левый поворот вокруг ***x*** без нарушения каках-либо красно-чёрных свойтва
#### Случай 2. Узел ***w*** - чёрный, оба его дочерхних узла - чёрные
Посколько узел ***w*** также чёрный, мы можем забрать чёрную окраску у ***x*** и ***w***, сделав ***x*** единожды чёрным, а ***w*** - красным. Чтобы компенсировать удаления чёрный цвет ***x*** и ***w***, мы можем добавить дополнительный чёрный цвет ***родителю x**
#### Случай 3. Брать ***w*** узла ***x*** - чёрный, левый дочерний узел узла ***w*** - красный, а правый - чёрный
Мы можем обменять цвета ***w*** и его левого дочерненго узла ***w.left***, а затем выполнить правый поворот вокруг ***w*** без нарушения св-в RBT
#### Случай 3. Брать ***w*** узла ***x*** - чёрный, правый дочерний узел узла ***w*** - красный
Выполняя обмен цветов и левый поворт вокруг ***родителя x***, мы можем устранить излишнюю чёрноту в ***x***, делая его просто чёрным, без наршения св-в RBT. Присваивая ***x*** укзатель на корень приводит к завешению цикла.
