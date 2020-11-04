#include <iostream>
#include <fstream>
#include <cstring>
#include <list>

typedef struct node {//структура для создания односвязных списков
    long int val;//данные узла
    struct node* next;//указатель на следующий узел
    node() {//конструктор структуры
        val = 0;
        next = nullptr;
    }
    ~node() {//деструктор
        next = nullptr;
    }
} Node;

void printArray(Node* shift) {//функция для вывода отсортировонного списка данных
    while (shift->next != nullptr) {
        std::cout << shift->val << " ";
        shift = shift->next;
    }
    std::cout << shift->val << "\n";
}

void deleteArray(Node* shift) {//освобождение памяти
    while (shift->next != nullptr) {
       Node* t = shift;
       shift = shift->next;
       delete t;
    }
    delete shift;
}
//функция для сортировки данных с помощью поразрядной сортировки
Node* radixSort(Node *current, int length) {//length - максимальная длина одной ячейки данных
    Node *shift, *head[10], *tail[10];//shift - указатель, служащий временным хранилищем, head - начало списка данных в определенном списке разрядности, а tail - конец соответственно
    int i, y, n, d = 1;//i, y - счетчики, n - переменная для хранения текущего разряда числа, d - переменная, нужная для выделения определенного разряда
    for (y = 0; y < length; y++) {//цикл для прохождения всех разрядов
        for (i = 0; i <= 9; i++)//цикл для обнуления указателя начала и конца массивов списков
            head[i] = (tail[i] = NULL);
        while (current != NULL) {//проход по всем данным
            n = (current->val / d) % 10;//получение разряда
            shift = tail[n];
            if (head[n] == NULL)//если данных, разряд которых равен, несколько, то они присоединяются к head
                head[n] = current;
            else
                shift->next = current;
            shift = tail[n] = current;//в tail только последняя структура данных
            current = current->next;
            shift->next = NULL;
        }
        for (i = 0; i <= 9; i++)//определяем начало данных для следующего витка цикла
            if (head[i] != NULL)
                break;
        current = head[i];
        shift = tail[i];
        for (n = i + 1; n <= 9; n++) {//связываем начала и концы списков последовательно
            if (head[n] != NULL) {
                shift->next = head[n];
                shift = tail[n];
            }
        }
        std::cout << "This is sorting by category of " << d << "\n";
        printArray(current);
        d *= 10;
    }
    return current;
}

void fcn(std::istream &fin) {//функция для универсальной работы с потоком ввода
    int n = 0, length = 0;//n - количество данных, length - максимальная длина ячейки данных
    fin >> n >> length;
    Node* head;
    std::list <int> nodes;//используется для стандартной сортировки
    if (!(n == 0 || length == 0)) {
        Node* shift = new Node();
        head = shift;
        for (int i = 0; i < n;i++) {//создание списка данных
            fin >> shift->val;
            nodes.push_back(shift->val);
            if (i != n -1)
                shift->next = new Node();
            shift = shift->next;
        }
        std::cout << "Nice job! Then my turn to work..\n";
        std::cout << "Demonstration of radix sort work:\n";
        head = radixSort(head, length);//поразрядная сортировка
        std::cout << "Demonstration of result:\n";
        printArray(head);//вывод отсортированных данных
        deleteArray(head);
        std::cout << "Demonstration of standard sort work:\n";
        nodes.sort();//стандартная сортировка для list
        std::list <int> :: iterator it;
        std::cout << "Demonstration of result:\n";
        for ( it = nodes.begin(); it != nodes.end(); it++) {//вывод отсортированных данных
            std::cout << (*it) << " ";
        }
    } else std::cout << "Error data!";
}

int main() {
    std::cout << "What do you prefer? (0 - terminal, n - number of file)\n";
    char n;//выбор источника входных данных
    std::cin >> n;
    if (n == 48) {//ввходные данные из терминала
        std::cout << "Enter count of array, max length of one data, then data:\n";
        fcn(std::cin);
    } else {
        char *filename = new char[30]();//ввходные данные из файла
        strcat(filename, "Tests//");
        strncat(filename, &n, 1);
        strcat(filename, ".txt");
        std::ifstream in(filename);
        fcn(in);
    }
    return 0;
}