#include "headers.h"

int main()
{
    BTree<char> *a; // работаем через указатели

    setlocale(LC_ALL, "rus"); // подключен русский язык

    cout << "Enter Binary Tree with \'/\': " << endl;
    a = readBT<char>(); // явно указываем тип, т.к. нет аргументов
    cout << endl;

    cout << "Entered Binary Tree:\n";
    writeBT(a); // а здесь компилятор сам видит тип
    cout << "\n\n";

    {
    int max_depth = 0;

    cout << "Starting finding max depth.\n" << endl;
    findMaxDepth(a, &max_depth, 0);
    cout << "\nEnding finding max depth.\n" << endl;

    cout << "Max depth = " << max_depth << '\n' << endl;
    }

    {
    cout << "\n\nStarting finding inner way of bt.\n" << endl;  
    InnerWayAndCount obj = findInnerWay(a, 0);
    cout << "\nEnding finding inner way of bt.\n" << endl;
    
    cout << "Inner Way of BT = " << obj.getInnerWay() << endl;
    } // obj будет уничтожен здесь

    return 0;
}

void printEmptyDepth(int depth) // просто печатает табуляции в количестве глубины
{
    for (int j = 0; j < depth; j++)
        cout << "   ";
    return;
}
