#ifndef UNTITLED15_BINKOR_H
#define UNTITLED15_BINKOR_H

#endif //UNTITLED15_BINKOR_H

#ifndef BINKOR_H
#define BINKOR_H
#include "iostream"
#include "fstream"
#include "cctype"
#include "string"
#include "BinKor.h"

using namespace std;
struct BinKor;
struct Weight{
BinKor* binKor = nullptr;
bool isBinKor;
int weight;
Weight() = default;
Weight(int weight)
        {
                isBinKor = false;
                this->weight = weight;
        }
Weight(BinKor* binkor)
{
this->weight = 0; 
this->isBinKor = true;
this->binKor = binkor;
}
~Weight();
};

struct Edge
{
    int length;
    Weight* weight;

    Edge() = default;

    Edge(int length, Weight* weight)
    {
        this->length = length; this->weight = weight;
    }
    ~Edge()
    {
        delete weight;
    }
};

struct BinKor
{
    Edge* leftEdge = nullptr; Edge* rightEdge = nullptr;

    BinKor() = default;
    BinKor(Edge* leftEdge, Edge* rightEdge)
    {
        this->leftEdge = leftEdge; this->rightEdge = rightEdge;
    }

    ~BinKor()
    {
        delete leftEdge; delete rightEdge;}
};

bool Parser(string inputString, int& curPosition, BinKor* binkor); bool BinKorParse(string inputString, int& curPosition, BinKor* binkor);
bool EdgeParse(string inputString, int& curPosition, Edge* edge); int Value(string stingValue);
bool WeightParser(string inputString, int& curPosition, Weight* weight);
bool Balanced(const BinKor* binkor, int count); int WeightFunc(BinKor* binKor);

#endif
