#include <cmath>
#include "fano.h"

// Types
typedef std::map<unsigned char, long> ElemMap;
typedef std::vector<std::pair<unsigned char, long>> ElemArr;

// Tree printing function
void print(Tree *q, long n) {
  long i;
  if (q != nullptr) {
    print(q->right(), n + q->getNode().size() + 2);
    for (i = 0; i < n; i++) std::cout << " ";
    std::cout << "\\" << q->getNode() << "\\\n";
    print(q->left(), n + q->getNode().size() + 2);
  }
}

Tree *buildCodeTree(ElemArr curFreq, bool output) {
  if (output) std::cout << "Symbols: ";
  // Quit recursion
  if (curFreq.size() == 0) {
    if (output) std::cout << "No symbol -> empty node\n";
    return nullptr;
  }
  // Symbol leaf case
  if (curFreq.size() == 1) {
    std::string s;
    s.push_back(curFreq.begin()->first);
    if (output)
      std::cout << s << " One symbol -> node {" << s << ", nullptr, nullptr}" << "\n";
    return new Tree(new Tree::node(s, nullptr, nullptr));
  }
  // Count average frequency
  long sum = 0;
  std::string nodestr;
  for (auto &f : curFreq) {
    nodestr.push_back(f.first);
    sum += f.second;
  }
  long avg = sum / 2;
  if (output) std::cout << "/" << nodestr << "/ Sum: " << sum << " Average: " << avg << "\n";
  // Splitting current array by frequency
  long cursum = 0, last = sum;
  auto iter = curFreq.begin();
  int strcnt = 0;
  while (last > fabs(cursum + (iter->second) - avg)) {
    cursum += iter->second;
    last = fabs(cursum - avg);
    iter++;
    strcnt++;
  }
  if (output)
    std::cout << "  left: " << nodestr.substr(0, strcnt) << "(" << cursum << ")\n"
              << "  right: " << nodestr.substr(strcnt) << "(" << sum - cursum << ")\n";
  // Building left and right subtree
  ElemArr left(curFreq.begin(), iter);
  ElemArr right(iter, curFreq.end());
  return new Tree(new Tree::node(nodestr, buildCodeTree(left, output),
                                 buildCodeTree(right, output)));
}

// Code cuildeing definitions
struct Code {
  bool bits[50];
  int len = 0;
};
Code curCode;
std::map<unsigned char, Code> newCodes;

void buildCodes(Tree *T) {
  // No subtrees -> symbol found
  if (T->left() == nullptr && T->right() == nullptr) {
    unsigned char ch = T->getNode()[0];
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
  if (i->second == j->second)
    return i->first - j->first;
  return j->second - i->second;
}

bool press(const char *filename) {
  int ch;
  long long size1 = 0, size2 = 0;
  ElemMap freq;
  std::cout << "Pressing file " << filename << "\n";
  setlocale(LC_CTYPE, ".1251");
  std::ifstream infile(filename, std::ios::in);
  if (!infile.is_open()) {
    std::cout << "Impossible to open file\n";
    return false;
  }
  std::ofstream outfile;
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
  // Write label
  outfile << "FN!";
  outfile << (int)freq.size();
  std::cout << "Frequencies:\n";
  // Write frequencies
  for (auto &i : curFreq) {
    std::cout << (unsigned char)i.first << "-" << i.second << ";";
    outfile << i.first;
    outfile.write(reinterpret_cast<char *>(&i.second), sizeof(long));
  }
  std::cout << "\n\n";
  // Building code tree
  std::cout << "Building code tree: \n";
  Tree *T = buildCodeTree(curFreq, true);
  std::cout << "\n";
  // Building new codes
  buildCodes(T);

  // Printing tree
  if (curFreq.size() <= 26) {
    std::cout << "Tree:\n";
    print(T, 0);
  }
  T->clear();
  std::cout << "\n";
  // Printing codes
  std::cout << "Codes:\n";
  for (auto &c : newCodes) {
    std::cout << c.first << ":";
    for (int i = 0; i < c.second.len; i++) std::cout << (int)c.second.bits[i];
    std::cout << "\n";
  }
  std::cout << "\n";
  /*** Passing through the file second time ***/
  // Coding input data to output file
  infile.seekg(infile.beg);
  unsigned char bitAccum = 0;
  int bitPos = 7;
  bool output = (size1 < 100);
  infile.close();
  infile.open(filename);
  if (output) std::cout << "Coded data: \n";
  while ((ch = infile.get()) != EOF) {
    for (int k = 0; k < newCodes[ch].len; k++) {
      int bit = newCodes[ch].bits[k] << bitPos--;
      if (output) std::cout << (int)newCodes[ch].bits[k];
      bitAccum |= bit;
      // Writing byte
      if (bitPos < 0) {
        size2++;
        outfile << bitAccum;
        bitAccum = 0;
        bitPos = 7;
      }
    }
    std::cout << " ";
  }
  std::cout << "\n";
  if (bitPos < 7) outfile << bitAccum, size2++;
  std::cout << "Input size: " << size1
            << "\nPressed size(pure input data): " << size2 << "\n";

  infile.close();
  outfile.close();
  return true;
}

// Decompress function
bool depress() {
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
  if (strcmp(label, "FN!") != 0) {
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
  // Sort frequencies
  Tree *tree, *start;
  ElemArr curFreq(freq.begin(), freq.end());
  std::qsort(curFreq.data(), curFreq.size(), sizeof(curFreq[0]),
             (int (*)(const void *, const void *))comp);
  // Building code tree
  tree = buildCodeTree(curFreq, false);
  start = tree;
  // Reading coded data
  int ch, bitPos = -1, res = 0;
  unsigned char bitAccum;
  bool isfirst = true, isstart = true;
  long num = 0;
  outfile.open("Files/decompressed.txt");
  while (1) {
    // Leaf -> symbol
    if (!isfirst && tree->left() == NULL) {
      if (isstart && !res)
        break;
      outfile << (unsigned char)tree->getNode()[0];
      num++;
      if (num == size)
        break;
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