#pragma once
#include <iostream>
#include <string>

class binSTree
{
public:
	binSTree();
	~binSTree();
	bool isNull();

	char info;
	int count, number;
	binSTree* lt;
	binSTree* rt;
};

int find(binSTree*& bt, char el); // Функция поиска элемента в БДП
void printBT(binSTree*&, std::string); //Функция печати БДП
void rotateRight(binSTree*&); //Функция вращение БДП вправо
void rotateLeft(binSTree*&); //Функция вращение БДП влево
void insertInRoot(binSTree*&, char info); //Функция вставки элемента в корень БДП
void randomInsert(binSTree*&, char info); //Функция рандомизированной вставки в БДП
