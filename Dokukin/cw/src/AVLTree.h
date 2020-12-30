#ifndef COURSEWORK_AVLTREE_H
#define COURSEWORK_AVLTREE_H

#include <iostream>
#include <fstream>

class AVLTree {
private:
	int height;
	int key;
	AVLTree* left;
	AVLTree* right;
public:
	AVLTree(int);
	int getHeight();
	bool findKey(int);
	void printTree(std::ostream*, int, int, int);
	int bFactor();
	void fixHeight();
	AVLTree* rotateRightSmall(std::ostream*);
	AVLTree* rotateLeftSmall(std::ostream*);
	AVLTree* balance(std::ostream*);
	AVLTree* insert(int, std::ostream*);
	AVLTree* findMin();
	AVLTree* removeMin(std::ostream*);
	AVLTree* remove(int, std::ostream*);
	void destroy();
};

#endif

