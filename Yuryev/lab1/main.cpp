#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "headers.h" // объявления функций
int main()
{
    setlocale(LC_ALL, "rus"); // подключение русского языка

    char* line = new char [410]; // сказали, что так можно
    string name_of_file = "./input.txt"; //  легко добавить считывание с терминала названия файла и отрезков текста, который нужно взять
    
    reading_file(name_of_file, line); // передаем название файла и массив, куда скопировать строку

    int count_of_chars = 0; 
    for(int k = 0; (line[k] != '\0') ; k++) // подсчет количества значащих символов в массиве
        count_of_chars++; 

    if (text_with_brackets(0, count_of_chars-1, line, 0))
        cout << "This input is Text in brackets!" << endl;
    else
        cout << "This input isn`t Text in brackets!" << endl;
    
    cout << "End of program" << endl;

    delete line;

    return 0;
}

/*
Построить синтаксический анализатор для понятия текст_со_скобками.

текст_со_скобками::= элемент | элемент текст_со_скобками

элемент::= А | B | (текст_со_скобками) | [текст_со_скобками] | {текст_со_скобками}
*/


// в отчете не забудь описания рекурсивных функций, тестирование, пример работы
// код в 10 кегле, шрифт Courier new, межстрочный интервал - одиночный


