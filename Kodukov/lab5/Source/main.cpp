#include <algorithm>
#include "fano.h"

typedef int Symbol;

void sort(Symbol *symbols, size_t size) {
  std::vector<Symbol> data;
  for (int i = 0; i < size; i++) data.push_back(symbols[i]);
  std::sort(data.begin(), data.end());
}

int main() { 
  std::string fname;
  
  std::cout << "Input filename: ";
  std::cin >> fname;
  if (Press(fname.data())) {
    std::cout << "Compression complete!\n";
    if (Depress()) std::cout << "Decompression complete!\n";
    else
      std::cout << "Decompression error\n";
  } else
    std::cout << "Compression error\n";
  system("pause");
}