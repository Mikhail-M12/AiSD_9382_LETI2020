#include <iostream>
#include <fstream>
#include <queue>
#include <set>
using namespace std;

ifstream infile ("KLP.txt");

/*
 * class BT - класс, реализующий бинарное дерево
 * Elem value - элемент, содержащийся в вершине
 * BT* left - указатель на левого ребенка вершины
 * BT* right - указатель на правого ребенка вершины
 */
template<typename Elem>
class BT{
public:
    Elem value;
    BT *left;
    BT *right;
    BT(Elem val, BT * l, BT * r);
    BT * enter();
    void checkForEqualElements(BT * root);
    void outBT(BT * root);
};
/*
 * BT(Elem val) - конструктор бинарного дерева
 * Elem val - элемент в будущей вершине
 * BT * l - левый ребенок в будущей вершине
 * BT * r - правый ребенок в будущей вершине
 */
template <typename Elem>
BT<Elem>::BT(Elem val,BT * l, BT * r) {
    this->value = val;
    this->left = l;
    this->right = r;
}

/*
 * BT<Elem>* enter() - метод для ввода дерева, возвращает указатель на корень дерева
 */
template<typename Elem>
BT<Elem>* BT<Elem>::enter() {
    Elem val;
    infile >> val;
    if(val == '/') return nullptr;
    else {
        BT<Elem> * l = enter();
        BT<Elem> * r = enter();
        return new BT<Elem>(val,l,r);
    }
}
/*
 * void outBT(BT<Elem> *root) - метод для вывода дерева в консоль
 * BT<Elem> * root - указатель на корень дерева
 */
template<typename Elem>
void BT<Elem>::outBT(BT<Elem> *root) {
    if(root!=nullptr){
        cout << root->value;
        outBT(root->left);
        outBT(root->right);
    } else {
        cout << "/";
    }

}

/*
 * void checkForEqualElements(BT* root) - метод, определяющий существуют ли одинаковые элементы в дереве
 * BT* root - указатель на корень дерева
 */
template<typename Elem>
void BT<Elem>::checkForEqualElements(BT * root) {
    if(root == nullptr){
        cout << "\nНекорректное дерево!\n";
        return;
    }
    //создаем очередь для итеративного обхода по дереву в ширину
    std::queue<BT<Elem>*> queueBFS;

    //заносим в очередь корень дерева
    queueBFS.push(root);
    cout << "Заносим корень дерева '" << root->value << "' в очередь \n";

    //создаем множество встречающихся во время итерации вершин
    std::set<Elem> previousNodes;

    //создаем множество вершин-дубликатов
    std::set<Elem> duplicateNodes;

    //обходим дерево в ширину
    while(!queueBFS.empty()){
        //достаем из очереди вершину
        BT<Elem> *tempNode = queueBFS.front();
        queueBFS.pop();
        cout << "Достаем вершину '" << tempNode->value << "' из очереди \n";

        //проверяем эта вершина дубликат или нет
        if(previousNodes.count(tempNode->value) == 1){
            cout << "Вершина '" << tempNode->value << "' уже встречалась в дереве!\n";
            //т.к. дубликат, то вставляем ее в множество дубликатов
            duplicateNodes.insert(tempNode->value);
        }
        else {
            //т.к. не дубликат, вставляем ее в множество пройденных вершин
            previousNodes.insert(tempNode->value);
            cout << "Вершины '" << tempNode->value << "' еще не было в дереве, запоминаем ее\n";
        }
        if(tempNode->left!=nullptr){
            //вставляем, если существует, левого ребенка с очередь
            queueBFS.push(tempNode->left);
            cout << "Левого ребенка '"<< tempNode->left->value <<"' текущей вершины '" << tempNode->value << "' записываем в очередь\n";
        }
        else {
            cout << "У текущей вершины '" << tempNode->value << "' нет левого ребенка!\n";
        }
        if(tempNode->right!=nullptr){
            //вставляем, если существует, правого ребенка в очередь
            queueBFS.push(tempNode->right);
            cout << "Правого ребенка '"<< tempNode->right->value<<"' текущей вершины '" << tempNode->value << "' записываем в очередь\n";
        }
        else {
            cout << "У текущей вершины '" << tempNode->value << "' нет правого ребенка!\n";
        }

    }
    //если существуют дубликаты, то выведем их
    if(!duplicateNodes.empty()) {
        cout << "\nВершины, которые встречаются в дереве более одного раза: \n";
        typename std::set<Elem>::iterator it = duplicateNodes.begin();
        while (it != duplicateNodes.end()) {
            cout << *it << " ";
            it++;
        }
    }
    //если дубликатов не существуют, выведем сообщение об этом
    else {
        cout << "\nВ данном дереве все элементы вершин различны";
    }
}

int main() {
    BT<char> * tree;
    tree = tree->enter();
    cout << "Рассматриваемое дерево: \n";
    tree->outBT(tree);
    cout << "\nПроходимся по дереву в ширину и ищем одинаковые элементы: \n";

    tree->checkForEqualElements(tree);
    cout << "\n";
    return 0;
}



