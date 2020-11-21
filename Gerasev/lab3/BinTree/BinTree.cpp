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
BinTree<T>::~BinTree()
{
    delete treeData;
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

template <typename T>
bool BinTree<T>::isHasAtLeastTwo(T value)
{
    int counter = 0;
    if (value == 0)
    {
        cout << "Error: Wrong value, can't be empty\n";
        raise(SIGILL);
    }

    for (int i=0; i < levelsToMasSize(levels); i++)
    {
        if (treeData[i] == value) counter++;
    }

    return (counter >= 2);
}

int main()
{
    cout << "tree deepness ";
    int inputLevels;
    cin >> inputLevels;

    BinTree<int> tree(inputLevels);

    string inputAddress = "empty";
    int inputValue = 0;

    while (inputValue != 0 || !(inputAddress.empty()))
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
    cin >> inputValue;

    if (tree.isHasAtLeastTwo(inputValue) == true)
    {
        cout << "There are 2 or more of " << inputValue << '\n';
    }

    cout << "There is 1 or less of " << inputValue << '\n';
    return 0;
}

