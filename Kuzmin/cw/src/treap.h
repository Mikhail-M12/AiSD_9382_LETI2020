#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <QString>
#include <QColor>

//элемент деремиды
class TreapElem {
public:
	int key;
	int prior;
	TreapElem* right = nullptr; 
	TreapElem* left = nullptr; 
	QColor color = Qt::white;
	TreapElem(int key, int prior) : key(key), prior(prior) {}
	TreapElem(int key):key(key) {
		prior = rand() % 100;
	}
	TreapElem() {}
	friend std::istream& operator>>(std::istream& in, TreapElem& e) { //оператор ввода из потока. каждый элемент представляется
																	//в виде(x, y), где x - ключ, y - приоритет
		while (in.get() != '(' && !in.eof()) {}
		in >> e.key;
		while (in.get() != ',' && !in.eof()) {}
		in >> e.prior;
		while (in.get() != ')' && !in.eof()) {}
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, TreapElem* e) {  //оператор вывода в поток
																		//пустые элементы выводятся как (null)
		if (e != nullptr)
			out << '(' << e->key << "," << e->prior << ")";
		else out << "(null)";
		return out;
	}
	operator QString()const{
		QString a;
		a.sprintf("(%d,%d)", key, prior);
		return a;
	}
};

bool isLeaf(TreapElem* e);//функция проверяет, является ли элемент листом

//дерамида
class Treap{
public:
	TreapElem* root;
	Treap() {
		root = nullptr;
	}
	//вставка элемента
	void insert(TreapElem*& root, TreapElem a);
	
	//поворот налево
	void rotateLeft(TreapElem*& el);

	//поворот направо
	void rotateRight(TreapElem*& el);

	//считывание и построение дерамиды
	void read(std::istream& is);
	
	//поиск элемента в дерамиде, функция возвращает количество вхождений
	int find(TreapElem* root, TreapElem e);

};
