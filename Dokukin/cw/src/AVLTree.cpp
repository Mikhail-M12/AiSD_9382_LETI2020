#include "pch.h"
#include <cmath>

#include "AVLTree.h"

AVLTree::AVLTree(int key) { // Конструктор дерева
	this->height = 1;
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
}

bool AVLTree::findKey(int k) { // Проверяем, есть ли в дереве элемент с ключом == k
	if (this == nullptr) { // Если пустой элемент - прекращаем рекурсию
		return false;
	}
	if (this->key == k) { // Если нашли - также прекращаем рекурсию
		return true;
	}
	return this->left->findKey(k) | this->right->findKey(k); // Запускаем поиск в левом и правом поддеревьях
}

int AVLTree::getHeight() { // Доступ к высоте элемента
	if (this != nullptr) {
		return this->height;
	}
	return 0;
}

int AVLTree::bFactor() { // Высчитывает баланс-фактор элемента
	return this->right->getHeight() - this->left->getHeight();
}

void AVLTree::fixHeight() { // Высчитываем высоту после поворота
	int lheight = left->getHeight();
	int rheight = right->getHeight();
	if (lheight > rheight) {
		this->height = lheight + 1;
	}
	else {
		this->height = rheight + 1;
	}
}

AVLTree* AVLTree::rotateRightSmall(std::ostream* stream) { // Правый поворот
	if (stream != nullptr) *stream << "Производится малый поворот элемента " << this->key << " вправо.\n";
	//std::cout << "Производится малый поворот элемента " << this->key << " вправо.\n";
	AVLTree* tmp = this->left;
	this->left = tmp->right;
	tmp->right = this;
	fixHeight();
	tmp->fixHeight();
	return tmp;
}

AVLTree* AVLTree::rotateLeftSmall(std::ostream* stream) { // Левый поворот
	if (stream != nullptr) *stream << "Производится малый поворот элемента " << this->key << " влево.\n";
	//std::cout << "Производится малый поворот элемента " << this->key << " влево.\n";
	AVLTree* tmp = right;
	this->right = tmp->left;
	tmp->left = this;
	fixHeight();
	tmp->fixHeight();
	return tmp;
}

AVLTree* AVLTree::balance(std::ostream* stream) { //Балансируем дерево
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

AVLTree* AVLTree::insert(int k, std::ostream* stream) { // Вставляем элемент с ключом == k
	if (this == nullptr) { // Если дошли до пустого элемента, создаём новый элемент
		//std::cout << "Производится вставка элемента " << k << '\n';
		if (stream != nullptr) *stream << "Производится вставка элемента " << k << '\n';
		return new AVLTree(k);
	}
	// Иначе...
	if (k < this->key) {
		this->left = this->left->insert(k, stream); // ...если ключ элемента меньше ключа текущего, смотрим левое поддерево
	}
	if (k > this->key) {
		this->right = this->right->insert(k, stream); // ...если ключ элемента больше ключа текущего, смотрим правое поддерево
	}
	return balance(stream);
}

AVLTree* AVLTree::findMin() { // Возвращает минимальный элемент
	if (this->left != nullptr) {
		return this->left->findMin();
	}
	else if (this->right != nullptr) {
		return this->right->findMin();
	}
	return this;
}

AVLTree* AVLTree::removeMin(std::ostream* stream) {  // Удаляет минимальный элемент 
	if (left == nullptr) {
		return right;
	}
	left = left->removeMin(stream);
	return balance(stream);
}

AVLTree* AVLTree::remove(int k, std::ostream* stream) { // Удаляет элемент с ключом == k
	if (this == nullptr) return this; // Если дошли до пустого элемента - возвращаем 0
	if (k < this->key) this->left = this->left->remove(k, stream); // Если ключ меньше ключа текущего элемента, ищем в левом поддереве
	else if (k > this->key) this->right = this->right->remove(k, stream); // Если ключ больше ключа текущего элемента, ищем в правом поддереве
	else {
		AVLTree* ltree = this->left;
		AVLTree* rtree = this->right;
		//std::cout << "Производится удаление элемента " << k << '\n';
		if (stream != nullptr) *stream << "Производится удаление элемента " << k << '\n';
		delete this;
		if (!rtree) return ltree;
		AVLTree* min = rtree->findMin();
		min->right = rtree->removeMin(stream);
		min->left = ltree;
		return min->balance(stream);
	}
	return balance(stream);
}

void AVLTree::destroy() { // Освобождаем память, выделенную под дерево
	if (this != nullptr) {
		this->left->destroy();
		this->right->destroy();
		delete this;
	}
}

void AVLTree::printTree(std::ostream* stream, int treeHeight, int depth = 0, int level = 0) { // Печатаем дерево в std::cout и в файл по уровням
	if (depth == level) {
		if (this != nullptr) *stream << key; // Печатаем корень
		else *stream << "  ";
		for (int i = 0; i < pow(2, treeHeight - (level + 1)); i++) *stream << "\t"; //отступ
		if (level < treeHeight - 1) *stream << "    ";
		return;
	}
	else {
		if (this == nullptr) {
			this->printTree(stream, treeHeight, depth + 1, level);
			this->printTree(stream, treeHeight, depth + 1, level);
		}
		else{
		this->left->printTree(stream, treeHeight, depth + 1, level); // Печатаем левое поддерево
		this->right->printTree(stream, treeHeight, depth + 1, level); // Печатаем левое поддерево
		}
	}
}