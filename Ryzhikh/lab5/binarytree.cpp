#include "binarytree.h"
#include <iostream>
template<class T> void swp(T & el1, T & el2)//������ �������� �������
{
	T temp = el1;
	el1 = el2;
	el2 = temp;
}
BinaryTree::BinaryTree(BinaryTree* left, BinaryTree* right)//�����������
{
	this->left = left;
	this->right = right;
	this->num = left->getNum() + right->getNum();
	this->root = left->root + right->root;
}
BinaryTree::BinaryTree(Elem elem, int num)//�����������
{
	this->root = elem;
	this->num = num;
}
BinaryTree::BinaryTree(std::vector<BinaryTree*>& vect)//�����������
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
void destroy(BinaryTree* tree)//�������� ������
{
	if (tree != nullptr)
	{
		destroy(tree->getLeft());
		destroy(tree->getRight());
		delete tree;
	}
}
Elem BinaryTree::getRoot()//���������� ������ ������
{
	return this->root;
}
BinaryTree* BinaryTree::getRight()//���������� ������ ���������
{
	return this->right;
}
BinaryTree* BinaryTree::getLeft()//���������� ����� ���������
{
		return this->left;
}
int BinaryTree::getNum()//���������� ��� ����� ������
{
	return this->num;
}
void BinaryTree::setNum(int num)//������������� ��� ����� ������
{
	this->num = num;
}
void BinaryTree::printBT(int level)//���������� ���������� ������ � ���� ����������� ������
{
	if (left != nullptr)
		left->printBT(level + 1);
	for (int i = 0; i < level; i++)std::wcout << " --- ";
	std::wcout << root << '(' << num << ')' << '\n';
	if (right != nullptr)
		right->printBT(level + 1);
}
void BinaryTree::setLeft(BinaryTree* bt)//������������� ����� ���������
{
	this->left = bt;
}
void BinaryTree::setRight(BinaryTree* bt)//������������� ������ ���������
{
	this->right = bt;
}
BinaryTree* createBinaryTreeHuff(std::vector<BinaryTree*>&
	elements)//�������� ������ ��������
{
	//���� � ������� ������� ���� �������, �� ���� ������� �������� ����������� ������� �������� � �� ������������ �� �������
		if (elements.size() == 1)
			return elements[0];
	BinaryTree* temp1 = elements[elements.size() - 1];
	BinaryTree* temp2 = elements[elements.size() - 2];
	elements.pop_back(); //������� ������� �� ����� �������
	elements.pop_back(); //������� ������� �� ����� �������
	BinaryTree* parent = new BinaryTree(temp1, temp2);//������� �������� ������,� ������� temp1 � temp2 ����� ���������
		elements.push_back(parent); //��������� ����� ������ � ������
		//���������� �� ������ ����� ����������� �������(����� ������ ��� ����������)
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
BinaryTree* createBinaryTreeSF(BinaryTree* tree, std::vector<BinaryTree*>
	elements)//�������� ������ ����- �������
{
	//���� ����� ����� ������ ����� 1, �� ���������� ��� ������
	if (tree->getRoot().length() == 1)
	{
			return tree;
	}
	std::wstring rootString = tree->getRoot(); //�������� �������� �����
	std::wstring rootBTLeft = L"";//������ ��� ����� ������ ���������
	std::wstring rootBTRight = L"";//������ ��� ����� ��������� ���������
	int weightBTLeft = 0;//��� ��� ����� ������ ���������
	int weightBTRight = 0;//��� ��� ����� ������� ���������
	int lastWeight;//��� ���� ����� ���������� ��������, ������������ � ������ ���������
		std::wstring lastSymb;//��� ����� ���������� ��������, ������� ����� �������� � ������ ���������
		for (auto i : rootString) //���������� �� ������� ������� �����
		{
			for (auto j : elements)//���������� �� ������� �������� �������
			{
				if (i == j->getRoot()[0])
				{
					//���� ������� ��� ����� ������� ��������� ������ �������� ���� ������, ��
						//��������� � ������� ��������� ��� ���� �������, ����� ��������� ������� � ������ ���������
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
	//��������� �������� �� ����������� ������� ����� ������ ������ ������� � ������ ���������
		//���� ���, �� ������� �� ������� ��������� ��������� ������� � ������ ��� � ������ ������ ���������
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
	tree->setLeft(createBinaryTreeSF(new
		BinaryTree(rootBTLeft, weightBTLeft), elements));
	tree->setRight(createBinaryTreeSF(new
		BinaryTree(rootBTRight, weightBTRight), elements));
	return tree;
}
void
BinaryTree::getCods(std::vector<std::pair<std::wstring, std::wstring>>&vec, std::wstring str = L"")
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
