#include <iostream>
#include <string>
#include "fstream"

template<typename type>
class Node;

template<typename type>
class NodeOperations;


template<typename type>
class Node {
    friend NodeOperations<type>;
    friend void printTree(Node<type>* tree, int level);
    type value;
    Node* left = nullptr;
    Node* right = nullptr;

public:
    explicit Node(char value = 0) : value(value) {}
    ~Node() {
        delete left;
        delete right;
    }
    void addLeftNode(Node* node) {
        delete left;
        left = node;
    }
    void addRightNode(Node* node) {
        delete right;
        right = node;
    }
};


template<typename type>
class NodeOperations {
    Node<type>* firstNode = nullptr;
    Node<type>* secondNode = nullptr;

public:
    NodeOperations(Node<type>* firstNode, Node<type>* secondNode)
            : firstNode(firstNode), secondNode(secondNode) {}

    bool areSimilar(){ // Метод проверки подобности
        if (firstNode == nullptr && secondNode == nullptr) return true;
        if (firstNode == nullptr || secondNode == nullptr) return false;
        return NodeOperations(firstNode->left, secondNode->left).areSimilar()
               && NodeOperations(firstNode->right, secondNode->right).areSimilar();
    }

    bool areEqual(){ // Метод проверки равности
        if (firstNode == nullptr && secondNode == nullptr) return true;
        if (firstNode == nullptr || secondNode == nullptr) return false;
        if (firstNode->value != secondNode->value) return false;
        return NodeOperations(firstNode->left, secondNode->left).areEqual()
               && NodeOperations(firstNode->right, secondNode->right).areEqual();
    }

    bool areMirroredSimilar(){ // Метод проверки зеркальной подобности
        if (firstNode == nullptr && secondNode == nullptr) return true;
        if (firstNode == nullptr || secondNode == nullptr) return false;
        return NodeOperations(firstNode->left, secondNode->right).areMirroredSimilar()
               && NodeOperations(firstNode->right, secondNode->left).areMirroredSimilar();
    }

    bool areMirroredEqual(){ // Метод проверки симметричности
        if (firstNode == nullptr && secondNode == nullptr) return true;
        if (firstNode == nullptr || secondNode == nullptr) return false;
        if (firstNode->value != secondNode->value) return false;
        return NodeOperations(firstNode->left, secondNode->right).areMirroredEqual()
               && NodeOperations(firstNode->right, secondNode->left).areMirroredEqual();
    }
};


class TreeCreator { // Класс для создания деревьев
    static bool isAlphabetSymbol(char symbol){ // Метод для проверки, является ли символ алфавитным нижнего регистра
        if (97 <= symbol && symbol <= 122) return true;
        return false;
    }

    static std::string indexFormatGenerator(const int* index) { // Метод для генерации форматного вывода
        return std::string("[") + std::to_string(*index) + std::string("] ");
    }

    static Node<char>* createTree(const std::string& string, int* index = nullptr) { // Рекурсивный метод создания дерева
        if (!index) { // Начальный вызов метода
            int startIndex = 0;
            index = &startIndex;
        }

        if (isAlphabetSymbol(string[*index]) || string[*index] == '/') { // Если символ алфавитный, создаем узел без ветвей
            std::cout << indexFormatGenerator(index) << "Встречен символ - " << string[*index] << std::endl;
            if (isAlphabetSymbol(string[*index])) return new Node<char>(string[*index]);
            // если символ /, значит возвращаем нулевой указатель
            return nullptr;
        }

        else if (string[*index] == '(') { // встречено дерево
            std::cout << indexFormatGenerator(index) << "Встречено дерево" << std::endl;
            *index += 1;
            if (!isAlphabetSymbol(string[*index])) { // проверяем корень
                std::cout << indexFormatGenerator(index) << "Встречен корень - " << string[*index] << ", данный символ некорректен!" << std::endl;
                throw std::invalid_argument(indexFormatGenerator(index) + "Found root - " + string[*index] + ", this symbol is incorrect!");
            }

            auto* node = new Node<char>(string[*index]); // создание корня
            *index += 1;

            std::cout << "Начато создание левой ветви" << std::endl;
            Node<char>* leftBranch = createTree(string, index); // создание левой ветви
            node->addLeftNode(leftBranch);
            *index += 1;
            std::cout << "Завершено создание левой ветви" << std::endl;

            std::cout << "Начато создание правой ветви" << std::endl;
            Node<char>* rightBranch = createTree(string, index); // создание правой ветви
            node->addRightNode(rightBranch);
            *index += 1;
            std::cout << "Завершено создание левой ветви" << std::endl;

            if (string[*index] != ')') { // проверка терминального символа
                std::cout << indexFormatGenerator(index) << "Не найден терминальный символ ')'" << std::endl;
                throw std::invalid_argument(indexFormatGenerator(index) + "Did not find the terminal symbol ')'");
            }

            std::cout << indexFormatGenerator(index) << "Найден терминальный символ ')'" << std::endl;

            return node;

        } else {
            std::cout << indexFormatGenerator(index) << "Встречен некорректный символ!" << std::endl;
            throw std::invalid_argument(indexFormatGenerator(index) + std::string("Incorrect symbol") + string[*index]);
        }
    }
public:
    static Node<char>** createTreesFromFile() { // создание деревьев из файла
        std::cout << "------Считывание деревьев из файла------" << std::endl;
        std::fstream treesFile("file.txt");
        if (!treesFile.is_open()) { // проверим, получилось ли открыть файл
            std::cout << "Не удалось открыть файл file.txt" << std::endl;
            throw std::invalid_argument("Can not to open file.txt");
        }

        std::string firstTree;
        std::string secondTree;
        std::getline(treesFile, firstTree, '\n');
        std::getline(treesFile, secondTree, '\n');
        treesFile.close();
        return createTrees(firstTree, secondTree);
    }

    static Node<char>** createTreesFromConsole() { // создание дерева из консоли
        std::cout << "------Считывание деревьев из консоли------" << std::endl;
        std::cout << "Введите первое дерево - ";
        std::string first;
        std::cin >> first;
        std::cout << "Введите второе дерево - ";
        std::string second;
        std::cin >> second;
        return createTrees(first, second);
    }

    static Node<char>** createTrees(const std::string& first, const std::string& second) {
        auto** treeArray = new Node<char>*[2];
        std::cout << "---Считывание первого дерева---" << std::endl;
        treeArray[0] = createTree(first); // создаем первое дерево
        std::cout << "---Считывание второго дерева---" << std::endl;
        treeArray[1] = createTree(second); // создаем второе дерево
        return treeArray; // возвращаем массив из двух деревьев
    }
};


// Функция печати дерева
void printTree(Node<char>* tree, int level)
{
    if(tree)
    {
        printTree(tree->left, level + 1);
        for (int i = 0; i < level; ++i) std::cout << "   ";
        std::cout << tree->value << std::endl;
        printTree(tree->right, level + 1);
    }
}


class Exercise { // класс задания
    Node<char>** treeArray = nullptr;
public:
    explicit Exercise(Node<char>** treeArray) : treeArray(treeArray) {}
    ~Exercise(){
        delete treeArray[0];
        delete treeArray[1];
        delete [] treeArray;
    }
    void executeTask() { // метод для выполнения задания
        std::cout << "---Вывод первого дерева---" << std::endl;
        printTree(treeArray[0], 0);
        std::cout << "---Конец вывода первого дерева---" << std::endl;

        std::cout << "---Вывод второго дерева---" << std::endl;
        printTree(treeArray[1], 0);
        std::cout << "---Конец вывода второго дерева---" << std::endl;

        std::cout << "---Выполнение задания---" << std::endl;
        NodeOperations<char> operations(treeArray[0], treeArray[1]);
        if (operations.areSimilar()) std::cout << "Заданные деревья подобны" << std::endl;
        else std::cout << "Заданные деревья не подобны" << std::endl;

        if (operations.areEqual()) std::cout << "Заданные деревья равны" << std::endl;
        else std::cout << "Заданные деревья не равны" << std::endl;

        if (operations.areMirroredSimilar()) std::cout << "Заданные деревья зеркально подобны" << std::endl;
        else std::cout << "Заданные деревья не подобны зеркально" << std::endl;

        if (operations.areMirroredEqual()) std::cout << "Заданные деревья симметричны" << std::endl;
        else std::cout << "Заданные деревья несимметричны" << std::endl;
        std::cout << "---Конец---" << std::endl;
    }
};


int main() {
    int value = 0;
    std::cout << "0 - ввод из консоли, 1 - ввод из файла file.txt" << std::endl;
    std::cout << "Введите значение: ";
    std::cin >> value;
    if (value) {
        Exercise(TreeCreator::createTreesFromFile()).executeTask();
    } else {
        Exercise(TreeCreator::createTreesFromConsole()).executeTask();
    }
    return 0;
}
