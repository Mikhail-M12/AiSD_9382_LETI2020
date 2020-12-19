#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// описывает узел дерева
class Node
{
public:
    // обеспечивают построение дерева Хаффмана с другими узлами
    Node* m_parent = nullptr;
    Node* m_right = nullptr;
    Node* m_left = nullptr;

    // характеристики узла
    unsigned int m_weight = 0; // вес узла
    unsigned int m_number = 187;
    char m_symbol = '\0'; // символ который хранится в листе
    bool m_isLeaf = false; // флаг листа (TRUE, если лист)
    bool m_isNYT = true; // является ли узел NYT
    int m_x = -1, m_y = -1;

    Node() = default; // базовый конструктор (исп. для корня)
    Node(Node* parent): m_parent{parent}, m_number{(parent->m_number) - 2} // конструктор для NYT с родителем
    {};
    Node(Node* parent, char symbol): m_parent{parent}, m_symbol{symbol}, m_isNYT{false}, m_isLeaf{true}, m_number{(parent->m_number) - 1} // конструктор для листьев
    {};
};

class PaintCell
{
public:
    char m_symbol = '#';
    int m_x = -1;
    int m_y = -1;
    int m_w = -1;
    PaintCell(char s, int x, int y, int w): m_symbol{s}, m_x{x}, m_y{y}, m_w{w}
    {}
};

void pushFirst(Node* a);
void deleteAllNodes();
void splitHafTree(Node* root, std::vector<Node*> *vec, short int level);
void paintTree(Node* root);
char identifySymbol(std::string ascii);
Node* findNextLeaf(std::string remainCode, int *count, Node* root);

std::string vitterCoder(char symbol);

#endif