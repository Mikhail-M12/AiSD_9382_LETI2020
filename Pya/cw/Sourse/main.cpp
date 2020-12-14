#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <vector>

#define NMAX 500
using namespace std;

int arr[NMAX+1];//массив значений
vector <int> iVec;//вектор для хранения индексов, которые нужно выделить
bool isFirst = true;//для переключения цвета фона при выводе

void printHeap(int n, int u) {//предназначена для вывода в форме кучи
    std::cout << "Current state of " << u <<"-nary heap is:\n";
    int k = 1, i = 0, y = 0;
    while (true) {
        while (i < k + y) {
            bool flag = false;
            if (!iVec.empty()) {
                for (auto v : iVec) {
                    if (isFirst && v == i) {//вывод рассматриваемых сыновей и родителя
                        cout << "\033[37;41m\033[1m\033[5m" << arr[i] << "[" << i << "]\033[0m ";
                        flag = true;
                    } else
                    if (v == i) {
                        cout << "\033[37;44m\033[1m\033[5m" << arr[i] << "[" << i << "]\033[0m ";
                        flag = true;
                    }
                }
            }
            if (!flag)
                cout << arr[i] << "[" << i << "] ";//вывод сыновей и родителя
            i++;
            if (i == n) {
                y = -1;
                break;
            }
        }
        cout << "\n";
        k *= u;
        if (y == -1) {//выход из цикла
            break;
        }
        y = i;
    }
    std::cout << "To continue enter any digit. If you want to skip, press any char...\n";
    iVec.clear();//отчищение вектора индексов
    cin >> y;
}

void printArray(int n, string message) {//предназначена для вывода массива
    system("clear");
    std::cout << message << "\nCurrent state of array is:\n";
    for (int q = 0;q < n;q++) {
        bool flag = false;
        if (!iVec.empty()) {
            for (auto v : iVec)
                if (isFirst && v == q) {//вывод рассматриваемых элементов
                    cout << "\033[37;41m\033[1m\033[5m" << arr[q] << "[" << q << "]\033[0m ";
                    flag = true;
                } else
                if (v == q) {
                    cout << "\033[37;44m\033[1m\033[5m" << arr[q] << "[" << q << "]\033[0m ";
                    flag = true;
                }
        }
        if (!flag)
            cout << arr[q] << "[" << q << "] ";//вывод элементов
    }
    std::cout << "\n\n";
}

void heapifyDown (int pos, int n, int u, int m, string message) {//предназначена для просейки снизу-вверх
    while (u * pos + 1 < n) {
        int max = u * pos + 1;
        isFirst = false;
        iVec.push_back(pos);
        iVec.push_back(max);
        for (int k = 2;k < u + 1;k++) {//поиск максимального сына
            if (u * pos + k < n) {
                iVec.push_back(u * pos + k);
                if (arr[u * pos + k] >= arr[max]) {
                    max = u * pos + k;
                }
            }
        }
        printArray(m, message);
        printHeap(m, u);
        isFirst = true;
        iVec.push_back(max);
        iVec.push_back(pos);
        printArray(m, message);
        printHeap(m, u);
        if (arr[pos] < arr[max]) {//обмен значениями, если родитель меньше сына
            swap(arr[pos], arr[max]);
            iVec.push_back(max);
            iVec.push_back(pos);
            printArray(m, message);
            printHeap(m, u);
            isFirst = false;
            pos = max; //сын становится рассматриваемым родителем
        } else
            break;
    }
}

void heapifyUp (int pos, int u, int m, string message) {//преназначена для просейки сверху-вниз
    if (pos > 0 && !(arr[(pos -1)/ u] < arr[pos])) {
        iVec.push_back(pos);
        iVec.push_back((pos - 1)/u);
        isFirst = true;
        printArray(m, "It's sifting up to down...\nSearching child, that is bigger than parent...\n");
        printHeap(m, u);
    } else
        while (pos > 0 && arr[(pos -1)/ u] < arr[pos]) {//обмен в случае, если сын больше родителя
            iVec.push_back(pos);
            iVec.push_back((pos - 1)/u);
            isFirst = true;
            printArray(m, message);
            printHeap(m, u);
            swap(arr[pos], arr[(pos - 1)/ u]);
            iVec.push_back(pos);
            iVec.push_back((pos - 1)/u);
            printArray(m, message);
            printHeap(m, u);
            pos = (pos - 1)/ u;//родитель становится рассматриваемым сыном
        }
}

void heapMakeDown(int n, int u, int m, string message) {//преназначена для формирвания кучи
    for (int i = (n - 1); i >= 0; i--) {
        heapifyDown(i, n, u, m, message);
    }
}

void heapMakeUp(int n, int u, int m, string message) {//преназначена для формирвания кучи
    for (int i = 1; i <= (n - 1); i++) {
        heapifyUp(i, u, m, message);
    }
}
void heapSortDown(int n, int u) {//преназначена для сортировки кучей
    system ("clear");
    cout << "At first we should sift our array to make a heap..\nWe will search the biggest of sons and compare with parent. If parent will be bigger, then we will swap them. The ones that we are swapping will be highlighted in \033[37;41m\033[1m\033[5mred.\033[0m\nTo continue enter any digit. If you want to skip, press any char...\n";
    int t;
    cin >> t;
    system ("clear");
    heapMakeDown(n, u, n, "It's sifting down to up...\n");//формирование кучи
    system ("clear");
    cout << "Now we are going to sort.\nMax array member will sent to the end, and array will be sift again.\nTo continue enter any digit. If you want to skip, press any char...\n";
    cin >> t;
    int m = n;
    while(n > 1) {
        isFirst = true;
        iVec.push_back(0);
        iVec.push_back(n - 1);
        printArray(m, "Forming an array of maximums.\n");
        printHeap(m, u);
        swap(arr[0], arr[n - 1]);//формирование массива по возрастанию
        iVec.push_back(0);
        iVec.push_back(n - 1);
        printArray(m, "Forming an array of maximums.\n");
        printHeap(m, u);
        n--;
        heapifyDown(0, n, u, m, "It's sorting...\n");
    }
}

void heapSortUp(int n, int u) {//преназначена для сортировки кучей
    system ("clear");
    cout << "At first we should sift our array to make a heap..\nIf child will be bigger than parent, we will swap them.The ones that we are swapping will be highlighted in \033[37;41m\033[1m\033[5mred.\033[0m\nTo continue enter any digit. If you want to skip, press any char...\n";
    int t;
    cin >> t;
    system ("clear");
    heapMakeUp(n, u, n, "It's sifting up to down...\n");//формирование кучи
    system ("clear");
    cout << "Now we are going to sort.\nMax array member will sent to the end, and array will be sift again.\nTo continue enter any digit. If you want to skip, press any char...\n";
    cin >> t;
    int m = n;
    while(n > 1) {
        isFirst = true;
        iVec.push_back(0);
        iVec.push_back(n - 1);
        printArray(m, "Forming an array of maximums.\n");
        printHeap(m, u);
        swap(arr[0], arr[n - 1]);//формирование массива по возрастанию
        iVec.push_back(0);
        iVec.push_back(n - 1);
        printArray(m, "Forming an array of maximums.\n");
        printHeap(m, u);
        n--;
        heapMakeUp(n, u, m, "It's sorting...\n");
    }
}

void fcn(std::istream &fin) {//функция для универсальной работы с потоком ввода
    int u = 0, i = 0, value;
    char* str = new char[30]();
    while ((str[u] = fin.get()) != '\n') {//считывание значений и запись в массив
        if (str[u] == ' ') {
            str[u] = '\0';
            u = -1;
            value = stoi(str, nullptr, 10);
            arr[i++] = value;
            delete[] str;
            str = new char[20]();
        } else if (!isdigit(str[u])) {
            break;
        }
        u++;
    }
    str[u] = '\0';
    try {
        value = stoi(str, nullptr, 10);//считывание последнего элемента
        arr[i++] = value;
    }
    catch (std::invalid_argument) {
        cout << "Error data\nYou entered the wrong data!\n";

        delete[] str;
        return;
    }
    int r;
    if (!(fin >> r)) {
        cout << "Error data\nYou entered the wrong data!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        delete[] str;
        return;
    }
    printArray(i, "It is our initial array.\n");
    std::cout << "What kind of sifting would you like to see?\n (0 - up to down, other digit - down to up)\n";
    int answer;
    while (!(std::cin >> answer)) {
        std::cout << "Error number of sifting!" << std::endl;
    }
    if (answer == 0)
        heapSortUp(i, r);
    else
        heapSortDown(i, r);
    printArray(i, "It is our finally sort array.\n");
    memset(arr, 0, sizeof(int)*i);
    delete[] str;
}


int main() {
    cout << "Good time of day. It's a coursework written by a student of group 9382 Pya Son Khwa on the topic \"Sorting an N-nary heap\".\n";
    cout << "Before starting the work, I want to provide some explanations.\nDuring operation, you will be given the option to select the input stream of input value and the sifting option. The parent and sons that we are currently considering will be highlighted in blue, and the ones that we are swapping will be highlighted in red.\nTo demonstrate, click on any button...\n";
    char c;
    cin >> c;
    system("clear");
    do {
        char n, *name = new char[100]();
        cout << "What input stream would you like to use?\n(0 - from console, 1 - from file)\n";
        cin >> n;
        if (n == '0') {
            cout << "Write array of data! Write number of children!\n";
            while (cin.get() != '\n');
            fcn(std::cin);
        } else if (n == '1'){
            cout << "Write the name of file:\n";
            cin >> name;
            char *filename = new char[30]();//ввходные данные из файла
            cin.sync();
            strcpy(filename, "Tests//");
            strcat(filename, name);
            strcat(filename, ".txt");
            std::ifstream in(filename);
            if (!in.is_open()) {
                std::cout << "File wasn't opened!";
                delete[] name;
                delete[] filename;
                break;
            }
            fcn(in);
            delete[] name;
            delete[] filename;
        } else {
            cout << "Wrong digit of stream!\n";
        }
        cout << "Do you want to continue? (y/n)\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (true) {
            cin >> c;
            if (c == 'y' || c == 'Y' || c == 'n' || c == 'N')
                break;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (c == 'y' || c == 'Y');
    return 0;
}