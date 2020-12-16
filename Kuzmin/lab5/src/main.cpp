#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
//элемент дерамиды
class TreapElem {
public:
	int key; 
	int prior;
	TreapElem* right = nullptr;
	TreapElem* left = nullptr;

	TreapElem(int key, char prior): key(key), prior(prior) {}
	TreapElem(int key):key(key){
		prior = rand() % 100;
	}
	TreapElem() {}
	friend std::istream& operator>>(std::istream& in, TreapElem& e) { //оператор ввода из потока. каждый элемент представляется
																	//в виде(x, y), где x - ключ, y - приоритет
		while (in.get() != '(' && !in.eof()) {}
		in >> e.key;
		while (in.get() != ',' && !in.eof()) {}
		in >> e.prior;
		while (in.get() != ')' && !in.eof()) {}
		return in;
	}

	friend std::ostream& operator<<(std::ostream& out, TreapElem* e) {  //оператор вывода в поток
																		//пустые элементы выводятся как (null)
		if(e != nullptr)
		out << '(' << e->key << "," << e->prior << ")";
		else out << "(null)";
		return out;
	}
};

class Treap {

public:

	TreapElem* root;

	Treap() {
		root = nullptr;
	}
	//вставка элемента
	void insert(TreapElem*& root, TreapElem a) 
	{
		//создание нового элемента на месте некоторого пустого, выход из функции
		if (root == nullptr)
		{
			std::cout << "Встречен пустой узел. Создание нового элемента " << &a << " на его месте.\n";
			root = new TreapElem(a);
			return;
		}
		//сравнения с ключом текущего узла
		if (a.key < root->key) {
			std::cout << "Значение ключа вставляемого элемента -" << &a << " меньше значения ключа текущего элемента - " << root << "\n";
			std::cout << "Переход к левому потомку\n";
			insert(root->left, a);
		}

		else if (a.key >= root->key) {
			std::cout << "Значение ключа вставляемого элемента -" << &a << " не меньше значения ключа текущего элемента - " << root<< "\n";
			std::cout << "Переход к правому потомку\n";
			insert(root->right, a);
		}

		//повороты (если требуется)
		if (root->left && root->left->prior > root->prior) { 
			std::cout << "Значение приоритета элемента " << root->left << " больше чем значение приоритета элемента " << root << "\n";
			std::cout << "Осуществляется поворот направо\n";
			rotRight(root);
		}

		if (root->right && root->right->prior > root->prior) {
			std::cout << "Значение приоритета элемента " << root->right << " больше чем значение приоритета элемента " << root << "\n";
			std::cout << "Осуществляется поворот налево\n";
			rotLeft(root);
		}
	}

	//поворот налево
	void rotLeft(TreapElem*& el) {

		std::cout<<"Поворот налево узла " << el <<":\n";
		TreapElem* newEl = el->right;
		std::cout << "Корень нового узла равен " << el->right;
		el->right = newEl->left;
		std::cout << "\nЛевый потомок нового узла равен " << el << "\n";
		newEl->left = el;
		el = newEl;
	}
	//поворот направо
	void rotRight(TreapElem*& el) {
		std::cout << "Поворот направово узла " << el << ":\n";
		TreapElem* newEl = el->left;
		std::cout << "Корень нового узла равен " << newEl;
		el->left = newEl->right;
		newEl->right = el;
		el = newEl;
		std::cout << "\nПравый потомок нового узла равен " << newEl->right <<"\n";
	}
	//считывание и построение дерамиды
	void read(std::istream& is) {
		std::vector<TreapElem> treapVector;
		while (1) {
			TreapElem a;
			is >> a;
			treapVector.push_back(a);
			char tmp = is.get();
			if (tmp == '\n' || tmp == EOF) break;
		}
		std::cout << "\nПостроение дерамиды:\n";
		for (auto it : treapVector) {
			std::cout << "Вставка элемента " << &it <<":\n";
			insert(root, it);
			std::cout << "\n";
		}
	}

	//проверка является ли элемент листом
	bool isLeaf(TreapElem* e) {
		return (!e->left && !e->right);
	}
	//поиск элемента в дерамиде, функция возвращает количество вхождений
	int find(TreapElem* root, TreapElem e){

		if (root) {
			std::cout << "Просмотр текущего узла " << root << "\n";
			if (root->key == e.key && root->prior == e.prior  && isLeaf(root)){
				std::cout << "Узел является листом и совпадает с искомым элементом. Количество вхожденией увеличено на 1.\n";
				return 1;
			}

			else if (root->key == e.key && root->prior == e.prior  && !isLeaf(root)) {
		
				std::cout << "Узел совпадает с искомым элементом и не является листом. Количество вхождений увеличено на 1. Переход к правому потомку.\n";
				return 1 + find(root->right, e);
			}

			else {
				std::cout << "Текущий узел не совпадает с искомым.\n";
				if (e.key >= root->key) {
					std::cout << "Ключ искомого элемента больше или равен ключу текущего узла " << root;
					std::cout << "\nПереход к правому потомку.\n";
					return find(root->right, e);
				}
				else {
					std::cout << "Ключ искомого элемента меньше ключа текущего узла " << root;
					std::cout << "\nПереход к левому потомку.\n";
					return find(root->left, e);
				}
			}
		}
		else {
			std::cout << "Встречен пустой узел.\n";
			return 0;
		}
	}
	//вывод узлов в формате ЛКП
	void printLKP(TreapElem* root) {
		if (root) {
			if (isLeaf(root)) std::cout << root;
			else {
				printLKP(root->left);
				std::cout << root;
				printLKP(root->right);
			}
		}
		else std::cout << root;
	}
};
//интерфейс для вызова функции поиска
void findInterface(Treap& treap) {
	
		std::cout << "\nВведите элемент в формате (ключ, приоритет), который нужно найти либо пустую строку для выхода из программы.\n";
		char* n = new char[20];
		fgets(n, 20, stdin);
		if (strcmp(n, "\n") == 0) return;
		else {
			std::stringstream ss(n);
			TreapElem b;
			ss >> b;

			std::cout << "\nПоиск элемента " << &b << "\n";
			int count = treap.find(treap.root, b);
			std::cout << "Количество вхождений элемента " << &b << " - " << count << "\n\n";

			std::cout << "Вставка элемента " << &b << ":\n";

			treap.insert(treap.root, b);

			std::cout << "Элемент " << &b << " добавлен в дерамиду\n\nПолученная дерамида(список узлов в порядке лкп):\n";

			treap.printLKP(treap.root);
			std::cout << "\n";

			findInterface(treap);
		}

}
int main() {
	
	Treap treap;
	setlocale(LC_ALL, "Russian");
	char* a = new char[20];
	while (1) {
		std::cout << "Введите 1 для ввода с консоли и 2 для ввода с файла:\n";
		fgets(a, 20, stdin);
		if (a[1] != '\n' || (a[0] != '1' && a[0] != '2')) continue;
		else {
			switch (a[0]) {
			case '1':
				std::cout << "Введите последовательность элементов дерамиды в виде (ключ, приоритет) через пробел\n";
				treap.read(std::cin);
				break;
			case '2':
				std::ifstream ifs("test.txt");
				char d;
				std::cout << "Содержимое файла: ";
				while (ifs.get(d)) std::cout << d;
				std::cout << "\n";
				ifs.close();
				ifs.open("test.txt");
				treap.read(ifs);
				ifs.close();
				break;
			}
				break;
		}
	}

	std::cout << "Построенная дерамида(узлы в порядке лкп):\n";

	treap.printLKP(treap.root);

	std::cout << "\n";

	findInterface(treap);

	return 0;

}