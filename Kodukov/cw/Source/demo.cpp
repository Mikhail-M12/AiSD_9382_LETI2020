#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <sstream>

#include "demo.h"
#include "code.h"

void PrintStatistics() {
  system("cls");
  std::cout << "Frequencies:\n";
  for (auto &i : curFreq)
    std::cout << (unsigned char)i.first << "-" << i.second << ";";
  std::cout << "\n\n";
  _getch();
}

void PrintCodeBuilding() {
  for (auto &code : newCodes) {
    system("cls");
    std::cout << code.first << ": ";
    for (int i = 0; i < code.second.len; i++)
      std::cout << (int)code.second.bits[i];
    std::cout << "\n";
    print(T, 0, code.first);
    char ch = _getch();
    if (ch == 27) return;
  }
}

void PrintTreeBuilding(Tree *(*buildCodeTree)(ElemArr curFreq, bool output)) {
  system("cls");
  T->clear();
  T = buildCodeTree(curFreq, true);
  _getch();
  print(T, 0, 0);
  _getch();
}

void PrintDecoding() {
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
  bool isfirst = true, isstart = true, res = false;
  long num = 0;
  Tree *start = T;
  long long cnt = 0, symstart = 0;
  std::string curres;

  while (1) {
    // Leaf -> symbol
    if (!isfirst && T->left() == NULL) {
      if (isstart && !res) break;
      unsigned char ch = (unsigned char)T->getNode().first[0];
      system("cls");
      for (size_t i = 0; i < coded.size(); i++) {
        if (i >= symstart && i < cnt) {
          SetConsoleTextAttribute(h, WORD(1 << 4 | 12));
          while (i >= symstart && i < cnt) std::cout << coded[i++];
          SetConsoleTextAttribute(h, WORD(1 << 4 | 14));
          i--;
        } else
          std::cout << coded[i];
      }
      std::cout << "\n";
      print(start, 0, ch);
      std::cout << "\nSymbol: " << ch << "\n";
      curres.push_back(ch);
      std::cout << "Current string: " << curres << "\n";
      char symbol = _getch();
      if (symbol == 27) break;
      num++;
      if (num == size) break;
      T = start;
      isstart = true;
      symstart = cnt;
    }
    if (isfirst) isfirst = false;
    // 0 - go left, 1 - go right
    res = coded[cnt++];
    if (res && (T->right() != nullptr)) {
      isstart = false;
      T = T->right();
    } else if (T->left() != nullptr) {
      isstart = false;
      T = T->left();
    }
  }
  T = start;
}