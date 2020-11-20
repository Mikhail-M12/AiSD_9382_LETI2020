#include "fano.h"

int main() { 
  std::string fname;
  
  std::cout << "Input filename: ";
  std::cin >> fname;
  if (press(fname.data())) {
    std::cout << "Compression complete!\n";
    if (depress()) std::cout << "Decompression complete!\n";
    else
      std::cout << "Decompression error\n";
  } else
    std::cout << "Compression error\n";
  system("pause");
}