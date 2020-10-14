#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/*________________*/

struct elem;

//Пара указателей на элементы списка
struct ptrs {
	elem* child;
	elem* next;
};

//Элемент списка
struct elem {
	bool atom;
	union node {
		char content;
		ptrs pair;
	} n;
};


//Создание атома и заполнение его полей
elem* create_atom(char c) {
	elem* n_el;
	n_el = new elem;
	n_el->atom = true;
	n_el->n.content = c;
	return n_el;
}

//Создание узла с полями next и child по умолчанию
elem* create_node() {
	elem* n_el;
	n_el = new elem;
	n_el->atom = false;
	n_el->n.pair.next = nullptr;
	n_el->n.pair.child = nullptr;
	return n_el;
}


//Генерация списка
elem *create_list(const string &list, int &i) {
	elem* n_list = create_node();
	elem* current = n_list;
	while (i < list.length()) {
		if (list[i] == '(') {
			//Создание подсписка, переход к след. узлу
			current->n.pair.child = create_list(list, ++i);
			current->n.pair.next = create_node();
			current = current->n.pair.next;
		}
		else if (list[i] == ' ' || list[i] == '\n' || list[i] == 'r' || list[i] == '\t') {
			//Игнорировать пробельные символы
			i++;
		}
		else if (list[i] == ')' || list[i] == '\0') {
			//Выход из цикла и завершение функции
			i++;
			break;
		}
		else {
			//Прикрепление к узлу атома, переход к след. узлу
			current->n.pair.child = create_atom(list[i]);
			if(list[i + 1] != ')'){
				current->n.pair.next = create_node();
			}
			current = current->n.pair.next;
			i++;
		}
	}
	return n_list;
}

//Поиск последнего узла на текущем уровне
elem* last_node(elem* list) {
	while (list->n.pair.next != nullptr) {
		list = list->n.pair.next;
	}
	return list;
}

//Оборачивание списка
elem* reverse_list(elem *list) {
	if (list != nullptr) {
		elem* new_head = list;
		if (!list->atom) {
			//Сохраняем голову, рекурсивно обходим след. элементы
			//и меняем направление списка на текущем уровне на обратное
			new_head = last_node(list);
			if (list->n.pair.child != nullptr && !(list->n.pair.child->atom)) {
				list->n.pair.child = reverse_list(list->n.pair.child);
			}
			if (list->n.pair.next != nullptr) {
				reverse_list(list->n.pair.next);
				list->n.pair.next->n.pair.next = list;
				list->n.pair.next = nullptr;
			}
		}
		return new_head;
	}
	return nullptr;
}

//Вывод списка на экран
void print_list(elem* list, int &depth) {
	if (list != nullptr) {
		if (!list->atom) {
			if (list->n.pair.child != nullptr) {
				depth++;
				print_list(list->n.pair.child, depth);
				depth--;
			}
			if(list->n.pair.next != nullptr){
				print_list(list->n.pair.next, depth);
			}
		}
		else {
			for (int n = 0; n < depth; n++) {
				cout << "\t";
			}
			cout << list->n.content << "\n";
		}
	}
}

//Удаление списка
void delete_list(elem* list) {
	if (list != nullptr) {
		if(!list->atom){
			if (list->n.pair.child != nullptr) {
				delete_list(list->n.pair.child);
			}
			if(list->n.pair.next != nullptr){
				delete_list(list->n.pair.next);
			}
		}
		delete list;
	}
}

//Запись заданной строки в файл с указанным именем
void write_to_file(const string filename, const string arg){
	ofstream output;
	output.open(filename, ios::app);
	output << arg;
	output.close();
}

//Вывод списка в файл
void print_list_to_file(elem* list, string filename) {
	if (list != nullptr) {
		if (!list->atom) {
			if (list->n.pair.child != nullptr) {
				if (list->n.pair.child->atom) {
					print_list_to_file(list->n.pair.child, filename);
				}
				else {
					write_to_file(filename, "(");
					print_list_to_file(list->n.pair.child, filename);
					write_to_file(filename, ")");
				}
			}
			if (list->n.pair.next != nullptr) {
				print_list_to_file(list->n.pair.next, filename);
			}
		}
		else {
			string str = "";
			str = str + list->n.content;
			write_to_file(filename, str);
		}
	}
}

//Обёртка для кореектной записи скобок 0 уровня в файл
void wrapper(elem* list, elem* rev_list, string filename) {
	write_to_file(filename, "(");
	print_list_to_file(list, filename);
	write_to_file(filename, ") -> (");
	print_list_to_file(rev_list, filename);
	write_to_file(filename, ")\n");
}

//Анализатор выражения
bool is_entry_valid(const string &list, int &i) {
	if (!i && list[i] != '(') {
		//Скобка не стоит в начале
		return false;
	}
	else if (list[i] == '(') {
		//Проверка каждого выражения со скобками
		i++;
		while (list[i] != ')') {
			if (list[i] == '\0' || !is_entry_valid(list, i)) {
				return false;
			}
			else {
				i++;
			}
		}
		return true;
	}
	else {
		//Встречен любой символ, кроме "("
		return true;
	}
}

int main() {
	elem* list = nullptr, *reversed_list = nullptr;
	string s = "", input_filename = "";
	const string output_filename = "output.txt";
	ofstream output;
	int i = 0, depth = 0, command = 0;
	ifstream input;

	//Открываем файл на перезапись
	output.open(output_filename);
	output << "";
	output.close();

	cout << "\tСпособ задания списка :\n\n\t1 - из консоли, 2 - из файла\n\n";
	cin >> command;
	if (command == 2) {
		cout << "Введите имя файла (он должен находиться в одной директории с исполняемым файлом) :";
		cin >> input_filename;
		input.open(input_filename);
		if (input.is_open()) {
			getline(input, s);
			do {
				if (is_entry_valid(s, i)) {
					//Создаём исходный и обращённый списки
					i = 1;
					list = create_list(s, i);
					i = 1;
					reversed_list = reverse_list(create_list(s, i));
					//Выводим их в файл
					wrapper(list, reversed_list, output_filename);
					cout << "\n";
					print_list(list, depth);
					cout << "\n";
					print_list(reversed_list, depth);
					//Удаляем их
					delete_list(list);
					delete_list(reversed_list);
				}
				else{
					//Записываем в файл сообщение об ошибке
					write_to_file(output_filename, s);
					write_to_file(output_filename, " -  INVALID ENTRY !\n");	
				}
				s = "";
				getline(input, s);
				i = 0;
			} while (!input.eof());
			input.close();
		}
		else {
			cout << "В текущей директории нет файла с таким названием!\n";
		}
	}
	else if(command == 1){
		cout << "Введите список (для выхода введите \"!\" ) :\n\n";
		getline(cin, s);
		while (s != "!") {
			if (is_entry_valid(s, i)) {
				//Процесс аналогичен предыдущему, но нет вывода в файл и ввод производится вручную из cin
				i = 1;
				list = create_list(s, i);
				i = 1;
				reversed_list = reverse_list(create_list(s, i));
				cout << "\n";
				print_list(list, depth);
				cout << "\n";
				print_list(reversed_list, depth);
				delete_list(list);
				delete_list(reversed_list);
			}
			else if(s != ""){
				//Если строка не пустая, но записана неверно, происходит ошибка
				cout << "Список записан некорректно!\n";
			}
			s = "";
			getline(cin, s);
			i = 0;
		}
	}
	else{
		cout << "Неизвестная команда, выход из программы.\n";
	}
	return 0;
}
