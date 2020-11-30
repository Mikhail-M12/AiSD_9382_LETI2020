#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <QPainter>
#include <QColor>

template<typename Elem> class AVL;

//класс вершины
template<typename Elem>
class Node
{
    friend class AVL<Elem>;
public:
    Node(const Elem &);
    Elem value;
    Node<Elem> *leftChild;
    Node<Elem> *rightChild;
    Node<Elem> *parent;

    int height;
    QColor color;
    int x;
};

//класс АВЛ-дерева
template<typename Elem>
class AVL
{
public:
    AVL();

    //методы для копирования дерева
    AVL copy();
    Node<Elem>* recursiveCopy(Node<Elem> *p);

    //метод проверяющий не пусто ли дерево
    bool isEmpty() const;

    //методы по удалению и вставки элемента в дерево
    Node<Elem>* insertNode(Node<Elem>* node, const Elem &, std::vector<AVL<Elem>> &vectorAVL, std::vector<std::string> &messages);
    bool insertValue(const Elem &, std::vector<AVL<Elem>> &vectorAVL, std::vector<std::string> &messages);
    Node<Elem>* deleteNode(Node<Elem>* node, const Elem &, std::vector<AVL<Elem>> &vectorAVL, std::vector<std::string> &messages);
    bool deleteValue(const Elem &, std::vector<AVL<Elem>> &vectorAVL, std::vector<std::string> &messages);

    //перебалансировка заданной вершины
    Node<Elem>* rebalance(Node<Elem> * node, const Elem &item, std::vector<AVL<Elem>> &vectorAVL, std::vector<std::string> &messages);

    //методы для осуществления поворота поддерева
    Node<Elem>* rightRotate(Node<Elem> *y);
    Node<Elem>* leftRotate(Node<Elem> *x);

    //подсчет баланса вершины
    int getBalance(Node<Elem> *node);

    //метод возвращающий минимальную вершину в поддереве
    Node<Elem>* minValueNode(Node<Elem>* node);

    //метод сбрасывает положения по горизонтали всех вершин дерева до 0
    void resetNodePosition(Node<Elem> *node);

    //метод возвращает минимальную вершину в поддереве с корнем в вершине node
    Node<Elem>* getLeftmostNode(Node<Elem>* node);

    //метод возвращает уровень вершины
    int getNodeLevel(Node<Elem> *node);

    //метод возвращающий положение по горизонтали самой правой вершины
    int getPxLocOfLeftTree(const Node<Elem> *node);

    //метод возвращающий положение по горизонтали первого предка вершины node(начиная с нее)
    int getPxLocOfAncestor(const Node<Elem> *node);

    //метод возвращающий корень дерева
    Node<Elem> *getRoot();

    //метод возвращающий ширину дерева
    int getTotalX() const;

    //метод возвращающий высоту дерева(расстояние)
    int getTotalY() const;

    //метод возвращающий высоту дерева(по количеству вершин)
    int getTreeHeight(const Node<Elem> *node) const;

    //метод возвращающий высоту вершины(по количеству вершин)
    int getHeight(Node<Elem> *node);

    int max(int a, int b) const;

    QPainter *painter;
    int yspace;
    int xspace;
    int nodeRadius;
    double scale;

private:
Node<Elem> *root;

};

template<typename Elem>
AVL<Elem> AVL<Elem>::copy(){
    AVL<Elem> avl = AVL<Elem>();
    avl.root = recursiveCopy(root);
    avl.painter = painter;
    avl.yspace = yspace;
    avl.xspace = xspace;
    avl.scale = scale;
    avl.nodeRadius = nodeRadius;
    return avl;
}

template<typename Elem>
Node<Elem>* AVL<Elem>::recursiveCopy(Node<Elem> *p){

    if(p == nullptr){
        return nullptr;
    }

    Node<Elem> *n = new Node<Elem>(p->value);
    n->leftChild=recursiveCopy(p->leftChild);

    if(n->leftChild != nullptr)
        n->leftChild->parent = n;

    n->rightChild=recursiveCopy(p->rightChild);

    if(n->rightChild != nullptr)
        n->rightChild->parent = n;

    n->height=p->height;
    n->x = p->x;
    n->color = p->color;

    return n;
}

template<typename Elem>
AVL<Elem>::AVL() : scale(1), root(nullptr) {}

template<typename Elem>
int AVL<Elem>::max(int a, int b) const{
    return (a>b)? a : b;
}

template<typename Elem>
int AVL<Elem>::getHeight(Node<Elem> *node){
    if(node == nullptr){
        return 0;
    }
    return node->height;
}

template<typename Elem>
int AVL<Elem>::getBalance(Node<Elem> *node){
    if(node == nullptr){
        return 0;
    }
    return getHeight(node->leftChild) - getHeight(node->rightChild);
}

template<typename Elem>
Node<Elem>::Node(const Elem &data) : value(data),  leftChild(nullptr),  rightChild(nullptr), parent(nullptr), height(1), color(QColor(88, 181, 191)) , x(0) {}

template<typename Elem>
bool AVL<Elem>::isEmpty() const {
    return root == nullptr;
}

template<typename Elem>
bool AVL<Elem>::insertValue(const Elem & item, std::vector<AVL<Elem>> &vectorAVL, std::vector<std::string> &messages){
    root = insertNode(root,item, vectorAVL, messages);
    vectorAVL.push_back(this->copy());
    messages.push_back("------------Вставка завершена------------");
    return true;
}

template<typename Elem>
Node<Elem>* AVL<Elem>::insertNode(Node<Elem>* node, const Elem &item, std::vector<AVL<Elem>> &vectorAVL, std::vector<std::string> &messages){
    //если мы достигли null-вершины, то вместо нее можно вставить новую вершину
    if(node == nullptr){
        Node<Elem> *newNode = new Node<Elem>(item);
        vectorAVL.push_back(this->copy());
        messages.push_back("Вставляем вершину " + std::to_string(item));
        return newNode;
    }

    //если вставляемое значение меньше текущей вершины, то нам следует переместиться к левому ребенку
    if(item < node->value){
        node->color = Qt::green;
        vectorAVL.push_back(this->copy());
        messages.push_back("Значение " + std::to_string(item) + " новой вершины меньше, чем у текущей вершины " + std::to_string(node->value) + " ,идем к левому ребенку ");
        node->color = QColor(88, 181, 191);
        node->leftChild = insertNode(node->leftChild, item, vectorAVL, messages);
        node->leftChild->parent = node;
    }
    //если вставляемое значение больше текущей вершины, то следует переместиться к правому ребенку
    else if(item > node->value){
        node->color = Qt::green;
        vectorAVL.push_back(this->copy());
        node->color = QColor(88, 181, 191);
        messages.push_back("Значение " + std::to_string(item) + " новой вершины больше, чем у текущей вершины " + std::to_string(node->value) + " ,идем к правому ребенку ");

        node->rightChild = insertNode(node->rightChild, item, vectorAVL, messages);
        node->rightChild->parent = node;
    }
    //если значение вершины равно вставляемому значению, выведем сообщение об этом
    else {
        node->color = QColor(255, 253, 111);
        vectorAVL.push_back(this->copy());
        node->color = QColor(88, 181, 191);
        messages.push_back("Вершина с таким значением уже существует в дереве!");
        return node;
    }

    //подстраиваем высоту вершины
    node->height = 1 + max(getHeight(node->leftChild), getHeight(node->rightChild));

    //проверяем баланс вершины
    return rebalance(node, item, vectorAVL, messages);
}

template<typename Elem>
Node<Elem> * AVL<Elem>::rebalance(Node<Elem> *node,const Elem& item, std::vector<AVL<Elem>> &vectorAVL, std::vector<std::string> &messages){
    int balance = getBalance(node);

    node->color = QColor(250, 184, 254);
    vectorAVL.push_back(this->copy());
    node->color = QColor(88, 181, 191);
    messages.push_back("Критерий баланса вершины " + std::to_string(node->value) + " равен " + std::to_string(balance));

    /*
     * Если balance > 1, значит проблема в левом поддереве
     * Если ключ меньше чем левый ребенок рассматриваемой вершины то это
     * случай Left Left
     */
    if(balance > 1 && item < node->leftChild->value){
        node->color = QColor(255, 0, 0);
        vectorAVL.push_back(this->copy());
        node->color = QColor(88, 181, 191);
        messages.push_back("LL случай, поворачиваем поддерево вправо в вершине " + std::to_string(node->value));

        return rightRotate(node);
    }

    /*
     * Если balance < -1, значит проблема в правом поддереве
     * Если ключ больше чем правый ребенок рассматриваемой вершины то это
     * случай Right Right
     */
    if(balance < -1 && item > node->rightChild->value){
        node->color = QColor(255, 0, 0);
        vectorAVL.push_back(this->copy());
        node->color = QColor(88, 181, 191);
        messages.push_back("RR случай, поворачиваем поддерево влево в вершине " + std::to_string(node->value));

        return leftRotate(node);
    }

    /*
     * Если balance > 1, значит проблема в левом поддереве
     * Если ключ больше чем левый ребенок рассматриваемой вершины то это
     * случай Left Right
     */
    if(balance > 1 && item > node->leftChild->value){
        node->leftChild->color = QColor(255, 0, 0);
        vectorAVL.push_back(this->copy());
        node->leftChild->color = QColor(88, 181, 191);
        messages.push_back("LR случай, сначала поворачиваем дерево влево в вершине " + std::to_string(node->leftChild->value));

        node->leftChild = leftRotate(node->leftChild);

        node->color = QColor(255, 0, 0);
        vectorAVL.push_back(this->copy());
        node->color = QColor(88, 181, 191);
        messages.push_back("Затем поворачиваем дерево вправо в вершине " + std::to_string(node->value));

        return rightRotate(node);
    }

    /*
     * Если balance < -1, значит проблема в правом поддереве
     * Если ключ меньше чем правый ребенок рассматриваемой вершины то это
     * случай Right Left
     */
    if(balance < -1 && item < node->rightChild->value){
        node->rightChild->color = QColor(255, 0, 0);
        vectorAVL.push_back(this->copy());
        node->rightChild->color = QColor(88, 181, 191);
        messages.push_back("RL случай, сначала поворачиваем дерево вправо в вершине " + std::to_string(node->rightChild->value));

        node->rightChild = rightRotate(node->rightChild);

        node->color = QColor(255, 0, 0);
        vectorAVL.push_back(this->copy());
        node->color = QColor(88, 181, 191);
        messages.push_back("Затем поворачиваем дерево влево в вершине " + std::to_string(node->value));

        return leftRotate(node);
    }

    node->color = QColor(197, 184, 254);
    vectorAVL.push_back(this->copy());
    node->color = QColor(88, 181, 191);
    messages.push_back("Вершина "+std::to_string(node->value)+" сбалансирована");

    return node;
}

template<typename Elem>
Node<Elem>* AVL<Elem>::minValueNode(Node<Elem>* node){
    Node<Elem>* current = node;
    while(current->leftChild != nullptr){
        current = current->leftChild;
    }
    return current;
}

template<typename Elem>
bool AVL<Elem>::deleteValue(const Elem &item, std::vector<AVL<Elem>> &vectorAVL, std::vector<std::string> &messages){
    root = deleteNode(root,item, vectorAVL, messages);

    vectorAVL.push_back(this->copy());
    messages.push_back("------------Удаление завершено------------");
    return true;
}

template<typename Elem>
Node<Elem>* AVL<Elem>::deleteNode(Node<Elem>* node, const Elem &item, std::vector<AVL<Elem>> &vectorAVL, std::vector<std::string> &messages){
    //если мы достигли null-вершины, то это значит, что вершины с таким значением нет в дереве и нам нечего удалять
    if(node == nullptr){
        vectorAVL.push_back(this->copy());
        messages.push_back("Вершины с значением " + std::to_string(item) + " не существует в дереве!");
        return node;
    }
    // если значение, которое мы хотим удалить, меньше значения текущей вершины, пойдем к левому дереву
    if(item < node->value){
        node->color = Qt::green;
        vectorAVL.push_back(this->copy());
        node->color = QColor(88, 181, 191);
        messages.push_back("Значение " + std::to_string(item) + " новой вершины меньше, чем у текущей вершины " + std::to_string(node->value) + " ,идем к левому ребенку ");


        node->leftChild = deleteNode(node->leftChild,item, vectorAVL, messages);
    }
    // если значение, которое мы хотим удалить, больше значения текущей вершины, пойдем к правому дереву
    else if(item > node->value){
        node->color = Qt::green;
        vectorAVL.push_back(this->copy());
        node->color = QColor(88, 181, 191);
        messages.push_back("Значение " + std::to_string(item) + " новой вершины больше, чем у текущей вершины " + std::to_string(node->value) + " ,идем к правому ребенку ");

        node->rightChild = deleteNode(node->rightChild,item, vectorAVL, messages);
    }
    //нашли вершину, которую надо удалить
    else {
        node->color = QColor(203, 205, 192);
        vectorAVL.push_back(this->copy());
        node->color = QColor(88, 181, 191);
        messages.push_back("Найдена удаляемая вершина");

        //смотрим случай, когда у вершины 0 или 1 ребенок
        if(node->leftChild == nullptr || node->rightChild == nullptr){
            Node<Elem> *temp = node->leftChild ? node->leftChild: node->rightChild;

            node->color = QColor(165, 205, 192);
            vectorAVL.push_back(this->copy());
            node->color = QColor(88, 181, 191);
            messages.push_back("У удаляемой вершины < 2 детей");

            // если нет обоих детей
            // то просто удаляем вершину
            if(temp == nullptr){
                temp = node;
                node = nullptr;
            }
            //если один ребенок, то "заменяем" эту вершину одним ребенком
            else {
                node->height = temp->height;
                node->leftChild = temp->leftChild;
                node->rightChild = temp->rightChild;
                node->value = temp->value;
                node->x = temp->x;
                node->color = temp->color;
            }
            delete temp;
        }
        //если же ребенка 2, то надо найти самую наименьшую(левую) вершину из правого поддерева
        //значение найденной вершины подставляем в "удаляемую" вершину, а найденную вершину удаляем
        else {
            node->color = QColor(237, 205, 192);
            vectorAVL.push_back(this->copy());
            node->color = QColor(88, 181, 191);
            messages.push_back("В удаляемой вершине 2 ребенка, находим наименьшую вершину из правого поддерева удаляем ее и меняем значения местами");

            Node<Elem>* temp = minValueNode(node->rightChild);
            node->value = temp->value;
            node->rightChild = deleteNode(node->rightChild, temp->value, vectorAVL, messages);
        }
    }

    //если у вершины не было детей, то баланс не изменится
    if(node == nullptr){
        return node;
    }

    node->height = 1 + max(getHeight(node->leftChild), getHeight(node->rightChild));

    return rebalance(node, item, vectorAVL, messages);
}


/*
 * Метод левого поворота
 *        x                     y
 *      /   \                 /   \
 *     T1    y     --->      x     T3
 *          / \            /   \
 *        T2   T3         T1    T2
 *
 */
template<typename Elem>
Node<Elem>* AVL<Elem>::leftRotate(Node<Elem>* x){
    Node<Elem> *y = x->rightChild;
    Node<Elem> *T2 = y->leftChild;

    y->leftChild = x;
    y->parent = x->parent;
    x->parent = y;
    x->rightChild = T2;

    if(T2 != nullptr){
        T2->parent = x;
    }

    x->height = max(getHeight(x->leftChild),  getHeight(x->rightChild)) + 1;
    y->height = max(getHeight(y->leftChild), getHeight(y->rightChild))+ 1;

    return y;
}


/*
 * Метод правого поворота
 *          y                        x
 *         / \                      /  \
 *        x  T3       --->         T1   y
 *      /  \                          /  \
 *     T1  T2                        T2  T3
 */
template<typename Elem>
Node<Elem>* AVL<Elem>::rightRotate(Node<Elem>* y){
    Node<Elem> *x = y->leftChild;
    Node<Elem> *T2 = x->rightChild;

    x->rightChild = y;
    x->parent = y->parent;
    y->parent = x;
    y->leftChild = T2;

    if(T2 != nullptr){
        T2->parent = y;
    }

    y->height = max(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;
    x->height = max(getHeight(x->leftChild),  getHeight(x->rightChild)) + 1;

    return x;
}

template<typename Elem>
Node<Elem> * AVL<Elem>::getRoot(){
    return this->root;
}


template<typename Elem>
void AVL<Elem>::resetNodePosition(Node<Elem> *node){
    if(node == nullptr){
        return;
    }
    resetNodePosition(node->leftChild);
    node->x = 0;
    resetNodePosition(node->rightChild);
}

template<typename Elem>
Node<Elem>* AVL<Elem>::getLeftmostNode(Node<Elem> *node){
    if(root == nullptr)
        return nullptr;
    if(node->leftChild == nullptr){
        return node;
    }
    return getLeftmostNode(node->leftChild);
}

template<typename Elem>
int AVL<Elem>::getNodeLevel(Node<Elem> *node){
    int level = 1;
    Node<Elem> *current = node;
    if(current != nullptr) {
        while(current->parent != nullptr){
            current = current->parent;
            ++level;
        }
    }
    return level;
}

template<typename Elem>
int AVL<Elem>::getPxLocOfLeftTree(const Node<Elem> *node){
    if(node->rightChild == nullptr){
        return node->x;
    }
    return getPxLocOfLeftTree(node->rightChild);
}

template<typename Elem>
int AVL<Elem>::getPxLocOfAncestor(const Node<Elem> *node){
    Node<Elem> *currentNode = node->parent;
    if(currentNode != nullptr){
    while(currentNode->x == 0)
        currentNode = currentNode->parent;
    return currentNode->x;
    }
    else {
        return node->x;
    }
}

template<typename Elem>
int AVL<Elem>::getTreeHeight(const Node<Elem> *node) const{
    if(node == nullptr || (node->leftChild == nullptr && node->rightChild == nullptr)){
        return 0;
    }
    return 1 + max(getTreeHeight(node->leftChild), getTreeHeight(node->rightChild));
}

template<typename Elem>
int AVL<Elem>::getTotalY() const {
    int level = getTreeHeight(root) + 1;
    return (level * nodeRadius * 2 + yspace * (level-1)) + nodeRadius * 2;
}

template<typename Elem>
int AVL<Elem>::getTotalX() const {
    if(this->root == nullptr){
        return nodeRadius*3;
    }
    Node<Elem> *current = root;
    while(current->rightChild != nullptr){
        current = current->rightChild;
    }
    return current->x + nodeRadius * 3;
}

#endif // AVL_H
