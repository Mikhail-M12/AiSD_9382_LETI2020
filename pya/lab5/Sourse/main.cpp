#include <cstring>
#include <string>
#include <iostream>
#include <cmath>
#include <fstream>

#define NMAX 500
using namespace std;
int arr[NMAX+1];

/*oid heapify (int pos, int n, int u) {
    while (u * pos + 1 < n) {
        int max = u * pos + 1;
        for (int k = 2;k < u + 1;k++)
        if (u * pos + k < n && arr[u * pos + k] >= arr[max]) {
            max = u * pos + k;
        }
        if (arr[pos] < arr[max]) {
            swap(arr[pos], arr[max]);
            pos = max;
        } else
            break;
    }
}

void heapMake(int n, int u) {
    for (int i = n - 1; i >= 0; i--) {
        heapify(i, n, u);
    }
}
void heapSort(int n, int u) {
    heapMake(n, u);
    while(n>0)
    {
        swap(arr[0],arr[n-1]);
        n--;
        heapify(0,n, u);
    }
}*/

void printHeap(int n, int u, int q, int h) {//предназначена для вывода в форме кучи
    int k = 1, i = 0, y = 0;
    while (true) {
 /*       for (int r = 0;r < q*u*h*4 / (k + 1);r++)
            cout << " ";*/
    while (i < k + y) {
        cout << arr[i] << "[" << i << "] ";//вывод сыновей
/*        for (int r = 0;r < q*u*h*4 / (k + 1);r++)
            cout << " ";*/
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

void printRoot(int n, int u) {//предназначена для вывода пути от корня до листа с выбором наибольшего сына
    int main = 0, max = 1, l = 1;
    cout << "It is " << l++ <<" level\n";
    cout << arr[0] << "[0]\n";
    while (true) {
        max = main + 1;
        if (max >= n) {
            cout << "\n";
            return;
        }
        cout << "I will choose the biggest son from:\n";
        for (int k = 1; k < u + 1; k++) {
            if (main + k < n)
                cout << arr[main + k] << " ";
            if (main + k < n && arr[main + k] >= arr[max]) {//выбор наибольшего сына
                max = main + k;
            }
        }
        cout << "\nIt is " << l++ <<" level\n";
        cout << arr[max] << "[" << max << "]\n";//вывод сына
        main = max * u;
    }
}

void fcn(std::istream &fin) {//функция для универсальной работы с потоком ввода
    int u = 0, i = 0, value, max = 0;
    char* str = new char[30]();
    while ((str[u] = fin.get()) != '\n') {//считывание значений и запись в массив
        if (str[u] == ' ') {
            if (max <= u)
                max = u;//максимальная длина значений
            str[u] = '\n';
            u = -1;
            value = stoi(str,nullptr, 10);
            arr[i++] = value;
            delete[] str;
            str = new char[20]();
        }  else if (!isdigit(str[u])) {
            break;
        }
        u++;
    }
    if (!arr[0]) {//проверка на неверные данные
        cout << "Error data\n";
        return;
    }
    value = stoi(str,nullptr, 10);//считывание последнего элемента
    arr[i++] = value;
    fin >> u;
    value = 0;
    for (int r = 0;r < i;) {
        r = pow(u, value++);
    }
    cout << "N-narny heap:\n";
    printHeap(i, u, value, max);//вывод в форме кучи
    cout << "Max root:\n";
    printRoot(i, u);//вывод пути от корня до листа с выбором наибольшего сына
    delete[] str;
}


int main() {
    char n;
    cout << "What stream do you want to use?(0 - cout, n - name of file)\n";
    cin >> n;
    if (n == '0') {
        cout << "Write array of data! Write number of children!\n";
        n = cin.get();
        fcn(std::cin);
    } else {
        char *filename = new char[30]();//ввходные данные из файла
        strcpy(filename, "Tests//");
        strncat(filename, &n, 1);
        strcat(filename, ".txt");
        std::ifstream in(filename);
        if (!in.is_open()) {
            std::cout << "File wasn't opened!";
            return 0;
        }
        fcn(in);
        delete[] filename;
    }
    return 0;
}