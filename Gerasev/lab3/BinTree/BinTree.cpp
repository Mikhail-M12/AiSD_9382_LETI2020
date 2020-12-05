#include "BinTree.h"

int levelsToMasSize(int inp)
{
    if (inp == 0) { return 1;}
    inp--;
    return (1 + 2* levelsToMasSize(inp));
}

template <typename T>
BinTree<T>::BinTree(unsigned int inputLevels) // Counting from 0
{
    levels = inputLevels;
    treeData = new T[levelsToMasSize(inputLevels)];
}

template <typename T>
BinTree<T>::BinTree(const BinTree<T> & binTree) // Copy operator
{
    treeData = new T[levelsToMasSize(levels)];
    for (int i=0; i< levelsToMasSize(levels); i++)
    {
        treeData[i] = binTree.treeData[i];
    }
}

template <typename T>
BinTree<T>::~BinTree()
{
    if (treeData != nullptr)
    {
        delete treeData;
    }
}

template <typename T>
void BinTree<T>::viewData()
{
    int size = levelsToMasSize(levels);
    for (int i=0; i<size; i++)
    {
        cout << treeData[i] << ' ';
    }
    cout << '\n';
}


template <typename T>
void BinTree<T>::addByDataAddress(int address, T value)
{
    if (address <= levelsToMasSize(levels))
        treeData[address] = value;
}

template <typename T>
void BinTree<T>::addByTreeAddress(string address, T value)
{
    int dataAddress = treeAddressToDataAddress(address);
    addByDataAddress(dataAddress, value);
}

int binToDec(int inpBin)
{
    int decimalNumber = 0;
    int base = 1;
    int temp = inpBin;

    while (temp)
    {
        int lastDigit = temp % 10;
        temp = temp/10;
        decimalNumber += lastDigit*base;
        base = base*2;
    }
    return decimalNumber;
}

int treeAddressToDataAddress(string address)
{
    if (address.empty())
    {
        return 0;
    }

    int offset = (levelsToMasSize(address.size() -1)) ;
    int binAddress = atoi(address.c_str());
    return (offset + binToDec(binAddress));
}

unsigned int RECURSION_DEEPNESS = 0;

template <typename T>
int BinTree<T>::howManyRecursiveHandler(int node, T value)
{
    RECURSION_DEEPNESS++;
    string buffer(RECURSION_DEEPNESS, ' ');

    cout << buffer << "in node " << node << '\n';

    int result = 0;
    if (node >= levelsToMasSize(levels))
    {
        cout << buffer << "There is no such node in tree, go out of the function\n";
        RECURSION_DEEPNESS--;
        return result;
    }

    if (treeData[node] == value)
    {
        cout << buffer << "Found value\n";
        result++;
    }
    int left = (node<<1) +1;
    int right = (node<<1) +2;

    cout << buffer << "Go left\n";
    unsigned int res1 = howManyRecursiveHandler(left, value);
    cout << buffer << "Go right\n";
    unsigned int res2 = howManyRecursiveHandler(right, value);
    cout << buffer << "Returning sum of left and right\n";
    result += res1 + res2;

    RECURSION_DEEPNESS--;
    return result;
}

template <typename T>
int BinTree<T>::howManyRecursive(T value)
{
    if (value == 0)
        return 0;
    cout << "Call howManyRecursiveHandler\n";
    return howManyRecursiveHandler(0, value);
}

template <typename T>
bool BinTree<T>::isContainsAtLeastTwoRecursive(T value)
{
    cout << "Call howManyRecursive\n";
    return (howManyRecursive(value) >= 2);
}

void inputHandler(BinTree<int> tree, int inputValue)
{
    if (inputValue <= 0)
    {
        cout << "inputValue can't be <= 0\n";
        return;
    }

    if (tree.isContainsAtLeastTwoRecursive(inputValue)) {
        cout << "There are 2 or more of " << inputValue << '\n';
    } else {
        cout << "There is 1 or less of " << inputValue << '\n';
    }   
}

void fileInputCase(string path)
{
    ifstream inFile;
    inFile.open(path);
    
    cout << "Tree deepth ";
    int inputLevels;

    while (inFile >> inputLevels)
    {
        BinTree<int> tree(inputLevels);

        string inputAddress = "empty";
        int inputValue = 0;

        while (inputValue != 0 || !(inputAddress.empty()))
        {
            tree.addByTreeAddress(inputAddress, inputValue);
            tree.viewData();
            cout << "\nNode value and address (0 empty to stop input, empty for empty address) ";
            inFile >> inputValue;
            inFile >> inputAddress;
            if (inputAddress == "empty") { inputAddress = ""; }
            cout << "\ninputValue is " << inputValue;
            cout << "\ninputAddress is " << inputAddress << '\n';
        }

        cout << "\nValue to find, is there >= 2 of them \n";
        if(inFile >> inputValue)
        {
            if (inputValue <= 0)
            {
                cout << "inputValue can't be <= 0\n";
            }
            else
            {
                if (tree.isContainsAtLeastTwoRecursive(inputValue)) {
                    cout << "There are 2 or more of " << inputValue << '\n';
                } else {
                    cout << "There is 1 or less of " << inputValue << '\n';
                }
            }   
        }
        cout << "Tree deepness ";
    }
    inFile.close();
}

void stdInputCase() // No obvious ways to unite std input and file input case
{
    cout << "Tree deepth ";
    int inputLevels;

    while (cin >> inputLevels && inputLevels >= 0)
    {
        cout << "Do the loop\n";
        BinTree<int> tree(inputLevels);

        string inputAddress = "empty";
        int inputValue = 0;

        while (inputValue != 0 || !(inputAddress.empty())) // empty exist because we need a way to call the first node
        {
            tree.addByTreeAddress(inputAddress, inputValue);
            tree.viewData();
            cout << "\nNode value and address (0 empty to stop input, empty for empty address) ";
            cin >> inputValue;
            cin >> inputAddress;
            if (inputAddress == "empty") { inputAddress = ""; }
            cout << "\ninputValue is " << inputValue;
            cout << "\ninputAddress is " << inputAddress << '\n';
        }

        cout << "\nValue to find, is there >= 2 of them ";
        if (cin >> inputValue)
        {
            if (inputValue <= 0)
            {
                cout << "inputValue can't be <= 0\n";
            }
            else
            {
                if (tree.isContainsAtLeastTwoRecursive(inputValue)) {
                    cout << "There are 2 or more of " << inputValue << '\n';
                } else {
                    cout << "There is 1 or less of " << inputValue << '\n';
                }
            }   
        }

        cout << "tree deepness ";
    }
}

void introductionMessageView()
{
    cout << "File input example: ./main -f test.txt\n\n";
    cout << "Examples of input see in inputExamples file\n";
    cout << "0 == empty node of tree\n";
    cout << "-1 in tree depth to exit\n";

    cout << "\n0 in address == left node\n1 == right node\n";
}

int main(int argc, char *argv[])
{
    cout << "\n\n\n";
    if (argc>= 2) // Arguments case
    {
        string flag(argv[1]);
        string path(argv[2]);
        if (flag.compare("-f") == 0)
            fileInputCase(path); // No obvious way to overload the function
        return 0;
    }
    introductionMessageView();
    stdInputCase();
    return 0;
}

