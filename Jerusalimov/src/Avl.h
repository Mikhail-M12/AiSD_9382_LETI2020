//
// Created by niki_ on 15.12.2020.
//

#ifndef ALGOS5_AVL_H
#define ALGOS5_AVL_H

#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <Windows.h>
using namespace std;

class TREE
{
private:


    int Key;
    int height;

    TREE *Left;
    TREE *Right;
public:
    TREE *duk; //Корень дерева.
    TREE(int k) {
        duk = nullptr;
        Left = nullptr;
        Right = nullptr;
        height = 1;
        Key = k;
    }
    TREE() {
        duk = nullptr;
        Left = nullptr;
        Right = nullptr;
        height = 1;
    }
    ~TREE(){
        delete this;
    }
    TREE* rotateLeft(TREE * node,int n);
    TREE* rotateRight(TREE * node,int n);

    TREE **GetDuk() { return &duk; }
    int Height(TREE** p){
        return (*p)?(*p)->height:0;
    }
    TREE* balance(TREE* p, int n);

    int balanceFactor(TREE** p){
        // cout<< Height(&((*p)->Right)) <<"-"<< Height(&((*p)->Left)) <<" = "<< int(Height(&((*p)->Right)) - Height(&((*p)->Left)))<<"\n";
        return Height(&((*p)->Right))-Height(&((*p)->Left));
    }

    void fixHeight(TREE** p){
        int hl = Height(&((*p)->Left));
         int hr = Height(&((*p)->Right));
        (*p)->height = (hl>hr?hl:hr)+1;
    }
    TREE* findmin(TREE* p) // поиск узла с минимальным ключом в дереве p
    {
        return p->Left?findmin(p->Left):p;
    }

    TREE* removemin(TREE* p,int n) // удаление узла с минимальным ключом из дерева p
    {
        if( p->Left==nullptr )
            return p->Right;
        p->Left = removemin(p->Left,n);
        return balance(p,n);
    }


    void Search(int num, int* count);
    TREE* Insert(int n,TREE** node, int newKey,int prevKey);
    TREE* popElem(int n,TREE* p, int k);



    void Tree (int, TREE **,char side,int depth, int parrent);
    void TreeFromFile (int n,TREE **p,ifstream& in,char side,int depth,int parrent);

    void print1(TREE ** root, short x, short y, short a, char c);
    void printDepth(int depth);
    void Vyvod (TREE **, int);
    void Start();
};

#endif //ALGOS5_AVL_H
