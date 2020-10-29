
#include <iostream>
#include <cstring>



class binTree {
public:
	int size = 100;
	char* elementsArray = new char[size]; //массив, в котором хранятся элементы деерва
	binTree() {
		for (int i = 0; i < size; i++)
			elementsArray[i] = '_'; //инициализируется "пустым" символом
	}
	friend void printLKP(binTree* b, int index);
	bool isLeaf(int index) {
		return (!strchr("+-/*", elementsArray[index])); //функция проверяет, является ли элемент "листом"
	}
	int getRightElemIndex(int index) {
		return index * 2 + 2; //возвращает индекс правого потомка
	}
	int getLeftElemIndex(int index) {
		return index * 2 + 1; //возвращает индекс левого потомка
	}

	bool areEqualElements(int index1, int index2) { //проверка идентичности двух элементов
		

		if (isLeaf(index1) && isLeaf(index2)) {
			
			return (elementsArray[index1] == elementsArray[index2]);
		}

			else if (isLeaf(index1) == isLeaf(index2)){ //если оба элемента поддеревья, то далее проверяются их потомки

				return areEqualElements(getLeftElemIndex(index1), getLeftElemIndex(index2))
					&& areEqualElements(getRightElemIndex(index1), getRightElemIndex(index2));
			}
      else return false;
		}
	

	
	void transform() { //замена поддеревьев вида (f + f) на (2 * f)
		int i = 0;
		for (int i = 0; i < size; i++)
		if (!isLeaf(i)) {
			std::cout << "Проверка поддерева: ";
			printLKP(this, i);
			std::cout << "\n";
			if (areEqualElements(getLeftElemIndex(i), getRightElemIndex(i)) && elementsArray[i] == '+') {

				std::cout << "Поддерево ";
				printLKP(this, i);
				std::cout << " соответствует виду (f+f). Производится замена на ";
				elementsArray[i * 2 + 1] = '2';
				elementsArray[getRightElemIndex(i * 2 + 1)] = '_';
				elementsArray[getLeftElemIndex(i * 2 + 1)] = '_';
				elementsArray[i] = '*';
				printLKP(this, i);
				std::cout << "\n";
			}
		}
	}
};
void readBinTree(binTree* b, int index, FILE* f);


void printLKP(binTree* b, int index = 0){//вывод дерева-формула

	if (index < b->size && b->elementsArray[index] != '_') {
		
		if (!b->isLeaf(index))
			std::cout << "(";
		printLKP(b, index * 2 + 1);
		std::cout << b->elementsArray[index];
		printLKP(b, index * 2 + 2);
		if (!b->isLeaf(index))
			std::cout << ")";
	}
}

//функции для считывания дерева
void readLeftElem(binTree* b, int index, FILE* f) {
	b->elementsArray[index * 2 + 1] = fgetc(f);
	readBinTree(b, index* 2 + 1, f);
}
void readRightElem(binTree* b, int index, FILE* f) {
	b->elementsArray[index * 2 + 2] = fgetc(f);
	readBinTree(b, index * 2 + 2, f);
	
}
void readBinTree(binTree* b, int index, FILE* f) {

	if (index == 0)b->elementsArray[index] = fgetc(f);

	if (strchr("+-/*", b->elementsArray[index])) {
		readLeftElem(b, index, f);
		readRightElem(b, index, f);
	}
	
}

int main()
{
	
	
	binTree bt;
	char* c = new char[300];
	char* a = new char[20];
	while (strcmp(a, "1\n") && strcmp(a, "2\n")) {
		std::cout << "Обработка бинарного дерева. Введите 1 для ввода дерева с консоли или 2 для ввода с файла\n";
			fgets(a, 20, stdin);
	}
	if (strcmp(a, "1\n") == 0) {
		std::cout << "Введите дерево в префиксной форме: ";
		readBinTree(&bt, 0, stdin);
		
	}
	else {
		FILE* f1 = fopen("test.txt", "r+");
		std::cout << "Содержимое файла: ";
		while (fgets(c, 300, f1)) std::cout << c;
		f1 = fopen("test.txt", "r+");
		readBinTree(&bt, 0, f1);
		std::cout << "\n";
	  fclose(f1);
		
	}

	std::cout << "Дерево-формула: ";
	printLKP(&bt);
	
	std::cout << "\nВывод преобразованного дерева-формулы с заменой поддеревьев вида (f + f) на (2 * f):\n";
	bt.transform();
	std::cout << "Результат: ";
	printLKP(&bt, 0);
	std::cout << "\n";
	
}
