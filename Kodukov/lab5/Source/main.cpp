#include <algorithm>
#include "fano.h"

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