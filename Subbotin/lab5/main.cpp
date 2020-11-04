#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<typename Elem>
class Node{
public:
    Elem key;
    Node *left;
    Node *right;
    int height;
    int count;
};
template<typename Elem>
void preOrder(Node<Elem>* root);

void shift(int depth){
    for(int i = 0; i<depth; i++){
        cout << "   ";
    }
}

int max(int a, int b){
    return (a>b)? a : b;
}

template<typename Elem>
int height(Node<Elem> *node){
    if(node == nullptr){
        return 0;
    }
    return node->height;
}

template<typename Elem>
Node<Elem>* newNode(Elem key){
    Node<Elem>* node = new Node<Elem>();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    node->count = 1;
    return node;
}
/*
 * Функция правого поворота
 *          y                        x
 *         / \                      /  \
 *        x  T3       --->         T1   y
 *      /  \                          /  \
 *     T1  T2                        T2  T3
 */
template<typename Elem>
Node<Elem> *rightRotate(Node<Elem> *y, int depth){
    Node<Elem> *x = y->left;
    Node<Elem> *T2 = x->right;

    //поворачиваем
    x->right = y;
    y->left = T2;

    //подгоняем высоту
    y->height = max(height(y->left), height(y->right) + 1);
    x->height = max(height(x->left), height(x->right) + 1);

    shift(depth);
    cout << "Повернутое дерево вправо: ";
    preOrder(x);
    cout << endl;

    return x;
}
/*
 * Функция левого поворота
 *        x                     y
 *      /   \                 /   \
 *     T1    y     --->      x     T3
 *          / \            /   \
 *        T2   T3         T1    T2
 *
 */
template<typename Elem>
Node<Elem> *leftRotate(Node<Elem> *x, int depth){
    Node<Elem> *y = x->right;
    Node<Elem> *T2 = y->left;

    //поворачиваем
    y->left = x;
    x->right = T2;

    //подгоняем высоту
    x->height = max(height(x->left), height(x->right) + 1);
    y->height = max(height(y->left), height(y->right) + 1);

    shift(depth);
    cout << "Повернутое дерево влево: ";
    preOrder(y);
    cout << endl;

    return y;
}

template<typename Elem>
int getBalance(Node<Elem> *node){
    if(node ==  nullptr){
        return 0;
    }
    return height(node->left) - height(node->right);
}


template<typename Elem>
Node<Elem>* insert(Node<Elem> *node, Elem key, int depth){
    //Если мы в несуществующей вершине, то на ее место вставим новую
    if(node == nullptr){
        shift(depth);
        cout << "Вставляем вершину " << key << endl;
        return newNode<Elem>(key);
    }

    //Если вставляемый элемент уже есть в дереве, то просто инкрементим поле count
    if(key == node->key){
        node->count +=1;
        shift(depth);
        cout << "Такая вершина уже существует в дереве, всего вершин с ключём "<< key <<" = " << node->count << endl;
        return node;
    }

    //Здесь мы передвигаемся по правилам BST
    if(key < node->key){
        shift(depth);
        cout << "Значение " << key << " новой вершины меньше, чем у текущей вершины " << node->key << " ,идем к левому ребенку "<< endl;
        node->left = insert(node->left, key, depth+1);
    }
    else if(key > node->key){
        shift(depth);
        cout << "Значение " << key << " новой вершины больше, чем у текущей вершины " << node->key << " ,идем к правому ребенку "<< endl;
        node->right = insert(node->right, key, depth+1);
    }

    //Задаем высоту  вершины
    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    shift(depth);
    cout << "Критерий баланса вершины " << node->key << " равен " << balance << endl;

    /*
     * Если balance > 1, значит проблема в левом поддереве
     * Если ключ меньше чем левый ребенок рассматриваемой вершины то это
     * случай Left Left
     */
    if(balance > 1 && key < node->left->key){
        shift(depth);
        cout << "LL случай, в поддереве: ";
        preOrder(node);
        cout << "поворачиваем дерево вправо с началом в вершине: " << node->key<< endl;
        return rightRotate(node, depth);
    }

    /*
     * Если balance < -1, значит проблема в правом поддереве
     * Если ключ больше чем правый ребенок рассматриваемой вершины то это
     * случай Right Right
     */
    if(balance < -1 && key > node->right->key){
        shift(depth);
        cout << "RR случай, в поддереве: ";
        preOrder(node);
        cout << " поворачиваем дерево влево с началом в вершине: " << node->key<< endl;
        return leftRotate(node, depth);
    }

    /*
     * Если balance > 1, значит проблема в левом поддереве
     * Если ключ больше чем левый ребенок рассматриваемой вершины то это
     * случай Left Right
     */
    if(balance > 1 && key > node->left->key){
        shift(depth);
        cout << "LR случай, в поддереве: ";
        preOrder(node);
        cout << " с началом в вершине: " << node->key<< endl;
        shift(depth);
        cout << "Сначала поворачиваем дерево влево в вершине " << node->left->key << endl;
        node->left = leftRotate(node->left, depth);
        shift(depth);
        cout << "Затем поворачиваем дерево вправо в вершине " << node->key << endl;
        return rightRotate(node, depth);
    }

    /*
     * Если balance < -1, значит проблема в правом поддереве
     * Если ключ меньше чем правый ребенок рассматриваемой вершины то это
     * случай Right Left
     */
    if(balance < -1 && key < node->right->key){
        shift(depth);
        cout << "RL случай, в поддереве: ";
        preOrder(node);
        cout << "с началом в вершине: " << node->key<< endl;
        shift(depth);
        cout << "Сначала поворачиваем дерево вправо в вершине " << node->right->key << endl;
        node->right = rightRotate(node->right, depth);
        shift(depth);
        cout << "Затем поворачиваем дерево влево в вершине " << node->key << endl;
        return leftRotate(node, depth);
    }
    shift(depth);
    cout << "Вершина сбалансированна" << endl;
    return node;
}

template<typename Elem>
Node<Elem>* countElemAndInsert(Node<Elem>* root, Elem elem){
    Node<Elem> *tempNode = root;
    //Передвигаемся по дереву и ищем дубликат
    while(tempNode!=nullptr){
        if(tempNode->key == elem){
            cout << "Вершина " << elem << " уже существует и ее дупликатов было " << tempNode->count << endl;
            tempNode->count++;
            return root;
        }
        if(tempNode->key < elem){
            tempNode = tempNode->right;
        }
        else if(tempNode->key > elem){
            tempNode = tempNode->left;
        }
    }
    //вставляем новый ключ
    cout << "Такой вершины " << elem << " нет в дереве, вставляем ее в дерево: " << endl;
    preOrder(root);
    cout << endl;
    root = insert(root, elem, 0);
    cout << "Дерево после вставки: ";
    preOrder(root);
    return root;
}

template<typename Elem>
void preOrder(Node<Elem>* root){
    if(root!=nullptr){
        cout << root->key << "(" << root->count << ") ";
        preOrder(root->left);
        preOrder(root->right);
    }
    else {
        cout << "# ";
    }
}


int main() {
    Node<int> *root = nullptr;

    string ch = "0";
    while(ch!="f" && ch!="c"){
        cout <<"Введите c/f для ввода из консоли/файла: ";
        cin >> ch;
    }

    if(ch == "f") {
        string filename = "../in.txt";
        ifstream myfile(filename);

        int n;
        myfile >> n;
        if( n < 0) {
            cout << "Некорректное значение количества вершин в дереве!";
            return 0;
        }
        for(int i = 0; i<n; i++){
            int key;
            myfile >> key;
            cout << "Хотим добавить вершину с ключём " << key << endl;
            root = insert(root, key, 1);
            cout << "Сбалансированное дерево после вставки: ";
            preOrder(root);
            cout << endl << endl;
        }

        myfile.close();
    }
    else if(ch == "c"){
        cout << "Введите сначала количество элементов в дереве и затем сами вершины: ";
        int n;
        cin >> n;
        if( n < 0) {
            cout << "Некорректное значение количества вершин в дереве!";
            return 0;
        }
        for(int i = 0; i<n; i++){
            int key;
            cin >> key;
            cout << "Хотим добавить вершину с ключём " << key << endl;
            root = insert(root, key, 1);
            cout << "Сбалансированное дерево после вставки: ";
            preOrder(root);
            cout << endl << endl;
        }
    }

    ch = "y";
    while(ch == "y") {
        cout << endl << "Если хотите/не хотите добавить вершину нажмите y/n: ";
        cin >> ch;
        if( ch == "y"){
            cout << "Введите вершину, которую хотите добавить: ";
            int elem;
            cin >> elem;
            root = countElemAndInsert(root,elem);
        }
    }

    return 0;
}