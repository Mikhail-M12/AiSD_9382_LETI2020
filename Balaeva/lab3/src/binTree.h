#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

class binTree {
public:
  struct node {
    char info;
    int lt;
    int rt;
    node(int inputlt = 0, int inputrt = 0) : lt(inputlt), rt(inputrt) {};
  };
  node *arr;
  binTree(int len = 100) {
    arr = new node[len];
    for(int i = 0; i < len-1; i++){
      arr[i].lt = i+1;
    }
    arr[len].lt = 0;
  }
  bool isNull(int b) {
    return (b == 0);
  }
  char RootBT(int b) {
    if (isNull(b)) { 
      cerr << "Error: RootBT(null) \n";
      return 0;
    }
    else return arr[b].info;
  }
  int Left(int b) {
    if (isNull(b)) { 
      cerr << "Error: Left(null) \n"; 
      return 0;
    }
    else return arr[b].lt;
  }
  int Right(int b) {
    if (isNull(b)) { 
      cerr << "Error: Right(null) \n"; 
      return 0;
    }
    else return arr[b].rt;
  }
  int ConsBT(char b) {
    int p = arr[0].lt;
    arr[0].lt = arr[p].lt;
    arr[p].info = b;
    arr[p].lt = 0;
    arr[p].rt = 0;
    return p;
  }
  ~binTree() {
    delete[] arr;
  }
};
