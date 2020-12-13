#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <iostream>
#include "List.h"

using namespace std;

template<typename T>
void printArray(T* arrayToPrint, int size){
    for(int i = 0; i < size; i++){
        cout << arrayToPrint[i] << ' ';
    }
    cout << '\n';
}


template<typename T>
void InsertionSortArray(T* arrayToSort, int size){
    T key;
    int j;
    for(int i = 1; i < size; i++){
        cout << "До сортировки: ";
        printArray(arrayToSort, size);
        key = arrayToSort[i];
        j = i - 1;
        while(j >= 0 && arrayToSort[j] > key){
            cout << "Поменял местами " << key << " и " << arrayToSort[j] << ":\t";
            arrayToSort[j + 1] = arrayToSort[j];
            arrayToSort[j] = key;
            printArray(arrayToSort, size);
            j--;
        }
        arrayToSort[j + 1] = key;
        cout << "Элемент " << key << " поставлен на место: ";
        printArray(arrayToSort, size);
    }
}

template<typename T>
void InsertionSortList(List<T>& listToSort){
    auto front = listToSort.getFront();
    auto tmp = front->nextNode;
    auto back = listToSort.getBack();
    while(tmp != nullptr){
        cout << "До сортировки: ";
        listToSort.print();
        auto tmp2 = tmp->prevNode;
        auto key = tmp;
        while(tmp2 != nullptr && tmp2->value > key->value){
            cout << "Поменял " << tmp2->value << " и " <<  key->value << ":\t";
            listToSort.swap(tmp2, key);
            listToSort.print();
            key = tmp2;
            tmp2 = tmp2->prevNode;
        }
        tmp = tmp->nextNode;
        cout << "Элемент " << key->value << " поставлен на место: ";
        listToSort.print();
        tmp2 = tmp;
    }
}

#endif
