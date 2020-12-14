#include <iostream>
#include <string>


template <typename type>
struct node // структура для представления узлов дерева
{
    type key;
    int size;
    int count;
    node* left;
    node* right;
    node(int k) { key = k; left = right = 0; size = 1; count = 1;}
};

template <typename type>
int find(node<type>* p, type k) // поиск ключа k в дереве p
{
    if( !p ) return 0; // в пустом дереве можно не искать
    if( k == p->key )
        return 1;
    if( k < p->key )
        return find(p->left,k);
    else
        return find(p->right,k);
}

template <typename type>
int getsize(node<type>* p) // обертка для поля size, работает с пустыми деревьями (t=NULL)
{
    if( !p ) return 0;
    return p->size + p->count - 1;
}

template <typename type>
void fixsize(node<type>* p) // установление корректного размера дерева
{
    if(p->left)
        fixsize(p->left);
    if(p->right)
        fixsize(p->right);
    p->size = getsize(p->left)+getsize(p->right)+1;
}

template <typename type>
node<type>* rotateright(node<type>* p) // правый поворот вокруг узла p
{
    using namespace std;
    cout << "Поддерево с вершиной '" << p->key << "' до поворота:" << endl;
    std::cout << "▶ ";
    printBT(p);
    cout << "*********rotateR*********" << endl;
    cout << "Корнем становится корень левого поддерева." << endl;
    cout << "Предыдущий корень перемещается на место корня правого поддерева главного корня." << endl;
    cout << "А смещенный на предыдщем этапе корень перемещается на место левого корня предыдущего корня." << endl;
    cout << "*********rotateR*********" << endl;
    node<type>* q = p->left;
    if( !q ) return p;
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixsize(p);
    cout << "После:" << endl;
    std::cout << "▶ ";
    printBT(q);
    cout << endl;
    return q;
}

template <typename type>
node<type>* rotateleft(node<type>* q) // левый поворот вокруг узла q
{
    using namespace std;
    cout << "Поддерево с вершиной '" << q->key << "' до поворота:" << endl;
    std::cout << "▶ ";
    printBT(q);
    cout << "*********rotateL*********" << endl;
    cout << "Корнем становится корень правого поддерева." << endl;
    cout << "Предыдущий корень перемещается на место корня левого поддерева главного корня." << endl;
    cout << "А смещенный на предыдщем этапе корень перемещается на место правого корня предыдущего корня." << endl;
    cout << "*********rotateL*********" << endl;
    node<type>* p = q->right;
    if( !p ) return q;
    q->right = p->left;
    p->left = q;
    p->size = q->size;
    fixsize(q);
    cout << "После:" << endl;
    std::cout << "▶ ";
    printBT(p);
    return p;
}

template <typename type>
node<type>* insertroot(node<type>* p, type k) // вставка нового узла с ключом k в корень дерева p
{
    if( !p ) return new node<type>(k);
    if( k < p->key )
    {
        p->left = insertroot(p->left,k);
        return rotateright(p);
    }
    if ( k > p->key )
    {
        p->right = insertroot(p->right,k);
        return rotateleft(p);
    }
    if (k == p->key)
    {
        p->count++;
    }
    return p;
}

template <typename type>
node<type>* insert(node<type>* p, type k) // рандомизированная вставка нового узла с ключом k в дерево p
{
    using namespace std;
    if( !p ) {
        cout << "Вставка согласно БДП!" << endl;
        return new node<type>(k);
    }
    if( rand()%(p->size+1)==0 ) {
        cout << endl << "Выпал шанс рандомизации, вставлю в корень, на место '" << p->key << "'" << endl;
        cout << "Для этого вставлю элемент в БДП, а затем буду перемещать его при помощи вращений к корню." << endl;
        return insertroot(p, k);
    }
    else {
        if (p->key > k) {
            cout << "'" << k << "' < '" << p->key << "'" << endl;
            cout << "Переход \x1b[34m<-\x1b[0m" << endl;
            p->left = insert(p->left, k);
        } else {
            if (p->key == k) {
                cout << "Элемент в дереве уже был, увеличиваю счетчик для этого элемента." << endl;
                p->count++;
            }
            else {
                cout << "'" << k << "' > '" << p->key << "'" << endl;
                cout << "Переход \x1b[31m->\x1b[0m" << endl;
                p->right = insert(p->right, k);
            }
        }
    }
    fixsize(p);
    return p;
}

template <typename type>
int heightBT(node<type>* bt) // Функция для подсчета высоты BT
{
    if (!bt) return 0;
    else{
        return (heightBT(bt->left) > heightBT(bt->right) ? heightBT(bt->left) : heightBT(bt->right)) + 1;
    }
}

template <typename type>
void printBT(node<type>* bt, std::string str="") // Функция для печати BT
{
    if (bt == nullptr) return;
    std::string _str = str;
    std::cout << bt->key << std::endl;
    //std::cout << bt->key << " (" << bt->size << "/" << bt->count << ")" << std::endl;
    if (bt->right != nullptr)
    {
        std::cout << str;
    }
    if (bt->left == nullptr && bt->right != nullptr)
    {
        std::cout << "\x1b[31m└▶ \x1b[0m";
    }
    if (bt->left != nullptr && bt->right != nullptr)
    {
        std::cout << "\x1b[31m├▶ \x1b[0m";
    }
    if (bt->left != nullptr)
    {
        printBT(bt->right, str.append("\x1b[34m│ \x1b[0m"));
    }
    else
    {
        printBT(bt->right, str.append(" "));
    }
    if (bt->left != nullptr)
    {
        std::cout << _str;
    }
    if (bt->left != nullptr)
    {
        std::cout << "\x1b[34m└▶ \x1b[m";
    }
    printBT(bt->left, _str.append(" "));
}



