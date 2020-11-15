#ifndef WEAK_HEAP_H
#define WEAK_HEAP_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <cstring>
#include <cmath>

class WeakHeap{     
        
public:

    std::vector <int> wheap;
    int size;
    unsigned char* r=nullptr;
    int s;
    WeakHeap(){}
    WeakHeap(int, std::istream&);

    void displayArray();
    void displayHeap(int i, int j, int col, int num);
    void displayHeap();
    void weakHeapMerge(unsigned char *r, int i, int j, int num);
    void weakHeapSort();
    WeakHeap* fileInputHeap();
    WeakHeap* consoleInputHeap();
    ~WeakHeap();

};

#endif