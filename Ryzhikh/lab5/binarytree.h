#ifndef BINARYTREEHUFF_H
#define BINARYTREEHUFF_H
#include <string>
#include <vector>
#include <algorithm>
typedef std::wstring Elem;
class BinaryTree
{
public:
	BinaryTree(BinaryTree* left, BinaryTree* right);//конструктор
	BinaryTree(Elem elem, int num);//конструктор
	BinaryTree(std::vector<BinaryTree*>& vect);//конструктор
	Elem getRoot();//возвращает значение корня
	BinaryTree* getLeft();//возвращает левое поддерево
	BinaryTree* getRight();//возвращает правое поддерево
	void setRight(BinaryTree* bt);//устанавливает правое поддерево
	void setLeft(BinaryTree* bt);//устанавливает левое поддерево
	int getNum();//возвращает вес корня
	void setNum(int num);//устанавливает вес корня
	void printBT(int level = 0);//изображает дерево в видеуступчатого списка
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
void destroy(BinaryTree* tree); //освобождение памяти
BinaryTree* createBinaryTreeHuff(std::vector<BinaryTree*>& elements);//создает дерево Хаффмана
BinaryTree* createBinaryTreeSF(BinaryTree* tree, std::vector<BinaryTree*> elements);//создает дерево Шеннона-Фано
#endif // BINARYTREEHUFF_H
