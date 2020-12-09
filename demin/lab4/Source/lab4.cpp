//
// Created by vikto on 17.11.2020.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#define NMax 10000

using namespace std;

class logger {
    ofstream file;

public:
    logger() {
        file.open("intermeiate.txt");
        if (!file.is_open())
            throw runtime_error("file open failure");
    }

//закрытие файла
    ~logger() {
        std::cout << "\nIntermeiate values write to file \"intermeiate.txt\"";
        file.close();
    }

    void startTimsort() {
        file << "Start sorting\n";
        file << "Array before sorting:";
    }

    void endTimsort() {
        file << "End sorting\n";
        file << "Array after sorting:";


    }

    void printArray(int *array, int count) {
        for (int i = 0; i < count; ++i) {
            file << array[i] << " ";
        }
        file << "\n";
        file << "__________________________________________________________\n";
    }

    void startSortByInsertsForSmallCount() {
        file << "_________________________________________________________\n";
        file << "N < 64, timsort isn't optimal\n";
        file << "Start simple sort by inserts\n";
    }

    void endSortByInsertsForSmallCount() {
        file << "Sorting end\n";
        file << "_________________________________________________________\n";
    }

    void startSortByInsertsForSubarray(int index) {
        file << "Sort by insert subarray with index:" << index << "\n";
    }

    void setMinrun(int i) {
        this->minrun = i;
    }

    void mergeBefore(int *array, int countX, int countY, int indexX, int indexY) {
        file << "Merging two subarrays\n";
        file << "BeforeMerge:\n";
        file << "First:";
        for (int i = 0; i < countX; ++i) {
            file << array[indexX + i] << " ";
        }
        file << "\n";
        file << "Second:";
        for (int i = 0; i < countY; ++i) {
            file << array[indexY + i] << " ";
        }
        file << "\n";
    }

    void mergeAfter(int *array, int count, int index) {
        file << "AfterMerge:\n";
        for (int i = 0; i < count; ++i) {
            file << array[index + i] << " ";
        }
        file << "\n";
    }

    int minrun;
};


struct subarray {
    int indexStart; //индекс начала подмасивов
    int countMassiv; //размер подмасссива
};
struct stack {
    struct subarray *subarrayes;
    int countSubarray = 0; // кол-во подмассивов
};

void push(struct stack *sub, int indexstart, int countmassiv) {//Добавление в стек
    if (sub->countSubarray == 0) {
        sub->subarrayes = new struct subarray[1000];
    }
    sub->subarrayes[sub->countSubarray].indexStart = indexstart;
    sub->subarrayes[sub->countSubarray].countMassiv = countmassiv;
    sub->countSubarray++;
}

void pop(struct stack *sub) {//удаление вершины
    sub->countSubarray--;
}

bool checkXYZ(struct stack *sub) {// проверка на слияние подмассивов
    if ((sub->subarrayes[sub->countSubarray - 1].countMassiv + sub->subarrayes[sub->countSubarray - 2].countMassiv <
         sub->subarrayes[sub->countSubarray - 3].countMassiv &&
         sub->subarrayes[sub->countSubarray - 1].countMassiv < sub->subarrayes[sub->countSubarray - 2].countMassiv)) {
        return true; //нужно выполнять слвияние текущего с предыдущим
    }
    return false;
}

void merge(int *left, int *right, int sizeLeft, int sizeRight, bool typeLeft, bool typeRight) // ф-ия слияния
{
    int *mLeft = new int[sizeLeft + 1];
    int *mRight = new int[sizeRight + 1];
    for (int i = 0; i < sizeLeft; ++i) {
        mLeft[i] = left[i];
    }
    for (int i = 0; i < sizeRight; ++i) {
        mRight[i] = right[i];
    }
    int i = 0;
    int j = 0;
    int k = 0;
    if (typeLeft && typeRight) { //оба возрастают

        while (i < sizeLeft && j < sizeRight) {
            if (mLeft[i] <= mRight[j]) {
                left[k] = mLeft[i];
                i++;
            } else {
                left[k] = mRight[j];
                j++;
            }
            k++;
        }

        // копирование левый
        while (i < sizeLeft) {
            left[k] = mLeft[i];
            k++;
            i++;
        }


        while (j < sizeRight) {
            left[k] = mRight[j];
            k++;
            j++;
        }

    } else if (typeLeft && !typeRight) {//левый возрастает
        while (i < sizeLeft && j < sizeRight) {
            if (mLeft[i] <= mRight[sizeRight - 1 - j]) {
                left[k] = mLeft[i];
                i++;
            } else {
                left[k] = mRight[sizeRight - 1 - j];
                j++;
            }
            k++;
        }


        while (i < sizeLeft) {
            left[k] = mLeft[i];
            k++;
            i++;
        }


        while (j < sizeRight) {
            left[k] = mRight[sizeRight - 1 - j];
            k++;
            j++;
        }

    } else if (!typeLeft && typeRight) {//правый возрастает
        while (i < sizeLeft && j < sizeRight) {
            if (mLeft[sizeLeft - 1 - i] <= mRight[j]) {
                left[k] = mLeft[sizeLeft - 1 - i];
                i++;
            } else {
                left[k] = mRight[j];
                j++;
            }
            k++;
        }


        while (i < sizeLeft) {
            left[k] = mLeft[sizeLeft - 1 - i];
            k++;
            i++;
        }


        while (j < sizeRight) {
            left[k] = mRight[j];
            k++;
            j++;
        }
    } else if (!typeLeft && !typeRight) {//никто не  возрастает
        while (i < sizeLeft && j < sizeRight) {
            if (mLeft[sizeLeft - 1 - i] <= mRight[sizeRight - 1 - j]) {
                left[k] = mLeft[sizeLeft - 1 - i];
                i++;
            } else {
                left[k] = mRight[sizeRight - 1 - j];
                j++;
            }
            k++;
        }


        while (i < sizeLeft) {
            left[k] = mLeft[sizeLeft - 1 - i];
            k++;
            i++;
        }


        while (j < sizeRight) {
            left[k] = mRight[sizeRight - 1 - j];
            k++;
            j++;
        }
    }
}

//вычисление оптимального размера для разбиения на подмассивы
int getMinrun(
        int n) //  берутся старшие 6 бит из N и добавляется единица, если в оставшихся младших битах есть хотя бы один ненулевой
{
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

void subarray(int *array, int N, int minrun, int *position)  //создани подмассивов и их сортировка вставками
{
    if (N - *position < minrun) {
        minrun = abs(N - *position);
    }

    int *curr;//конкретный подмассив
    curr = array + *position;
    int *run = new int[minrun];//временный подмассив

    int runCount = 2;//количество элементов в подмассиые
    run[0] = *curr;
    run[1] = *(curr + 1);

    int j = 1;
    int i = 1;

    bool order = run[0] <= run[1];

    for (i = 1; (i < N - 1) && (j != minrun); i++)//ищем упорядоченный подмассив
    {
        if (order) {
            if (curr[i] <= curr[i + 1]) {
                run[i + 1] = curr[i + 1];
                ++runCount;
            } else break;
        } else {
            if (curr[i] >= curr[i + 1]) {
                run[i + 1] = curr[i + 1];
                ++runCount;
            } else break;
        }
    }
    if (runCount <
        minrun) //Если размер текущего run’а меньше, чем minrun — выбираются следующие за найденным run-ом элементы.
    {
        while (runCount < minrun) {
            run[runCount] = curr[i];
            ++i;
            ++runCount;
        }
    }
    if (!order)  // сорт по уб.
    {
        int j = 0;
        for (int i = 1; i < minrun; i++) {
            int value = run[i];
            j = i - 1;

            while (j >= 0 && run[j] < value) {
                run[j + 1] = run[j];
                run[j] = value;
                j = j - 1;

            }
        }
    } else {
        for (int i = 1; i < minrun; i++) {
            int value = run[i];
            int j = i - 1;

            while (j >= 0 && run[j] > value) {
                run[j + 1] = run[j];
                run[j] = value;
                j = j - 1;
            }
        }
    }

    for (int i = 0, j = *position; i < runCount; i++, j++) {
        array[j] = run[i];
        ++(*position);
    }
}

void timsort(int *arr, int count) {
    logger *log = new logger();
    log->startTimsort();
    log->printArray(arr, count);
    int minrun;
    if (count < 64) //  простая сортировка вставкой . тк. не оптимален timsort
    {
        log->startSortByInsertsForSmallCount();
        int minrun = count;
        int j = 0;
        for (int i = 1; i < minrun; i++) {
            log->printArray(arr, count);
            int value = arr[i];
            j = i - 1;

            while (j >= 0 && arr[j] > value) {
                arr[j + 1] = arr[j];
                arr[j] = value;
                j = j - 1;
            }

        }
    } else {
        minrun = getMinrun(count);
        log->setMinrun(minrun);
        cout << "minrun= " << minrun << endl;
        int position = 0;
        int lastRun = count % minrun;//размер последнего подмассива
        int countRun = count / minrun;//размер подмассивов

        while (position < count) // разделение на подмассивы и их сортировка вставками
        {
            log->startSortByInsertsForSubarray(position / minrun);
            if (count - position < minrun) {
                log->printArray(arr + position, lastRun);
                subarray(arr, count, minrun, &position);
                log->printArray(arr + position - lastRun, lastRun);
            } else {
                log->printArray(arr + position, minrun);
                subarray(arr, count, minrun, &position);
                log->printArray(arr + position - minrun, minrun);
            }
        }


        struct stack sub;

        for (int i = 0;
             i < countRun + 1; i++) //заносится пара данных в стек , индекс начала подмассивов и количество эл-ов в нем.
        {

            if ((i == countRun && lastRun != 0)) {
                push(&sub, i * minrun, lastRun);
                break;
            } else if (i == countRun && lastRun == 0) {
                break;
            }
            push(&sub, i * minrun, minrun);
        }
        //сортировка слиянием
        int index_start_X;
        int index_start_Y;
        int index_start_Z;
        int count_X;
        int count_Y;
        int count_Z;
        while (sub.countSubarray >= 3) // пока больше 3-ех происходит сияние ранов
        {

            index_start_X = sub.subarrayes[sub.countSubarray - 1].indexStart;
            index_start_Y = sub.subarrayes[sub.countSubarray - 2].indexStart;
            index_start_Z = sub.subarrayes[sub.countSubarray - 3].indexStart;
            count_X = sub.subarrayes[sub.countSubarray - 1].countMassiv;
            count_Y = sub.subarrayes[sub.countSubarray - 2].countMassiv;
            count_Z = sub.subarrayes[sub.countSubarray - 3].countMassiv;

            if (checkXYZ(&sub)) // проверка на слияния
            {
                log->mergeBefore(arr, count_X, count_Y, index_start_X, index_start_Y);
                merge(&arr[index_start_Y], &arr[index_start_X], count_Y, count_X,
                      (arr[index_start_Y] < arr[index_start_Y + count_Y - 1]),
                      (arr[index_start_X] < arr[index_start_X + count_X - 1]));
                sub.subarrayes[sub.countSubarray - 2].countMassiv += count_X;
                log->mergeAfter(arr, count_Y + count_X, index_start_Y);
                pop(&sub);
            } else {
                if (count_X <= count_Z) {
                    log->mergeBefore(arr, count_X, count_Y, index_start_X, index_start_Y);
                    merge(&arr[index_start_Y], &arr[index_start_X], count_Y, count_X,
                          (arr[index_start_Y] < arr[index_start_Y + count_Y - 1]),
                          (arr[index_start_X] < arr[index_start_X + count_X - 1]));

                    sub.subarrayes[sub.countSubarray - 2].countMassiv += count_X;
                    log->mergeAfter(arr, count_Y + count_X, index_start_Y);
                    pop(&sub);
                } else {
                    log->mergeBefore(arr, count_Z, count_Y, index_start_Z, index_start_Y);
                    merge(&arr[index_start_Z], &arr[index_start_Y], count_Z, count_Y,
                          (arr[index_start_Z] < arr[index_start_Z + count_Z - 1]),
                          (arr[index_start_Y] < arr[index_start_Y + count_Y - 1]));

                    sub.subarrayes[sub.countSubarray - 3].countMassiv += count_Y;
                    log->mergeAfter(arr, count_Z + count_Y, index_start_Z);
                    pop(&sub);
                    sub.subarrayes[sub.countSubarray - 1].indexStart = index_start_X;
                    sub.subarrayes[sub.countSubarray - 1].countMassiv = count_X;
                }
            }
        }
        // оставшеся два
        index_start_X = sub.subarrayes[sub.countSubarray - 1].indexStart;
        index_start_Y = sub.subarrayes[sub.countSubarray - 2].indexStart;
        count_X = sub.subarrayes[sub.countSubarray - 1].countMassiv;
        count_Y = sub.subarrayes[sub.countSubarray - 2].countMassiv;
        log->mergeBefore(arr, count_X, count_Y, index_start_X, index_start_Y);
        merge(&arr[index_start_Y], &arr[index_start_X], count_Y, count_X,
              (arr[index_start_Y] < arr[index_start_Y + count_Y - 1]),
              (arr[index_start_X] < arr[index_start_X + count_X - 1]));
        log->mergeAfter(arr, count_Y + count_X, index_start_Y);
    }
    log->endTimsort();
    log->printArray(arr, count);
    delete log;
}

void enter(int *array, int *count) {
    int type = 0;//Тип ввода
    cout << "Enter from file -1\n";
    cout << "Enter from console -2\n";
    cin >> type;
    ifstream file;
    string name;//Название файла
    int temp;
    switch (type) {
        case 1:
            cout << "Enter file name\n";
            cin >> name;
            file.open(name);
            if (file.is_open()) {
                temp = 0;
                while (!file.eof()) {//считывание элементов из файла
                    file >> array[temp];
                    temp++;
                }
                *count = temp;
            } else {
                cout << "File isn't open." << endl;
            }
            break;
        case 2:
            cout << "Enter count elements:\n";
            cin >> *count;
            cout << "Enter elements: \n";
            for (int i = 0; i < *count; ++i) {//считывание элементов из строки
                cin >> array[i];
            }
            break;
        default:
            break;
    }
}

void print(int *array, int count) {
    int type = 0;
    cout << "\nPrint to console -1\n";
    cout << "Print to file -2\n";
    cin >> type;
    ofstream file;
    string name_f;
    switch (type) {
        case 1: {
            cout << "\n\nArray after sorting:\n";
            for (int i = 0; i < count; i++) {
                cout << array[i] << ' ';
            }
        }
            break;
        case 2:
            cout << "Enter file name\n";
            cin >> name_f;
            file.open(name_f);
            if (file.is_open()) {
                file << "\n\nArray after sorting:\n";
                for (int i = 0; i < count; i++) {
                    file << array[i] << ' ';
                }
            } else file << "Unable to open file";
            break;
        default:
            break;
    }


}

int main() {
    int mode = 1;
    while (mode) {
        int *array = new int[NMax];//Рассматриваемый массив
        int count = 0;//Количество элементов в массиве
        enter(array, &count);//Ввод массива

        timsort(array, count);//Сортировка

        print(array, count);//Вывод массива
        std::cout << "\nIf you want to close the program, enter 0" << endl;
        std::cout << "If you want to continue the program, enter 1" << endl;
        cin >> mode;
        while (mode!=0&&mode!=1) {
            if(mode!=0&&mode!=1){
                std::cout<<"wrong: try again!"<<endl;
            }
            std::cout << "\nIf you want to close the program, enter 0" << endl;
            std::cout << "If you want to continue the program, enter 1" << endl;
            cin >> mode;
        }
        delete[] array;
    }
}