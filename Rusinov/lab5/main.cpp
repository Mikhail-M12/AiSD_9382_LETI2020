#include <fstream>
#include "iostream"

#define BLACK true
#define RED false

template<typename Elem>
struct Node {
    Elem data{};
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    bool color{};
};

template<typename Elem>
std::ostream& operator<<(std::ostream& out, Node<Elem> node) {
    std::cout << "(" << node.data << ", " << node.color << ", ";
    if (!node.left) std::cout << "#, ";
    else std::cout << "*, ";

    if (!node.right) std::cout << "#, ";
    else std::cout << "*, ";

    if (!node.parent) std::cout << "#)";
    else std::cout << "*)";
    return out;
}

std::string generateFormatPrint(int count) {
    auto string = std::string();
    for (int i = 0; i < count; ++i) string += ".";
    return string;
}

template<typename Elem>
class RBTree {
    Node<Elem>* root;

    Node<Elem>* grandparent(Node<Elem>* n) { // дедушка
        if ((n != nullptr) && (n->parent != nullptr)) return n->parent->parent;
        return nullptr;
    }

    Node<Elem>* uncle(Node<Elem>* n) { // дядя
        Node<Elem> *g = grandparent(n);
        if (g == nullptr) return nullptr;
        if (n->parent == g->left) return g->right;
        return g->left;
    }

    void restoreRoot(Node<Elem>* n) { // восстановление корня
        while (n->parent) n = n->parent;
        root = n;
    }

    /*
     * Функция левого поворота
     *        n                   y
     *       / \                 / \
     *      T1  y     --->      n  T3
     *         / \             / \
     *        T2 T3           T1 T2
     *
     * В правую ветку N подставляется левая ветка Y
     * В левую ветку Y подставляется N
     *
     */

    void leftRotate(Node<Elem>* n) {
        Node<Elem>* y = n->right;

        y->parent = n->parent; /* при этом, возможно, y становится корнем дерева */
        if (n->parent != nullptr) {
            if (n->parent->left == n)
                n->parent->left = y;
            else
                n->parent->right = y;
        }

        n->right = y->left;
        if (y->left != nullptr)
            y->left->parent = n;

        n->parent = y;
        y->left = n;
    }

    /*
     * Функция правого поворота
     *          n                        y
     *         / \                      / \
     *        y  T3       --->         T1  n
     *       / \                          / \
     *      T1 T2                        T2 T3
     *
     * В левую ветку N подставляется правая ветка Y
     * В правую ветку Y подставляется N
     *
     */

    void rightRotate(Node<Elem>* n) {
        Node<Elem>* y = n->left;

        y->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
        if (n->parent != nullptr) {
            if (n->parent->left==n)
                n->parent->left = y;
            else
                n->parent->right = y;
        }

        n->left = y->right;
        if (y->right != nullptr)
            y->right->parent = n;

        n->parent = y;
        y->right = n;
    }

    // Поиск элемента + подсчитывание количества заданного элемента
    int find(Elem const& data, Node<Elem>* node, int count = 0) {
        auto format = generateFormatPrint(count);
        if (!node) { // Если Node пустой, то элементов 0
            std::cout << format << "Ветвь пустая, возвращаю 0" << std::endl;
            return 0;
        }
        // Если node->data > data, то нужно пойти в левую ветку
        if (data < node->data) {
            std::cout << format << data << " < " << *node << ". Вызов поиска для левой ветви" << std::endl;
            int result = find(data, node->left, count+1);
            std::cout << format << ". Получено значение от левой ветви - " << result << std::endl;
            return result;
        }
        // Если node->data < data, то нужно пойти в правую ветку
        else if (data > node->data) {
            std::cout << format << data << " > " << *node << ". Вызов поиска для правой ветви" << std::endl;
            int result = find(data, node->right, count+1);
            std::cout << format << ". Получено значение от правой ветви - " << result << std::endl;
            return result;
        }
        // Если node->data == data, то элемент найден и нужно посетить left и right
        else {
            std::cout << format << data << " == " << *node << std::endl;
            std::cout << format << "Вызов поиска для правой ветви" << std::endl;
            int rightResult = find(data, node->right, count+1);
            std::cout << format << "Получено значение от правой ветви - " << rightResult << std::endl;

            std::cout << format << "Вызов поиска для левой летви" << std::endl;
            int leftResult = find(data, node->left, count+1);
            std::cout << format << "Получено значение от левой ветви - " << leftResult << std::endl;
            return leftResult + rightResult + 1;
        }
    }

    // случай, когда нет корня
    void insertCase1(Node<Elem>* n) {
        std::cout << "[CASE 1] ";

        if (n->parent == nullptr) {
            n->color = BLACK;
            std::cout << *n << " - не имеет отца, поэтому стал корнем дерева" << std::endl;
        } else {
            std::cout << *n << " - имеет отца, переход к следующему случаю" << std::endl;
            insertCase2(n);
        }
    }

    // cлучай, когда отец черный
    void insertCase2(Node<Elem>* n) {
        std::cout << "[CASE 2] ";
        if (n->parent->color == BLACK) {
            std::cout << "Отец " << *n->parent << " является черным, свойство 3 не нарушено" << std::endl;
            return;
        } else {
            std::cout << "Отец " << *n->parent << " является красным, свойство 3 нарушено" << std::endl;
            insertCase3(n);
        }

    }

    // случай, когда отец красный и есть красный дядя
    void insertCase3(Node<Elem>* n) {
        std::cout << "[CASE 3] ";
        Node<Elem>* u = uncle(n), *g;

        if ((u != nullptr) && (u->color == RED)) {
            // && (n->parent->color == RED) Второе условие проверяется в insertCase2, то есть родитель уже является красным.
            std::cout << "У " << *n << " есть дядя - " << *u << " и он красный" << std::endl;
            n->parent->color = BLACK;
            u->color = BLACK;
            g = grandparent(n);
            g->color = RED;
            std::cout << "[CASE 3] Отец стал черным, дядя стал черным, дедушка стал красным. Повтор балансировки для дедушки" << std::endl;
            insertCase1(g);
        } else {
            std::cout << "У " << *n << " нет дяди или дядя не красный" << std::endl;
            insertCase4(n);
        }
    }

    // случай, когда нет красного дяди
    void insertCase4(Node<Elem>* n) {
        Node<Elem>* g = grandparent(n);
        std::cout << "[CASE 4] Дедушка " << *n << " - " << *g << std::endl;

        // n правый сын и отец левый сын
        if ((n == n->parent->right) && (n->parent == g->left)) {
            std::cout << "[CASE 4] " << *n << " является правым сыном отца " << *n->parent << ", и отец является левым сыном" << std::endl;
            std::cout << "[CASE 4] " << "Левый поворот отца" << std::endl;
            leftRotate(n->parent);
            n = n->left;
        // n левый сын и отец правый сын
        } else if ((n == n->parent->left) && (n->parent == g->right)) {
            std::cout << "[CASE 4] " << *n << " является левым сыном отца " << *n->parent << ", и отец является правым сыном" << std::endl;
            std::cout << "[CASE 4] " << "Правый поворот отца" << std::endl;
            rightRotate(n->parent);
            n = n->right;
        } else {
            std::cout << "[CASE 4] " << "Ни один из вариантов для случая 4 не выполнен для " << *n << std::endl;
        }
        std::cout << "[CASE 4] Переход к случаю 5" << std::endl;
        insertCase5(n);
    }

    // продолжение случая 4
    void insertCase5(Node<Elem>* n)
    {
        Node<Elem>* g = grandparent(n);
        n->parent->color = BLACK;
        g->color = RED;
        std::cout << "[CASE 5] Отец стал черным, дедушка стал красным" << std::endl;
        // n левый сын и отец левый сын
        if ((n == n->parent->left) && (n->parent == g->left)) {
            std::cout << "[CASE 5] " << *n << " является левым сыном отца " << *n->parent << ", и отец является левым сыном" << std::endl;
            std::cout << "[CASE 5] " << "Правый поворот дедушки" << std::endl;
            rightRotate(g);
        } else { // n правый сын и отец правый сын
            std::cout << "[CASE 5] " << *n << " является правым сыном отца " << *n->parent << ", и отец является правым сыном" << std::endl;
            std::cout << "[CASE 5] " << "Левый поворот дедушки" << std::endl;
            leftRotate(g);
        }
    }

public:
    RBTree() : root(nullptr) {}
    ~RBTree() { delete root; }

    Node<Elem>* getRoot() { return root; }

    int count(Elem const& data) { return find(data, root); }

    void insert(Elem stuff) { // Вставка элемента
        auto newNode = new Node<Elem>();
        newNode->data = stuff;
        newNode->color = RED;
        std::cout << "---Вставка элемента---" << std::endl;

        auto linker = root;

        // если node < linker, то идем в левую ветку
        // если node >= linker, то идем в правую ветку
        // когда нет след ветки, то вставляем туда элемент
        while (linker) {
            if (newNode->data < linker->data) {
                std::cout << *newNode << " < " << *linker << ", переход к левой ветке" << std::endl;
                if (!linker->left) {
                    linker->left = newNode;
                    newNode->parent = linker;
                    std::cout << "Левая ветка пустая. ";
                    break;
                } else linker = linker->left;
            } else {
                std::cout << *newNode << " >= " << *linker << ", переход к правой ветке" << std::endl;
                if (!linker->right) {
                    linker->right = newNode;
                    newNode->parent = linker;
                    std::cout << "Правая ветка пустая. ";
                    break;
                } else linker = linker->right;
            }
        }
        std::cout << "Элемент " << *newNode << " вставлен" << std::endl;
        std::cout << "-----Балансировка-----" << std::endl;
        insertCase1(newNode);
        restoreRoot(newNode);
        std::cout << "\n";
    }
};


void printTree(Node<int>* tree, int level) // печать дерева
{
    if(tree)
    {
        printTree(tree->right, level + 1);
        for (int i = 0; i < level; ++i) std::cout << "   ";
        std::cout << tree->color << std::endl;
        printTree(tree->left, level + 1);

    }
}


RBTree<int>* insert(int file = 0) {
    int N;
    RBTree<int>* tree;

    std::cout << "---Построение структуры данных начато---" << "\n\n";

    if (!file) {
        std::cout << "Введите кол-во элементов: ";
        std::cin >> N; // получаем кол-во элементов
        if (N <= 0) {
            if (N < 0) {
                std::cout << "Кол-во элементов должно быть >= 0" << std::endl;
                return nullptr;
            }
            else new RBTree<int>;
        }
        tree = new RBTree<int>;
        for (int i = 0; i < N; ++i) { // считываем N элементов
            int k;
            std::cout << "[" << i+1 << "] " << "Введите число: ";
            std::cin >> k;
            tree->insert(k); // Добавляем в список
        }
    } else {
        std::ifstream input("file.txt"); // открываем файл
        if (!input.is_open()) { // проверяем на доступность
            input.close();
            std::cout << "Не удалось открыть файл file.txt" << std::endl;
            return nullptr;
        }
        else {
            if(!(input >> N)) { // считываем N
                std::cout << "Не удалось считать кол-во элементов" << std::endl;
                return nullptr;
            }

            if (N <= 0) {
                if (N < 0) {
                    std::cout << "Кол-во элементов должно быть >= 0" << std::endl;
                    return nullptr;
                }
                else new RBTree<int>;
            }

            tree = new RBTree<int>;
            for (int i = 0; i < N; ++i) { // Считываем N элементов
                int k;
                if(!(input >> k)) { // проверяем, получилось ли считать
                    std::cout << "Задано " << N << " элементов, но было введено меньше " << N << std::endl;
                    delete tree;
                    return nullptr; // если не удалось, вызываем деструктор списка
                }
                else tree->insert(k); // добавляем элемент
            }
        }
    }
    std::cout << "---Построение структуры данных завершено---" << "\n\n";
    return tree;
}

char executeTask(RBTree<int>* tree) {
    int e;
    std::cout << "Введите элемент, который хотите найти в дереве: ";
    std::cin >> e;
    std::cout << "---Подсчет количества элементов со значением '" << e << "'" << " начат---" << std::endl;
    int count = tree->count(e);
    std::cout << "Результат подсчета: " << count << std::endl;
    std::cout << "---Подсчет количества элементов окончен---" << "\n\n";

    char next;
    std::cout << "Если хотите продолжить, введите '+': ";
    std::cin >> next;
    return next;
}

int main()
{
    int file;
    std::cout << "Если хотите строить дерево в live-режиме, введите 0\n";
    std::cout << "Иначе любое другое число\n";
    std::cout << "Ввод: ";
    std::cin >> file;

    RBTree<int>* tree = insert(file);
    if (!tree) return 0;

    char flag = '+';
    while (flag == '+') flag = executeTask(tree);

    std::cout << "---Представление дерева---" << std::endl;
    std::cout << "0 - КРАСНЫЙ" << std::endl;
    std::cout << "1 - ЧЕРНЫЙ" << std::endl;
    printTree(tree->getRoot(), 0);

    return 0;
} 