#include "pch.h"
#include <cmath>

#include "AVLTree.h"

AVLTree::AVLTree(int key) { // ����������� ������
	this->height = 1;
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
}

bool AVLTree::findKey(int k) { // ���������, ���� �� � ������ ������� � ������ == k
	if (this == nullptr) { // ���� ������ ������� - ���������� ��������
		return false;
	}
	if (this->key == k) { // ���� ����� - ����� ���������� ��������
		return true;
	}
	return this->left->findKey(k) | this->right->findKey(k); // ��������� ����� � ����� � ������ �����������
}

int AVLTree::getHeight() { // ������ � ������ ��������
	if (this != nullptr) {
		return this->height;
	}
	return 0;
}

int AVLTree::bFactor() { // ����������� ������-������ ��������
	return this->right->getHeight() - this->left->getHeight();
}

void AVLTree::fixHeight() { // ����������� ������ ����� ��������
	int lheight = left->getHeight();
	int rheight = right->getHeight();
	if (lheight > rheight) {
		this->height = lheight + 1;
	}
	else {
		this->height = rheight + 1;
	}
}

AVLTree* AVLTree::rotateRightSmall(std::ostream* stream) { // ������ �������
	if (stream != nullptr) *stream << "������������ ����� ������� �������� " << this->key << " ������.\n";
	//std::cout << "������������ ����� ������� �������� " << this->key << " ������.\n";
	AVLTree* tmp = this->left;
	this->left = tmp->right;
	tmp->right = this;
	fixHeight();
	tmp->fixHeight();
	return tmp;
}

AVLTree* AVLTree::rotateLeftSmall(std::ostream* stream) { // ����� �������
	if (stream != nullptr) *stream << "������������ ����� ������� �������� " << this->key << " �����.\n";
	//std::cout << "������������ ����� ������� �������� " << this->key << " �����.\n";
	AVLTree* tmp = right;
	this->right = tmp->left;
	tmp->left = this;
	fixHeight();
	tmp->fixHeight();
	return tmp;
}

AVLTree* AVLTree::balance(std::ostream* stream) { //����������� ������
	fixHeight();
	if (this->bFactor() == 2)
	{
		if (this->right->bFactor() < 0) this->right = this->right->rotateRightSmall(stream);
		return this->rotateLeftSmall(stream);
	}
	if (this->bFactor() == -2)
	{
		if (this->left->bFactor() > 0) this->left = this->left->rotateLeftSmall(stream);
		return this->rotateRightSmall(stream);
	}
	return this;
}

AVLTree* AVLTree::insert(int k, std::ostream* stream) { // ��������� ������� � ������ == k
	if (this == nullptr) { // ���� ����� �� ������� ��������, ������ ����� �������
		//std::cout << "������������ ������� �������� " << k << '\n';
		if (stream != nullptr) *stream << "������������ ������� �������� " << k << '\n';
		return new AVLTree(k);
	}
	// �����...
	if (k < this->key) {
		this->left = this->left->insert(k, stream); // ...���� ���� �������� ������ ����� ��������, ������� ����� ���������
	}
	if (k > this->key) {
		this->right = this->right->insert(k, stream); // ...���� ���� �������� ������ ����� ��������, ������� ������ ���������
	}
	return balance(stream);
}

AVLTree* AVLTree::findMin() { // ���������� ����������� �������
	if (this->left != nullptr) {
		return this->left->findMin();
	}
	else if (this->right != nullptr) {
		return this->right->findMin();
	}
	return this;
}

AVLTree* AVLTree::removeMin(std::ostream* stream) {  // ������� ����������� ������� 
	if (left == nullptr) {
		return right;
	}
	left = left->removeMin(stream);
	return balance(stream);
}

AVLTree* AVLTree::remove(int k, std::ostream* stream) { // ������� ������� � ������ == k
	if (this == nullptr) return this; // ���� ����� �� ������� �������� - ���������� 0
	if (k < this->key) this->left = this->left->remove(k, stream); // ���� ���� ������ ����� �������� ��������, ���� � ����� ���������
	else if (k > this->key) this->right = this->right->remove(k, stream); // ���� ���� ������ ����� �������� ��������, ���� � ������ ���������
	else {
		AVLTree* ltree = this->left;
		AVLTree* rtree = this->right;
		//std::cout << "������������ �������� �������� " << k << '\n';
		if (stream != nullptr) *stream << "������������ �������� �������� " << k << '\n';
		delete this;
		if (!rtree) return ltree;
		AVLTree* min = rtree->findMin();
		min->right = rtree->removeMin(stream);
		min->left = ltree;
		return min->balance(stream);
	}
	return balance(stream);
}

void AVLTree::destroy() { // ����������� ������, ���������� ��� ������
	if (this != nullptr) {
		this->left->destroy();
		this->right->destroy();
		delete this;
	}
}

void AVLTree::printTree(std::ostream* stream, int treeHeight, int depth = 0, int level = 0) { // �������� ������ � std::cout � � ���� �� �������
	if (depth == level) {
		if (this != nullptr) *stream << key; // �������� ������
		else *stream << "  ";
		for (int i = 0; i < pow(2, treeHeight - (level + 1)); i++) *stream << "\t"; //������
		if (level < treeHeight - 1) *stream << "    ";
		return;
	}
	else {
		if (this == nullptr) {
			this->printTree(stream, treeHeight, depth + 1, level);
			this->printTree(stream, treeHeight, depth + 1, level);
		}
		else{
		this->left->printTree(stream, treeHeight, depth + 1, level); // �������� ����� ���������
		this->right->printTree(stream, treeHeight, depth + 1, level); // �������� ����� ���������
		}
	}
}