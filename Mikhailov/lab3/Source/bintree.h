#ifndef bintree_hpp
#define bintree_hpp

#include <stdio.h>
#include<iostream>
#include <cmath>
#include<vector>
#include<string>




struct Node
{

    std::string data = "";
    Node* left = nullptr;
    Node* right = nullptr;

};

class BinTree
{
private:
    Node* Current = nullptr;
    std::string data;
public:
    Node* Head = nullptr;
    BinTree();
    Node* createTree(std::vector<std::string> tokens);
    int max_depth(Node *hd);
    int getFullWeight(Node *hd, int now = 0);
};


#endif /* bintree_hpp */