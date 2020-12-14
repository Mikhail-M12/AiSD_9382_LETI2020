#include <fstream>
#include "binSTree.h"
#include <ctime>
#include <cstdlib>


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите f если хотите загрузить из файла, иначе любой другой символ для работы с консолью (Только латинские символы)" << std::endl;
    char symbol;
    char elem;
    node<char>* bt = nullptr;
    std::cin >> symbol;
    if (symbol == 'f') {
        std::ifstream file;
        std::string path;
        std::cout << "Введите название файла, откуда будет считыватся дерево в формате <name.txt>" << std::endl;
        std::cin >> path;
        file.open(path);
        if (file.is_open()) {
            std::cout << "Файл успешно открыт, начинаю построение" << std::endl;
            std::cout
                    << "Случайные БДП с рандомизацией имеют такую особенность, что добавление очередного элемента может производиться"
                    << std::endl;
            std::cout
                    << "как в корень элемента, используя вращения, так и в свое законное место в обычном случайном БДП."
                    << std::endl;
        } else {
            std::cout << "Открыть файл не удалось, завершение программы" << std::endl;
            return 0;
        }


        int step = 1;
        while (file >> elem) {
            std::cout << std::endl << "Шаг " << step << ":" << std::endl;
            std::cout << "Получен элемент " << elem << std::endl;
            bt = insert(bt, elem);
            std::cout << "******************" << std::endl;
            std::cout << "Дерево после " << step << " шага:" << std::endl;
            std::cout << "▶ ";
            step++;
            printBT(bt);
        }
        std::cout << "Дерево из файла построено." << std::endl;
        std::cout << "Всего символов прочитано: " << (step - 1) << std::endl;
        std::cout << "Высота дерева = " << heightBT(bt) << std::endl;
    } else{
        std::cout << "Введите количество элементов" << std::endl;
        int count;
        std::cin >> count;
        std::cout << "Введите данные" << std::endl;
        int step = 1;
        for (int i = 0; i < count; i++) {
            std::cin >> elem;
            std::cout << std::endl << "Шаг " << step << ":" << std::endl;
            std::cout << "Получен элемент " << elem << std::endl;
            bt = insert(bt, elem);
            std::cout << "******************" << std::endl;
            std::cout << "Дерево после " << step << " шага:" << std::endl;
            std::cout << "▶ ";
            step++;
            printBT(bt);
        }
        std::cout << "Дерево из консоли построено." << std::endl;
        std::cout << "Всего символов прочитано: " << (step - 1) << std::endl;
        std::cout << "Высота дерева = " << heightBT(bt) << std::endl;
    }
	
	std::cout << "Какой элемент найти?" << std::endl;
	std::cin >> elem;
	int count = find(bt, elem);
	if (count == 0) std::cout << "Такого элемета нет в дереве" << std::endl;
	else std::cout << "В дереве находится " << count << " экз. введенного элемента" << std::endl;
    std::cout << "Произвожу встваку элемента " << elem << " в дерево" << std::endl;
	bt = insert(bt, elem);
	std::cout << "Дерево после добавления:" << std::endl;
	std::cout << "▶ ";
	printBT(bt);

	char isWork = '\0';
	while (isWork != 'n'){
		std::cout << "Хотите ли продолжить работу с деревом? y - да, n - завершить программу" << std::endl;
		std::cin >> isWork;
		if (isWork == 'y'){
			std::cout << "Какой элемент добавить в дерево?" << std::endl;
			std::cin >> elem;
            bt = insert(bt, elem);
			std::cout << "Дерево после добавления:" << std::endl;
			std::cout << "▶ ";
			printBT(bt);
		}
	}
	return 0;
}
