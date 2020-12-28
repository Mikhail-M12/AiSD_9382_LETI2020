#include "TestGenerator.h"
float* usedProbability;
int insertCounter = 0;
int joinCounter = 0;

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
            pointers.left = new BinarySearchTree(inputData);        
        else
            pointers.left = pointers.left->insertInRoot(inputData);
        return rotateRight();
    }

    if (pointers.right == nullptr)
        pointers.right = new BinarySearchTree(inputData);
    else
        pointers.right = pointers.right->insertInRoot(inputData);
    return rotateLeft();
}

BinarySearchTree* BinarySearchTree::insert(int inputData)
{
    int randNumber = rand();
    
    usedProbability[insertCounter++] = (1.0*(randNumber%(quantityOfNodes + 1)))/(quantityOfNodes + 1);
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

void BinarySearchTree::drawInString(string* res, string buffer, bool isLast)
{
    string branch = "├";
    string pipe = "|";
    string end = "└";
    string dash = "─";

    if (isLast)
    {
        *res += buffer + end + dash + to_string(data) + '\n';
        buffer += "  ";
    }

    else
    {
        *res += buffer + pipe + dash + to_string(data) + '\n';
        buffer += pipe + " ";
    }

    if (pointers.right != nullptr)
        pointers.right->drawInString(res, buffer, false);
    else
        *res += buffer + branch + dash + " empty\n";


    if (pointers.left != nullptr)
        pointers.left->drawInString(res, buffer, true);
    else
        *res += buffer + end + dash + " empty\n";
}

bool isInMasLength(unsigned int n, int x, int* mas)
{
    for (int i=0; i<n; i++)
    {
        if (mas[i] == x)
        {
            return true;
        }
    }
    return false;
}

int* giveRandMasWithLength(unsigned int n, unsigned int upperBoundary)
{
    auto res = new int[n];
    int r;
    for (int i=0; i<n; i++)
    {
        do
        {
            r = rand();
            srand(r);
        } while(isInMasLength(i+1, r%upperBoundary + 1, res));
        res[i] = r%upperBoundary +1;
    }
    return res;
}

BinarySearchTree* giveTreeWithLength(int* mas, unsigned int n)
{
    auto result = new BinarySearchTree(mas[0]);
    if (n == 0 || n == 1)
        return result;

    for (int i=1; i<n; i++)
    {
        result = result->insert(mas[i]);
    }

    return result;
}

void makeTest(unsigned int n, unsigned int upBound)
{
    usedProbability = new float[1<<n];
    string path = "./RandomTreeTest.txt";
    ofstream fout;
    fout.open(path);
    int* theMas = giveRandMasWithLength(n, upBound);
    auto res = giveTreeWithLength(theMas, n);

    fout << "\nЗадание:\nCоздайте случайное дерево поиска из следующих чисел:\n";
    for (int i=0; i<n; i++)
        fout << theMas[i] << ' ';

    fout << "\nИспользуя следующую последовательность случайных чисел от 0 до 1.\n";
    for (int i=0; i<insertCounter; i++)
      fout << usedProbability[i] << ' ';
    fout << '\n';

    fout << "При выборе вставки в корень дерева или продолжения рекурсивного прохода посмотрите на текущее случайное число, проведите вставку в корень, если случайное число меньше вероятности вставки в корень на данном шаге.\n";
    fout << "На самом первом шаге случайные числа не используются.\n";
    
    fout << "\nОтвет на задание:\n";

    string treeString;
    res->drawInString(&treeString);
    fout << treeString;
    treeString = "";
}

int main(int argc, char *argv[])
{
    srand(time(0));
    cout << "Please input the length of tree and upper boundary for test ";
    unsigned int len;
    unsigned int upBound;
    cin >> len;
    cin >> upBound;
    cout << "\nThe length is " << len << '\n';
    cout << "\nThe upper boundary " << upBound << '\n';

    if (0 < len <= upBound)
    {
        makeTest(len, upBound);
        cout << "\nThe test has been made\n";
    }
    else
    {
        cout << "Wrong input\n";
    }
    return 0;
}
