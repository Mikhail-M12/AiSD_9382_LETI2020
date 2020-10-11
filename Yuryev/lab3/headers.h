#ifndef HEADERS_H
#define HEADERS_H
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class BTree
{
private:
public:
    BTree* m_l_tree = nullptr;
    BTree* m_r_tree = nullptr;
    T m_BTroot = '\0';

    BTree* get_left() {return m_l_tree;};
    BTree* get_right() {return m_r_tree;};
    T get_BTroot() {return m_BTroot;};
};

#include "funcs.inl" 
#include "my_funcs.inl"
#endif