#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>

using namespace std;

bool check_TRUE_FALSE_LETTER(string str) {//Проверяет, является ли строка верным одиночным параметром
    int NOT_pos = str.find("NOT");
    if (NOT_pos != -1) {
        string checkstr;
        if (str[NOT_pos + 3] != ' ')
            return 0;
        int i = NOT_pos + 4;
        while (str[i] != ' ' && i != str.length()) {
            checkstr += str[i];
            i++;
        }
        if (checkstr.compare("TRUE") == 0 || checkstr.compare("FALSE") == 0 || (checkstr.length() == 1 && isalpha(checkstr[0]))) {
            str = str.substr(0, NOT_pos) + "TRUE" + str.substr(i, str.length() - i);
        }
        else
            return 0;

    }
    return (str.compare("TRUE") == 0 || str.compare("FALSE") == 0 || (str.length() == 1 && isalpha(str[0])));
}

int analize(string str) {//Функция анализа строки
    cout << "Analizing " << str << endl;
    if (check_TRUE_FALSE_LETTER(str))
        return 0;

    int AND_pos = str.find("AND");
    if (AND_pos != -1) {
        if (AND_pos == 0 || AND_pos >= str.length() - 3 || str[AND_pos - 1] != ' ' || str[AND_pos + 3] != ' ')
            return 0;
        if (check_TRUE_FALSE_LETTER(str.substr(0, AND_pos - 1)) &&
            check_TRUE_FALSE_LETTER(str.substr(AND_pos + 4, str.length() - AND_pos - 4))) {
            return 1;
        }
    }

    int OR_pos = str.find("OR");
    if (OR_pos != -1) {
        if (OR_pos == 0 || OR_pos >= str.length() - 2 || str[OR_pos - 1] != ' ' || str[OR_pos + 2] != ' ')
            return 0;
        if (check_TRUE_FALSE_LETTER(str.substr(0, OR_pos - 1)) &&
            check_TRUE_FALSE_LETTER(str.substr(OR_pos + 3, str.length() - OR_pos - 3))) {
            return 1;
        }
    }
    return 0;
}

void findPar(string str, int* a, int* b) {//Функция поиска скобок
    int x1 = -1, x2 = -1;
    int i = 0;
    while (i < str.length() && str[i] != ')') {//Идем до первой ')'
        if (str[i] == '(') {//Попутно находя соответствующую ей '('
            x1 = i;
        }
        i++;
    }
    if (i != str.length())
        x2 = i;
    *a = x1;
    *b = x2;
}

void printThings(int a) {//Вывод глубины рекурсии
    for (int i = 0; i < a; i++) {
        cout << "---";
        cout << "|";
    }
}

int func(string* str, int depth) { //Рекурсивная функция
    if (check_TRUE_FALSE_LETTER(*str))//Проверяем на один параметр
        return 1;
    int a = 0, b = 0;
    findPar(*str, &a, &b);//Находим первые скобки, в которых нет других скобок
    if (a == -1 || b == -1) {//Если в строке нет какой-то одной скобки - неверно
        return 0;
    }
    printThings(depth);
    if (analize(str->substr(a + 1, b - a - 1))) {//Запускаем анализ строки в скобках
        string tmp = str->substr(0, a) + "TRUE" + str->substr(b + 1, (str->length() - a - 4));//Меняем эту строку если все ок
        printThings(depth);
        cout << "Making " << *str << " to " << tmp << endl;
        (*str) = tmp;
        if (func(str, depth + 1)) {//Запускаем снова эту функцию
            printThings(depth);
            cout << "Nice string\n";
            return 1;
        }
        else
            return 0;
    }
    return 0;
}

int main() {
    int choose = 0;
    cout << "Choose input:\n0.CIN\n1.FILE\n";
    cin >> choose;//Выбираем между вводом с консоли и из файла
    string x;
    if (choose == 0) {
        cin.ignore(1);
        getline(cin, x);
    }
    else {
        ifstream ff;
        ff.open("Lab1.txt");
        if (ff.is_open())
            getline(ff, x);
        else
            return 0;
        cout << "In file:\n" << x << "\n";
        ff.close();
    }
    if (func(&x, 0) == 1) {//Запускаем рекурсию
        cout << "OK\n";
    }
    else {
        cout << "NOT OK\n";
    }
    return 0;
}