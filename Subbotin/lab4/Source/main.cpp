#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void shift(int depth){
    for(int i = 0; i<depth; i++){
        cout << "   ";
    }
}

void printArr(int arr[], int left, int right, int depth){
    shift(depth);
    for(int i = left; i<=right; i++){
        cout << arr[i] << " ";
    }
}

void merge(int arr[], int left, int middle, int right, int depth){
    //вычисляем размеры двух подмассивов
    int leftSubArrSize = middle - left + 1;
    int rightSubArrSize = right - middle;

    /*
     * создаем два подмассива - левая и правая половины
     * начиная с индекса left до right
     * от исходного массива
     * оба эти массива по отдельности уже отсортированы
     */

    int leftSubArr[leftSubArrSize];
    int rightSubArr[rightSubArrSize];

    for(int i = 0; i<leftSubArrSize; i++){
        leftSubArr[i] = arr[left + i];
    }

    for(int i = 0; i<rightSubArrSize; i++){
        rightSubArr[i] = arr[middle + i + 1];
    }

    int leftIdx = 0;
    int rightIdx = 0;
    int mergedIdx = left;

    /*
     * Теперь мы сравниваем поочередно элементы из двух подмассивов.
     * Минимальный из двух сравниваемых элементов мы записываем в исходный массив под индексом mergedIdx.
     * В подмассиве, который содержал минимальный из двух сравниваемых элементов,
     * в следующий раз будем рассматривать следующий за ним элемент.
     */
    int counter = 1;
    while(leftIdx < leftSubArrSize && rightIdx < rightSubArrSize){
        shift(depth);
        cout <<counter<<".1 Рассматриваемые элементы: " << leftSubArr[leftIdx] << " и " << rightSubArr[rightIdx] << " ";
        if(leftSubArr[leftIdx] <= rightSubArr[rightIdx]){
            arr[mergedIdx] = leftSubArr[leftIdx];
            leftIdx++;
        }
        else {
            arr[mergedIdx] = rightSubArr[rightIdx];
            rightIdx++;
        }

        cout << ", min = "<< arr[mergedIdx] << "\n";
        shift(depth);

        cout << counter << ".2 Массив, образующийся в результате слияния: [ ";
        printArr(arr,left,mergedIdx,0);
        cout << "]\n";

        shift(depth);
        cout << counter <<".3 Оставшиеся элементы в левом [ ";
        printArr(leftSubArr, leftIdx,leftSubArrSize-1, 0);
        cout << "], правом [ ";
        printArr(rightSubArr, rightIdx, rightSubArrSize-1, 0);
        cout << "] подмассивах\n";
        counter++;
        mergedIdx++;
    }

    /*
     * Когда мы запишем полностью один из подмассивов, цикл закончится,
     * но у нас еще останутся не записанные элементы из другого массива
     * здесь мы и займемся дозаполнением
     */
    shift(depth);
    if(leftIdx >= leftSubArrSize){
        cout << "Левый подмассив пуст. ";
    }
    else {
        cout << "Оставшиеся элементы из левого подмассива в том же порядке вставляем в результирующий. ";
        while (leftIdx < leftSubArrSize) {
            arr[mergedIdx] = leftSubArr[leftIdx];
            leftIdx++;
            mergedIdx++;
        }
    }
    if(rightIdx >= rightSubArrSize){
        cout << "Правый подмассив пуст. ";
    }
    else {
        cout << "Оставшиеся элементы из правого подмассива в том же порядке вставляем в результирующий. ";
        while (rightIdx < rightSubArrSize) {
            arr[mergedIdx] = rightSubArr[rightIdx];
            rightIdx++;
            mergedIdx++;
        }
    }
    cout << "\n";
    shift(depth);
    cout <<"Результирующий массив: [ ";
    printArr(arr,left,right,0);
    cout << "] \n";
}

void mergeSort(int arr[], int left, int right, int &depth){
    /*
     * если сортируемый подмассив состоит больше чем из 1 элемента,
     * то его надо разделить и слить
     * 1 элементный подмассив - база рекурсии.
     */
    if(left < right){
        /*
         * мы считаем средний индекс таким образом из-за возможного переполнения
         * при больших значениях left и right
         */
        int middle = left + (right - left)/2;
        printArr(arr,left,middle,depth);
        cout << " - рассматриваем левый подмассив \n";

        depth++;

        //сортируем левую часть
        mergeSort(arr, left, middle,depth);
        depth--;

        printArr(arr,middle+1,right,depth);
        cout <<" - рассматриваем правый подмассив  \n";

        depth++;
        //сортируем правую часть
        mergeSort(arr, middle + 1, right,depth);
        depth--;

        shift(depth);
        cout << "Левый [ ";
        printArr(arr,left,middle,0);
        cout<<"] и правый [ ";
        printArr(arr,middle+1,right,0);
        cout<<"] подмассивы отсортированы, сливаем их : \n";

        //сливаем две отсортированные части
        merge(arr, left, middle, right,depth);
    }
    else {
        shift(depth);
        cout << "Подмассив состоит из одного элемента " << arr[left] << " и отсортирован \n";
    }
}


bool sortFunction(int i, int j){
    return (i<=j);
}

int main() {
    char inputCh='0';
    while(inputCh != 'c' && inputCh != 'f'){
        cout << "Напишите f/c для получения данных из файла/консоли: ";
        cin >> inputCh;
    }
    int arraySize = 0;
    if(inputCh == 'f') {
        ifstream infile("../in.txt");
        infile >> arraySize;
        if (arraySize <=0){
            cout << "Некорректная длина массива!";
            return 0;
        }
        infile.close();
    }
    else if (inputCh == 'c'){
        cout << "Введите количество элементов в массиве: ";
        cin >> arraySize;
        if(arraySize <=0){
            cout <<"Некорректная длина массива!";
            return 0;
        }
    }

    int arr[arraySize];

    if(inputCh == 'f') {
        ifstream infile("../in.txt");
        int passLength;
        infile >> passLength;
        for (int i = 0; i < arraySize; i++) {
            infile >> arr[i];
        }
        infile.close();
    }
    else if (inputCh == 'c'){
        cout << "Введите массив: ";
        for (int i = 0; i < arraySize; i++) {
            cin >> arr[i];
        }
    }

    cout << "Сортируемый массив: ";
    for(int i = 0; i<arraySize; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";

    int arrChecker[arraySize];
    for(int i = 0; i<arraySize; i++){
        arrChecker[i] = arr[i];
    }

    int depth = 1;
    mergeSort(arr,0, arraySize-1,depth);

    cout << "\nМассив после сортировки слиянием: ";
    for(int i = 0; i<arraySize; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";

    sort(arrChecker,arrChecker+arraySize,sortFunction);

    cout << "Массив после сортировки из стандартной библиотеки: ";
    for(int i = 0; i<arraySize; i++){
        cout << arrChecker[i] << " ";
    }
    cout << "\n";

    bool equal = true;
    int idx = 0;
    while(equal && idx<arraySize){
        if(arr[idx] != arrChecker[idx]){
            equal = false;
        }
        idx++;
    }
    if(equal){
        cout << "Массивы сортировки слиянием и из стандартной библиотеки равны";
    }
    else {
        cout << "Массивы сортировки слиянием и из стандартной библиотеки не равны";
    }
    return 0;
}