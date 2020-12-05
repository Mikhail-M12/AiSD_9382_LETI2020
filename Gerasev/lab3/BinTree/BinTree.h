#pragma once

#include <iostream>
#include <string.h>
#include <csignal>
#include <fstream>

using namespace std;

template <typename T>
class BinTree
{
private:
    int levels;
    T* treeData;

void addByTreeAddress(string address, int offset, T value);


public:
    BinTree(unsigned int levels = 0);
    BinTree(const BinTree<T> & binTree);
    ~BinTree();
    void addByDataAddress(int address, T value);
    void addByTreeAddress(string address, T value);
    void viewData();
    
    int howManyRecursiveHandler(int node, T value);
    int howManyRecursive(T value);

    bool isContainsAtLeastTwoRecursive(T value);};

int treeAddressToDataAddress(string address);