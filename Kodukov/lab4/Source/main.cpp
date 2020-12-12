#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void PrintArray(int *A, int size, int left, int right, int lvl) {
  for (int i = 0; i < lvl; i++) std::cout << "  ";
  for (int k = 0; k < size; k++)
    std::cout << (k == left ? "|" : "") << A[k] << (k == right ? "| " : " ");
  if (right == size) std::cout << "|";
  std::cout << "\n";
}

void QuickSort(int *A, int size, int lvl) {
  long i = 0, j = size - 1;  // set pointers
  int temp, p;

  p = A[size / 2];  // pivot element

  for (int i = 0; i < lvl; i++) std::cout << "  ";
  std::cout << "Pivot: " << p << "\n";

  bool done = false;
  while (!done) {
    // move left pointer
    while (i <= j && A[i] < p) {
      PrintArray(A, size, i, j, lvl);
      i++;
    }
    // move right pointer
    while (i <= j && A[j] > p) {
      PrintArray(A, size, i, j, lvl);
      j--;
    }

    for (int k = 0; k < lvl; k++) std::cout << "  ";
    for (int k = 0; k < size; k++)
      std::cout << (k == i ? "|" : "") << A[k] << (k == j ? "| " : " ");

    if (A[i] != A[j] && i != j) {
      if (j < i) {
        std::cout << "\n";
        done = true;
      }
      // swap elements
      else {
        std::cout << "swap(" << A[i] << ", " << A[j] << ")\n";
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
      }
    } else {
      j--, i++;
      done = true;
      std::cout << "\n";
    }
  }
  if (j > 0) QuickSort(A, j + 1, lvl + 1);
  if (size > i) QuickSort(A + i, size - i, lvl + 1);
}

std::vector<int> Read(std::istream &s) {
  std::vector<int> v;
  std::string str;
  std::getline(s, str);
  int n = 0;
  bool passed = false;
  bool neg = false;
  for (auto &ch : str) {
    if (ch == '-') {
      if (!passed) {
        std::cout << "Wrong input";
        return std::vector<int>({});
      }
      neg = true;
    }
    else if (ch == ' ') {
      if (neg) n *= -1;
      v.push_back(n);
      passed = true;
      neg = false;
      n = 0;
    } else if (ch <= '9' && ch >= '0'){
      n = n * 10 + ch - '0';
      passed = false;
    }
    else {
      std::cout << "Wrong input";
      return std::vector<int>({});
    }
  }
  if (!passed) {
    if (neg) n *= -1;
    v.push_back(n);
  }
  return v;
}

int main() { 
  std::vector<int> v;
  bool m;
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
      f.seekg(0, std::ios_base::beg);
      v = Read(f);
      f.close();
    }
  } else {
    v = Read(std::cin);
  }
  std::cout << "\n";
  if (!v.empty()) {
    std::vector<int> v1 = v, v2 = v;
    QuickSort(v1.data(), v1.size(), 0);
    std::cout << "\nSorted:  ";
    PrintArray(v1.data(), v1.size(), -1, -1, 0);
    std::sort(v2.begin(), v2.end());
    std::cout << "Control: ";
    PrintArray(v2.data(), v2.size(), -1, -1, 0);
    if (v1 == v2) 
      std::cout << "Sorting is correct";
    else
      std::cout << "Wrong sorting";
  }
  _getch();
  return 30;
}