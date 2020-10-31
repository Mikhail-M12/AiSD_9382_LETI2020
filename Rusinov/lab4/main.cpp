#include <iostream>
#include "fstream"


struct List { // односвязный линейный список
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
    }
};

// функция для вывода списка
void showList(List* list) {
    while (list) {
        std::cout << list->value << " ";
        list = list->next;
    }
}

List* insertionSort(List* list) {
    // начинать сортировку можно с первого элемента списка
    for (List* i = list->next; i;) {
        // начинаем сравнивать предыдущий элемент за рассматриваемым элементом
        List* j = i->prev;
        // запоминаем значение рассматриваемого элемента
        std::cout << "Начал рассматривать элемент " << i->value << std::endl;

        // доходим до элемента, который будет <= рассматриваемого
        while (j && j->value > i->value) {
            std::cout << "Сравнение " << j->value << " > " << i->value << std::endl;
            j = j->prev;
        }

        // запоминаем следующий рассматриваемый элемент
        List* next = i->next;

        // выдергиваем из списка текущий рассматриваемый элемент
        i->prev->next = i->next;
        if (i->next) i->next->prev = i->prev;

        if (j) {
            // если попали сюда, то рассматриваемый элемент устанавливаем правее найденного
            // найденный <= рассматриваемого
            std::cout << j->value << " <= " << i->value << ". Элемент " << i->value << " выставляется правее " << j->value << "." << std::endl;
            if (j->next) j->next->prev = i;
            i->next = j->next;
            i->prev = j;
            j->next = i;
        } else {
            // если попали сюда, то рассматриваемый элемент станет началом списка
            // мы не нашли элементов, которые <= рассматриваемого
            std::cout << "Вышел за границу списка, элемент " << i->value << " стал началом списка!" << std::endl;
            list->prev = i;
            list->prev->prev = nullptr;
            list->prev->next = list;
            list = i;
        }

        // устанавливаем следующий рассматриваемый элемент
        i = next;

        std::cout << "[Промежуточный результат] ";
        showList(list);
        std::cout << std::endl;

    }
    std::cout << "Прошелся по всему списку, сортировка окончена!" << std::endl;
    return list;
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
    List* sorted = insertionSort(source);
    std::cout << "[Список после сортировки] ";
    showList(sorted);
    delete sorted;
    return 0;
}
