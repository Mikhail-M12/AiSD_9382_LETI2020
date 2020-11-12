#include <fstream>
#include "binSTree.h"
#include <ctime> 

int main()
{
	srand(time(NULL));

    std::cout << "Write f - if reading from file, any other - if console" << std::endl;
    char symbol;
    std::cin >> symbol;
    char elem;
    /*
     * Считывания данных из файла
     */
    binSTree* bt = nullptr;
    if (symbol == 'f'){
        std::ifstream file;
        std::string path;
        std::cout << "Enter the name of the file where the tree will be read from" << std::endl;
        std::cin >> path;
        file.open(path);
        if (!file) {
            std::cout << "File could not be opened, program terminated" << std::endl;
            system("pause");
            std::cout << "To continue the program, press any key ...";
            std::cin.get();
            exit(1);
        }
        std::cout << "File opened successfully, start building" << std::endl;
        while (file >> elem)
        {
            /*
             * Занесение данных в дерево
             */
            randomInsert(bt, elem);
        }
        printBT(bt, "");
    } else{
        /*
         * Считывание данных из стандартного потока
         */
        std::cout<< "Enter count of elem"<< std::endl;
        int count;
        std::cin >> count;
        for (int i = 0; i < count; i++)
        {
            std::cin >> elem;
            /*
             * Занесение данных в дерево
             */
            randomInsert(bt, elem);
        }
        printBT(bt, "");
    }

	
	std::cout << "Which item to find?" << std::endl;
	std::cin >> elem;
	int count = find(bt, elem);
	if (count == 0) std::cout << "There is no such element in the tree" << std::endl;
	else std::cout << "In the tree is " << count << " an instance of the injected element" << std::endl;
    /*
     * Вызов функции вставки элемента
     */
	randomInsert(bt, elem);
	std::cout << "The tree after adding:" << std::endl;
	printBT(bt, "");
    /*
     * Работа с пользователем
     * Возможность закончить программу или продолжить работу
     */
	char isWork = '\0';
	while (isWork != 'n')
	{
		std::cout << "Do you want to continue working with the tree? y - yes, n - end the program" << std::endl;
		std::cin >> isWork;
		if (isWork == 'y')
		{
			std::cout << "Which element to add to the tree?" << std::endl;
			std::cin >> elem;
			randomInsert(bt, elem);
			std::cout << "The tree after adding:" << std::endl;
			printBT(bt, "");
		}
	}
	return 0;
}