#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

struct Node {
    char symbol_;
    std::string code_;
};

int getHash(int tableSize, std::string s) {
    int k = 0;
    for (int i = 0; i < s.size(); i++)
        k += (s.at(i) - '0') * pow(2, s.size() - i - 1);
    //std::cout << "Code = " << s << "Hash == " << k % tableSize << std::endl;
    return k % tableSize;
}

struct HashTable {
    std::vector<char> arr_;

    explicit HashTable(int size) {
        arr_ = std::vector<char>(size);
    }

    void addElement(const Node &n) {
        int k = getHash(arr_.size(), n.code_);
        if (arr_.at(k) != '\0') {
            throw std::runtime_error("Внимание коллизия");
        }
        arr_.at(k) = n.symbol_;
    }
    char getElement(std::string s)
    {
        int k = getHash(arr_.size(), s);
        std::cout<<"Найден код : "<< s <<"  Хэш : "<< k<<std::endl;
        return arr_.at(k);
    }
};

int getLog(int a);

template<typename StreamT>
void getCode(StreamT &in, std::string &res) {
    char c;
    res.clear();

    in >> std::noskipws;

    in >> c;
    if (c != ' ')
        throw std::runtime_error("Нехватает пробела");
    while (in >> c && c != '\n') {
        if (c != '0' && c != '1')
            throw std::runtime_error("Неверный код");
        res.push_back(c);
    }
}

template<typename StreamT>
void readTable(StreamT &in, std::vector<Node> &table, int size) {
    char symbol;
    std::string code;
    int codeSize = getLog(size);
    while (in >> symbol && symbol != '\n') {
        getCode(in, code);
        if (code.size() != codeSize)
            throw std::runtime_error("Неверная длина кода");
        //std::cout << symbol << "-->" << code << std::endl;
        for (auto &i:table) {
            if (i.code_ == code)
                throw std::runtime_error("Введенный код уже используется");
            if (i.symbol_ == symbol)
                throw std::runtime_error("Введенный символ уже имеет код");
            if (table.size() > size - 1)
                throw std::runtime_error("Введено неверное кол-во символов");
        }
        Node n{symbol, code};
        table.push_back(n);
    }
    if (table.size() != size)
        throw std::runtime_error("Введено неверное кол-во символов");
}

void printNode(const Node &n) {
    std::cout << "имя - " << n.symbol_ << "  Код - " << n.code_ << std::endl;
}

void printTable(const std::vector<Node> &table) {
    for (auto &i:table)
        printNode(i);
}

void printHashTable(const HashTable &t) {
    std::cout << "Вывод хэш-таблицы" << std::endl;
    for (int i = 0; i < t.arr_.size(); i++)
        std::cout << i << " : " << t.arr_.at(i) << std::endl;
}

int getLog(int k) {
    if (k == 1)
        return 1;
    int t = k - 1;
    int res = 0;
    while (t != 0) {
        t /= 2;
        res++;
    }
    return res;
}


template<typename StreamT>
bool readCode(StreamT &in, int codeSize, std::string &temp) {
    char c;
    temp.clear();
    for (int i = 0; i < codeSize; i++) {
        in >> c;
        if (c == '\n')
            break;
        if (c != '1' && c != '0')
            throw std::runtime_error("Неверный формат закодированного сообщения c =" + c);
        temp.push_back(c);
    }
    if (temp.size() != 0 && temp.size() != codeSize)
        throw std::runtime_error("Неверный формат закодированного сообщения");
    return temp.size() == codeSize;
}

template<typename StreamT>
std::string deCode(StreamT &in, int codeSize,  HashTable &hTable) {
    std::string res;
    std::string temp;
    char c;
    int k;
    while (readCode(in, codeSize, temp)) {
        c = hTable.getElement(temp);
        if (c == '\0')
            throw std::runtime_error("Неопознанный код " + temp);
        res.push_back(c);
    }
    return res;
}

void launch() {
    int symbolCount;
    std::vector<Node> table;
    int readFormat;

    std::cout << "0 - считать из файла, 1 - считать с консоли" << std::endl;
    std::cin >> readFormat;
    std::cin.ignore();
    switch (readFormat) {
        case 0: {
            std::cout << "Введите имя файла : ";
            std::ifstream in;
            std::string fileName;
            std::cin >> fileName;
            in.open(fileName);
            if (in) {
                in >> symbolCount;
                HashTable hTable(pow(2, getLog(symbolCount)));
                readTable(in, table, symbolCount);

                for (auto &i:table) {
                    hTable.addElement(i);
                }
                printHashTable(hTable);
                std::string res = deCode(in, getLog(symbolCount), hTable);
                std::cout << "res-->" << res;
            } else
                throw std::runtime_error("Файл не найден!");
            in.close();
            break;
        }
        case 1: {
            std::cout
                    << "Введите количество символов в словаре"
                    << std::endl;

            std::cin >> symbolCount;
            HashTable hTable(pow(2, getLog(symbolCount)));
            std::cout
                    << "Введите символы и их коды через пробел, каждая пара символ-код с новой строки."
                       " Конец ввода - пустая строка. Например: a 101"
                    << std::endl;
            std::cout << "Длина кода = " << getLog(symbolCount) << std::endl;
            readTable(std::cin, table, symbolCount);
            for (auto &i:table) {
                hTable.addElement(i);
            }

            printHashTable(hTable);
            std::cout
                    << "Введите закодированное сообщение"
                    << std::endl;
            std::string res = deCode(std::cin, getLog(symbolCount), hTable);
            std::cout << "res-->" << res;
            break;
        }
        default: {
            throw std::runtime_error("Неверное действие");
        }
    }
}

int main() {
    try {
        launch();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}