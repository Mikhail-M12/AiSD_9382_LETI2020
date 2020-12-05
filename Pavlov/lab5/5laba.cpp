#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

//Пара значений (необходимо для разных типов данных)
template <typename T> struct Pair {
	T x;
	T y;

	Pair(T x, T y) : x(x), y(y) {}
};

//Узел - элемент дерева
struct Node {
	Pair<int> p;
	Node* l, * r;

	Node(int x, int y) : p(Pair<int>(x, y)), l(nullptr), r(nullptr) {}
	Node(int x, int y, Node* l, Node* r) : p(Pair<int>(x, y)), l(l), r(r) {}
};

//Запись в файл значений различных типов
template <typename T>
void writeToFile(const string filename, const T arg) {
	ofstream output;
	output.open(filename, ios::app);
	output << arg;
	output.close();
}

//Отступ (нужен для рекурсивного вывода)
void indent(int n) {
	for (int i = 0; i < n; i++) {
		cout << "\t";
	}
}

//Освобождение памяти (удаление дерева)
void dispose(Node* t) {
	if (t == nullptr) {
		return;
	}
	dispose(t->l);
	dispose(t->r);
	delete t;
}

//Проверка на вхождение элемента с заданным ключом в дерево
bool isIn(Node* t, int k) {
	if (t != nullptr) {
		if (k > t->p.x) {
			return isIn(t->r, k);
		}
		else if (k < t->p.x) {
			return isIn(t->l, k);
		}
		return true;
	}
	return false;
}

//Слияние двух деревьев
Node* merge(Node* l, Node* r, int& depth) {
	if (!depth) {
		cout << "\nAttempting to merge trees\n";
	}
	if (l == nullptr) {			//Если одно из деревьев - nullptr, возвращаем другое (тоже может быть nullptr)
		return r;
	}
	if (r == nullptr) {
		return l;
	}

	if (l->p.y > r->p.y) {
		//Если у левого дерева приоритет больше, возвращаем его корень,
		//предварительно рекурсивно вызвав функцию слияния для его правого поддерева,
		//сохраняя неизменным исходное правое дерево.
		indent(depth);
		cout << "Merging with the right branch of  " << l->p.x << "  " << l->p.y << "\n";
		depth++;
		l->r = merge(l->r, r, depth);
		depth--;
		return l;
	}
	//Иначе возвращем корень правого дерева, перед этим
	//выполнив аналогичные действия с его левым поддеревом и
	//сохраняя исходное левое дерево
	indent(depth);
	cout << "Merging with the left branch of  " << r->p.x << "  " << r->p.y << "\n";
	depth++;
	r->l = merge(l, r->l, depth);
	depth--;
	return r;
}

//Разбиение дерева на два поддерева
Pair<Node*> split(Node* t, int k, int& depth) {
	if (!depth) {
		cout << "\nAttempting to split the tree.\n";
	}
	if (t == nullptr) {
		return Pair<Node*>(nullptr, nullptr);
	}
	else if (k > t->p.x) {
		//Если заданный ключ больше ключа текущего элемента, спускаемся по правой ветви
		//и возвращаем пару значений - исходный элемент и правое поддерево результата разбиения
		indent(depth);
		cout << "Descending to  the right branch of  " << t->p.x << "  " << t->p.y << "\n";
		depth++;
		Pair<Node*> nPair = split(t->r, k, depth);
		depth++;
		t->r = nPair.x;
		return Pair<Node*>(t, nPair.y);
	}
	else{
		//Иначе спускаемся по левой ветви и возвращаем левое поддерево результата разбиения
		//и исходный элемент
		indent(depth);
		cout << "Descending to  the left branch of  " << t->p.x << "  " << t->p.y << "\n";
		depth++;
		Pair<Node*> nPair = split(t->l, k, depth);
		depth--;
		t->l = nPair.y;
		return Pair<Node*>(nPair.x, t);
	}
	return Pair<Node*>(t, nullptr);
}


//Добавление заданного элемента
Node* add(Node* t, int k, int v) {
	int depth = 0;
	cout << "\n\nSplitting the treap by key " << k << "\n";
	Pair<Node*> p = split(t, k, depth);		//Разбиение по заданному ключу
	Node* n = new Node(k, v);
	return merge(merge(p.x, n, depth), p.y, depth);	//Слияние левого поддерева результата разбиения
													//с новым элементом, а затем с правым поддеревом
}

//Удаление элемента из дерева
Node* remove(Node* t, int k, int& depth) {
	if (!depth) {
		cout << "\nAttempting to remove existing element.\n";
	}
	if (t != nullptr) {
		indent(depth);
		cout << "Current element: " << t->p.x << "  " << t->p.y << "\n";
		if (t->p.x < k) {
			//Если заданный ключ больше, спускаемся к правому поддереву
			depth++;
			t->r = remove(t->r, k, depth);
			depth--;
			return t;
		}
		else if (t->p.x > k) {
			//Если меньше - к левому поддереву
			depth++;
			t->l = remove(t->l, k, depth);
			depth--;
			return t;
		}
		else {
			//Если нашёлся данный ключ, удаляем его, сливая затем его поддеревья
			indent(depth);
			cout << "\nRequired element found: " << t->p.x << "  " << t->p.y << " , removing...\n";
			Node* l = t->l, * r = t->r;
			t->l = nullptr;
			t->r = nullptr;
			dispose(t);
			return merge(l, r, depth);
		}
	}
	//Если t = nullptr
	return t;
}


//Вывод дерева на экран
void printTreap(Node* t, int& depth) {
	if (t != nullptr) {
		if (t->r != nullptr) {
			//П
			depth++;
			printTreap(t->r, depth);
			depth--;
		}
		//К
		indent(depth);
		cout << t->p.x << "  " << t->p.y << "\n";
		if (t->l != nullptr) {
			//Л
			depth++;
			printTreap(t->l, depth);
			depth--;
		}
	}
}

//Печать элементов дерева в файл по возрастанию ключей
void printAscendingToFile(Node* t, const string& filename) {
	if (t != nullptr) {
		if (t->l != nullptr) {
			//Л
			printAscendingToFile(t->l, filename);
		}
		//К
		writeToFile(filename, t->p.x);
		writeToFile(filename, "  ");
		writeToFile(filename, t->p.y);
		writeToFile(filename,  '\n');
		if (t->r != nullptr) {
			//П
			printAscendingToFile(t->r, filename);
		}
	}
}

int main() {
	srand(time(nullptr));
	int command = 0;
	int key = 0, value = 0;
	int depth = 0;
	Node* treap = nullptr;
	cout << "Enter : 1 - Console input , 2 - File Input:\n\n";
	cin >> command;

	if (command == 2) {
		string input_filename;
		const string output_filename = "output.txt";
		ifstream in;
		ofstream out;

		//Открыть файл на перезапись
		out.open(output_filename);
		out << "";
		out.close();

		//Ввод имени файла со входными данными
		cout << "Enter the input file name: \n\n";
		cin >> input_filename;
		in.open(input_filename);

		if (in.is_open()) {
			while (!in.eof()) {
				if (!(in >> key) || !(in >> value)) {
					//Если не удалось считать пару ключ-значение
					break;
				}
				if (isIn(treap, key)) {
					//Если элемент с таким ключом уже есть, убрать
					cout << "\n\nElement with key = " << key << " already exists. Replacing...";
					treap = remove(treap, key, depth);
				}
				//Добавление элемента
				cout << "\n\nAdding new element with key = " << key << " to the treap\n";
				treap = add(treap, key, value);
			}
			if (treap != nullptr) {
				//Если дерево не пустое, вывести необходимые данные
				printTreap(treap, depth);
				printAscendingToFile(treap, output_filename);
				cout << "\nCheck out the results in \"output.txt\"\n";
			}
			else {
				//Если файл пуст или данные некорректны
				cout << "File is empty or contains incorrect data.\n";
				writeToFile(output_filename, "File is empty or contains incorrect data.\n");
			}
		}
		else {
			//Если не удалось открыть файл
			cout << input_filename << " doesn't exist!\n";
		}
	}
	else if (command == 1) {
		//Те же действия, только ввод и вывод осуществляются в консоли
		cout << "Enter the pairs (key then value, both integer) or anything except that (to finish): \n\n";
		while ((cin >> key)) {
			if (!(cin >> value)) {
				break;
			}
			if (isIn(treap, key)) {
				cout << "\n\nElement with key = " << key << " already exists. Replacing...";
				treap = remove(treap, key, depth);
			}
			cout << "\n\nAdding new element with key = " << key << " to the treap\n";
			treap = add(treap, key, value);
		}
		if (treap != nullptr) {
			printTreap(treap, depth);
		}
		else {
			cout << "The treap is empty.\n";
		}
	}
	else {
		cout << "\nUnknown command, program finished\n";
	}

	return 0;
}