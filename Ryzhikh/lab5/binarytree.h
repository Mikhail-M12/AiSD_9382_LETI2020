#ifndef BINARYTREEHUFF_H
#define BINARYTREEHUFF_H
#include <string>
#include <vector>
#include <algorithm>
typedef std::wstring Elem;
class BinaryTree
{
public:
	BinaryTree(BinaryTree* left, BinaryTree* right);//�����������
	BinaryTree(Elem elem, int num);//�����������
	BinaryTree(std::vector<BinaryTree*>& vect);//�����������
	Elem getRoot();//���������� �������� �����
	BinaryTree* getLeft();//���������� ����� ���������
	BinaryTree* getRight();//���������� ������ ���������
	void setRight(BinaryTree* bt);//������������� ������ ���������
	void setLeft(BinaryTree* bt);//������������� ����� ���������
	int getNum();//���������� ��� �����
	void setNum(int num);//������������� ��� �����
	void printBT(int level = 0);//���������� ������ � ��������������� ������
	void printCods();
	void
		getCods(std::vector<std::pair<std::wstring, std::wstring>>& vec,
			std::wstring str);
private:
	Elem root;
	BinaryTree * left = nullptr;
	BinaryTree* right = nullptr;
	int num;
};
void destroy(BinaryTree* tree); //������������ ������
BinaryTree* createBinaryTreeHuff(std::vector<BinaryTree*>& elements);//������� ������ ��������
BinaryTree* createBinaryTreeSF(BinaryTree* tree, std::vector<BinaryTree*> elements);//������� ������ �������-����
#endif // BINARYTREEHUFF_H
