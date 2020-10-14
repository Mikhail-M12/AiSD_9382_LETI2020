#include <iostream>
#include<cstring>
#include <fstream>
#include <cstdlib>
#include <locale.h>
#include <conio.h>

using namespace std;
enum attributes { EOI, NUM, OR, AND, NOT, LP, RP };
typedef struct
{
    enum attributes attrib;
    char symbol;
} symbolFieald;

namespace main_vars {
    unsigned int str_index;
    char *input_str = nullptr;
}
//объявляем заранее что-бы у каждой функции была видимость другой функции
string state(char* input, int n, ofstream &fout);
int orExept(symbolFieald &symb, int n, ofstream &fout);
int term(symbolFieald &symb, int n, ofstream &fout);
int parentheses(symbolFieald &symb, int n, ofstream &fout);
int nparentheses(symbolFieald &symb, int n, ofstream &fout);
char interpretator(const char* str);
symbolFieald getNext();


int main() { /* головная функция, тут реализован ввод и вывод из файла, преобразование строки из слов в
     в символьную и вызов функции state, которая является точкой запуска рекурсивного алгоритма */
   setlocale(LC_ALL, "Russian"); // задаём русский текст
    ifstream fin;
    ofstream fout;
    string path1, path2;
    cout << "Введите путь откуда читать логическое выражение и путь куда записывать:\n";
    //работа с файлами
    cin >> path1 ;
    cin >> path2;
    fin.open(path1);
    fout.open(path2);
    if(fin.is_open()) cout << "Файл " << path1<< " успешно открыт\n";
    else{
        cout << "Не удалось открыть файл " << path2;
        return 0;
    }
    string input;
    getline(fin, input);
    fin.close();

    char *pch;
    int len = input.size();
    int count = 0;
    int str_size =0;
    for(int i = 0; i < len; i++) {
        if (input.substr(i, 1) == " ")
            str_size++;
    }
    str_size+=2;
    char* input_str_cpy = new char[len+1];
    strcpy(input_str_cpy, input.c_str());
    char *str = new char[str_size];
    pch = strtok(input_str_cpy, " ");
    while(pch){
        str[count] = interpretator(pch);
        count++;
        pch = strtok(nullptr, " ");
    }
    str[count] = '\0';
    string result = state(str, 0, fout);
    cout << "Значение выражения: " << result <<"\n";
    fout << "Значение выражения: " << result <<"\n";
    delete [] str;
    delete [] input_str_cpy;
    fout.close();
	getch();
    return 0;
}
void printDepth(int n, ofstream& fout){ // Для вывода глубины рекурсии
    for(int i = 0; i < n; i++)
        fout << ".";
}



string state(char* input, int n, ofstream &fout) { /* Проверяем первый символ строки, после чего
 * запускается алгоритм рекурсивного спуска и вычисляется результат выражения */
    printDepth(n, fout);
    fout << "Зашёл в функцию state. " << "Аргумент: " << input << "\n";
    int result = 0;
    symbolFieald symb;
    main_vars::input_str = input;
    main_vars::str_index = 0;
    symb = getNext();
    switch (symb.attrib) {
        case LP:
        case NUM:
        case NOT:
            // orExept может начинаться с открывающейся скобки,  числа или слова not
            result = orExept(symb, n + 1, fout);
            break;
        default:
            break;
    }
    printDepth(n, fout);
    fout << "Вышел из функции state. Возвращаемое значение: ";
    if (result > 0) {
        fout << "TRUE\n";
        return "TRUE";
    } else {
        fout << "FALSE\n";
        return "FALSE";
    }
}

int orExept(symbolFieald &symb, int n, ofstream &fout) { // разбирает значения, между которыми стоит or   expr
    printDepth(n, fout);
    fout << "Зашёл в функцию orExept. " << "Текущий символ: " << symb.symbol << "\n";
    symbolFieald tmp_symb = symb;
    int ret = 0;
    switch (tmp_symb.attrib) {
        case NUM:
        case LP:
        case NOT:
            ret = term(tmp_symb, n + 1, fout);
            tmp_symb = getNext();
            switch (tmp_symb.attrib) {
                case OR:
                    tmp_symb = getNext();
                    ret += orExept(tmp_symb, n + 1, fout);
                    break;
                case RP:
                    // Если символ равен закрывающейся скобке, возвращаем его назад в строку
                    main_vars:: str_index--;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    printDepth(n, fout);
    fout << "Вышел из функции orExept. Возвращаемое значение: " << ret << "\n";
    return ret;
}

int term(symbolFieald &symb, int n, ofstream &fout) { // разбирает выражения, между которыми стоит and
    printDepth(n, fout);
    fout << "Зашёл в функцию term. " << "Текущий символ: " << symb.symbol << "\n";
    symbolFieald tmp_symb = symb;
    int ret = 0;
    switch (tmp_symb.attrib) {
        case LP:
        case NUM:
            ret = parentheses(tmp_symb, n + 1, fout);
            tmp_symb = getNext();
            switch (tmp_symb.attrib) {
                case AND:
                    tmp_symb = getNext();
                    ret *= term(tmp_symb, n + 1, fout);
                    break;
                case OR:
                case RP:
                    // Если символ равен плюсу или закрывающейся скобке, возвращаем его назад
                    main_vars:: str_index--;
                default:
                    break;
            }
            break;
        case NOT:
            ret = nparentheses(symb, n + 1, fout);
            tmp_symb = getNext();
            switch (tmp_symb.attrib) {
                case AND:
                    tmp_symb = getNext();
                    ret *= term(tmp_symb, n + 1, fout);
                    break;
                case OR:
                case RP:
                    // Если текущий символ равен or или закрывающейся скобке, возвращаем его назад
                    main_vars:: str_index--;
                default:
                    break;
            }
            break;

        default:
            break;
    }
    printDepth(n, fout);
    fout << "Вышел из функции term. Возвращаемое значение: " << ret << "\n";
    return ret;
}
int nparentheses(symbolFieald &symb, int n, ofstream &fout) {
    // разбирает  любые элементарные значения  и выражения в скобках, если перед ними стоит отрицание
    printDepth(n, fout);
    fout << "Зашёл в функцию nparentheses. " << "Текущий символ: " << symb.symbol << "\n";
    int ret = 0;
    symbolFieald tmp_symb = getNext();
    switch (tmp_symb.attrib) {
        case NUM:
            ret = (atoi(&tmp_symb.symbol) == 0);
            break;
        case LP:
            tmp_symb = getNext();
            ret = (orExept(tmp_symb, n + 1, fout) == 0);
            tmp_symb = getNext();
            break;
        case NOT:
            ret = !nparentheses(symb, n + 1, fout);
            break;
        default:
            break;
    }
    printDepth(n, fout);
    fout << "Вышел из функции nparentheses. Возвращаемое значение: " << ret << "\n";
    return ret;
}
int parentheses(symbolFieald &symb, int n, ofstream &fout) { // разбирает элементарные значения и выражения в скобках   fact
    printDepth(n, fout);
    fout << "Зашёл в функцию parentheses. " << "Текущий символ: " << symb.symbol << "\n";
    int ret = 0;
    symbolFieald tmp_symb = symb;
    switch (tmp_symb.attrib) {
        case NUM:
            ret = atoi(&tmp_symb.symbol);
            break;
        case LP:

            tmp_symb = getNext();
            ret = orExept(tmp_symb, n + 1, fout);
            tmp_symb = getNext();
            // Считываем закрывающуюся скобку
            break;
        default:
            break;
    }
    printDepth(n, fout);
    fout << "Вышел из функции parentheses. Возвращаемое значение: " << ret << "\n";
    return ret;
}

using namespace main_vars;

symbolFieald getNext() /* последовательно даёт доступ к символам логического выражения ,
 * присваивает им атрибуты. За каждый запуск символ сдвигается на 1 */
{
    symbolFieald cur_symb;
    cur_symb.attrib = EOI;

    switch (input_str[str_index])
    {
        case '0':
        case '1':
            cur_symb.attrib = NUM;
            break;
        case '|':
            cur_symb.attrib = OR;
            break;
        case '&':
            cur_symb.attrib = AND;
            break;
        case '(':
            cur_symb.attrib = LP;
            break;
        case ')':
            cur_symb.attrib = RP;
            break;
        case '`':
            cur_symb.attrib = NOT;
            break;
        default:
            break;
    }

    if (cur_symb.attrib != EOI)
    {
        cur_symb.symbol = input_str[str_index];
        str_index++;
    }

    return cur_symb;
}

char interpretator(const char* str){ // позволяет преобразовать строку, состоящую из слов, в символьную
    switch(*str){
        case 'T':
            return '1';
        case 'F':
            return '0';
        case 'A':
            return '&';
        case 'O':
            return '|';
        case '(':
            return '(';
        case ')':
            return ')';
        case 'N':
            return '`';
        default:
            return '*';
    }
}
