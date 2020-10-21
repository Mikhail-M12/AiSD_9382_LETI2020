#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#define FILE "/home/indiora/C++/Aisd/read.txt"

using namespace std;


string readFile(const string& file_name) {
    ifstream f(file_name); // Экземпляр класса
    stringstream ss;
    ss << f.rdbuf(); // Возвращает указатель на потоковый буфер
    return ss.str(); // Возвращает строку
}

template <typename T>
void printArray(vector<T>& array) {
    // os... записывает элементы в поток вывода
    copy(begin(array), end(array), ostream_iterator<T>(cout, " "));
    std::cout << '\n';
}

template <typename T>
void sortMass1(vector<T>& array) {
    // Перебираем каждый элемент массива кроме последнего
    for (int startIndex = 0; startIndex < array.size() - 1; ++startIndex) {
        // Наименьшим считается 1 элеменент
        int smallestIndex = startIndex;
        // Ищем элемент поменьше в остальной части массива
        for (int currentIndex = startIndex + 1; currentIndex < array.size(); ++currentIndex) {
            if (array[currentIndex] < array[smallestIndex])
                smallestIndex = currentIndex;
        }
        // Меняем местами первый элемент подмассива и наименьший в нем
        swap(array[startIndex], array[smallestIndex]);
        // Выводим массив
        std::cout << "Sort number " << startIndex << " : ";
        printArray(array);
        // Выводим промежуточное значение
        std::cout << '\t' << "Smallest number: " << array[startIndex] << '\n' << '\n';
    }
}

template <typename T>
void sortMass2(vector<T>& array) {
    // Перебираем каждый элемент массив
    for(int i = 0; i < ((array.size())/2); i++) {
        int smallestIndex = i;
        int biggestIndex = array.size() - 1 - i;
        // Ищем наименьший элеммент подмассива
        for(int j = i + 1; j < array.size() - i; j++) {
            if(array[j] < array[smallestIndex])
                smallestIndex = j;
        }
        // Меняем местами первый элемент подмассива и наименьший в нем
        swap(array[i], array[smallestIndex]);
        // Ищем наибольший элеммент подмассива
        for(int k = i + 1; k < array.size() - i; k++) {
            if(array[k] > array[biggestIndex])
                biggestIndex = k;
        }
        // Меняем местами последний элемент подмассива и наибольший в нем
        swap(array[array.size() - 1 - i],array[biggestIndex]);
        // Выводим массив
        std::cout << "Sort number " << i << " : ";
        printArray(array);
        // Выводим промежуточные значения
        std::cout << '\t' << "Smallest number: " << array[i] << '\n';
        std::cout << '\t' << "Biggest number: " << array[biggestIndex] << '\n' << '\n';
    }

}


int main() {
    stringstream ss(readFile(FILE)); // Вставляет строку в поток
    vector<int> mass;
    // Переносим значение из строки в массив
    copy(istream_iterator<int>(ss), {}, back_inserter(mass)); // back_inserter - добавление в конец вектора
                                                                // is... считывает элементы с входного потока

    vector<int> mass1 = mass;
    vector<int> mass2 = mass;

    std::cout << "Sort by selection" << '\n';
    std::cout << "Initial array: ";
    printArray(mass1);
    std::cout << '\n';
    sortMass1(mass1);
    std::cout << '\n';

    std::cout << "Sort by selection with min and max search" << '\n';
    std::cout << "Initial array: ";
    printArray(mass2);
    std::cout << '\n';
    sortMass2(mass2);
    std::cout << "\n" << "Sorted array: ";
    printArray(mass2);
}
