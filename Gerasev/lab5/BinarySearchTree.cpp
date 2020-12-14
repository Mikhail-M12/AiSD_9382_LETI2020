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
    unsigned int quantityOfNodesLeft = 0;
    unsigned int quantityOfNodesRight = 0;
    if (pointers.left != nullptr)
        quantityOfNodesLeft = pointers.left->getQuantityOfNodes();
    
    if (pointers.right != nullptr)
        quantityOfNodesRight = pointers.right->getQuantityOfNodes();

    quantityOfNodes = 1 + quantityOfNodesLeft + quantityOfNodesRight;
    cout << "quantityOfNodes is " << quantityOfNodes << '\n';
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
    BinarySearchTree* right = pointers.right;
    if (right == nullptr)
        return this;
    pointers.right = right->pointers.left;
    right->pointers.left = this;

    right->quantityOfNodes = quantityOfNodes;
    updateQuantityOfNodes();
    return right;
}

BinarySearchTree* BinarySearchTree::rotateRight() //((A, B), C)) -> (A, (B, C))
{
    BinarySearchTree* left = pointers.left;
    if (left == nullptr)
        return this;
    pointers.left = left->pointers.right;
    left->pointers.right = this;

    left->quantityOfNodes = quantityOfNodes;
    updateQuantityOfNodes();
    return left;
}

BinarySearchTree* BinarySearchTree::insertInRoot(int inputData)
{
    if (inputData < data)
    {
        if (pointers.left == nullptr)
        {
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
        if (pointers.right == nullptr)
        {
            pointers.right = new BinarySearchTree(inputData);
            return this;
        }
        else
        {
            pointers.right = pointers.right->insertInRoot(inputData);
            return rotateLeft();
        }
    }

    cout << "ERROR, unexpected behavour on insertInRoot metod\n";
    return nullptr;
}

BinarySearchTree* BinarySearchTree::insert(int inputData)
{
    srand(time(0));
    int randNumber = rand();
    srand(randNumber);

    bool stopHere = false;
    if (randNumber%(quantityOfNodes + 1) == 0)
        stopHere = true;
    
    cout << "\n\ninputData is " << inputData << '\n';
    cout << "quantityOfNodes is " << quantityOfNodes << '\n';
    cout << "Stop here is " << stopHere << '\n';
    cout << "Call on tree \n";
    view();

    if (stopHere)
        return insertInRoot(inputData);

    if (inputData < data)
    {
        if (pointers.left == nullptr)
            pointers.left = new BinarySearchTree(inputData);
        else
            pointers.left = pointers.left->insert(inputData);
    }
    else
    {
        if (pointers.right == nullptr)
            pointers.right = new BinarySearchTree(inputData);
        else
            pointers.right = pointers.right->insert(inputData);
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
    int data;
    cin >> data;
    BinarySearchTree* bt_ptr = new BinarySearchTree(data); 


    while (data != 0)
    {
        bt_ptr = bt_ptr->insert(data);
        cin >> data;
    }

    bt_ptr->view();
    return 0;
}