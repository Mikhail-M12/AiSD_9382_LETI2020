#include <iostream>
#include "fstream"


struct List { // односвязный линейный список
    List* next = nullptr;
    int value;

    void append(int element) { // добавить элемент в конец
        List* current = this;
        while(current->next) current = current->next;
        current->next = new List(element);
    }

    int last() { // получить значение последнего элемента
        List* current = this;
        while (current->next) current = current->next;
        return current->value;
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


List* merge(List* first, List* second) { // слияние двух списков
    if (!first) return second; // если первый пустой, то вернуть второй
    if (!second) return first; // если второй пустой, то вернуть первый

    List* mergedList;

    List* headFirst = first; // фиксируем головы списков, чтобы в конце функции очистить память
    List* headSecond = second;

    std::cout << "[Слияние] ";
    showList(first);
    std::cout << "| ";
    showList(second);
    std::cout << std::endl;

    if (first->value < second->value) { // инициализация головы списка
        mergedList = new List(first->value);
        first = first->next; // переход к следующему элементу
    } else {
        mergedList = new List(second->value);
        second = second->next;
    }

    while (first || second) { // пока списки не пустые
        if (first && second) { // если оба списка не пустые
            if (first->value < second->value) { // если значение первого списка < второго
                mergedList->append(first->value); // тогда в результативный список добавляем значение первого
                first = first->next; // обрезаем первый список
            } else {
                mergedList->append(second->value); // аналогично
                second = second->next;
            }
        } else if (first) { // если непустой только первый, то добавляем в результативный список элементы первого
            mergedList->append(first->value);
            first = first->next;
        } else {
            mergedList->append(second->value); // аналогия
            second = second->next;
        }
    }

    delete headFirst; // очистка памяти
    delete headSecond;

    std::cout << "[Результат слияния] ";
    showList(mergedList);
    std::cout << std::endl;

    return mergedList; // результат слияния
}

// Strand sort is a recursive sorting algorithm that sorts items of a list into increasing order
// сортирущий алгоритм для сортировки элементов списка
// поэтому была реализована модель односвязного линейного списка
List* strandSort(List* list) { // нитевидная сортировка
    // в эту функцию нельзя передать пустой список
    if (!list->next) return list; // если список из одного элемента, то возвращаем его

    List* sublist = new List(list->value); // промежуточный список
    list = list->next;
    // в него передается первый элемент списка
    // затем добавляются элементы из оригинального списка, которые больше последнего элемента промежуточного списка

    List* source = nullptr;
    // данный список необходим, чтобы хранить элементы, которые <= последнего элемента промежуточного списка
    // данный шаг упрощает работу с односвязным списком

    while (list) { // идем по элементам списка
        // если последний элемент промежуточного списка < элемента списка, то добавляем элемент списка
        // в промежуточный список
        if (sublist->last() < list->value) sublist->append(list->value);
        else {
            // элемент списка <= последнего элемента промежуточного списка
            // значит нужно добавить в source
            if (!source) source = new List(list->value); // инициализация, если source пустой
            else source->append(list->value);
        }
        // след элемент списка
        list = list->next;
    }

    // теперь есть промежуточный список и оригинальный без элементов промежуточного
    // оригинальный без элементов промежуточного нужно еще раз отсортировать
    // затем сделать слияние
    if (source) return merge(sublist, strandSort(source)); // если source не пустой, то проводим его сортировку
    else return sublist; // иначе вернем промежуточный, он уже отсортирован
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
    List* result = strandSort(source); // сортировка
    if (result != source) delete source;
    std::cout << "[Результат сортировки] ";
    showList(result); // отображение списка
    delete result;

    return 0;
}
