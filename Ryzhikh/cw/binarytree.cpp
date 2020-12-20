#include "binarytree.h"
#include <iostream>
template<class T> void swp(T & el1, T & el2)//меняет элементы местами
{
	T temp = el1;
	el1 = el2;
	el2 = temp;
}
BinaryTree::BinaryTree(BinaryTree* left, BinaryTree* right)//конструктор
{
	this->left = left;
	this->right = right;
	this->num = left->getNum() + right->getNum();
	this->root = left->root + right->root;
}
BinaryTree::BinaryTree(Elem elem, int num)//конструктор
{
	this->root = elem;
	this->num = num;
}
BinaryTree::BinaryTree(std::vector<BinaryTree*>& vect)//конструктор
{
	std::sort(vect.begin(), vect.end(), [](BinaryTree* el1, BinaryTree* el2)
		{
			if (el1->getNum() != el2->getNum())
				return el1->getNum() > el2->getNum();
			return el1->getRoot()[0] < el2->getRoot()[0];
		});
	std::wstring temp;
	int n = 0;
	for (auto i : vect)
	{
		temp += i->getRoot();
		n += i->getNum();
	}
	this->root = temp;
	this->num = n;
}
void destroy(BinaryTree* tree)//очищение памяти
{
	if (tree != nullptr)
	{
		destroy(tree->getLeft());
		destroy(tree->getRight());
		delete tree;
	}
}
Elem BinaryTree::getRoot()//возвращает корень дерева
{
	return this->root;
}
BinaryTree* BinaryTree::getRight()//возвращает правое поддерево
{
	return this->right;
}
BinaryTree* BinaryTree::getLeft()//возвращает левое поддерево
{
		return this->left;
}
int BinaryTree::getNum()//возвращает вес корня дерева
{
	return this->num;
}
void BinaryTree::setNum(int num)//устанавливает вес корня дерева
{
	this->num = num;
}
void BinaryTree::printBT(int level)//рекурсивно изображает дерево в виде уступчатого списка
{
	if (left != nullptr)
		left->printBT(level + 1);
	for (int i = 0; i < level; i++)std::wcout << " --- ";
	std::wcout << root << '(' << num << ')' << '\n';
	if (right != nullptr)
		right->printBT(level + 1);
}
void BinaryTree::setLeft(BinaryTree* bt)//устанавливает левое поддерево
{
	this->left = bt;
}
void BinaryTree::setRight(BinaryTree* bt)//устанавливает правое поддерево
{
	this->right = bt;
}
BinaryTree* createBinaryTreeHuff(std::vector<BinaryTree*>& elements)//строится дерево Хаффмана
{
	//если в векторе остался один элемент, то этот элемент является построенным деревом Хаффмана и он возвращается из функции
		if (elements.size() == 1)
			return elements[0];
	BinaryTree* temp1 = elements[elements.size() - 1];
	BinaryTree* temp2 = elements[elements.size() - 2];
	elements.pop_back(); //удаляем элемент из конца вектора
	elements.pop_back(); //удаляем элемент из конца вектора
	BinaryTree* parent = new BinaryTree(temp1, temp2);//создаем бинарное дерево,в котором temp1 и temp2 будут потомками
		elements.push_back(parent); //добавляем новое дерево в вектор
		//перемещаем на нужное место добавленный элемент(чтобы вектор был поубыванию)
	for (auto i = elements.end() - 1; i != elements.begin(); i--)
	{
		if ((*i)->getNum() >= (*(i - 1))->getNum())
		{
			swp(*i, *(i - 1));
		}
		else
		{
			break;
		}
	}
	return createBinaryTreeHuff(elements);
}
BinaryTree* createBinaryTreeSF(BinaryTree* tree, std::vector<BinaryTree*> elements)//строится дерево Фано- Шеннона
{
	//если длина корня дерева равна 1, то возвращаем это дерево
	if (tree->getRoot().length() == 1)
	{
			return tree;
	}
	std::wstring rootString = tree->getRoot(); //получаем значение корня
	std::wstring rootBTLeft = L"";//строка для корня левого поддерева
	std::wstring rootBTRight = L"";//строка для корня правового поддерева
	int weightBTLeft = 0;//вес для корня левого поддерева
	int weightBTRight = 0;//вес для корня правого поддерева
	int lastWeight;//для веса корня последнего элемента, добавленного в правое поддерево
		std::wstring lastSymb;//для корня последнего элементы, который будет добавлен в правое поддерево
		for (auto i : rootString) //проходимся по каждому символу корня
		{
			for (auto j : elements)//проходимся по каждому элементу вектора
			{
				if (i == j->getRoot()[0])
				{
					//если текущий вес корня правого поддерева меньше половины веса дерева, то
						//добавляем к правому поддереву еще один элемент, иначе добавляем элемент к левому поддереву
						if (weightBTRight <= tree->getNum() / 2)
						{
							rootBTRight += j->getRoot();
							weightBTRight += j->getNum();
							lastWeight = j->getNum();
							lastSymb = j->getRoot();
						}
						else
						{
							rootBTLeft += j->getRoot();
							weightBTLeft += j->getNum();
						}
				}
			}
		}
	//проверяем получили ли минимальную разницу между весами корней правого и левого поддерева
	//если нет, то удаляем из правого поддерева последний элемент и ставим его в начало левого поддерева
	int diff = weightBTRight - weightBTLeft;
	if (abs(weightBTRight - lastWeight - (weightBTLeft + lastWeight)) <= diff)
	{
		weightBTRight -= lastWeight;
		weightBTLeft += lastWeight;
		rootBTLeft = lastSymb + rootBTLeft;
		rootBTRight.pop_back();
		if (weightBTLeft >= weightBTRight)
		{
			swp(weightBTLeft, weightBTRight);
			swp(rootBTLeft, rootBTRight);
		}
	}
	tree->setLeft(createBinaryTreeSF(new BinaryTree(rootBTLeft, weightBTLeft), elements));
	tree->setRight(createBinaryTreeSF(new BinaryTree(rootBTRight, weightBTRight), elements));
	return tree;
}
void BinaryTree::getCods(std::vector<std::pair<std::wstring, std::wstring>>&vec, std::wstring str = L"")
{
		if (this->left != nullptr && this->right != nullptr)
		{
			this->left->getCods(vec, str + L"0");
			this->right->getCods(vec, str + L"1");
		}
		else
		{
			vec.push_back(std::pair<std::wstring, std::wstring>(this->getRoot(), str));
		}
}
void BinaryTree::printCods()
{
	std::vector<std::pair<std::wstring, std::wstring>> vec;
	getCods(vec, L"");
	std::sort(vec.begin(), vec.end(), [](std::pair<std::wstring, std::wstring>i, std::pair<std::wstring, std::wstring> j)
		{
			if (i.second.length() != j.second.length())
			{
				return i.second.length() < j.second.length();
			}
			return i.first < j.first;
		});
	std::wstring str = L"";
	for (auto i : vec)
	{
		str += i.first;
		str += L"(";
		str += i.second;
		str += L")";
	}
	std::wcout << str << '\n';
}

Elem BinaryTree::getCods()
{
	std::vector<std::pair<std::wstring, std::wstring>> vec;
	getCods(vec, L"");
	std::sort(vec.begin(), vec.end(), [](std::pair<std::wstring, std::wstring>i, std::pair<std::wstring, std::wstring> j)
		{
			if (i.second.length() != j.second.length())
			{
				return i.second.length() < j.second.length();
			}
			return i.first < j.first;
		});
	std::wstring str = L"";
	for (auto i : vec)
	{
		str += i.first;
		str += L"(";
		str += i.second;
		str += L")";
	}
	str += L'\n';
	return str;
}
