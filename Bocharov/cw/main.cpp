#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <memory>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <list>
#include <time.h>
#include <chrono>


int depth = 0;

std::string outFileName;

struct Symbol {
    char value_; //символ
    int weight_; // количество повторений
    std::string code_;

    Symbol() {
        value_ = '\0';
        weight_ = 0;
        code_ = "";
    }

    Symbol(char value, int weight, std::string code) {
        value_ = value;
        weight_ = weight;
        code_ = code;
    }
};

struct Symbols {
    std::vector<Symbol> values_;
    int weight_;

    Symbols() {
        weight_ = 0;
    }
};

struct Node {
    Symbols symbols_;
    std::string code_;
    Node *left_;
    Node *right_;

    explicit Node() {
        code_ = "";
        left_ = nullptr;
        right_ = nullptr;
    }

    Node(const Symbols &symbols, const std::string &code) {
        symbols_ = symbols;
        code_ = code;
        left_ = nullptr;
        right_ = nullptr;
    }

    void createLeft(const Symbols &symbols, const std::string &code) {
        if (left_ != nullptr)
            throw std::runtime_error("Левое поддерево не пусто");
        left_ = new Node(symbols, code);
    }

    void createRight(const Symbols &symbols, const std::string &code) {
        if (right_ != nullptr)
            throw std::runtime_error("Левое поддерево не пусто");
        right_ = new Node(symbols, code);
    }

    void addChild(const Symbols &symbols, const std::string &code) {
        if (left_ == nullptr)
            createLeft(symbols, code);
        else if (right_ == nullptr)
            createRight(symbols, code);
        else
            throw std::runtime_error("Некуда добавить потомка");
    }
};


// Компараторы
bool comp(const Symbol &i, const Symbol &j) {
    return i.weight_ > j.weight_;
}

struct comp1 {
    bool operator()(Node *i, Node *j) const {
        return i->symbols_.weight_ > j->symbols_.weight_;
    }
};

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

//считывание
template<typename StreamT>
std::string readSymbol(StreamT &in, std::vector<Symbol> &atoms) {
    std::string result;
    char c;
    in >> std::noskipws;
    while (in >> c && c != '\n') {
        int k = (int) c;
        atoms.at(k).value_ = c;
        atoms.at(k).weight_ += 1;
        result.push_back(c);
    }
    return result;
}

template<typename StreamT>
bool getCode(StreamT &in, Node *head, std::string &res) {
    char c;
    if (head->symbols_.values_.size() == 1) {
        res.push_back(head->symbols_.values_.at(0).value_);
        return true;
    }
    in >> std::noskipws;
    in >> c;

    if (c == '0')
        return getCode(in, head->left_, res);
    else if (c == '1')
        return getCode(in, head->right_, res);
    else if (c == '\n')
        return false;
    else
        throw std::runtime_error("Неверный формат закодированного сообщения" + c + ' --');
}

template<typename StreamT>
void deCode(StreamT &in, Node *head, std::string &res) {
    while (getCode(in, head, res));
}

template<typename StreamT>
void readCountTable(StreamT &in, std::vector<Symbol> &symbols) {
    std::string line;
    char c;
    int weight;
    in >> std::noskipws;
    while (std::getline(in, line) && !line.empty()) {
        std::istringstream str(line);
        str >> c;
        str >> weight;
        symbols.at(c).value_ = c;
        symbols.at(c).weight_ = weight;
    }

}

void printAtoms(Symbols &atoms) {
    for (auto &i:atoms.values_)
        std::cout << "Символ - " << i.value_ << "  Кол-во вхождений - " << i.weight_ << std::endl;
    std::cout << "Общий вес строки = " << atoms.weight_ << std::endl;
}


//работа с символами

void cutZeroes(std::vector<Symbol> &symbols, Symbols &res) {
    for (auto &i:symbols)
        if (i.value_ != '\0' && i.weight_ != 0) {
            Symbol a(i.value_, i.weight_, i.code_);
            res.values_.push_back(a);
            res.weight_ += a.weight_;
        }
}

void splitAtoms(Symbols &atoms, Symbols &res1, Symbols &res2) {
    bool k = true;
    for (auto &i:atoms.values_) {
        if (abs(res1.weight_ + i.weight_ - atoms.weight_ / 2) > abs(res1.weight_ - atoms.weight_ / 2))
            k = false;
        if (k) {
            res1.values_.push_back(i);
            res1.weight_ += i.weight_;
        } else {
            res2.values_.push_back(i);
            res2.weight_ += i.weight_;
        }
    }

}

void unitAtoms(Symbols &atoms1, Symbols &atoms2, Symbols &res) {
    for (auto &i:atoms1.values_) {
        res.values_.push_back(i);
        res.weight_ += i.weight_;
    }
    for (auto &i:atoms2.values_) {
        res.values_.push_back(i);
        res.weight_ += i.weight_;
    }
}




//Получение кодов символов


// Построение бинарного дерева Фано-Шенона
void S_F_Code(Node *&head, std::vector<Symbol> &S) {
    if (head->symbols_.values_.size() == 1) {
        S.at(head->symbols_.values_.at(0).value_).code_ = head->code_;
        return;
    }
    Symbols arr1;
    Symbols arr2;
    splitAtoms(head->symbols_, arr1, arr2);
    head->addChild(arr1, head->code_ + '0');
    head->addChild(arr2, head->code_ + '1');
    S_F_Code(head->left_, S);
    S_F_Code(head->right_, S);
}

void printTree(Node *head) {
    depth++;
    if (head == nullptr)
        return;
    std::cout << "<Depth " << depth << " > " << std::endl;
    std::string s(depth, ' ');

    printAtoms(head->symbols_);
    printTree(head->left_);
    depth--;
    printTree(head->right_);
    depth--;
}

void printTreeCode(Node *head) {
    if (head == nullptr)
        return;
    if (head->left_ == nullptr && head->right_ == nullptr)
        std::cout << "<Символ - " << head->symbols_.values_.at(0).value_ << " Код -  " << head->code_ << std::endl;

    printTreeCode(head->left_);
    printTreeCode(head->right_);
}

void initHahmanCodes(Node *head, std::string code, std::vector<Symbol> &S) {
    if (head == nullptr)
        return;

    head->code_ = code;
    if (head->symbols_.values_.size() == 1) {
        S.at(head->symbols_.values_.at(0).value_).code_ = head->code_;
    }
    initHahmanCodes(head->left_, head->code_ + "0", S);
    initHahmanCodes(head->right_, head->code_ + "1", S);
}

// Построение бинарного дерева Хафмана
Node *Hafman_Code(Symbols &atoms, std::vector<Symbol> &S) {
    std::list<Node *> strings;
    for (auto &i:atoms.values_) {
        Node *n = new Node();
        n->symbols_.values_.push_back(i);
        n->symbols_.weight_ = i.weight_;
        strings.push_back(n);
    }
    while (strings.size() != 1) {
        strings.sort(comp1());
        Symbols s;

        Node *left = strings.back();
        strings.pop_back();

        Node *right = strings.back();
        strings.pop_back();

        Node *parent = new Node();
        parent->left_ = left;
        parent->right_ = right;

        unitAtoms(left->symbols_, right->symbols_, s);
        parent->symbols_ = s;
        strings.push_front(parent);
    }
    initHahmanCodes(strings.front(), "", S);
    return strings.front();
}

std::string codeMessage(std::string &message, std::vector<Symbol> &S) {
    std::string result;
    for (auto &i:message) {
        result += S.at(i).code_;
    }
    return result;
}


void printMenu() {
    std::cout << "1 - кодирование методом Фано-Шенона\n"
                 "2 - кодирование мотодом Хафмана\n"
                 "3 - декодирование методом Фано-Шенона\n"
                 "4 - декодирование методом Хафмана\n" << std::endl;
}

template<typename StreamT>
void askAction(StreamT &in) {

    std::string line;
    std::getline(std::cin, line);
    std::istringstream str(line);
    int k;
    str >> k;

    switch (k) {
        case 1: {
            clock_t time;
            time = clock();
            std::vector<Symbol> symbols(256); //для кодирования
            Symbols atoms;
            std::string message = readSymbol(in, symbols);


            cutZeroes(symbols, atoms);

            std::sort(atoms.values_.begin(), atoms.values_.end(), comp);

            Node *head = new Node(atoms, "");
            S_F_Code(head, symbols);

            printTreeCode(head);

            std::string res = codeMessage(message, symbols);
            std::cout << res << std::endl;

            time = clock() - time;

            std::cout<<"Исходное сообщение - "<< message << "\nКол-во символов в исходном сообщении - " << atoms.weight_
                      << "\nРазмер Кода - " << res.size() <<
                      "\nРазмер кода при равномерном кодировании - " << getLog(atoms.values_.size()) * atoms.weight_
                      << "\nВремя работы алгоритмма - " << (double) time / CLOCKS_PER_SEC
                      << std::endl;

            outFileName ="Shennon_Fano_Code_"+ outFileName;
            std::ofstream fout;
            fout.open(outFileName);
            fout << res<<std::endl;
            fout<<"Исходное сообщение - "<< message << "\nКол-во символов в исходном сообщении - " << atoms.weight_
                      << "\nРазмер Кода - " << res.size() <<
                      "\nРазмер при равномерном кодировании - " << getLog(atoms.values_.size()) * atoms.weight_
                      << "\nВремя работы алгоритмма - " << (double) time / CLOCKS_PER_SEC
                      << std::endl;
            fout.close();

            break;
        }
        case 2: {
            clock_t time;
            time = clock();

            std::vector<Symbol> symbols(256); //для кодирования
            Symbols atoms;
            std::string message = readSymbol(in, symbols);

            cutZeroes(symbols, atoms);

            std::sort(atoms.values_.begin(), atoms.values_.end(), comp);

            Node *head = Hafman_Code(atoms, symbols);
            printTreeCode(head);
            std::string res = codeMessage(message, symbols);
            std::cout << res << std::endl;

            time = clock() - time;


            std::cout<<"Исходное сообщение - "<< message << "\nКол-во символов в исходном сообщении - " << atoms.weight_
                      << "\nРазмер Кода - " << res.size() <<
                      "\nРазмер при равномерном кодировании - " << getLog(atoms.values_.size()) * atoms.weight_
                      << "\nВремя работы алгоритмма - " << (double) time / CLOCKS_PER_SEC
                      << std::endl;

            outFileName ="Haffman_Code_"+ outFileName;
            std::ofstream fout;
            fout.open(outFileName);

            fout << res<<std::endl;
            fout<<"Исходное сообщение - "<< message << "\nКол-во символов в исходном сообщении - " << atoms.weight_
                      << "\nРазмер Кода - " << res.size() <<
                      "\nРазмер при равномерном кодировании - " << getLog(atoms.values_.size()) * atoms.weight_
                      << "\nВремя работы алгоритмма - " << (double) time / CLOCKS_PER_SEC
                      << std::endl;
            fout.close();
            break;
        }
        case 3: {
            clock_t time;

            time = clock();
            std::vector<Symbol> symbols(256); //для кодирования
            Symbols atoms;

            readCountTable(in, symbols);
            cutZeroes(symbols, atoms);

            if(atoms.values_.empty())
            {
                throw std::runtime_error("Пустые входное данные");
            }

            std::sort(atoms.values_.begin(), atoms.values_.end(), comp);

            Node *head = new Node(atoms, "");
            S_F_Code(head, symbols);


            printTreeCode(head);
            std::string result;

            deCode(in, head, result);

            time = clock() - time;

            std::cout << "Исходное сообщение -" << result
                      << "\nВремя работы алгоритмма - " << (double) time / CLOCKS_PER_SEC
                      << std::endl;


            outFileName ="Shennon_Fano_Decode_"+ outFileName;
            std::ofstream fout;
            fout.open(outFileName);

            fout << "Исходное сообщение -" << result
                      << "\nВремя работы алгоритмма - " << (double) time / CLOCKS_PER_SEC
                      << std::endl;
            fout.close();
            break;
        }
        case 4: {
            clock_t time;
            time = clock();
            std::vector<Symbol> symbols(256); //для кодирования
            Symbols atoms;

            readCountTable(in, symbols);
            cutZeroes(symbols, atoms);
            if(atoms.values_.empty())
            {
                throw std::runtime_error("Пустые входное данные");
            }

            std::sort(atoms.values_.begin(), atoms.values_.end(), comp);

            Node *head = Hafman_Code(atoms, symbols);

            std::string result;


            printTreeCode(head);

            deCode(in, head, result);

            time = clock() - time;

            std::cout << "Исходное сообщение -" << result
                      << "\nВремя работы алгоритмма - " << (double) time / CLOCKS_PER_SEC
                      << std::endl;

            outFileName ="Haffman_Decode_"+ outFileName;
            std::ofstream fout;
            fout.open(outFileName);

            fout << "Исходное сообщение -" << result
                 << "\nВремя работы алгоритмма - " << (double) time / CLOCKS_PER_SEC
                 << std::endl;
            fout.close();

            break;
        }
        default:
            break;
    }
}

void askFormat() {
    int readFormat;
    std::cout << "0 - считать из файла, 1 - считать с консоли" << std::endl;

    std::string line;
    std::getline(std::cin, line);
    std::istringstream str(line);

    str >> readFormat;
    switch (readFormat) {
        case 0: {
            std::cout << "Введите имя файла : ";
            std::ifstream in;
            std::string fileName;
            std::getline(std::cin, fileName);
            in.open(fileName);
            if (in) {
                outFileName = fileName;
                printMenu();
                askAction(in);
            } else
                throw std::runtime_error("Файл не найден!");
            in.close();
            break;
        }
        case 1: {

            printMenu();
            std::cout
                    << "Введите дествие, затем кодироемое сообщение"
                       "или декодироемое сообщение(Должно содержать символы и кол-во их повторений и закодированную последовательность)"
                       "\nПример кодируемой последовательности : abbssa"
                       "\n Пример декодируемой последовательности :"
                       "\ns 5"
                       "\nk 10"
                       "\nl 7"
                       "\n"
                       "\n1111111111000000000010101010101010"
                    << std::endl;
            askAction(std::cin);
            break;
        }
        default: {
            throw std::runtime_error("Неверное действие");
        }
    }

}

int main() {

    askFormat();
    return 0;
}
