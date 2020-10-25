#include <iostream>
#include "fstream"


struct List { // двусвязный линейный список
    List* next = nullptr;
    List* prev = nullptr;
    int value;

    void append(int element) { // добавить элемент в конец
        List* current = this;
        while(current->next) current = current->next;
        current->next = new List(element);
        current->next->prev = current;
    }

    explicit List(int value) : value(value) {} // конструктор

    ~List() { // деструктор
        delete next;
        delete prev;
    }
};

// функция для вывода списка
void showList(List* list) {
    while (list) {
        std::cout << list->value << " ";
        list = list->next;
    }
}

void insertionSort(List* list) {
    // начинать сортировку можно с первого элемента списка
    for (List* i = list->next; i; i = i->next) {
        // начинаем сравнивать предыдущий элемент за рассматриваемым элементом
        List* j = i->prev;
        // запоминаем значение рассматриваемого элемента
        int key = i->value;
        std::cout << "Начал рассматривать элемент " << key << std::endl;

        // пока предыдущий элемент существует и его значение > рассматриваемого элемента
        // пред. элементом становится пред. элемент пред. элемента
        // а так же мы сдвигаем пред элемент вперед
        for (; j && j->value > key; j = j->prev) {
            std::cout << "Сравнил c " << j->value;
            std::cout << ". " << j->value << " > " << key << ". Сдвигаю " << j->value << " вправо" << std::endl;
            j->next->value = j->value;
        }

        // если элемент существует, то мы дошли до момента, когда пред. элемент <= рассматриваемого
        // тогда значение след. элемента нужно заменить на значение рассматриваемого
        if (j) {
            std::cout << "Дошел до значения " << j->value;
            std::cout << ". " << j->value << " <= " << key << ". Поэтому устанавливаю " << key << " правее." << std::endl;
            j->next->value = key;
        }
        // а если не существует, то мы вышли за границы массива, значит нужно переместить
        // значение рассматриваемого элемента в начало списка
        else {
            std::cout << "Вышел за границу списка, поэтому устанавливаю значение " << key << " в начало списка" << std::endl;
            list->value = key;
        }
        std::cout << "[Промежуточный результат] ";
        showList(list);
        std::cout << std::endl;
    }
    std::cout << "Прошелся по всему списку, сортировка окончена!" << std::endl;
}

// ввод из консоли или из файла
List* insert(int file = 0) {
    int N;
    List* source = nullptr;

    if (!file) {
        std::cout << "Введите кол-во чисел: ";
        std::cin >> N; // получаем кол-во элементов
        if (N <= 0) {
            std::cout << "Кол-во чисел должно быть больше 0";
            return source;
        }

        for (int i = 0; i < N; ++i) { // считываем N элементов
            int k;
            std::cout << "[" << i+1 << "] " << "Введите число: ";
            std::cin >> k;

            if (!source) source = new List(k);
            else source->append(k); // Добавляем в список
        }
    } else {
        std::ifstream input("file.txt"); // открываем файл
        if (!input.is_open()) { // проверяем на доступность
            input.close();
            std::cout << "Не удалось открыть файл file.txt" << std::endl;
            return source;
        }
        else {
            if(!(input >> N)) { // считываем N
                std::cout << "Не удалось считать кол-во элементов" << std::endl;
                return nullptr;
            }

            if (N <= 0) {
                std::cout << "Кол-во чисел должно быть больше 0";
                return source;
            }

            for (int i = 0; i < N; ++i) { // Считываем N элементов
                int k;
                if(!(input >> k)) { // проверяем, получилось ли считать
                    std::cout << "Задано N чисел, но было введено меньше N чисел" << std::endl;
                    delete source;
                    return nullptr; // если не удалось, вызываем деструктор списка
                }
                if (!source) source = new List(k); // инициализация списка
                else source->append(k); // добавляем элемент
            }
        }
    }
    return source;
}

int main() {
    int file;
    std::cout << "Ввод из файла? 0 - если нет: ";
    std::cin >> file;
    List* source = insert(file); // считывание списка
    if (!source) return 0;

    std::cout << "[Список до сортировки] ";
    showList(source);
    std::cout << std::endl;
    insertionSort(source);
    std::cout << "[Список после сортировки] ";
    showList(source);
    delete source;
    return 0;
}
