#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree(int inputData)
{
    data = inputData;
    quantityOfNodes = 1;
    pointers.left = nullptr;
    pointers.right = nullptr;
}

BinarySearchTree* buildTree(char* input, BinarySearchTree* prevTree = nullptr)
{
    int data = 0;
    char* tail;
    sscanf(input, "%d %s", &data, tail);

    if (!data)
    {
        if (prevTree == nullptr)
            return buildTree(tail, new BinarySearchTree(data));
        else
        {
            prevTree->insert(data);
            return buildTree(tail, prevTree);
        }
    }
    return prevTree;
}

BinarySearchTree::~BinarySearchTree()
{
    if (pointers.left != nullptr)
        delete pointers.left;
    if (pointers.right != nullptr)
        delete pointers.right;
}

int BinarySearchTree::getQuantityOfNodes()
{
    return quantityOfNodes;
}

void BinarySearchTree::updateQuantityOfNodes()
{
    quantityOfNodes = 1 + pointers.left->getQuantityOfNodes() + pointers.right->getQuantityOfNodes();
}

BinarySearchTree* BinarySearchTree::find(int inputData)
{
    if (data == inputData)
        return this;
    
    if (inputData < data)
    {
        if (pointers.left == nullptr) return nullptr;
        return (pointers.left->find(inputData));
    }

    else
    {
        if (pointers.right == nullptr) return nullptr;
        return (pointers.right->find(inputData));
    }
}

BinarySearchTree* BinarySearchTree::rotateLeft() // (A, (B, C)) -> ((A, B), C))
{

    cout << "Call rotateLeft\nTree before\n";
    view();

    BinarySearchTree* right = pointers.right;
    if (right == nullptr)
        return this;
    pointers.right = right->pointers.left;
    right->pointers.left = this;

    right->quantityOfNodes = quantityOfNodes;
    updateQuantityOfNodes();

    cout << "Tree after\n";
    view();

    return right;

}

BinarySearchTree* BinarySearchTree::rotateRight() //((A, B), C)) -> (A, (B, C))
{

    cout << "Call rotateRight\nTree before\n";
    view();

    BinarySearchTree* left = pointers.left;
    if (left == nullptr)
        return this;
    pointers.left = left->pointers.right;
    left->pointers.right = this;

    left->quantityOfNodes = quantityOfNodes;
    updateQuantityOfNodes();

    cout << "Tree after\n";
    view();

    return left;
}

// BinarySearchTree* rotateRight(BinarySearchTree* p) // правый поворот вокруг узла p
// {
// 	BinarySearchTree* q = p->pointers.left; 
// 	if( !q ) return p; 
// 	p->pointers.left = q->pointers.right; 
// 	q->pointers.right = p; 
// 	q->quantityOfNodes = p->quantityOfNodes; 
//     p->updateQuantityOfNodes(); 
// 	return q; 
// }

// BinarySearchTree* rotateLeft(BinarySearchTree* q)
// {
// 	BinarySearchTree* p = q->pointers.right;
// 	if( !p ) return q;
// 	q->pointers.right = p->pointers.left;
// 	p->pointers.left = q;
// 	p->quantityOfNodes = q->quantityOfNodes;
// 	q->updateQuantityOfNodes();
// 	return p;
// }

BinarySearchTree* BinarySearchTree::insertInRoot(int inputData)
{
    cout << "Insearting " << inputData << '\n';
    cout << "IN TREE\n";
    view();

    if (inputData < data)
    {
        cout << "Go left\n";
        if (pointers.left == nullptr)
        {
            cout << "Left is empty\n";
            pointers.left = new BinarySearchTree(inputData);        
            return this;
        }
        else
        {
            pointers.left = pointers.left->insertInRoot(inputData);
            return rotateRight();
        }
    }

    else
    {
        cout << "Go right\n";
        if (pointers.right == nullptr)
        {
            cout << "Right is empty\n";
            pointers.right = new BinarySearchTree(inputData);
            return this;
        }
        else
        {
            pointers.right = pointers.right->insertInRoot(inputData);
            return rotateLeft();
        }
    }

    return nullptr;
}

BinarySearchTree* BinarySearchTree::insert(int inputData)
{
    bool stopHere = false;
    if (rand()%(quantityOfNodes + 1) == 0)
        stopHere = true;

    if (stopHere)
        return insertInRoot(inputData);

    if (inputData < data)
    {
        if (pointers.left == nullptr)
            pointers.left = new BinarySearchTree(inputData);
        else
            pointers.left = insert(inputData);
    }
    else
    {
        if (pointers.right == nullptr)
            pointers.right = new BinarySearchTree(inputData);
        else
            pointers.right = insert(inputData);
    }

    updateQuantityOfNodes();
    return this;
}

void BinarySearchTree::view(int d)
{
    string buff(d, ' ');
    cout << buff << data << '\n';
    
    if (pointers.left != nullptr)
        pointers.left->view(d+1);
    if (pointers.right != nullptr)
        pointers.right->view(d+1);
}

int main()
{
    char input[] = "1 2 0";
    BinarySearchTree* ptr = new BinarySearchTree(5); 
    ptr->insertInRoot(7);
    ptr->insertInRoot(1);
    ptr->insertInRoot(2);
    ptr->insertInRoot(3);
    ptr->view();

    return 0;
}