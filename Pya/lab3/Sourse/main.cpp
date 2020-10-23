#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
template <typename Elem>// Elem - параметр шаблона класса, в качестве него используем char
class BinaryTree {
private:
    typedef struct Node {//структура, описывающая содержимое узла
        Elem data;//данные, хранящиеся в узле
        struct Node *left;//левое поддерево
        struct Node *right;//правое поддерево
        Node() {
            left = nullptr;
            right = nullptr;
        }
    } node;

    node *createBinaryTree(char LKP[], char KLP[], int n = 0) {//рекурсивный метод для создания дерева
        n++;
        if (strlen(KLP) <= i) {//в случае некорректных данных выводится сообщение об ошибке
            cout << "Error Data";
            return nullptr;
        }
        node *binaryTree = new node();
        binaryTree->data = KLP[i++];//содержимое узла
        char *rshift = strchr(LKP, binaryTree->data);
        if (rshift == nullptr) {//в случае некорректных данных выводится сообщение об ошибке
            i = strlen(KLP) + 1;
            return nullptr;
        }
        char *lshift = new char[100]();
        strncat(lshift, LKP, rshift - LKP);
        strcat(lshift, "\0");
        for (int y = 0; y < n;y++)
            cout << " ";
        cout << n << ".Data of current node is: " << binaryTree->data << "\n";
        for (int y = 0; y < n;y++)
            cout << " ";
        cout << n << ".Left subtree is: " << lshift << "\n";
        if (strlen(lshift) != 0) {
            binaryTree->left = createBinaryTree(lshift, KLP, n);//передаем левую часть строки, из которой формируется поддерево
        }
        for (int y = 0; y < n;y++)
            cout << " ";
        cout << n << ".Right subtree is: " << rshift + 1 << "\n";
        if (strlen(rshift) != 1) {//так как в правой части хранится искомый узел, то здесь рекурсивный цикл прекращается на количестве элементов в правой части, равном 1
            binaryTree->right = createBinaryTree(rshift + 1, KLP, n);//передаем правую часть строки, из которой формируется поддерево
        }
        delete[] lshift;
        return binaryTree;
    }

public:
    int i;//счетчик для KLP
    node *tree;//бинарное дерево, созданно для многократного безопасного обращения к одному и тому же дереву

    BinaryTree(char LKP[], char KLP[]) {
        i = 0;
        tree = createBinaryTree(LKP, KLP, 0);//создание дерева
    }

    void printInorder(node *node, int n, char *shift) {//вывод дерева
        n++;//номер уровня
        char k[10];
        char *_k_ = new char[10]();//строка, в которой будет хранится номер уровня
        _k_[0] = ' ';
        if (node == NULL) {//завершение рекурсивного цикла
            delete[] _k_;
            return;
        }
        printInorder(node->right, n, shift);//вход в самую левую ветку
        sprintf(k, "%d", n);
        strcat(_k_, k);
        strcat(_k_, " ");
        char *t = strstr(shift, _k_);//поиск номера в строке из номеров
        delete[] _k_;
        if (!(n == 1) &&
            t) {//в случае нахождения текущего номера в строке номеров знаем, что узел находится левее в бинарном дереве
            for (int i = 0; i < n + 3 * n; i++)//сдвигаем узел до его уровня
                cout << " ";
            cout << "[" << node->data << "]" << ":" << n << "\n";
            char *tshift = new char[50]();
            strncat(tshift, shift, t - shift);//убираем номер из строки номеров
            strcat(tshift, t + 2);
            delete[] shift;
            shift = new char[50]();
            strcat(shift, tshift);
            delete[] tshift;
            int m = 1;
            while (m != 4) {
                for (int i = 0; i < n + 3 * n - m; i++)//рисуем ветку
                    cout << " ";
                cout << "/\n";
                m++;
            }
        } else if (n != 1 &&
                   !t) {//в случае отсутствия текущего номера в строке номеров знаем, что узел находится правее в бинарном дереве
            int m = 3;
            while (m != 0) {
                for (int i = 0; i < n + 3 * n - m; i++)//рисуем ветку
                    cout << " ";
                cout << "\\\n";//рисуем ветку
                m--;
            }
            for (int i = 0; i < n + 3 * n; i++)
                cout << " ";//сдвигаем узел до его уровня
            cout << "[" << node->data << "]" << ":" << n << "\n";
            sprintf(k, "%d", n);//добавляем номер обратно в строку номеров
            strcat(shift, k);
            strcat(shift, " ");
        } else//если номер 1, то это вершина дерева, его корень
            cout << "[" << node->data << "]" << ":" << n << "\n";
        printInorder(node->left, n, shift);//после самого левого прохода идем вправый
    }

    static void printLPK(node *node) {//вывод постфиксной записи (ЛПК)
        if (node != nullptr) {
            printLPK(node->left);//сначала идем в левые поддеревья
            printLPK(node->right);//после в правые поддеревья
            cout << node->data << " ";//пишем узел
        }
    }
};

int main() {
    auto *in = new char[30]();//строка для инфиксной записи ЛКП
    auto *pre = new char[30]();//строка для префиксной записи КЛП
    char x;//переменная для выбора ввода пользователем
    cout << "Do you want to enter data(0) or read it from file(write number of file)?\n";
    cin >> x;
    if (x ==
        48) {//так как на вход принимается символ, то номер нуля = 48, это работает, пока количество тестов не привышает 9
        cin >> in >> pre;//считывание строк из консоли
    } else {
        char *file = new char[50]();
        strcat(file, ".//Tests//");
        file[strlen(file)] = x;
        strcat(file, ".txt");
        fstream fin(file);//файл для считывания выражений
        if (!fin.is_open())
            throw ("File cannot be opened");
        fin >> in >> pre;//считывание строк из файла
        delete[] file;
    }
    cout << "Data is:\n" << in << "\n" << pre << "\n";
    BinaryTree<char> tree(in, pre);//создание экземпляра класса BinaryTree
    if (tree.tree == nullptr || strlen(pre) < tree.i)
        return -1;
    delete[] in;
    char *shift = new char[50]();//строка, в которой будут находиться номера уровней узлов для вывода дерева
    shift[0] = ' ';
    char k[10];
    for (int i = 1; i < strlen(pre) + 1; i++) {//запись номеров в строку, они не будут превышать количество узлов
        sprintf(k, "%d", i);
        strcat(shift, k);
        strcat(shift, " ");
    }
    shift[strlen(shift)] = '\0';
    tree.printInorder(tree.tree, 0, shift);//вывод дерева
    cout << "\nLPK is\n";
    tree.printLPK(tree.tree);//вывод постфикной записи
    delete[] pre;
    delete[] shift;
    return 0;
}