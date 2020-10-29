#include <iostream>
#include <string>
#include <cctype>
#include <typeinfo>
#include <fstream>
using namespace std;

struct BinKor;

//Плечо ::= (Длина Груз(Гирька | БинКор))
struct Side {
    int length;// Длинна плеча
    bool isWeight;// true:Груз false:БинКор
    union {
        int weight;//Масса груза
        BinKor* bin_kor;//БинКор
    } data;
};

//БинКор ::= (Плечо Плечо)
struct BinKor {
    Side* left;// Левое плечо
    Side* right;//Правое плечо
};

void rightPrint(int indent, int result) {
    for (int i = 0; i < indent; i++) {//выводим нужное количество отступов
        std::cout << ("\t");
    }
    std::cout << "right weight weights: " << result;//Выводим результат рекурсии
    std::cout << '\n' << '\n';
}

void leftPrint(int indent, int result) {
    for (int i = 0; i < indent; i++) {//выводим нужное количество отступов
        std::cout << ("\t");
    }
    std::cout << "left weight weights: " << result;//Выводим результат рекурсии
    std::cout << '\n' << '\n';
}

void rightLeftPrint(int indent, int result) {
    for (int i = 0; i < indent; i++) {//выводим нужное количество отступов
        std::cout << ("\t");
    }
    std::cout << "right + left weights weight: " << result;;//Выводим результат рекурсии
    std::cout << '\n' << '\n';
}

unsigned int W(BinKor* bin_kor, int indent) {//Функция для поиска длины
    unsigned int result = 0;

    if (bin_kor->right) {//Если есть правое плечо
        if (bin_kor->right->isWeight) {
            rightPrint(indent, bin_kor->right->data.weight);// Выводим результат
            result += bin_kor->right->data.weight;
        }
        if (!bin_kor->right->isWeight)//Если груз
            result += W(bin_kor->right->data.bin_kor, indent + 1);
    }
    if (bin_kor->left) {//Если есть левое плечо
        if (bin_kor->left->isWeight) {
            leftPrint(indent, bin_kor->left->data.weight);// Выводим результат
            result += bin_kor->left->data.weight;
        }
        if (!bin_kor->left->isWeight)//Если груз
        {
            result += W(bin_kor->left->data.bin_kor, indent + 1);
        }
        rightLeftPrint(indent, result);// Выводим результат
    }
    return result;//Возвращает результат
}


void drop(std::string& str, int n) {
    if (str.length() >= n) {//Если длинна больше или равно
        str = str.substr(n);//Отрезаем лишнии символы
    }
}

short readNum(string& str) {
    string number = "";

    while (isdigit(str[0])) {//Пока цифры сохраняем в строчку
        number += str[0];
        drop(str, 1);// Отрезаем не нужный символ
    }
    try {
        string i;
        i = stoi(number);
    }
    catch (const std::invalid_argument&) {
        std::cout << "Wrong input !" << '\n';
        exit(0);
    }
    return stoi(number);//Возвращаем число
}


// (Side Side)
Side* createNewSide(string& input);
BinKor* createNewBinKor(string& input) {
    BinKor* bin_kor = new BinKor;
    drop(input, 1);// Отрезаем ненужный символ
    bin_kor->left = createNewSide(input);
    drop(input, 1);// Отрезаем ненужный символ
    bin_kor->right = createNewSide(input);
    drop(input, 1);// Отрезаем ненужный символ
    return bin_kor;
}

Side* createNewSide(string& input) {// Создаем сторону
    Side* side = new Side;
    drop(input, 1);// Отрезаем ненужный символ
    side->length = readNum(input);
    drop(input, 1);// Отрезаем ненужный символ
    side->isWeight = (input[0] != '(');
    if (side->isWeight) {
        side->data.weight = readNum(input);
    }
    else {
        side->data.bin_kor = createNewBinKor(input);
    }
    drop(input, 1);// Отрезаем не нужный символ
    return side;
}


void freeBinKor(BinKor* bin_kor) {
    if (bin_kor != nullptr) {// Если указывает на  BinKor
        if (bin_kor->right->isWeight == 0) {// Если не груз
            freeBinKor(bin_kor->right->data.bin_kor);// Вызываем рекурсивную функцию
            delete bin_kor->right;// Освобождаем сторону
        }
        else {
            delete bin_kor->right;// Освобождаем сторону
        }
        if (bin_kor->left->isWeight == 0) {// Если не груз
            freeBinKor(bin_kor->left->data.bin_kor);// Вызываем рекурсивную функцию
            delete bin_kor->left;// Освобождаем сторону
        }
        else {
            delete bin_kor->left;// Освобождаем сторону
        }
        delete bin_kor;// Освобождаем BinKor
    }
    else {
        std::cout << "delete" << '\n';
    }
}

void printBinKor(BinKor* bin_kor, int n)
{
    std::cout << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << '\t';
    std::cout << "Left side: ";
    if (bin_kor->left->isWeight)
        std::cout << '(' << bin_kor->left->length << ' ' << bin_kor->left->data.weight << ')' << std::endl;
    else
    {
        std::cout << '(' << bin_kor->left->length << " (...))" << std::endl;
        printBinKor(bin_kor->left->data.bin_kor, n+1);
    }
    std::cout << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << '\t';
    std::cout << "Right side: ";
    if (bin_kor->right->isWeight)
        std::cout << '(' << bin_kor->right->length << ' ' << bin_kor->right->data.weight << ')' << std::endl;
    else
    {
        std::cout << '(' << bin_kor->right->length << " (...))" << std::endl;
        printBinKor(bin_kor->right->data.bin_kor, n+1);
    }
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    std::string input;
    if (argc == 2)
    {
        std::string file = argv[1];
        std::ifstream fin(file);// окрываем файл для чтения
        if (fin.is_open())
            getline(fin, input);
        else
        {
            std::cout << "Can`t open file" << std::endl;
            return 0;
        }
        fin.close();
    }
    else
    {
        getline(cin, input);
    }
    int indent = 0;// отступ
    if (input.length() == 0) {// Если файл  пуст
        std::cout << "Input is empty" << '\n';
        exit(0);
    }
    std::cout << '\n' << "You entered:" << input << '\n' << '\n';
    BinKor* bin_kor = new BinKor;// Создаем указатель на BinKor
    bin_kor = createNewBinKor(input);
    std::cout << std::endl;
    std::cout << "Программа печатает сначала левую сторону бинарного коромысла, затем правую\nЕсли груз == бинарное коромысло, то выводится (...) и с бОльшим отступом печатается его левая и правая сторона\nОтступ == глубина рекурсивного прохода бинарного коромысла\n";
    printBinKor(bin_kor, 0);
    std::cout << std::endl << "_______________________________________" << "\n\n";
    int res = W(bin_kor, indent);
    std::cout << '\n' << "Weight of all weights: " << res << '\n';
    freeBinKor(bin_kor);// Особождаем память
    return 0;
}
