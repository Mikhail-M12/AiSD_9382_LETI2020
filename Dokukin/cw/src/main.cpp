#include "pch.h"
#include <iostream>
#include <string>
#include <ctime>

#include "AVLTree.h"

void treeOutput(std::ostream* stream, AVLTree* tree) {
	if (tree == nullptr) {
		*stream << "[пустое дерево]\n";
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

void clear(AVLTree** trees, int* actions, int count) { // Очищаем все деревья
	for (int i = 0; i < count; i++) {
		trees[i]->destroy();
	}
	delete actions;
	delete trees;
}

void saveTasks(AVLTree** trees, int* actions, int insertcount, int deletecount) { // Заполнение файла с заданиями
	std::string insstr = ". Постройте дерево, получаемое из данного вставкой элемента ";
	std::string delstr = ". Постройте дерево, получаемое из данного исключением элемента ";

	std::filebuf t;
	t.open("tasks.txt", std::ios::out);
	std::ostream tasks(&t);
	tasks << "Текущий контроль\nСписок заданий\n\n";

	for (int i = 0; i < insertcount; i++) {
		tasks << "№" << i + 1 << insstr << actions[i] << ".\n\n"; // Записываем условие
		treeOutput(&tasks, trees[i]);
		tasks << '\n';
	}
	for (int i = insertcount; i < deletecount + insertcount; i++) {
		tasks << "№" << i + 1 << delstr << actions[i] << ".\n\n"; // Записываем условие
		treeOutput(&tasks, trees[i]);
		tasks << '\n';
	}
	t.close();

	std::filebuf a;
	a.open("answers.txt", std::ios::out);
	std::ostream answers(&a);
	answers << "Текущий контроль\nОтветы к заданиям\n\n";
	for (int i = 0; i < insertcount; i++) {
		answers << "№" << i + 1 << ".\nОперации над деревом:\n";
		trees[i]->insert(actions[i], &answers); // Вставляем в дерево элемент
		answers << "\nОтвет:\n";
		treeOutput(&answers, trees[i]); // Печатаем полученное дерево
		answers << '\n';
	}
	for (int i = insertcount; i < deletecount + insertcount; i++) {
		answers << "№" << i + 1 << ".\nОперации над деревом:\n";
		trees[i] = trees[i]->remove(actions[i], &answers); // Удаляем элемент из дерева
		answers << "\nОтвет:\n";
		treeOutput(&answers, trees[i]); // Печатаем полученное дерево
		answers << '\n';
	}
	std::cout << '\n';
	a.close();
}

AVLTree* randGenerator() {
	int key;
	int count = rand() % 16 + 5; // Генерируем количество элементов
	AVLTree* randtree = nullptr;
	for (int i = 0; i < count; i++) {
		key = rand() % 100 + 1;
		while (randtree->findKey(key)) {
			key = rand() % 100 + 1; // Если такой элемент уже есть - генерируем заново
		}
		randtree = randtree->insert(key, &std::cout); // Вставляем элемент в дерево
	}
	return randtree;
}

AVLTree* userGenerator() {
	int key, option;
	AVLTree* usertree = nullptr;
	while (true) { // Заполняем дерево
		std::cout << "Выберите действие:\n1 - вставка элемента\n2 - удаление элемента\n3 - сохранить дерево\n";
		std::cin >> option;
		switch (option) {
		case 1:
			std::cout << "Введите элемент для вставки: ";
			std::cin >> key;
			if (!usertree->findKey(key)) usertree = usertree->insert(key, &std::cout);
			else {
				std::cout << "Такой ключ уже имеется в дереве!\n";
				break;
			}
			std::cout << "Ваше дерево:\n";
			treeOutput(&std::cout, usertree);
			break;
		case 2:
			std::cout << "Введите элемент для удаления: ";
			std::cin >> key;
			if (usertree->findKey(key)) usertree = usertree->remove(key, &std::cout);
			else {
				std::cout << "Такого ключа в дереве нет!\n";
				break;
			}
			std::cout << "Ваше дерево:\n";
			treeOutput(&std::cout, usertree);
			break;
		case 3:
			std::cout << "Ваше дерево сохранено.\n";
			return usertree;
			break;
		default:
			std::cout << "Ошибка ввода.\n";
			break;
		}
	}
}

int treeCreator(int mode) {
	int insertcount;
	std::cout << "Введите количество заданий со вставкой элемента: ";
	std::cin >> insertcount;

	int deletecount;
	std::cout << "Введите количество заданий с удалением элемента: ";
	std::cin >> deletecount;

	if ((insertcount < 0) && (deletecount < 0)) { // Если введено некорректное количество - возвращаемся в главное меню
		std::cout << "Ошибка при вводе количества заданий.\n";
		return 1;
	}

	int count = insertcount + deletecount;
	AVLTree** trees = new AVLTree*[count];
	int* actions = new int[count];
	int option;

	std::cout << "------------------------------------------------------\n";
	for (int i = 0; i < insertcount; i++) {
		if (mode == 1) {
			std::cout << "Промежуточные данные:\n";
			trees[i] = randGenerator(); // Генерируем рандомные деревья
			actions[i] = rand() % 100 + 1;
			while (trees[i]->findKey(actions[i])) {
				actions[i] = rand() % 100 + 1; // Генерируем число, которое нужно будет вставить по заданию
			}
		}
		if (mode == 2) {
			std::cout << "Cоздание " << i + 1 << "-го дерева для задания по вставке.\n";
			trees[i] = userGenerator();
			std::cout << "Введите элемент, который необходимо вставить по условию задания: ";
			while (true) {
				std::cin >> actions[i];
				if (!trees[i]->findKey(actions[i])) break;
				std::cout << "Некорректный ключ для вставки.";
			}
		}
		std::cout << "\nИтоговое задание:\n№" << i + 1 << ". Постройте дерево, получаемое из данного вставкой элемента " << actions[i] << ".\n\n";
		treeOutput(&std::cout, trees[i]);
		std::cout << '\n';
	}
	for (int i = insertcount; i < count; i++) {
		if (mode == 1) {
			std::cout << "Промежуточные данные:\n";
			trees[i] = randGenerator(); // Генерируем рандомные деревья
			actions[i] = rand() % 100 + 1;
			while (!trees[i]->findKey(actions[i])) {
				actions[i] = rand() % 100 + 1; // Генерируем число, которое нужно будет удалить по заданию
			}
		}
		if (mode == 2) {
			std::cout << "Создание " << i + 1 << "-го дерева для задания по удалению.\n";
			trees[i] = userGenerator();
			std::cout << "Введите элемент, который необходимо удалить по условию задания: ";
			while (true) {
				std::cin >> actions[i];
				if (trees[i]->findKey(actions[i])) break;
				std::cout << "Некорректный ключ для удаления.";
			}
		}
		std::cout << "\nИтоговое задание:\n№" << i + 1 << ". Постройте дерево, получаемое из данного удалением элемента " << actions[i] << ".\n\n";
		treeOutput(&std::cout, trees[i]);
		std::cout << '\n';
	}

	while (true) {
		std::cout << "Сохранить результаты работы?\n1 - сохранить\n2 - не сохранять\n";
		std::cin >> option;
		switch (option) {
		case 1:
			saveTasks(trees, actions, insertcount, deletecount);
			clear(trees, actions, count);
			return 0;
			break;
		case 2:
			clear(trees, actions, count);
			return 1;
			break;
		default:
			std::cout << "Ошибка ввода.\n";
			break;
		}
	}
}

int main()
{
	srand(time(0));  // Берём случайное зерно генерации
	setlocale(LC_ALL, "rus");

	int option = 0;
	while (true) { // Основной цикл программы
		std::cout << "Выберите действие:\n1 - случайная генерация заданий\n2 - пользовательский ввод\n";
		std::cin >> option;
		switch (option) {
		case 1:
			std::cout << "Выбрана генерация случайных заданий.\n\n";
			if (!treeCreator(1)) {
				return 0;
			}
			break;
		case 2:
			std::cout << "Выбран режим пользовательского ввода.\n\n";
			if (!treeCreator(2)) {
				return 0;
			}
			break;
		default:
			std::cout << "Ошибка ввода.\n";
		}
	}
}