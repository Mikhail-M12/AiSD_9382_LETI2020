#ifndef __TREE_H
#define __TREE_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <queue>

template <class Elem>
class Tree {
 public:
  struct node {
    Elem info;
    Tree *lt;
    Tree *rt;

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
   node *Node = nullptr;

 public:
  Tree() {}

  Tree(node *N) {
    Node = N;
  }

  void Clear() {
    if (Node != nullptr) {
      if (Node->lt != nullptr) Node->lt->Clear();
      if (Node->rt != nullptr) Node->rt->Clear();
      delete Node;
      Node = nullptr;
    }
  }

  ~Tree() { Clear(); }

  Tree *Left() {
    if (Node == nullptr) {
      std::cout << "Error: Left(null) \n";
      exit(1);
    } else
      return Node->lt;
  }

  Tree *Right() {
    if (Node == nullptr) {
      std::cout << "Error: Right(null) \n";
      exit(1);
    } else
      return Node->rt;
  }
  node *NodePtr() {
    if (Node == nullptr) {
      std::cout << "Error: RootBT(null) \n";
      exit(1);
    } else
      return Node;
  }
  Elem GetNode() {
    if (Node == nullptr) {
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
    if (cur > max || cur < min) {
      std::cout << "false\n";
      return false;
    }
    std::cout << "true\n";
    // Check left subtree
    if (Left() != nullptr) {
      for (int i = 0; i < lvl; i++) std::cout << "  ";
      std::cout << "Check left: (max -> " << cur << ")\n";
      // max -> cur
      L = Left()->CheckSearchTree(min, cur, lvl + 1);
    }
    if (!L)
      return false;
    // Check right subtree
    if (Right() != nullptr) {
      for (int i = 0; i < lvl; i++) std::cout << "  ";
      std::cout << "Check right: (min -> " << cur << ")\n";
      // min -> cur
      R = Right()->CheckSearchTree(cur, max, lvl + 1);
    }
    if (!R) 
      return false;
    return true;
  }
  // Checking if the tree is a pyramid tree
  bool CheckPyramidTree() {
    std::queue<Tree<Elem> *> q;

    // Push root
    q.push(this);
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
      Tree<Elem> *cur = q.front();
      q.pop();
      std::cout << "  Element:" << cur->GetNode() << "\n";
      bool L = false, R = false;
      // Check left
      if (cur->Left() != nullptr) {
        std::cout << "  Left: " << cur->GetNode()
                  << " >= " << cur->Left()->GetNode()
                  << " ? ";
        L = cur->GetNode() >= cur->Left()->GetNode();
        std::cout << (L ? "true" : "false") << "\n";
        if (!L)
          return false;
        q.push(cur->Left());
      }
      // Check right
      if (cur->Right() != nullptr) {
        std::cout << "  Right: " << cur->GetNode()
                  << " >= " << cur->Right()->GetNode() << " ? ";
        R = cur->GetNode() >= cur->Right()->GetNode();
        std::cout << (R ? "true" : "false") << "\n";
        if (!R) return false;
        q.push(cur->Right());
      }
      std::cout << "\n";
    }
    return true;
  }
};
#endif // __TREE_H