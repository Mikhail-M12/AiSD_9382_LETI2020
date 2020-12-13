#include <iostream>
#include <algorithm>
#include <chrono>
#include "List.h"
#include "InsertionSort.h"

int main(){
    srand(0);

    int n;
    cout << "Введите размер входных данных: ";
    cin >> n;
    float* myArr = new float[n];
    float* myArr2 = new float[n];
    cout << "Введите входные данные: ";
    for(int i = 0; i < n; i++){
        cin >> myArr[i];
        myArr2[i] = myArr[i];
    }
    List<float> myList1 = List<float>(myArr, n);
    //List<int> myList2 = List<int>(myArr, n);
    cout << "Исходный массив до сортировки: ";
    printArray(myArr, n);
    InsertionSortArray(myArr, n);
    cout << "Исходный массив после сортировки: ";
    printArray(myArr, n);
    cout << "Исходный список до сортировки: ";
    myList1.print();
    InsertionSortList(myList1);
    cout << "Исходный список после сортировки: ";
    myList1.print();
    
    //chrono::steady_clock::time_point start = chrono::steady_clock::now();
    //InsertionSortArray(myArr, n);
    //chrono::steady_clock::time_point end = chrono::steady_clock::now();
    //cout << "Время на сортировку массива: " << std::chrono::duration<double>(end - start).count() << " секунд\n";

    //start = chrono::steady_clock::now();
    //sort(myArr2, myArr2 + n);
    //end = chrono::steady_clock::now();
    //cout << "Время на сортировку массива стандартной сортировкой: " << std::chrono::duration<double>(end - start).count() << " секунд\n";

    //start = chrono::steady_clock::now();
    //InsertionSortList(myList1);
    //end = chrono::steady_clock::now();
    //cout << "Время на сортировку списка: " << std::chrono::duration<double>(end - start).count() << " секунд\n";

    return 0;
}
