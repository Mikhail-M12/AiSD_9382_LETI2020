#include <map>
#include <Windows.h>
#include <conio.h>
#include <sstream>

#include "code.h"

// Tree printing function
void print(Tree *q, long n, char path_to) {
  long i;
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

  if (q != nullptr) {
    print(q->right(), n + q->getNode().first.size() + 2, path_to);
    for (i = 0; i < n; i++)
      std::cout << " ";
    for (auto &c: q->getNode().first)
      if (c == path_to) {
        SetConsoleTextAttribute(h, WORD(1 << 4 | 12));
        break;
      }
    std::cout << "\\" << q->getNode().first << "\\\n";
    SetConsoleTextAttribute(h, WORD(1 << 4 | 14));
    print(q->left(), n + q->getNode().first.size() + 2, path_to);
  }
}

// Code building definitions

Code curCode;
std::map<unsigned char, Code> newCodes;

void buildCodes(Tree *T) {
  // No subtrees -> symbol found
  if (T->left() == nullptr && T->right() == nullptr) {
    unsigned char ch = T->getNode().first[0];
    if (curCode.len == 0) {
      curCode.bits[0] = 1;
      curCode.len = 1;
    }
    // Inserting new code
    newCodes.insert({ch, curCode});
    return;
  }
  // left subtree (0 to code)
  if (T->left() != NULL) {
    curCode.bits[curCode.len] = 0;
    curCode.len++;
    // Go left
    buildCodes(T->left());
    curCode.len--;
  }
  // right subtree (1 to code)
  if (T->right() != NULL) {
    curCode.bits[curCode.len] = 1;
    curCode.len++;
    // Go right
    buildCodes(T->right());
    curCode.len--;
  }
}

// Compare function for sorting
int comp(const std::pair<unsigned char, long> *i,
         const std::pair<unsigned char, long> *j) {
  if (i->second == j->second) return i->first - j->first;
  return j->second - i->second;
}

ElemArr curFreq;
Tree *T;
std::vector<bool> coded;

bool press(std::istream &input, Tree * (*buildCodeTree)(ElemArr curFreq, bool output)) {
  int ch;
  long long size1 = 0, size2 = 0;
  ElemMap freq;

  setlocale(LC_CTYPE, ".1251");
  std::ofstream outfile;
  if (T != nullptr) T->clear();
  curFreq.clear();
  // Counting Frequensies
  for (char ch = input.get(); ch != EOF; ch = input.get()) {
    size1++;
    auto iter = freq.find(ch);
    if (iter != freq.end())
      (*iter).second++;
    else
      freq.insert({ch, 1});
  }
  // Sorting frequencies
  curFreq.clear();
  curFreq = ElemArr(freq.begin(), freq.end());
  std::qsort(curFreq.data(), curFreq.size(),
             sizeof(std::pair<unsigned char, long>),
             (int (*)(const void *, const void *))comp);

  outfile.open("Files/pressed.txt", std::ios::binary);

  // Write label
  outfile << "CD!";
  outfile << (int)freq.size() << " ";
  // Write frequencies
  for (auto &i : curFreq) {
    outfile << i.first;
    outfile.write(reinterpret_cast<char *>(&i.second), sizeof(long));
  }
  // Building code tree
  T = buildCodeTree(curFreq, false);
  // Building new codes
  newCodes.clear();
  curCode.len = 0;
  buildCodes(T);
  
  /*** Passing through the file second time ***/
  // Coding input data to output file
  input.clear();
  input.seekg(input.beg);
  unsigned char bitAccum = 0;
  int bitPos = 7;
  coded.clear();
  for (ch = input.get(); ch != EOF; ch = input.get()) {
    for (int k = 0; k < newCodes[ch].len; k++) {
      int bit = newCodes[ch].bits[k] << bitPos--;
      coded.push_back(bit);
      bitAccum |= bit;
      // Writing byte
      if (bitPos < 0) {
        size2++;
        outfile << bitAccum;
        bitAccum = 0;
        bitPos = 7;
      }
    }
  }
  if (bitPos < 7) outfile << bitAccum, size2++;

  outfile.close();
  return true;
}

long long size;

// Decompress function
bool depress(Tree *(*buildCodeTree)(ElemArr curFreq, bool output)) {
  std::ifstream infile("Files/pressed.txt", std::ios::binary);
  std::ofstream outfile;
  if (!infile.is_open()) {
    std::cout << "Impossible to open file\n";
    return false;
  }
  setlocale(LC_ALL, "Russian");
  // Check label
  char label[4];
  infile.read(label, 3);
  label[3] = '\0';
  if (strcmp(label, "CD!") != 0) {
    infile.close();
    std::cout << "Wrong pressed file\n";
    return false;
  }
  // Read frequencies
  int cnt;

  size = 0;
  infile >> cnt;
  infile.get();
  ElemMap freq;
  for (int i = 0; i < cnt; i++) {
    unsigned char ch, numstr[4];
    unsigned long num = 0;
    ch = infile.get();
    for (int i = 0; i < 4; i++) numstr[3 - i] = infile.get();
    for (int i = 0; i < 4; i++) {
      num <<= 8;
      num |= numstr[i];
    }
    freq.insert({ch, num});
    size += num;
  }
  // Sort frequencies
  Tree *tree, *start;
  ElemArr curFreq(freq.begin(), freq.end());
  std::qsort(curFreq.data(), curFreq.size(), sizeof(curFreq[0]),
             (int (*)(const void *, const void *))comp);
  // Building code tree
  tree = buildCodeTree(curFreq, false);

  start = tree;
  // Reading coded data
  outfile.open("Files/decompressed.txt");
  int ch, bitPos = -1, res = 0;
  unsigned char bitAccum;
  bool isfirst = true, isstart = true;
  long num = 0;
  while (1) {
    // Leaf -> symbol
    if (!isfirst && tree->left() == NULL) {
      if (isstart && !res) break;
      // Write symbol, go to tree start
      unsigned char ch = (unsigned char)tree->getNode().first[0];
      outfile << ch;
      num++;
      if (num == size) break;
      tree = start;
      isstart = true;
    }
    if (isfirst) isfirst = false;
    // Get new byte
    if (bitPos < 0) {
      ch = infile.get();
      if (ch == EOF) break;
      bitAccum = ch;
      bitPos = 7;
    }
    // 0 - go left, 1 - go right
    res = (bitAccum >> bitPos--) & 1;
    if (res && (tree->right() != nullptr)) {
      tree = tree->right();
      isstart = false;
    } else if (tree->left() != nullptr) {
      isstart = false;
      tree = tree->left();
    }
  }
  infile.close();
  outfile.close();

  return true;
}