#include <iostream>
#include <fstream>
#include <string>

#include "AVLTree.h"

void treeOutput(std::ostream* stream, AVLTree* tree) { // Наглядный вывод дерева на экран
	if (tree == nullptr) {
		*stream << "[empty tree]\n";
		return;
	}
	for (int j = 0; j < tree->getHeight(); j++) {
		if (j < tree->getHeight() - 1) {
			for (int k = 0; k < pow(2, tree->getHeight() - j - 2) - 1; k++) {
				*stream << "\t";
			}
			*stream << "    ";
		}
		tree->printTree(stream, tree->getHeight(), 0, j);
		*stream << "\n\n";
	}
}

int main()
{
	int a;
	std::cout << "Choose input option(0 - file input, 1 - console input):\n";
	std::cin >> a;

	int count;
	int key;
	AVLTree* tree = nullptr;

	std::filebuf outputf;
	outputf.open("output.txt", std::ios::out);
	std::ostream output(&outputf);

	if (a) {
		std::cout << "Insert elements' count: ";
		std::cin >> count;
		for (int i = 0; i < count; i++) {
			std::cout << "Insert element key: ";
			std::cin >> key;
			if (tree == nullptr) tree = new AVLTree(key);
			else tree = tree->insert(key, &std::cout);
			treeOutput(&std::cout, tree);
		}
		output << "Sorted elements: ";
		if (tree != nullptr) tree->printLKP(&output);
		else output << "Empty tree\n";
		output << "\nYour tree:\n";
		treeOutput(&output, tree);
		tree->destroy();
		tree = nullptr;
		return 0;
	}

	std::ifstream inputf("tests.txt");
	if (!inputf) {
		std::cout << "Couldn't open file.\n";
		return 1;
	}
	
	while (!inputf.eof()) {
		inputf >> count;
		for (int i = 0; i < count; i++) {
			inputf >> key;
			if (tree == nullptr) tree = new AVLTree(key);
			else tree = tree->insert(key, &std::cout);
		}
		output << "Sorted elements: ";
		if (tree != nullptr) tree->printLKP(&output);
		else output << "Empty tree\n";
		output << "\nYour tree:\n";
		treeOutput(&output, tree);
		tree->destroy();
		tree = nullptr;
		output << "---------------------------------------------\n";
	}
	return 0;
}