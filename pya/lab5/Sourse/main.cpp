#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>

#define NMAX 500
using namespace std;
int arr[NMAX+1];

void printHeap(int n, int u) {//предназначена для вывода в форме кучи
    int k = 1, i = 0, y = 0;
    while (true) {
    while (i < k + y) {
        cout << arr[i] << "[" << i << "] ";//вывод сыновей
        i++;
        if (i == n) {
            y = -1;
            break;
        }
    }
    cout << "\n";
        k *= u;
        if (y == -1)//выход из цикла
            break;
        y = i;
    }
}

int printRoot(int n, int u, int* &finallyArr) {//предназначена для вывода пути от корня до листа с выбором наибольшего сына
    int main = 0, max = 1, l = 1, i = 0;
    cout << "It is " << l++ <<" level\n";
    cout << arr[0] << "[0]\n";
    finallyArr[i++] = arr[0];
    while (true) {
        max = main + 1;
        if (max >= n) {
            return i;
        }
        cout << "Searching the biggest son from:\n";
        for (int k = 1; k < u + 1; k++) {
            if (main + k < n)
                cout << arr[main + k] << " ";
            if (main + k < n && arr[main + k] >= arr[max]) {//выбор наибольшего сына
                max = main + k;
            }
        }
        cout << "\nIt is " << l++ <<" level\n";
        cout << arr[max] << "[" << max << "]\n";//вывод сына
        finallyArr[i++] = arr[max];
        main = max * u;
    }
}

void printFinallyRoot(int* &finallyArr, int count) {//предназначена для окончательного вывода искомого пути
    for (int i = 0;i < count;i++) {
        std::cout << finallyArr[i] << " ";
    }
    cout << "\n";
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
    fin >> r;
    if (!r) {
        cout << "Error data\nYou entered the wrong data!\n";
        delete[] str;
        return;
    }
    cout << "N-narny heap:\n";
    printHeap(i, u);//вывод в форме кучи
    cout << "Define max root:\n";
    int* finallyArr = new int[i]();
    int count = printRoot(i, u, finallyArr);//вывод пути от корня до листа с выбором наибольшего сына
    cout << "Max root is:\n";
    printFinallyRoot(finallyArr, count);
    memset(arr, 0, sizeof(int)*i);
    delete[] str;
}


int main() {
    char c;
    do {
        char n, *name = new char[100]();
        cout << "What input stream would you like to use?\n(0 - from console, 1 - from file)\n";
        cin >> n;
        if (n == '0') {
            cout << "Write array of data! Write number of children!\n";
            n = cin.get();
            fcn(std::cin);
        } else {
            cout << "Write the name of file:\n";
            cin >> name;
            char *filename = new char[30]();//ввходные данные из файла
            strcpy(filename, "Tests//");
            strcat(filename, name);
            strcat(filename, ".txt");
            std::ifstream in(filename);
            if (!in.is_open()) {
                std::cout << "File wasn't opened!";
                return 0;
            }
            fcn(in);
            delete[] name;
            delete[] filename;
        }
        cout << "Do you want to countinue? (y/n)\n";
        c = getch();
    } while (c == 'y' || c == 'Y');
    return 0;
}