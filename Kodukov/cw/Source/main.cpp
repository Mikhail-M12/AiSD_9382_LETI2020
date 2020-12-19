#include <limits>
#include <conio.h>
#include <Windows.h>
#include <sstream>

#include "fanohuffman.h"
#include "demo.h"

void ShowMenu(Tree *(*buildCodeTree)(ElemArr curFreq, bool output)) {
  while (1) {
    char choise;
    system("cls");
    std::cout << "Choose item:\n1 - Statistics\n2 - Tree building\n3 - Code building\n4 - Decoding\n";
    choise = _getch();
    switch (choise) {
      case '1':
        PrintStatistics();
        break;
      case '2':
        PrintTreeBuilding(buildCodeTree);
        break;
      case '3': 
        PrintCodeBuilding();
        break; 
      case '4':
        PrintDecoding();
        break;
      case 27:
        return;
      default:
        std::cout << "Wrong option\n ";
        system("pause");
    }
  }
}

int main() { 
  std::string str;
  auto buildFunc = buildCodeTreeFano;
  bool exitmode;
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(h, WORD(1 << 4 | 14));

  while (1) {
    system("cls");
    std::cout << "Input filename or string (if its not file name): ";
    std::cin >> str;
    std::ifstream file;
    while (1) {
      exitmode = false;
      while (1) {
        char mode;
        system("cls");
        std::cout << "Choose mode:\n1 - fano\n2 - huffman\n";
        mode = _getch();
        if (mode == '1') {
          buildFunc = buildCodeTreeFano;
          break;
        } else if (mode == '2') {
          buildFunc = buildCodeTreeHuffman;
          break;
        } 
        else if (mode == 27) {
          exitmode = true;
          break;
        }
        else {
          std::cout << "Wrong option";
          _getch();
        }
      }
      if (exitmode)
        break;
      bool isok = false;
      file.open(str);
      if (file.is_open()) {
        isok = press(file, buildFunc);
        file.close();
      }
      else {
        std::stringstream ss(str);
        isok = press(ss, buildFunc);
      }
      if (isok) {
        if (depress(buildFunc)) ShowMenu(buildFunc);
        else std::cout << "Decompression error\n";
      } else std::cout << "Compression error\n";
    }
  }
}