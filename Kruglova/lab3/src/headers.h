#ifndef HEADERS_H
#define HEADERS_H

#include "InnerWayAndCount.h" // подключили созданный класс
#include <iostream>
using namespace std;


// базовые функции 

template<class T>
class BTree
{
private:
public:
    BTree* m_l_tree = nullptr;
    BTree* m_r_tree = nullptr;
    T m_BTroot = '\0';

    BTree* get_left() {return m_l_tree;};
    BTree* get_right() {return m_r_tree;};
    T get_BTroot() {return m_BTroot;};
};

template<typename T>
bool isNullptr(BTree<T>* a) // проверка на nullptr
{return a == nullptr;}

template<typename T>
BTree<T>* ConsBT(const T x, BTree<T>* lst,  BTree<T>* rst) // объединение корня и 2 подддеревьев
{	
    BTree<T>* p = nullptr;
	p = new BTree<T>;

	if (!isNullptr(p))	
    { 	
		p->m_BTroot = x;
		p->m_l_tree = lst;
		p->m_r_tree = rst;
		return p;
	}
	else 
    {
        cerr << "Memory error!\n"; 
        exit(1);
    }
}

template<typename T>
void destroy (BTree<T>* b) // рекурсивная очистка дерева
{
    if (!isNullptr(b))
    {
		destroy (b->m_l_tree);  // рекурсивный вызов этой же функции для обоих поддеревьев
		destroy (b->m_r_tree);
		delete b;               // и очистка памяти для дерева, в котором находимся
		b = nullptr;			// обнуление висячего указателя
	}
}

template<typename T>
BTree<T>* readBT() // считывание дерева заданного с пом. '/'
{	
	T ch;
	BTree<T> *p, *q;
	cin >> ch;

	if (ch == '/') 
		return nullptr;
	else 
	{
		p = readBT<T>(); // рекурсивный вызов этой же функции для создания левого поддерева
		q = readBT<T>(); // для создания правого поддерева
		return ConsBT(ch, p, q); // объединение поддеревьев и корня в одно бинарное дерево
	}
}

template<typename T>
void writeBT(BTree<T> *b) // вывод дерева в том же виде, в котором оно и задано
{	
	if (!isNullptr(b)) 
    {
		cout << b->get_BTroot();
		writeBT(b->get_left());
		writeBT(b->get_right());
	}
	else cout << '/';
}

// специфичные для конкретного варианта функции

void printEmptyDepth(int depth);

template<typename T>
void findMaxDepth(BTree<T>* a, int *max, int depth)
{
    if (!isNullptr(a)) // если переданный указатель не пуст (дерево есть)
    {
        if (*max < depth) // если глубина нынешнего дерева вдруг больше максимальной
        {
            { // отладочная информация
                printEmptyDepth(depth);
                cout << "Max depth < current depth." << endl;
            }
            *max += 1;  // то значение значение между ними различается лишь на 1
        }

        { // отладочная информация
            printEmptyDepth(depth);
            cout << "Checking left subtree." << endl;
        }
        findMaxDepth(a->get_left(), max, depth + 1); // вызвали эту же функцию для левого поддерева

        { // отладочная информация
            printEmptyDepth(depth);
            cout << "Checking right subtree." << endl;
        }
        findMaxDepth(a->get_right(), max, depth + 1); // вызвали эту же функцию для правого поддерева
    }
    else // отладочная информация
    {
        printEmptyDepth(depth);
        cout << "Binary tree is empty." << endl;
    }
}

template<typename T>
InnerWayAndCount findInnerWay(BTree<T>* a, int depth)
{
    // функция основана на формуле: длина внутреннего пути = внутренний путь правого поддерева + внутренний путь левого поддерева + количество узлов в дереве - 1        

    InnerWayAndCount object; // создали объект с полями (way = 0, count = 1) (корень тоже узел, отсюда и 1)

    if((depth == 0) && isNullptr(a)) // если начального дерева не существует
    {
        cout << "Binary tree is empty." << endl;
        return object;
    }

    if (!isNullptr(a->get_left())) // если есть левое поддерево
    {
        { // отладочная информация
            printEmptyDepth(depth);
            cout << "Checking left subtree." << endl;
        }
        // то вызовем для него эту же функцию
        InnerWayAndCount subObject = findInnerWay(a->get_left(), depth + 1); // этот объект уничтожится уже при выходе из этого блока if

        object.addCount(subObject.getCount()); // прибавили количество узлов из левого поддерева
        object.addInnerWay(subObject.getInnerWay()); // прибавили внутренний путь из левого поддерева
    }
    else // отладочная информация
    {
        printEmptyDepth(depth);
        cout << "Left subtree is empty." << endl;
    }

    if (!isNullptr(a->get_right())) // если есть правое поддерево
    {
        { // отладочная информация
            printEmptyDepth(depth);
            cout << "Checking right subtree." << endl;
        }
        InnerWayAndCount subObject = findInnerWay(a->get_right(), depth + 1); // то вызовем для него эту же функцию

        object.addCount(subObject.getCount()); // прибавили количество узлов из правого поддерева
        object.addInnerWay(subObject.getInnerWay()); // прибавили внутренний путь из правого поддерева
    }
    else // отладочная информация
    {
        printEmptyDepth(depth);
        cout << "Right subtree is empty." << endl;
    }

    object.addInnerWay(object.getCount() - 1); // добавляем к внутреннему пути кол-во узлов - 1 (для листьев после действия ничего не поменяется)

    { // отладочная информация
        printEmptyDepth(depth);
        cout << "Count of nodes in this bt = " << object.getCount() << endl;

        printEmptyDepth(depth);
        cout << "Inner way in this bt = " << object.getInnerWay() << endl;
    }

    return object; // объект передается по значению -> там, где он будет приниматься, вызовется конструктор копирования по-умолчанию
} // здесь будет уничтожен object



#endif
