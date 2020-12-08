#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <memory>
#include <fstream>

int depth = 0;

struct Node {
    std::string value_;
    std::unique_ptr<Node> left_;
    std::unique_ptr<Node> right_;

    explicit Node(const std::string &value) {
        value_ = value;
    }

    Node(const std::string &value, std::unique_ptr<Node> &left, std::unique_ptr<Node> &right) {
        value_ = value;
        left_ = std::move(left);
        right_ = std::move(right);
    }

    void createLeft(const std::string &value) {
        if (left_ != nullptr)
            throw std::runtime_error("Левое поддерево не пусто");
        left_ = std::make_unique<Node>(value);
    }

    void createRight(const std::string &value) {
        if (right_ != nullptr)
            throw std::runtime_error("Правое поддерево не пусто");
        right_ = std::make_unique<Node>(value);
    }

    void addChild(std::string &value) {
        if (left_ == nullptr)
            createLeft(value);
        else if (right_ == nullptr)
            createRight(value);
        else
            throw std::runtime_error("Некуда добавить потомка");
    }

    void addChild(std::unique_ptr<Node> &child) {
        if (left_ == nullptr)
            left_ = std::move(child);
        else if (right_ == nullptr)
            right_ = std::move(child);
        else
            throw std::runtime_error("Некуда добавить потомка");
    }
};

//Функция проверяет является ли строка числом
bool isNumber(std::string &s) {
    for (auto &i: s)
        if (!isdigit(i))
            return false;
    return true;
}

bool isOperator(std::string &op) {
    if ((op == "+") || (op == "-") || (op == "*") || (op == "/"))
        return true;
    return false;
}

bool isVar(std::string &op) {
    if (isOperator(op) || op == "(" || op == ")")
        return false;
    if (!isNumber(op) && !isalpha(op.at(0)))
        return false;
    return true;
}

//Разбиение выражение на подстроки
template<typename StreamT>
std::vector<std::string> getToken(StreamT &stream) {
    std::vector<std::string> result;
    std::string temp;
    char symbol = 0;
    std::string line;
    std::getline(stream, line);
    line.push_back('\n');
    std::istringstream str(line);
    str >> std::noskipws;
    while (symbol != '\n') {
        str >> symbol;
        if ((symbol == ' ') || ((symbol == '\n'))) {
            if (!temp.empty())
                result.push_back(temp);
            temp.clear();
        }
        if ((symbol == '(') || (symbol == ')')) {
            if (!temp.empty())
                result.push_back(temp);
            temp.clear();
            temp.push_back(symbol);
            result.push_back(temp);
            temp.clear();
        }
        if ((symbol != '(') && (symbol != ')') && (symbol != ' ') && (symbol != '\n'))
            temp.push_back(symbol);
    }
    return result;
}

//Считывание оператора
template<typename IterT>
void readOperator(IterT &first, const IterT &last, std::unique_ptr<Node> &parent);

//Считывание аргументов оператора
template<typename IterT>
void readArgument(IterT &first, const IterT &last, std::unique_ptr<Node> &parent) {
    if (first < last)
        throw std::runtime_error("Неверный формат входных данных");
    if (isVar(*first))
        if (parent == nullptr)
            parent = std::make_unique<Node>(*first);
        else
            parent->addChild(*first);
    else if (isOperator(*first))
        readOperator(first, last, parent);
    else
        throw std::runtime_error("Неверный формат входных данных");
}

template<typename IterT>
void readOperator(IterT &first, const IterT &last, std::unique_ptr<Node> &parent) {
    if (first < last)
        throw std::runtime_error("Неверный формат входных данных");
    if (!isOperator(*first))
        throw std::runtime_error("Неверный формат входных данных");
    if (parent == nullptr) {
        parent = std::make_unique<Node>(*first);
        readArgument(--first, last, parent);
        readArgument(--first, last, parent);
    } else {
        std::unique_ptr<Node> child = std::make_unique<Node>(*first);
        readArgument(--first, last, child);
        readArgument(--first, last, child);
        parent->addChild(child);
    }
}

//Считывание корня
template<typename IterT>
void readSentence(IterT &first, const IterT &last, std::unique_ptr<Node> &parent) {
    if (first < last)
        throw std::runtime_error("Неверный формат входных данных");
    if (isOperator(*first))
        readOperator(first, last, parent);
    else
        readArgument(first, last, parent);
    if (first != last)
        throw std::runtime_error("Неверный формат входных данных");
}


//Функции считывания дерева в скобочном представлении
template<typename IterT>
void readTOperator(IterT &first, const IterT &last, std::unique_ptr<Node> &parent);

template<typename IterT>
void readTLComma(IterT &first, const IterT &last, std::unique_ptr<Node> &parent) {
    if (first >= last)
        throw std::runtime_error("Неверный формат входных данных");
    if (*first != ")") {
        throw std::runtime_error("Неверный формат входных данных");
    }
}

template<typename IterT>
void readTArgument(IterT &first, const IterT &last, std::unique_ptr<Node> &parent) {
    if (first >= last)
        throw std::runtime_error("Неверный формат входных данных");
    if (*first != "(") {
        throw std::runtime_error("Неверный формат входных данных");
    }
    if (isVar(*(++first)))
        if (parent == nullptr)
            parent = std::make_unique<Node>(*first);
        else
            parent->addChild(*first);
    else if (isOperator(*first))
        readTOperator(first, last, parent);
    readTLComma(++first, last, parent);
}

template<typename IterT>
void readTOperator(IterT &first, const IterT &last, std::unique_ptr<Node> &parent) {
    if (first >= last)
        throw std::runtime_error("Неверный формат входных данных");
    if (!isOperator(*first)) {
        throw std::runtime_error("Неверный формат входных данных");
    }
    if (parent == nullptr) {
        parent = std::make_unique<Node>(*first);
        readTArgument(++first, last, parent);
        readTArgument(++first, last, parent);
    } else {
        std::unique_ptr<Node> child = std::make_unique<Node>(*first);
        readTArgument(++first, last, child);
        readTArgument(++first, last, child);
        parent->addChild(child);
    }
}

//Преобразование дерева в формулу
void TreeToSentence(const std::unique_ptr<Node> &head, std::vector<std::string> &Tokens) {
    if (head == nullptr)
        return;
    Tokens.push_back(head->value_);
    TreeToSentence(head->left_, Tokens);
    TreeToSentence(head->right_, Tokens);
}

//вывод выражения на экран в обратном порядке
void printSentenceReverse(std::vector<std::string> &Tokens) {
    for (auto i = Tokens.end() - 1; i >= Tokens.begin(); i--)
        if (i->size() != 1 && i->at(0) == '-')
            std::cout << "\"0 " << *i << "\" ";
        else
            std::cout << *i << " ";
}
//вывод дерева на экран
void printTree(const std::unique_ptr<Node> &head) {
    depth++;
    if (head == nullptr)
        return;
    std::string s(depth, '  ');
    if (head->value_.size() != 1 && head->value_.at(0) == '-')
        std::cout << s << "\"0" << head->value_ << "\"" << std::endl;
    else
        std::cout << s << head->value_ << std::endl;
    printTree(head->left_);
    depth--;
    printTree(head->right_);
    depth--;
}

//Функция проверяет является ли строка цифрой
bool isDigit(const std::string &s) {
    if (s.size() == 1 && isdigit(s.at(0)))
        return true;
    return false;
}

bool subst(std::unique_ptr<Node> &head) {
    if (head == nullptr)
        return false;
    if (head->value_ == "-")
        if (isDigit(head->left_->value_) && isDigit(head->right_->value_)) {
            int d = std::stoi(head->right_->value_) - std::stoi(head->left_->value_);

            std::cout << "Совершено действие: " << head->right_->value_ << " " << head->value_ << " "
                      << head->left_->value_<< " ="<< d << std::endl;
            head->value_ = std::to_string(d);
            head->left_ = nullptr;
            head->right_ = nullptr;
            return true;
        }
    return subst(head->left_) || subst(head->right_);
}

int main() {
    std::unique_ptr<Node> head;
    std::vector<std::string> Tokens;
    std::vector<std::string> result; // итоговое выражение
    int readFormat;
    try {
        while (1) {
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
                        Tokens = getToken(in);
                    } else
                        throw std::runtime_error("Файл не найден!");
                    in.close();
                    break;
                }
                case 1: {
                    std::cout << "Введите выражение в постфиксной форме. Например : a b + c * d e f g * + / -"
                              << std::endl;
                    Tokens = getToken(std::cin);
                    break;
                }
                default:
                    throw std::runtime_error("Неверное действие");
            }

            if (Tokens.empty())
                throw std::runtime_error("Пустое выражение!");
            auto end = Tokens.begin(), beg = Tokens.end() - 1;
            readSentence(beg, end, head);

            int action;
            std::cout << " 1 - вывести дерево, \n"
                         " 2 - вывести формулу,\n"
                         " 3 - заменить все разности с константами,\n"
                         " 0 - выход" << std::endl;
            while ((std::cin >> action) && (action != 0)) {
                switch (action) {
                    case 1: {
                        std::cout<<"Вывод дерева"<<std::endl;
                        printTree(head);
                        depth = 0;
                        break;
                    }
                    case 2: {

                        std::cout<<"Вывод выражения"<<std::endl;
                        result.clear();
                        TreeToSentence(head, result);
                        printSentenceReverse(result);
                        break;
                    }
                    case 3: {
                        std::cout<<"Замена операций вычитания"<<std::endl;
                        while (subst(head));
                        break;
                    }
                    case 0: {
                        break;
                    }
                    default:
                        std::cout << "Выбрано неверное действие" << std::endl;
                        break;
                }
            }
            int temp;
            std::cout << "Для повторного ввода нажмите 1, для выхода - любую другую клавишу" << std::endl;
            std::cin >> temp;
            std::cin.ignore();
            if (temp != 1)
                break;
            head.reset();
            result.clear();

        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
