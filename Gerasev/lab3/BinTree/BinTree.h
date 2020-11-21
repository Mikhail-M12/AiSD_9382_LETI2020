#pragma once

#include <iostream>
#include <string.h>
#include <csignal>

using namespace std;

template <typename T>
class BinTree
{
private:
    int levels;
    T* treeData;

void addByTreeAddress(string address, int offset, T value);

public:
    BinTree(unsigned int levels);
    ~BinTree();
    void addByDataAddress(int address, T value);
    void addByTreeAddress(string address, T value);
    void viewData();
    bool isHasAtLeastTwo(T value);
};

int treeAddressToDataAddress(string address);