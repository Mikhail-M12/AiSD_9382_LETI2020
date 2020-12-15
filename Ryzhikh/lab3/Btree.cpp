#include "Btree.h"
#include <queue>
//#include <Windows.h>
using namespace std;

ifstream infile("KLP.txt");



BinTree create() {
	return nullptr;
}


bool isNull(BinTree b) {
	return (b == nullptr);
}


char root(BinTree b) {
	if (b == nullptr) {
		cout << "������! �������� ������ ������.\n";
		exit(1);
	}
	else
		return b->getInfo();
}


BinTree left(BinTree b) {
	if (b == nullptr) {
		cout << "������! �������� ������ ������.\n";
		exit(1);
	}
	else
		return b->getLeft();
}


BinTree right(BinTree b) {
	if (b == nullptr) {
		cout << "������! �������� ������ ������.\n";
		exit(1);
	}
	else
		return b->getRight();
}


BinTree cons(const char& x, BinTree& lst, BinTree& rst) {    //��������� �������� ������ �� ��������� ���� � ���� �������� ��������
	BinTree p;
	p = new Tree;
	if (p != NULL) {
		p->setInfo(x);
		p->setLeft(lst);
		p->setRight(rst);
		return p;
	}
	else {
		cout << "�������� ������.\n";
		exit(1);
	}
}


void destroy(const BinTree& b) {
	if (b != nullptr) {
		destroy(b->getLeft());
		destroy(b->getRight());
		delete b;
	}
}


void printForest(BinTree b) {     // �1 ��������� ����
	BinTree p = b->getLeft();
	BinTree q = b->getRight();
	cout << "����������� ���� (����� ������):\n";
	if (p) {
		//cout << ' ' << root(p);	
		if (!isNull(p)) 
		{ 
			startOut(p);
		}
		else 
			cout << "\n";
	}
	cout << "\n�������� ���� (����� ������) � �������������� �������:\n";
	que(p);
	cout << "\n\n";
	cout << "����������� ���� (������ ������):\n";
	if (q) {
		//cout << ' ' << root(q);
		if (!isNull(q)) 
		{
			startOut(q);
		}
		else 
			cout << "\n";
	}
	cout << "\n�������� ���� (������ ������) � �������������� �������:\n";
	que(q);
}


BinTree readTree() {
	char ch;
	BinTree p, q;
	infile >> ch;
	if (ch == '/')
		return NULL;
	else {
		p = readTree();
		q = readTree();
		return cons(ch, p, q);
	}
}

void printBinTree(BinTree b) {	//����� ���������� ������
	if (b != NULL) {
		cout << root(b);
		printBinTree(left(b));
		printBinTree(right(b));
	}
	else
		cout << '/';
}


void printTree(BinTree b, int level) {     //����������� ������
	if (b) {
		cout << ' ' << root(b);
		if (!isNull(right(b)))
			printTree(right(b), level + 1);
		else cout << "\n";
		if (!isNull(left(b))) {
			for (int i = 1; i <= level; i++)
				cout << "  ";
			printTree(left(b), level + 1);
		}
	}
}



void que(BinTree b) {        //����� � ������
	queue <BinTree> Q;
	BinTree p;
	Q.push(b);
	while (!Q.empty()) {
		p = Q.front();
		Q.pop();
		cout << root(p) << ' ';
		if (left(p) != NULL)
			Q.push(left(p));
		if (right(p) != NULL)
			Q.push(right(p));
	}
}

void startOut(BinTree b) {
	if (!b) {
		cout << "Nothing to print!\n";
		return;
	}
	out(b, "");
}
void out(BinTree b, string str) {
	if ((b->getLeft() == NULL) && (b->getRight() == NULL)) 
	{
		cout << str << b->getInfo() << endl;
	}
	else {
		string str1 = str;
		//cout << str << b->getInfo() << endl;
		if (b->getRight() != NULL) {
			str1 += "	";
			out(b->getRight(), str1);
		}
		cout << str << b->getInfo() << endl;
		if (b->getLeft() != NULL) {
			str += "	";
			out(b->getLeft(), str);
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	BinTree b;
	b = readTree();
	cout << "��������� �������� ������:\n";
	printBinTree(b);
	cout << "\n\n";
	cout << "����������� ������ (���������):\n";  //�2 ������� ����������� ��������� ������
	startOut(b);
	//startOut(b->getLeft());
	//startOut(b->getRight());
	//PrintTree(b, level);
	cout << "\n\n";
	cout << "����������� ����:\n";
	if (b)
		printForest(b);
	cout << "\n\n";
	destroy(b);
	return (0);
}