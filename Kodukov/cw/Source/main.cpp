#include <limits>

#include "code.h"
#include "fanohuffman.h"

int main() { 
  std::string fname;
  auto buildFunc = buildCodeTreeFano;
  
  std::cout << "Input filename: ";
  std::cin >> fname;
  while (1) {
    char mode;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    system("cls");
    std::cout << "Choose mode:\n1 - fano\n2 - huffman\n";
    mode = getchar();
    if (mode == '1') {
      buildFunc = buildCodeTreeFano;
      break;
    } else if (mode == '2') {
      buildFunc = buildCodeTreeHuffman;
      break;
    } else {
      std::cout << "Wrong option";
      getchar();
    }
  }
  if (press(fname.data(), buildFunc)) {
    std::cout << "Compression complete!\n";
    if (depress(buildFunc)) std::cout << "Decompression complete!\n";
    else
      std::cout << "Decompression error\n";
  } else
    std::cout << "Compression error\n";
  system("pause");
}