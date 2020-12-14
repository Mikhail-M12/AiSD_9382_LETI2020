#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree(int inputData)
{
    data = inputData;
    quantityOfNodes = 1;
    pointers.left = nullptr;
    pointers.right = nullptr;
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

BinarySearchTree* BinarySearchTree::insert(int inputData)
{
    int randNumber = rand();
    srand(randNumber);

    bool stopHere = false;
    if (randNumber%(quantityOfNodes + 1) == 0)
        stopHere = true;

    if (stopHere)
    {
        BinarySearchTree* res = insertInRoot(inputData);
        updateQuantityOfNodes();
        return res;
    }

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

void BinarySearchTree::draw(string buffer, bool isLast)
{
    string branch = "├";
    string pipe = "|";
    string end = "└";
    string dash = "─";

    if (isLast)
    {
        cout << buffer << end << dash << data << '\n';
        buffer += "  ";
    }

    else
    {
        cout << buffer << pipe << dash << data << '\n';
        buffer += pipe + " ";
    }

    if (pointers.right != nullptr)
        pointers.right->draw(buffer, false);
    else
        cout << buffer << branch << dash << " empty\n";


    if (pointers.left != nullptr)
        pointers.left->draw(buffer, true);
    else
        cout << buffer << end << dash << " empty\n";
}

int main()
{
    srand(time(0));

    int data;
    cin >> data;
    BinarySearchTree* bt_ptr = new BinarySearchTree(data); 
    cin >> data;

    while (data != 0)
    {
        bt_ptr = bt_ptr->insert(data);
        cin >> data;
    }

    bt_ptr->draw();

    return 0;
}