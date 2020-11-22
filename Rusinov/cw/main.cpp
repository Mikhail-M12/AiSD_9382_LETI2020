#include "iostream"
#include "vector"
#include "algorithm"

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

void printTree(Node<int>* tree, int level, std::vector<Node<int>*> specialNodes) // печать дерева
{
    if(tree)
    {
        std::vector<Node<int>*>::iterator it;
        it = std::find(specialNodes.begin(), specialNodes.end(), tree);
        printTree(tree->right, level + 1, specialNodes);

        for (int i = 0; i < level; ++i) std::cout << "   ";
        if (it != specialNodes.end()) std::cout << "\x1b[38m" << tree->data << "\x1b[0m" << std::endl;
        else if (tree->color == BLACK) std::cout << "\x1b[30m" << tree->data << "\x1b[0m" << std::endl;
        else std::cout << "\x1b[31m" << tree->data << "\x1b[0m" << std::endl;
        printTree(tree->left, level + 1, specialNodes);

    }
}

void waitNextStep() {
    char s;
    std::cout << "Введите любой символ, чтобы продолжить выполнение: ";
    std::cin >> s;
    system("clear");
}

template<typename Elem>
class RBTree {
    Node<Elem>* root;

    Node<Elem>* getGrandparent(Node<Elem>* n) { // дедушка
        if ((n != nullptr) && (n->parent != nullptr)) return n->parent->parent;
        return nullptr;
    }

    Node<Elem>* getUncle(Node<Elem>* n) { // дядя
        Node<Elem> *g = getGrandparent(n);
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
        restoreRoot(n);
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
        restoreRoot(n);
    }

    // случай, когда нет корня
    void insertCase1(Node<Elem>* n) {



        waitNextStep();
        std::cout << "------Балансировка------" << std::endl;
        std::vector<Node<Elem>*> specialNodes {};
        specialNodes.push_back(n);
        printTree(root, 0, specialNodes);
        std::cout << "[СЛУЧАЙ 1] Проверяется, есть ли родитель у вставленного элемента" << std::endl;

        waitNextStep();
        if (n->parent == nullptr) {
            specialNodes.clear();
            std::cout << "------Балансировка------" << std::endl;
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 1] У данного элемента нет родителя, поэтому он становится корнем!" << std::endl;
            n->color = BLACK;
        } else {
            specialNodes.clear();
            specialNodes.push_back(n->parent);
            std::cout << "------Балансировка------" << std::endl;
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 1] У данного элемента есть родитель (выделен)!" << std::endl;
            insertCase2(n);
        }
    }

    // cлучай, когда отец черный
    void insertCase2(Node<Elem>* n) {
        waitNextStep();
        std::cout << "------Балансировка------" << std::endl;
        std::vector<Node<Elem>*> specialNodes {};
        specialNodes.push_back(n);
        printTree(root, 0, specialNodes);
        std::cout << "[СЛУЧАЙ 2] Проверяется, является ли родитель рассматриваемого элемента черным" << std::endl;

        waitNextStep();
        specialNodes.clear();
        if (n->parent->color == BLACK) {
            std::cout << "------Балансировка------" << std::endl;
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 2] Рассматриваемый элемент красный, родитель черный, свойство не нарушено!" << std::endl;
            return;
        } else {
            std::cout << "------Балансировка------" << std::endl;
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 2] Рассматриваемый элемент красный, родитель красный, свойство нарушено!" << std::endl;
            insertCase3(n);
        }

    }

    // случай, когда отец красный и есть красный дядя
    void insertCase3(Node<Elem>* n) {

        waitNextStep();
        std::cout << "------Балансировка------" << std::endl;
        std::vector<Node<Elem>*> specialNodes {};
        specialNodes.push_back(n);
        printTree(root, 0, specialNodes);
        std::cout << "[СЛУЧАЙ 3] Проверяется, есть ли красный дядя у выделенного элемента" << std::endl;

        Node<Elem>* u = getUncle(n), *g;
        waitNextStep();
        specialNodes.clear();
        if ((u != nullptr) && (u->color == RED)) {
            // && (n->parent->color == RED) Второе условие проверяется в insertCase2, то есть родитель уже является красным.

            std::cout << "------Балансировка------" << std::endl;
            specialNodes.push_back(n->parent);
            specialNodes.push_back(u);
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 3] У рассматриваемого элемента есть красный отец и красный дядя" << std::endl;
            std::cout << "В этом случае отец становится черным, дядя становится черным, дедушка красным" << std::endl;
            std::cout << "И операция балансировки повторяется для дедушки" << std::endl;

            n->parent->color = BLACK;
            u->color = BLACK;
            g = getGrandparent(n);
            g->color = RED;
            insertCase1(g);
        } else {
            specialNodes.push_back(n);
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 3] У рассматриваемого элемента нет красного дяди" << std::endl;
            insertCase4(n);
        }
    }

    // случай, когда нет красного дяди
    void insertCase4(Node<Elem>* n) {
        Node<Elem>* g = getGrandparent(n);

        waitNextStep();
        std::cout << "------Балансировка------" << std::endl;
        std::vector<Node<Elem>*> specialNodes {};

        specialNodes.push_back(n);
        specialNodes.push_back(n->parent);

        printTree(root, 0, specialNodes);
        std::cout << "[СЛУЧАЙ 4] Проверяется, является ли рассматриваемый элемент правым сыном" << std::endl;
        std::cout << "[СЛУЧАЙ 4] И является ли его отец левым сыном" << std::endl;
        std::cout << "[СЛУЧАЙ 4] (ИЛИ рассматриваемый левый, а его отец правый)" << std::endl;
        std::cout << "Рассматриваемый элемент и его отец выделены" << std::endl;


        waitNextStep();
        // n правый сын и отец левый сын
        if ((n == n->parent->right) && (n->parent == g->left)) {

            std::cout << "------Балансировка------" << std::endl;
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 4] Рассматриваемый элемент - правый сын, его отец - левый сын" << std::endl;
            std::cout << "[СЛУЧАЙ 4] В таком случае необходимо выполнить левый поворот отца рассматриваемого элемента" << std::endl;
            leftRotate(n->parent);

            waitNextStep();
            specialNodes.clear();
            n = n->left;
            specialNodes.push_back(n);
            std::cout << "------Балансировка------" << std::endl;
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 4] Был выполнен левый поворот, рассматриваемый элемент выделен" << std::endl;

            // n левый сын и отец правый сын
        } else if ((n == n->parent->left) && (n->parent == g->right)) {
            std::cout << "------Балансировка------" << std::endl;
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 4] Рассматриваемый элемент - левый сын, его отец - правый сын" << std::endl;
            std::cout << "[СЛУЧАЙ 4] В таком случае необходимо выполнить правый поворот отца рассматриваемого элемента" << std::endl;

            rightRotate(n->parent);


            waitNextStep();
            specialNodes.clear();
            n = n->right;
            specialNodes.push_back(n);
            std::cout << "------Балансировка------" << std::endl;
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 4] Был выполнен правый поворот, рассматриваемый элемент выделен" << std::endl;
        } else {
            std::cout << "------Балансировка------" << std::endl;
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 4] Заданные требования не выполнены для элементов" << std::endl;
        }
        insertCase5(n);
    }

    // продолжение случая 4
    void insertCase5(Node<Elem>* n)
    {
        Node<Elem>* g = getGrandparent(n);

        waitNextStep();
        std::cout << "------Балансировка------" << std::endl;
        std::vector<Node<Elem>*> specialNodes {};

        specialNodes.push_back(n);
        specialNodes.push_back(n->parent);
        specialNodes.push_back(g);

        printTree(root, 0, specialNodes);

        std::cout << "[СЛУЧАЙ 5] Дедушка рассматриваемого элемента становится красным" << std::endl;
        std::cout << "[СЛУЧАЙ 5] Отец рассматриваемого элемента становится черным" << std::endl;
        std::cout << "[СЛУЧАЙ 5] Рассматриваемый элемент и его предки выделены" << std::endl;
        std::cout << "[СЛУЧАЙ 5] Если рассматриваемый элемент левый сын и его отец левый," << std::endl;
        std::cout << "[СЛУЧАЙ 5] то выполняется правый поворот дедушки" << std::endl;
        std::cout << "[СЛУЧАЙ 5] Если правый и правый, то выполняется левый поворот!" << std::endl;

        n->parent->color = BLACK;
        g->color = RED;
        // n левый сын и отец левый сын
        waitNextStep();
        specialNodes.clear();
        if ((n == n->parent->left) && (n->parent == g->left)) {
            rightRotate(g);
            std::cout << "------Балансировка------" << std::endl;
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 5] Рассматриваемый элемент был левым и его отец был тоже левым" << std::endl;
            std::cout << "[СЛУЧАЙ 5] Был выполнен правый поворот дедушки" << std::endl;
        } else { // n правый сын и отец правый сын
            leftRotate(g);
            std::cout << "------Балансировка------" << std::endl;
            printTree(root, 0, specialNodes);
            std::cout << "[СЛУЧАЙ 5] Рассматриваемый элемент был правым и его отец был тоже правым" << std::endl;
            std::cout << "[СЛУЧАЙ 5] Был выполнен левый поворот дедушки" << std::endl;
        }
    }


public:
    RBTree() : root(nullptr) {}
    ~RBTree() { delete root; }

    Node<Elem>* getRoot() { return root; }

    void insert(Elem stuff) { // Вставка элемента
        auto newNode = new Node<Elem>();
        newNode->data = stuff;
        newNode->color = RED;

        auto linker = root;
        std::vector<Node<int>*> specialNodes = {};


        // если node < linker, то идем в левую ветку
        // если node >= linker, то идем в правую ветку
        // когда нет след ветки, то вставляем туда элемент
        while (linker) {


            specialNodes.clear();
            waitNextStep();
            std::cout << "-----------------------------" << std::endl;
            specialNodes.push_back(linker);
            printTree(getRoot(), 0, specialNodes);
            std::cout << "------Вставка элемента-------" << std::endl;


            if (newNode->data < linker->data) {
                if (!linker->left) {
                    linker->left = newNode;
                    newNode->parent = linker;

                    specialNodes.clear();
                    waitNextStep();
                    std::cout << "-----------------------------" << std::endl;
                    specialNodes.push_back(newNode);
                    printTree(getRoot(), 0, specialNodes);
                    std::cout << "------Элемент вставлен-------" << std::endl;

                    break;
                } else linker = linker->left;
            } else {
                if (!linker->right) {
                    linker->right = newNode;
                    newNode->parent = linker;

                    specialNodes.clear();
                    waitNextStep();
                    std::cout << "-----------------------------" << std::endl;
                    specialNodes.push_back(newNode);
                    printTree(getRoot(), 0, specialNodes);
                    std::cout << "------Элемент вставлен-------" << std::endl;

                    break;
                } else linker = linker->right;
            }
        }

        insertCase1(newNode);
        restoreRoot(newNode);

        if (!root->left && !root->right) {
            waitNextStep();
            std::cout << "------Вставлен корень--------" << std::endl;
            specialNodes.push_back(root);
            printTree(getRoot(), 0, specialNodes);
            std::cout << "-----------------------------" << std::endl;
        }

    }
};


char userInput(RBTree<int>* tree) {
    system("clear");
    int stuff;
    std::cout << "Введите элемент, который хотите вставить: ";
    std::cin >> stuff;
    tree->insert(stuff);
    std::vector<Node<int>*> specialNodes;
    std::cout << "-----Текущее дерево-----" << std::endl;
    printTree(tree->getRoot(), 0, specialNodes);
    std::cout << "------------------------" << std::endl;

    char flag;
    std::cout << "Если хотите продолжить ввод, отправьте '+': ";
    std::cin >> flag;
    return flag;
}


int main()
{
    std::cout << " ---------------------------------------------------- " << std::endl;
    std::cout << "| Здравствуйте, вы попали в курсовую работу студента |" << std::endl;
    std::cout << "|             Русинова Д.А. группы 9382              |" << std::endl;
    std::cout << " ---------------------------------------------------- " << std::endl;
    std::cout << "|    Демонстрация вставки в красно-черное дерево     |" << std::endl;
    std::cout << " ---------------------------------------------------- " << std::endl;
    std::cout << "|   Красным цветом выделяются красные элементы КЧД   |" << std::endl;
    std::cout << "|    Черным цветом выделяются черные элементы КЧД    |" << std::endl;
    std::cout << "|  Белым цветом выделяются рассматриваемые элементы  |" << std::endl;
    std::cout << "|             в ходе выполнения алгоритма            |" << std::endl;
    std::cout << " ---------------------------------------------------- " << std::endl;

    char start;
    std::cout << "Для начала работы, введите любой символ: ";
    std::cin >> start;

    auto* tree = new RBTree<int>;
    char flag = userInput(tree);
    while (flag == '+') flag = userInput(tree);

    return 0;
}