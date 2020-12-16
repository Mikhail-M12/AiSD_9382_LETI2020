#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <QString>
#include <QColor>

//������� ��������
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
	friend std::istream& operator>>(std::istream& in, TreapElem& e) { //�������� ����� �� ������. ������ ������� ��������������
																	//� ����(x, y), ��� x - ����, y - ���������
		while (in.get() != '(' && !in.eof()) {}
		in >> e.key;
		while (in.get() != ',' && !in.eof()) {}
		in >> e.prior;
		while (in.get() != ')' && !in.eof()) {}
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, TreapElem* e) {  //�������� ������ � �����
																		//������ �������� ��������� ��� (null)
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

bool isLeaf(TreapElem* e);//������� ���������, �������� �� ������� ������

//��������
class Treap{
public:
	TreapElem* root;
	Treap() {
		root = nullptr;
	}
	//������� ��������
	void insert(TreapElem*& root, TreapElem a);
	
	//������� ������
	void rotateLeft(TreapElem*& el);

	//������� �������
	void rotateRight(TreapElem*& el);

	//���������� � ���������� ��������
	void read(std::istream& is);
	
	//����� �������� � ��������, ������� ���������� ���������� ���������
	int find(TreapElem* root, TreapElem e);

};
