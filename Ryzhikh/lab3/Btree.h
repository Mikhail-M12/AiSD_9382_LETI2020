#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

class Tree 
{
public:
	char getInfo()
	{
		return info;
	}

	Tree* getLeft()
	{
		return lt;
	}

	Tree* getRight()
	{
		return rt;
	}

	void setInfo(char data)
	{
		info = data;
	}

	void setLeft(Tree* left)
	{
		lt = left;
	}

	void setRight(Tree* right)
	{
		rt = right;
	}

	Tree() 
	{
		info = '\0';
		lt = nullptr;
		rt = nullptr;
	}
private:
	char info;
	Tree* lt;
	Tree* rt;
};


typedef Tree* BinTree; //представитель бинарного дерева


BinTree create(void);
bool isNull(BinTree);
char root(BinTree);
BinTree left(BinTree);
BinTree right(BinTree);
BinTree cons(const char& x, BinTree& lst, BinTree& rst);
void destroy(const BinTree&);
BinTree getForest(BinTree);
void printBinTree(BinTree);
BinTree readTree();
int level = 0;    //уровень бинарного дерева
int level1 = 0;   //уровень левого дерева
int level2 = 0;   //уровень правого дерева
void printTree(BinTree, int level);
void que(BinTree);
void printForest(BinTree);
void out(BinTree, std::string);
void startOut(BinTree);



#endif