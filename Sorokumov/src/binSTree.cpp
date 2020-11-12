#include "binSTree.h"

binSTree::binSTree()
{
	this->info = '\0';
	this->count = 0;
	this->number = 0;
	this->lt = nullptr;
	this->rt = nullptr;
}

binSTree::~binSTree()
{
	delete this->lt;
	delete this->rt;
}

bool binSTree::isNull()
{
	return this->info == '\0';
}

/*
 * рекурсивная функция поиска элемента в БДП
 */
int find(binSTree*& bt, char el)
{
	if (bt == nullptr || bt->isNull()) return 0;
	if (el == bt->info) return bt->count;
	if (el < bt->info)
		return find(bt->lt, el);
	else
		return find(bt->rt, el);
}

void rotateRight(binSTree*& temp)
{
	binSTree* x;
	x = temp->lt;
	temp->lt = x->rt;
	x->rt = temp;
	temp = x;

	if (temp->lt != nullptr) 
	{
		temp->lt->number = temp->lt->count;
		if (temp->lt->lt != nullptr)
			temp->lt->number += temp->lt->lt->number;

		if (temp->lt->rt != nullptr)
			temp->lt->number += temp->lt->rt->number;
	}
	temp->number = temp->count;
	if (temp->lt != nullptr)
		temp->number += temp->lt->number;

	if (temp->rt != nullptr)
		temp->number += temp->rt->number;
}

void rotateLeft(binSTree*& temp)
{
	binSTree* x;
	x = temp->rt;
	temp->rt = x->lt;
	x->lt = temp;
	temp = x;
	if (temp->rt != nullptr)
	{
		temp->rt->number = temp->rt->count;
		if (temp->rt->lt != nullptr)
			temp->rt->number += temp->rt->lt->number;

		if (temp->rt->rt != nullptr)
			temp->rt->number += temp->rt->rt->number;
	}
	temp->number = temp->count;
	if (temp->lt != nullptr)
		temp->number += temp->lt->number;

	if (temp->rt != nullptr)
		temp->number += temp->rt->number;
}
/*
 * Рекурсивная функция вставки элемента в БДП
 */
void insertInRoot(binSTree*& bt, char x)
{
	if (bt == nullptr || bt->isNull())
	{
		bt = new binSTree();
		bt->info = x;
		bt->count = 1;
		bt->number = 1;
	}
	else
	{
		if (x < bt->info)
		{
			insertInRoot(bt->lt, x);
			rotateRight(bt);
		}
		else
		{
			if (x > bt->info)
			{
				insertInRoot(bt->rt, x);
				rotateLeft(bt);
			}
			else
			{
				bt->count++;
				bt->number++;
			}
		}
	}
}
/*
 * Рекурсивная функция рандомной вставки элемента в БДП
 * в зависимости от условий может вызвать как себя, так и функцию insertInRoot
 */
void randomInsert(binSTree*& bt, char x)
{
	if (bt == nullptr || bt->isNull())
	{
		bt = new binSTree();
		bt->info = x;
		bt->count = 1;
		bt->number = 1;
		return;
	}
	if (rand() % (bt->number + 1) == 0)
	{
		insertInRoot(bt, x);
		return;
	}
	else if (x < bt->info)
	{
		randomInsert(bt->lt, x);
	}
	else if (x == bt->info)
	{
		bt->count++;
	}
	else
	{
		randomInsert(bt->rt, x);
	}
	bt->number++;
}
/*
 * Функция печати БДП
 */
void printBT(binSTree*& bt, std::string str)
{
	if (bt == nullptr) return;
	std::string _str = str;
	static bool isFirstCall = true;
	if (isFirstCall)
	{
		std::cout << "▶ ";
		isFirstCall = false;
	}
	std::cout << bt->info << " (" << bt->number << ")" << std::endl;
	if (bt->rt != nullptr) 
	{ 
		std::cout << str; 
	}
	if (bt->lt == nullptr && bt->rt != nullptr) 
	{
		std::cout << "└▶ "; 
	}
	if (bt->lt != nullptr && bt->rt != nullptr)
	{
		std::cout << "├▶ "; 
	}
	if (bt->lt != nullptr)
	{
		printBT(bt->rt, str.append("│ "));
	}
	else 
	{
		printBT(bt->rt, str.append(""));
	}
	if (bt->lt != nullptr)
	{
		std::cout << _str;
	}
	if (bt->lt != nullptr)
	{
		std::cout << "└▶ ";
	}
	printBT(bt->lt, _str.append(" "));
}

