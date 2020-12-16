#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree(int inputData)
{
    data = inputData;
    quantityOfNodes = 1;
    pointers.left = nullptr;
    pointers.right = nullptr;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree & binarySearchTree) // Copy operator
{
    data = binarySearchTree.data;

    if (binarySearchTree.pointers.left != nullptr)
        pointers.left = new BinarySearchTree(*binarySearchTree.pointers.left);

    if (binarySearchTree.pointers.right != nullptr)
        pointers.right = new BinarySearchTree(*binarySearchTree.pointers.right);
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

BinarySearchTree* join(BinarySearchTree* smallerTree, BinarySearchTree* biggerTree)
{
    if (smallerTree == nullptr)
        return biggerTree;
    if (biggerTree == nullptr)
        return smallerTree;

    int randNumber = rand();
    srand(randNumber);
    bool  goSmaller = false;
    if (randNumber%(smallerTree->getQuantityOfNodes() + biggerTree->getQuantityOfNodes()) < smallerTree->getQuantityOfNodes())
         goSmaller = true;

    if (goSmaller) {
        smallerTree->pointers.right = join(smallerTree->pointers.right, biggerTree);
        smallerTree->updateQuantityOfNodes();
        return smallerTree;
    } else {
        biggerTree->pointers.left = join(smallerTree, biggerTree->pointers.left);
        biggerTree->updateQuantityOfNodes();
        return biggerTree;
    }
}

BinarySearchTree* BinarySearchTree::deleteFirst(int inputData)
{
    if (inputData == data)
    {
        BinarySearchTree* res = join(pointers.left, pointers.right);
        return res;
    }

    if (inputData < data)
    {
        if (pointers.left != nullptr)
            pointers.left = pointers.left->deleteFirst(inputData);
    }

    else
    {
        if (pointers.right != nullptr)
            pointers.right = pointers.right->deleteFirst(inputData);
    }

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

void greetingMessage()
{
    cout << "\nFile input example -- ./main -f input.txt\n\n";
    cout << "Hello. Please input null terminated ";
    cout << "sequence of numbers.\nThe programm will make ";
    cout << "binary out of them.\nThen input a number, to ";
    cout << "delete it from the tree.\n";
}

BinarySearchTree* stdInputTree()
{
    int data;
    cin >> data;
    BinarySearchTree* tree = new BinarySearchTree(data); 
    cin >> data;

    while (data != 0)
    {
        tree = tree->insert(data);
        cin >> data;
    }
    return tree;
}

void stdInputCase()
{
    BinarySearchTree* tree = stdInputTree(); 

    cout << "\nYour tree -- \n";
    tree->draw();

    int data;
    cout << "\nNumber to delete -- ";
    cin >> data;
    tree = tree->deleteFirst(data);

    cout << "\nThe result -- \n";
    tree->draw();
}

void fileInputCase(string path)
{
    ifstream fin;
    fin.open(path);

    int data;
    fin >> data;
    BinarySearchTree* tree = new BinarySearchTree(data); 

    while (fin >> data)
    {
        tree = tree->insert(data);
    }

    cout << "\nYour tree -- \n";
    tree->draw();


    cout << "\nNumber to delete -- ";
    cin >> data;

    tree->deleteFirst(data);

    cout << "\nResult -- \n";
    tree->draw();
}

int main(int argc, char *argv[])
{
    srand(time(0));
    if (argc>= 2) // Arguments case
    {
        string flag(argv[1]);
        string path(argv[2]);
        if (flag.compare("-f") == 0)
            fileInputCase(path); // No obvious way to overload the function
        return 0;
    }
    greetingMessage();
    stdInputCase();
    return 0;
}