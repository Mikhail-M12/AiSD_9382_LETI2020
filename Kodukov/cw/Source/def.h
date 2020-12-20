#ifndef DEF_H_
#define DEF_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
#include <set>
#include <cstdlib>
#include <queue>

typedef std::pair<std::string, long> Elem;

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
  void clear() {
    if (Node != nullptr) {
      if (Node->lt != nullptr) Node->lt->clear();
      if (Node->rt != nullptr) Node->rt->clear();
      delete Node;
      Node = nullptr;
    }
  }

  ~Tree() { clear(); }

  // left child getting function
  Tree *left() {
    if (Node == nullptr) {  // No node
      std::cout << "Error: left(null) \n";
      exit(1);
    } else
      return Node->lt;
  }

  // right child getting function
  Tree *right() {
    if (Node == nullptr) {
      std::cout << "Error: right(null) \n";
      exit(1);
    } else
      return Node->rt;
  }
  // Node pointer getting function
  node *nodePtr() {
    if (Node == nullptr) {
      std::cout << "Error: RootBT(null) \n";
      exit(1);
    } else
      return Node;
  }
  // Node data getting function
  Elem getNode() {
    if (Node == nullptr) {  // No node
      std::cout << "Error: RootBT(null) \n";
      exit(1);
    } else
      return Node->info;
  }
};

// Types
typedef std::map<unsigned char, long> ElemMap;
typedef std::vector<std::pair<unsigned char, long>> ElemArr;

#endif // DEF_H_