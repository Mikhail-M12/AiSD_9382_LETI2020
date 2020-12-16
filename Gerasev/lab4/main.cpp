#include <iostream>
#include <bits/stdc++.h>
#include <string.h>

using namespace std;

// No templatres bc i made them in lab3

void greetingMessage()
{
    cout << "Please, input size of massive and data\n";
    cout << "The programm will sort data 2 different ways -- \n";
    cout << "By C++ sort and self-written shaker sort\n";
}

void copyMas(int* from, int sizeFrom, int* to, int sizeTo)
{
    // Can lead to unexpected results on different size masses
    for(int i=0; i<sizeFrom && i<sizeFrom; i++)
    {
        to[i] = from[i];
    }
}

void printMas(int* mas, int size)
{
    for (int i=0; i<size; i++)
    {
        cout << mas[i] << ' ';
    }
    cout << '\n';    
}

void compareResults(int* mas1, int size1, int* mas2, int size2)
{
    // For strange test only, so output is in the function
    bool res = true;
    for(int i=0; i<size1 && i<size2; i++)
    {
        if (mas1[i] != mas2[i])
            res = false;
    }

    if (size1 != size2)
        res = false;

    if (res) {
        cout << "Expected and actual results are the same\n";
    } else {
        cout << "Expected and actual results are NOT the same\n";
    }
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shakerSort(int* mas, int size)
{
    int left = 0;
    int right = size-1;
    bool swappedOnCycle = true;

    while ((left < right) && swappedOnCycle)
    {
        cout << "Go on new cycle\n";
        swappedOnCycle = false;
        cout << "  Go right\n";
        for (int i=left; i<right; i++)
        {
            if (mas[i] > mas[i+1])
            {
                swap(&mas[i], &mas[i+1]);
                cout << "   Swapping " << mas[i] << " and " << mas[i+1] << '\n';
                cout << "   Now mass is ";
                printMas(mas, size);
                swappedOnCycle = true;
            }
        }
        right--;

        cout << "  Go left\n";
        for (int i=right; left<i; i--)
        {
            if (mas[i-1] > mas[i])
            {
                swap(&mas[i-1], &mas[i]);
                cout << "   Swapping " << mas[i-1] << " and " << mas[i] << '\n';
                cout << "   Now mass is ";
                printMas(mas, size);
                swappedOnCycle = true;
            }
        }
        left++;
    }
}

void outputResult(int* inputMas, int size)
{
    // All mass handle here
    cout << "Input mas -- ";
    printMas(inputMas, size);

    int expectedResult[size];
    copyMas(inputMas, size, expectedResult, size);
    sort(expectedResult, expectedResult+size);
    cout << "Expected output is -- ";
    printMas(expectedResult, size);

    int actualResult[size];
    copyMas(inputMas, size, actualResult, size);
    shakerSort(actualResult, size);
    cout << "Actual output -- ";
    printMas(actualResult, size);

    compareResults(expectedResult, size, actualResult, size);
}

void stdInputCase()
{
    // Standart input
    // Will continue untill size of mass <= 0
    cout << "The input will continue untill size of mass <= 0\n";
    int size;
    cin >> size;
    while (size > 0)
    {
        int inputMas[size] = { 0 };
        for (int i=0; i<size; i++)
        {
            cin >> inputMas[i];
        }

        outputResult(inputMas, size);
        cout << "-1 to stop\n";
        cin >> size;
    }
}

void fileInputCase(string path)
{
    // File input case
    ifstream inFile;
    inFile.open(path);

    int size;

    while (inFile >> size)
    {
        int mas[size];
        for (int i=0; i<size && inFile >> mas[i]; i++);
        cout << "\n\n\n";
        outputResult(mas, size);
    }
}

int main(int argc, char *argv[])
{
    if (argc>= 2) // Arguments case
    {
        string flag(argv[1]);
        string path(argv[2]);
        if (flag.compare("-f") == 0)
            fileInputCase(path); // No obvious way to overload the function
        return 0;
    }
    greetingMessage();
    stdInputCase();
    return 0;
}