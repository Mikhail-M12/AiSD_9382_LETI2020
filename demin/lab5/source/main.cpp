//
// Created by vikto on 20.11.2020.
//
// add logger

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;
typedef struct nodeTree node;

struct nodeTree {//узел бинарного дерева
    nodeTree(int w, char c) {
        this->weight = w;
        this->ch = c;
        this->left = nullptr;
        this->right = nullptr;
    }

    nodeTree() {
        weight = 0;
        ch = -1;
        left = nullptr;
        right = nullptr;
    }

    int weight;//вес узла
    char ch;//символ в узле
    node *left;//левое поддерево
    node *right;//правое поддерево
};

//класс для вывода промежуточных значений
class logger {
    ofstream file;

public:
    logger() {
        file.open("intermeiate.txt");
        if (!file.is_open())
            throw runtime_error("file open failure");
    }

    void logAlphabet(vector<pair<char, int>> &alphabet) {
        for (auto it = alphabet.begin(); it != alphabet.end(); ++it) {
            file << "Symbol: " << it->first << " -> Weight:" << it->second << "\n";
        }
    }

    void logTree(node *tree, int level = 0) {
        if (tree) {
            logTree(tree->left, level + 1);
            for (int i = 0; i < level; i++) file << "   ";
            if (tree->ch == -1) {
                file << '<' << "\n";
            } else {
                file << tree->ch << "\n";
            }
            logTree(tree->right, level + 1);
        }
    }

    void logCode(vector<pair<char, string>> &code) {
        for (auto it = code.begin(); it != code.end(); ++it) {
            file << "Symbol: " << it->first << " -> Code:" << it->second << "\n";
        }
    }

//закрытие файла
    ~logger() {
        std::cout << "\nIntermeiate values write to file \"intermeiate.txt\"";
        file.close();
    }
};

static logger *log = new logger();

//функция для объединения двух узлов
node *cons(node *a, node *b) {
    node *c = new node();
    c->weight = a->weight + b->weight;
    c->ch = -1;
    if (a->weight > b->weight) {//узел у которого вес больше станет правым поддеревом
        c->right = a;
        c->left = b;
    } else {
        c->right = b;
        c->left = a;
    }
    return c;
}

//ввод текста для кодирования
void enter(string &str) {
    int type = 0;
    cout << "Enter from console -1\n";
    cout << "Enter from file -2\n";
    cin >> type;

    ifstream file;
    string name;
    string temp;

    switch (type) {
        case 1:
            std::cin.ignore(32767, '\n');
            getline(cin, str);
            break;
        case 2:
            cout << "Enter file name\n";
            cin >> name;
            file.open(name);
            if (file.is_open()) {
                while (file.good()) {
                    getline(file, temp);
                    str.append(temp);
                }
            } else cout << "Unable to open file";
            break;
        default:
            cout << "incorrect type\n";
    }

}

//формирование алфавит текста для кодирования
//считает вес символа
void formAlpabet(string const &str, vector<pair<char, int>> &alphabet) {

    bool flag = false;
    for (int i = 0; i < str.size(); ++i) {
        flag = false;
        for (auto it = begin(alphabet); it != end(alphabet); ++it) {
            if (str[i] == it->first) {
                flag = true;
                it->second++;
                break;
            }
        }
        if (flag) {
            continue;
        }
        alphabet.emplace_back(make_pair(str[i], 1));
    }
};

//  для сортировки алфавита
bool compair(pair<char, int> a1, pair<char, int> a2) {
    return a1.second > a2.second;
}

// для сортировки узлов дерева
bool compairNode(node *a1, node *a2) {
    return a1->weight > a2->weight;
}

//создает бинарное дерево из алфавита
node *makeBinaryTree(vector<pair<char, int>> alphabet) {
    vector<node *> tree;
    for (auto it = alphabet.begin(); it != alphabet.end(); ++it) {
        tree.push_back(new node(it->second, it->first));
    }
    sort(tree.begin(), tree.end(), compairNode);
    while (tree.size() != 1) {
        tree.push_back(cons(tree[tree.size() - 2], tree[tree.size() - 1]));
        sort(tree.begin(), tree.end(), compairNode);
        tree.pop_back();
        tree.pop_back();
    }

    return tree[0];
}

//формирует код символа из бинарного дерева
void makeCode(node *tree, char ch, string &code, bool &flag) {
    if (flag) {
        if (tree != nullptr) {
            if (tree->ch == ch) {
                flag = false;
                return;
            }
            code += "0";
            makeCode(tree->left, ch, code, flag);
            if (flag) {
                code.pop_back();
            } else { return; }
            code += "1";
            makeCode(tree->right, ch, code, flag);
            if (flag) {
                code.pop_back();
            }
        }
    }
}
//Основная функция кодирование в не входит
//формирование алфавита
//формирование бинарного дерева
//создание кодов символов из дерева
vector<pair<char, string>> coding(string &str) {
    vector<pair<char, int>> alphabet;
    vector<pair<char, string>> alphabetWithCode;
    formAlpabet(str, alphabet);
    log->logAlphabet(alphabet);
    sort(alphabet.begin(), alphabet.end(), compair);
    node *binaryTree = makeBinaryTree(alphabet);
    log->logTree(binaryTree);
    string code;
    bool flag = true;
    for (auto it = begin(alphabet); it != end(alphabet); ++it) {
        makeCode(binaryTree, it->first, code, flag);
        alphabetWithCode.emplace_back(make_pair(it->first, code));
        code = "";
        flag = true;
    }
    return alphabetWithCode;
}
//запись полученного текста
int write(string text, vector<pair<char, std::string>> code) {
    int type = 0;
    cout << "Print to console -1\n";
    cout << "Print to file -2\n";
    cin >> type;
    ofstream file;
    string nameF;
    unsigned int sizeHuffman = 0;
    unsigned int size = 8* text.size();
    switch (type) {
        case 1:
            for (auto ch = text.begin(); ch != text.end(); ++ch) {
                for (auto it = code.begin(); it != code.end(); ++it) {
                    if (it->first == *ch.base()) {
                        cout << it->second;
                        sizeHuffman += it->second.size();
                    }
                }
            }
            cout << "\nThe size of the text in bytes before encoding:" << size << "\n";
            cout << "The size of the text in bytes after encoding:" << sizeHuffman << "\n";
            break;
        case 2:
            cout << "Enter file name\n";
            cin >> nameF;
            file.open(nameF);
            if (file.is_open()) {
                for (auto ch = text.begin(); ch != text.end(); ++ch) {
                    for (auto it = code.begin(); it != code.end(); ++it) {
                        if (it->first == *ch.base()) {
                            file << it->second;
                            sizeHuffman += it->second.size();
                        }
                    }
                }
                file << "\nThe size of the text in bit before encoding:" << size << "\n";
                file << "The size of the text in bit after encoding:" << sizeHuffman << "\n";
            } else {
                cout << "file don't open\n";
            }
            break;
        default:
            cout << "error";
    }

    return 0;
}


int main() {
    string str;
    enter(str);
    vector<pair<char, string>> code = coding(str);
    log->logCode(code);
    write(str, code);
    delete log;
    return 0;
}

