#ifndef __TREE_H
#define __TREE_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <queue>

template <class Elem>
class Tree {
 public:
  // Tree node structure
  struct node {
    Elem info; // Node data
    Tree *lt, *rt; // Node childs

    node() {
      lt = nullptr;
      rt = nullptr;
    }

    node(const Elem &x, Tree *lst, Tree *rst) {
      info = x;
      lt = lst;
      rt = rst;
    }
  };

 private:
   node *Node = nullptr; // Tree root

 public:
  Tree() {}

  Tree(node *N) {
    Node = N;
  }

  // Tree memory clear function
  void Clear() {
    if (Node != nullptr) {
      if (Node->lt != nullptr) Node->lt->Clear();
      if (Node->rt != nullptr) Node->rt->Clear();
      delete Node;
      Node = nullptr;
    }
  }

  ~Tree() { Clear(); }

  // Left child getting function
  Tree *Left() {
    if (Node == nullptr) { //No node
      std::cout << "Error: Left(null) \n";
      exit(1);
    } else
      return Node->lt;
  }

  // Right child getting function
  Tree *Right() {
    if (Node == nullptr) {
      std::cout << "Error: Right(null) \n";
      exit(1);
    } else
      return Node->rt;
  }
  // Node pointer getting function
  node *NodePtr() {
    if (Node == nullptr) {
      std::cout << "Error: RootBT(null) \n";
      exit(1);
    } else
      return Node;
  }
  // Node data getting function
  Elem GetNode() {
    if (Node == nullptr) { // No node
      std::cout << "Error: RootBT(null) \n";
      exit(1);
    } else
      return Node->info;
  }
  // Checking if the tree is a binary search tree
  bool CheckSearchTree(float min, float max, int lvl) {
    bool L = true, R = true;
    Elem cur = GetNode();

    std::cout << "\n";
    for (int i = 0; i < lvl; i++) std::cout << "  ";
    std::cout << "ELEMENT: " << cur << "\n";

    for (int i = 0; i < lvl; i++) std::cout << "  ";
    std::cout << min << "(min)" << " <= " << cur << " <= " << max << "(max)" << " ? ";
    // Check current node
    if (cur > max || cur < min) { // Tree isn't BST
      std::cout << "false\n";
      return false;
    }
    std::cout << "true\n";
    // Check left subtree
    if (Left() != nullptr) {
      for (int i = 0; i < lvl; i++) std::cout << "  ";
      std::cout << "Check left: (max -> " << cur << ")\n";
      // max -> cur
      L = Left()->CheckSearchTree(min, cur, lvl + 1); // Continue checking left subtree
    }
    if (!L) // Left subtree isn't BST
      return false;
    // Check right subtree
    if (Right() != nullptr) {
      for (int i = 0; i < lvl; i++) std::cout << "  ";
      std::cout << "Check right: (min -> " << cur << ")\n";
      // min -> cur
      R = Right()->CheckSearchTree(cur, max, lvl + 1); // Continue checking right subtree
    }
    if (!R) // Right subtee isn't BST
      return false;

    return true; // Current tree is BST
  }

  // Checking if the tree is a pyramid tree
  bool CheckPyramidTree() {
    std::queue<Tree<Elem> *> q; // Nodes queue

    // Push root
    q.push(this);
    //iterative breadth-first traversal
    while (!q.empty()) {
      //Print queue
      std ::cout << "  Queue: ";
      std::queue<Tree<Elem> *> t = q;
      while (!t.empty()) {
        std::cout << t.front()->GetNode() << " ";
        t.pop();
      }
      std ::cout << "\n";

      // Check current node
      Tree<Elem> *cur = q.front(); // Get node from queue
      q.pop();
      std::cout << "  Element:" << cur->GetNode() << "\n";
      bool L = false, R = false;
      // Check left
      if (cur->Left() != nullptr) {
        std::cout << "  Left: " << cur->GetNode()
                  << " >= " << cur->Left()->GetNode()
                  << " ? ";
        L = cur->GetNode() >= cur->Left()->GetNode(); // Compare current node and left child
        std::cout << (L ? "true" : "false") << "\n";
        if (!L) return false; // Left node false state
        q.push(cur->Left()); // Push node to queue
      }
      // Check right
      if (cur->Right() != nullptr) {
        std::cout << "  Right: " << cur->GetNode()
                  << " >= " << cur->Right()->GetNode() << " ? ";
        R = cur->GetNode() >= cur->Right()->GetNode(); // Compare current node and right child
        std::cout << (R ? "true" : "false") << "\n";
        if (!R) return false; // Right node false state
        q.push(cur->Right()); // Push node to queue
      }
      std::cout << "\n";
    }
    return true; // Tree is pyramid
  }
};
#endif // __TREE_H