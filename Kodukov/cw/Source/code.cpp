#include <map>

#include "code.h"

// Tree printing function
void print(Tree *q, long n, std::ofstream &f) {
  long i;
  if (q != nullptr) {
    print(q->right(), n + q->getNode().first.size() + 2, f);
    for (i = 0; i < n; i++) {
      std::cout << " ";
      f << " ";
    }
    std::cout << "\\" << q->getNode().first << "\\\n";
    f << "\\" << q->getNode().first << "\\\n";
    print(q->left(), n + q->getNode().first.size() + 2, f);
  }
}

// Code building definitions
struct Code {
  bool bits[50];
  int len = 0;
};
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
    newCodes.insert({ch, curCode});
    return;
  }
  // left subtree (0 to code)
  if (T->left() != NULL) {
    curCode.bits[curCode.len] = 0;
    curCode.len++;
    buildCodes(T->left());
    curCode.len--;
  }
  // right subtree (1 to code)
  if (T->right() != NULL) {
    curCode.bits[curCode.len] = 1;
    curCode.len++;
    buildCodes(T->right());
    curCode.len--;
  }
}

int comp(const std::pair<unsigned char, long> *i,
         const std::pair<unsigned char, long> *j) {
  if (i->second == j->second) return i->first - j->first;
  return j->second - i->second;
}

bool press(const char *filename, Tree * (*buildCodeTree)(ElemArr curFreq, bool output, std::ofstream &info)) {
  int ch;
  long long size1 = 0, size2 = 0;
  ElemMap freq;
  bool output = false;

  std::cout << "Pressing file " << filename << "\n";
  setlocale(LC_CTYPE, ".1251");
  std::ifstream infile(filename, std::ios::in);
  if (!infile.is_open()) {
    std::cout << "Impossible to open file\n";
    return false;
  }
  std::ofstream outfile, info;
  // Counting Frequensies
  while ((ch = infile.get()) != EOF) {
    size1++;
    auto iter = freq.find(ch);
    if (iter != freq.end())
      (*iter).second++;
    else
      freq.insert({ch, 1});
  }
  // Sorting frequencies
  ElemArr curFreq(freq.begin(), freq.end());
  std::qsort(curFreq.data(), curFreq.size(),
             sizeof(std::pair<unsigned char, long>),
             (int (*)(const void *, const void *))comp);

  outfile.open("Files/pressed.txt", std::ios::binary);

  info.open("Files/info.txt");
  output = size1 < 100;

  // Write label
  outfile << "CD!";
  outfile << (int)freq.size();
  if (output) {
    std::cout << "Frequencies:\n";
    info << "Frequencies:\n";
  }
  // Write frequencies
  for (auto &i : curFreq) {
    if (output) {
      std::cout << (unsigned char)i.first << "-" << i.second << ";";
      info << (unsigned char)i.first << "-" << i.second << ";";
    }
    outfile << i.first;
    outfile.write(reinterpret_cast<char *>(&i.second), sizeof(long));
  }
  if (output) {
    std::cout << "\n\n";
    info << "\n\n";
  }
  // Building code tree
  if (output) {
    std::cout << "Building code tree: \n";
    info << "Building code tree: \n";
  }
  Tree *T = buildCodeTree(curFreq, output, info);
  if (output) {
    std::cout << "\n";
    info << "\n";
  }
  // Building new codes
  buildCodes(T);

  // Printing tree

  if (output) {
    std::cout << "Tree:\n";
    info << "Tree:\n";
    print(T, 0, info);
    std::cout << "\n";
    info << "\n";
  }
  T->clear();
  // Printing codes
  std::cout << "Codes:\n";
  info << "Codes:\n";
  for (auto &c : newCodes) {
    std::cout << c.first << ":";
    info << c.first << ":";
    for (int i = 0; i < c.second.len; i++) {
      std::cout << (int)c.second.bits[i];
      info << (int)c.second.bits[i];
    }
    std::cout << "\n";
    info << "\n";
  }
  std::cout << "\n";
  info << "\n";
  
  /*** Passing through the file second time ***/
  // Coding input data to output file
  infile.seekg(infile.beg);
  unsigned char bitAccum = 0;
  int bitPos = 7;
  infile.close();
  infile.open(filename);
  if (output) {
    std::cout << "Coded data: \n";
    info << "Coded data: \n";
  }
  while ((ch = infile.get()) != EOF) {
    for (int k = 0; k < newCodes[ch].len; k++) {
      int bit = newCodes[ch].bits[k] << bitPos--;
      if (output) {
        std::cout << (int)newCodes[ch].bits[k];
        info << (int)newCodes[ch].bits[k];
      }
      bitAccum |= bit;
      // Writing byte
      if (bitPos < 0) {
        size2++;
        outfile << bitAccum;
        bitAccum = 0;
        bitPos = 7;
      }
    }
    if (output) {
      std::cout << " ";
      info << " ";
    }
  }
  if (output) {
    std::cout << "\n";
    info << "\n";
  }
  if (bitPos < 7) outfile << bitAccum, size2++;
  std::cout << "Input size: " << size1
            << "\nPressed size(pure input data): " << size2 << "\n";
  info << "Input size: " << size1
            << "\nPressed size(pure input data): " << size2 << "\n";

  info.close();
  infile.close();
  outfile.close();
  return true;
}

// Decompress function
bool depress(Tree *(*buildCodeTree)(ElemArr curFreq, bool output, std::ofstream &info)) {
  std::ifstream infile("Files/pressed.txt", std::ios::binary);
  std::ofstream outfile, info("Files/info.txt", std::ios::app);
  if (!infile.is_open()) {
    std::cout << "Impossible to open file\n";
    return false;
  }
  std::cout << "Decompressing file pressed.txt\n";
  info << "Decompressing file pressed.txt\n";
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
  long long size = 0;
  infile >> cnt;
  ElemMap freq;
  for (int i = 0; i < cnt; i++) {
    unsigned char ch;
    unsigned long num = 0;
    ch = infile.get();
    unsigned char numstr[4];
    for (int i = 0; i < 4; i++) numstr[3 - i] = infile.get();
    for (int i = 0; i < 4; i++) {
      num <<= 8;
      num |= numstr[i];
    }
    freq.insert({ch, num});
    size += num;
  }
  bool output = size < 100;
  // Sort frequencies
  Tree *tree, *start;
  ElemArr curFreq(freq.begin(), freq.end());
  std::qsort(curFreq.data(), curFreq.size(), sizeof(curFreq[0]),
             (int (*)(const void *, const void *))comp);
  // Building code tree
  tree = buildCodeTree(curFreq, false, info);

  if (output) {
    std::cout << "Code tree:\n";
    info << "Code tree:\n";
    print(tree, 0, info);
    std::cout << "\n";
    info << "\n";
  }
  start = tree;
  // Reading coded data
  int ch, bitPos = -1, res = 0;
  unsigned char bitAccum;
  bool isfirst = true, isstart = true;
  long num = 0;
  outfile.open("Files/decompressed.txt");
  if (output) {
    std::cout << "Decoding data: (0 - left, 1 - right)\n";
    info << "Decoding data: (0 - left, 1 - right)\n";
  }
  while (1) {
    // Leaf -> symbol
    if (!isfirst && tree->left() == NULL) {
      if (isstart && !res) break;
      unsigned char ch = (unsigned char)tree->getNode().first[0];
      if (output) {
        std::cout << "Symbol: " << ch << "\n";
        info << "Symbol: " << ch << "\n";
      }
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
      if (output) {
        std::cout << "1 -> /" << tree->getNode().first << "/; ";
        info << "1 -> /" << tree->getNode().first << "/; ";
      }
      isstart = false;
    } else if (tree->left() != nullptr) {
      isstart = false;
      tree = tree->left();
      if (output) {
        std::cout << "0 -> /" << tree->getNode().first << "/; ";
        info << "0 -> /" << tree->getNode().first << "/; ";
      }
    }
  }
  info.close();
  infile.close();
  outfile.close();

  return true;
}