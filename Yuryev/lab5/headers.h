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

    Node() = default; // базовый конструктор (исп. для корня)
    Node(Node* parent): m_parent{parent}, m_number{(parent->m_number) - 2} // конструктор для NYT с родителем
    {};
    Node(Node* parent, char symbol): m_parent{parent}, m_symbol{symbol}, m_isNYT{false}, m_isLeaf{true}, m_number{(parent->m_number) - 1} // конструктор для листьев
    {};
};

void pushFirst(Node* a);
void deleteAllNodes();

std::string vitterCoder(char symbol);

#endif