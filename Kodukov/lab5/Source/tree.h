#ifndef TREE_H_
#define TREE_H_

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>

typedef std::string Elem;

class Tree {
 public:
  // Tree node structure
  struct node {
    Elem info; // Node data
    Tree *lt, *rt;  // Node childs

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
  node *Node = nullptr;  // Tree root

 public:
  Tree() {}

  Tree(node *N) { Node = N; }

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
    if (Node == nullptr) {  // No node
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
    if (Node == nullptr) {  // No node
      std::cout << "Error: RootBT(null) \n";
      exit(1);
    } else
      return Node->info;
  }
};

#endif // TREE_H_