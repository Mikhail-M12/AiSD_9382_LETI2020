/* Kodukov Aleksabdr 9382, v. 18d */

#include <conio.h>

#include "tree.h"

template <typename Elem>
Tree<Elem> *Read(std::istream &f) {
  char ch;
  bool neg = false, num = false;
  Elem e = 0;
  Tree<Elem> *p, *q;

  f >> ch;
  int d = 0;
  if (ch == '-') {
    f >> ch;
    neg = true;
  }
  while (ch >= '0' && ch <= '9') {
    num = true;
    e = e * 10 + (ch - '0') * (pow(-1, neg));
    f >> ch;
  }
  if (neg && !num)
    return nullptr;
  if (ch == '/')
    return nullptr;
  else {
    p = Read<Elem>(f);
    q = Read<Elem>(f);
    typename Tree<Elem>::node *N = new typename Tree<Elem>::node(e, p, q);
    return new Tree<Elem>(N);
  }
}

template <typename Elem>
void Print(Tree<Elem> *q, long n) {
  long i;
  if (q != nullptr) {
    Print<Elem>(q->Right(), n + 5);
    for (i = 0; i < n; i++) 
      std::cout << " ";
    std::cout << q->GetNode() << "\n";
    Print<Elem>(q->Left(), n + 5);
  }
}

int main() {
  bool m;
  Tree<int> *t = nullptr;
  
  while (1) {
    char mode;

    system("cls");
    std::cout << "Choose mode:\n1 - console input\n2 - file input\n";
    mode = _getch();
    if (mode == '1') {
      m = false;
      break;
    } else if (mode == '2') {
      m = true;
      break;
    } else {
      std::cout << "Wrong option";
      _getch();
    }
  }
  system("cls");
  if (m) {
    char s[200];
    std::ifstream f("Tests/input.txt");
    f.getline(s, 200);
    if (f.is_open()) {
      std::cout << "File input: " << s;
      f.close();
      f = std::ifstream("Tests/input.txt");
      t = Read<int>(f);
      f.close();
    }
  } else {
    t = Read<int>(std::cin);
  }
  std::cout << "\n";

  if (t != nullptr) {
    Print(t, 0);
    std::cout << "Check search:\n";
    bool Search = t->CheckSearchTree(-INFINITY, INFINITY, 1);
    std::cout << "Search: " << (Search ? "true" : "false") << "\n\n";
    std::cout << "Check pyramid:\n";
    bool Pyramid = t->CheckPyramidTree();
    std::cout << "Pyramid: " << (Pyramid ? "true" : "false") << "\n";
    t->Clear();
  } else
    std::cout << "Wrong input";
}