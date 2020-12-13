#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

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

//Отступ (нужен для рекурсивного вывода)
void indent(int n, ostream& write = cout) {
	for (int i = 0; i < n; i++) {
		write << "\t";
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

//Расчёт высоты дерамиды
int height(Node* t) {
	int rHeight = 0, lHeight = 0;
	if (t->l != nullptr) {
		lHeight = height(t->l);
	}
	if (t->r != nullptr) {
		rHeight = height(t->r);
	}
	if (lHeight > rHeight) return lHeight + 1;
	return rHeight + 1;
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
	else {
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

//Добавление заданного элемента
Node* add(Node* t, int k, int v) {
	int depth = 0;
	if (isIn(t, k)) {
		cout << "\n\nElement with key = " << k << " already exists. Replacing...";
		t = remove(t, k, depth);
	}
	cout << "\n\nSplitting the treap by key " << k << "\n";
	Pair<Node*> p = split(t, k, depth);		//Разбиение по заданному ключу
	Node* n = new Node(k, v);
	return merge(merge(p.x, n, depth), p.y, depth);	//Слияние левого поддерева результата разбиения
													//с новым элементом, а затем с правым поддеревом
}

//Вывод дерева в файл
void printTreap(const Node* t, int& depth, ostream& write) {
	if (t != nullptr) {
		if (t->r != nullptr) {
			//П
			depth++;
			printTreap(t->r, depth, write);
			depth--;
		}
		//К
		indent(depth, write);
		write << t->p.x << ":" << t->p.y << "\n";
		if (t->l != nullptr) {
			//Л
			depth++;
			printTreap(t->l, depth, write);
			depth--;
		}
	}
}

//Переопределение оператора вывода в поток для дерамиды
ostream& operator<<(ostream& out, const Node& t) {
	int depth = 0;
	printTreap(&t, depth, out);
	return out;
}


//Получение случайного элемента из кучи
Node* getRandom(Node* t, int& depth, int h) {
	bool dir = rand() % 2;		//Выбор направления

	//Если спуск по левой ветви и не достигнут указанный уровень
	if (depth != h && dir && t->l != nullptr) return getRandom(t->l, depth, h);

	//Если спуск по правой ветви и не достигнут указанный уровень
	else if (depth != h && !dir && t->r != nullptr) return getRandom(t->r, depth, h);

	//Если был достигнут указанный уровень или элемент является концевым
	else {
		cout << "RANDOMLY GOT ELEMENT : (" << t->p.x << ":" << t->p.y << ")\n\n";
		return new Node(t->p.x, t->p.y);
	}
}

//Генерация случайной дерамиды
Node* generateTreap() {
	Node* treap = nullptr;
	cout << "GENERATING RANDOM TREAP\n\n";
	for (int i = 0; i < 10 + rand()%5; i++) {
		treap = add(treap, rand() % 100 - 50, rand() % 100 - 50);
	}
	return treap;
}


//Запись ответа в скобочном представлении
void writeBracketsAnswer(Node* t, ostream& answer) {
	if (t != nullptr) {
		cout << "WRITING ELEMENT (" << t->p.x << ":" << t->p.y << ") TO A FILE\n\n";
		answer << "((" << t->p.x << ":" << t->p.y << ")";

		//Проверка на то, какие есть дочерние объекты - нужно для сокращённого представления
		if (t->l != nullptr) {
			writeBracketsAnswer(t->l, answer);
			writeBracketsAnswer(t->r, answer);
		}
		else if (t->r != nullptr) {
			answer << "#";		//Пустое поддерево
			writeBracketsAnswer(t->r, answer);
		}
		answer << ")";
	}
}

//Запись ответа по уровням слева направо
void writeLevelsAnswer(Node* t, ostream& answer, int& depth, int level) {
	if (t != nullptr) {
		//Только на заданном уровне
		if (depth == level) {
			cout << "WRITING ELEMENT (" << t->p.x << ":" << t->p.y << ") TO A FILE\n\n";
			answer << "(" << t->p.x << ":" << t->p.y << ")";
		}
		//Иначе спуск, пока возможно
		else {
			depth++;
			writeLevelsAnswer(t->l, answer, depth, level);
			writeLevelsAnswer(t->r, answer, depth, level);
			depth--;
		}
	}
}

//Запись узлов в прямом (КЛП) порядке
void writeKLPAnswer(Node* t, ostream& answer) {
	if (t != nullptr) {
		cout << "WRITING ELEMENT (" << t->p.x << ":" << t->p.y << ") TO A FILE\n\n";
		answer << "(" << t->p.x << ":" << t->p.y << ")";
		writeKLPAnswer(t->l, answer);
		writeKLPAnswer(t->r, answer);
	}
}

//Запись узлов в обратном (ЛКП) порядке
void writeLKPAnswer(Node* t, ostream& answer) {
	if (t != nullptr) {
		writeLKPAnswer(t->l, answer);
		cout << "WRITING ELEMENT (" << t->p.x << ":" << t->p.y << ") TO A FILE\n\n";
		answer << "(" << t->p.x << ":" << t->p.y << ")";
		writeLKPAnswer(t->r, answer);
	}
}

//Запись узлов в концевом (ЛПК) порядке
void writeLPKAnswer(Node* t, ostream& answer) {
	if (t != nullptr) {
		writeLPKAnswer(t->l, answer);
		writeLPKAnswer(t->r, answer);
		cout << "WRITING ELEMENT (" << t->p.x << ":" << t->p.y << ") TO A FILE\n\n";
		answer << "(" << t->p.x << ":" << t->p.y << ")";
	}
}

//Генерация задания на скобочное представление
void generateBrackets(ostream& task, ostream& answer) {
	ifstream read;
	string curString;
	Node* treap = generateTreap();

	//Получение шаблона оформления
	read.open("Templates/brackets.txt");
	getline(read, curString);
	//Запись формулировки задания и дерамиды
	cout << "WRITING TASK TO A FILE\n\n";
	task << "1. " << curString << "\n\n" << *treap << "\n";

	cout << "WRITING ANSWER TO A FILE\n\n";
	answer << "1. ";
	//Запись ответа
	writeBracketsAnswer(treap, answer);
	answer << ".\n\n";
	
	read.close();

	dispose(treap);
}

//Генерация задания на перечисление по уровням слева направо
void generateLevels(ostream& task, ostream& answer) {
	ifstream read;
	string curString;
	Node* treap = generateTreap();
	Node* unit;
	int depth = 0;
	int h = height(treap);


	//Получение шаблона оформления
	read.open("Templates/levels.txt");
	getline(read, curString);
	//Запись формулировки задания
	cout << "WRITING TASK TO A FILE\n\n";
	task << "2. " << curString;

	//Случайный выбор - добавление либо удаление элемента
	bool addrem = rand() % 2;
	if (addrem) {
		//Создание нового элемента
		unit = new Node(rand() % 100 - 50, rand() % 100 - 50);
		getline(read, curString);
		//Запись добавления
		task << curString;
		getline(read, curString);
	}
	else {
		//Получение элемента для удаления
		unit = getRandom(treap, depth, rand()%h);
		getline(read, curString);
		getline(read, curString);
		//Запись удаления
		task << curString;
	}

	//Запись выбранного элемента и дерамиды
	getline(read, curString);
	task << curString << "(" << unit->p.x << ":" << unit->p.y << ")" << ".\n\n" << *treap << "\n";

	//Добавление/удаление элемента непосредственно
	if (addrem) {
		treap = add(treap, unit->p.x, unit->p.y);
	}
	else {
		treap = remove(treap, unit->p.x, depth);
	}

	//Запись ответа
	cout << "WRITING ANSWER TO A FILE\n\n";
	answer << "2. ";
	for (int i = 0; i < h; i++) {
		writeLevelsAnswer(treap, answer, depth, i);
	}
	answer << ".\n\n";

	read.close();
	dispose(unit);
	dispose(treap);
}

//Генерация задания на перечисление узлов в указанном порядке
void generateTraversal(ostream& task, ostream& answer, int cond) {
	ifstream read;
	string curString;
	Node* treap = generateTreap();

	//Получение шаблона оформления
	read.open("Templates/traversal.txt");
	getline(read, curString);
	//Запись формулировки задания
	cout << "WRITING TASK TO A FILE\n\n";
	task << "3. " << curString;

	//Запись подходящего порядка
	switch (cond) {
	case 0:			//Прямой
		getline(read, curString);
		task << curString;
		getline(read, curString);
		getline(read, curString);
		break;
	case 1:			//Обратный
		getline(read, curString);
		getline(read, curString);
		task << curString;
		getline(read, curString);
		break;
	case 2:			//Концевой
		getline(read, curString);
		getline(read, curString);
		getline(read, curString);
		task << curString;
		break;
	}
	getline(read, curString);
	task << curString;

	//Запись дерамиды
	task << "\n\n" << *treap << "\n";

	//Запись соответствующего ответа
	cout << "WRITING ANSWER TO A FILE\n\n";
	answer << "3. ";
	switch (cond) {
	case 0:
		writeKLPAnswer(treap, answer);
		break;
	case 1:
		writeLKPAnswer(treap, answer);
		break;
	case 2:
		writeLPKAnswer(treap, answer);
		break;
	}
	answer << ".\n\n";

	read.close();
	dispose(treap);
}

//Создание наборов заданий
void generateTasks(int n) {
	ofstream task, answer;
	string curVar, curAns;

	//Общий формат названий файлов
	const string var = "Tasks/variant", ans = "Answers/answer";

	cout << "\n\nGENERATION STARTED\n\n";
	char buff[3];
	for (int i = 0; i < n; i++) {
		cout << "\n\nGENERATING VARIANT #" << i + 1 << "\n\n";
		//Добавление к исходным строкам номера варианта
		_itoa_s(i + 1, buff, 10);
		curVar = var + buff + ".txt";
		curAns = ans + buff + ".txt";

		task.open(curVar);
		answer.open(curAns);

		//Запись заданий и ответов
		cout << "\nGENERATING \"BRACKETS\" TYPE TASK\n\n";
		generateBrackets(task, answer);
		cout << "\nGENERATING \"LEVELS\" TYPE TASK\n\n";
		generateLevels(task, answer);
		cout << "\nGENERATING \"TRAVERSAL\" TYPE TASK\n\n";
		generateTraversal(task, answer, rand()%3);

		task.close();
		answer.close();
	}
	cout << "\n\n\nGENERATION COMPLETED\n";
}

int main() {
	srand(time(nullptr));
	setlocale(LC_ALL, "rus");

	//Вывод инструкции на экран
	string s;
	ifstream instruction;
	instruction.open("Templates/Instruction.txt");
	while (!instruction.eof()) {
		getline(instruction, s);
		cout << s << "\n";
	}

	int nStudents = 0;

	cout << "Введите количество вариантов теста, которое необходимо сгенерировать (не более 30!): \n\n";
	cin >> nStudents;
	while (nStudents <=0 || nStudents > 30) {
		cout << "Недопустимое количество, повторите ввод: ";
		cin >> nStudents;
	}

	generateTasks(nStudents);
	system("pause");
	return 0;
}