#include "fano.h"

// Types
typedef std::map<unsigned char, long> ElemMap;
typedef std::vector<std::pair<unsigned char, long>> ElemArr;

// Tree printing function
void Print(Tree *q, long n) {
  long i;
  if (q != nullptr) {
    Print(q->Right(), n + q->GetNode().size() * 2);
    for (i = 0; i < n; i++) std::cout << " ";
    std::cout << "\\" << q->GetNode() << "\\\n";
    Print(q->Left(), n + q->GetNode().size() * 2);
  }
}

Tree *BuildCodeTree(ElemArr CurFreq) {
  // Quit recursion
  if (CurFreq.size() == 0) return nullptr;
  // Symbol leaf case
  if (CurFreq.size() == 1) {
    std::string s;
    s.push_back(CurFreq.begin()->first);
    return new Tree(
        new Tree::node(s, nullptr, nullptr));
  }
  // Count average frequency
  long sum = 0;
  std::string nodestr;
  for (auto &f : CurFreq) {
    nodestr.push_back(f.first);
    sum += f.second;
  }
  long avg = sum / 2;
  // Splitting current array by frequency
  long cursum = 0;
  auto iter = CurFreq.begin();
  while (cursum < avg) {
    cursum += iter->second;
    iter++;
  }
  // Building left and right subtree
  ElemArr Left(CurFreq.begin(), iter);
  ElemArr Right(iter, CurFreq.end());
  return new Tree(new Tree::node(nodestr, BuildCodeTree(Left),
                                 BuildCodeTree(Right)));
}

// Code cuildeing definitions
struct CODE {
  bool Bits[50];
  int Len = 0;
};
CODE CurCode;
std::map<unsigned char, CODE> NewCodes;

void BuildCodes(Tree *T) {
  // No subtrees -> symbol found
  if (T->Left() == nullptr && T->Right() == nullptr) {
    unsigned char ch = T->GetNode()[0];
    if (CurCode.Len == 0) {
      CurCode.Bits[0] = 1;
      CurCode.Len = 1;
    }
    NewCodes.insert({ch, CurCode});
    return;
  }
  // Left subtree (0 to code)
  if (T->Left() != NULL) {
    CurCode.Bits[CurCode.Len] = 0;
    CurCode.Len++;
    BuildCodes(T->Left());
    CurCode.Len--;
  }
  // Right subtree (1 to code)
  if (T->Right() != NULL) {
    CurCode.Bits[CurCode.Len] = 1;
    CurCode.Len++;
    BuildCodes(T->Right());
    CurCode.Len--;
  }
}

int comp(const std::pair<unsigned char, long> *i,
         const std::pair<unsigned char, long> *j) {
  return j->second - i->second;
}

bool Press(const char *filename) {
  // Count frequency
  int ch;
  long long size1 = 0, size2 = 0;
  ElemMap Freq;
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
    auto iter = Freq.find(ch);
    if (iter != Freq.end())
      (*iter).second++;
    else
      Freq.insert({ch, 1});
  }
  // Sorting frequencies
  ElemArr CurFreq(Freq.begin(), Freq.end());
  std::qsort(CurFreq.data(), CurFreq.size(),
             sizeof(std::pair<unsigned char, long>),
             (int (*)(const void *, const void *))comp);
  // Building code tree
  Tree *T = BuildCodeTree(CurFreq);
  // Building new codes
  BuildCodes(T);
  // Passing through the file second time
  infile.seekg(infile.beg);
  outfile.open("Files/pressed.txt", std::ios::binary);
  // Write label
  outfile << "FN!";
  outfile << (int)Freq.size();
  std::cout << "Frequencies:\n";
  // Write frequencies
  for (auto &i : CurFreq) {
    std::cout << (unsigned char)i.first << "-" << i.second << ";";
    outfile << i.first;
    outfile.write(reinterpret_cast<char *>(&i.second), sizeof(long));
  }
  std::cout << "\n";
  if (CurFreq.size() <= 15) {
    std::cout << "Tree:\n";
    Print(T, 0);
  }
  T->Clear();
  std::cout << "Codes:\n";
  for (auto &c : NewCodes) {
    std::cout << c.first << ":";
    for (int i = 0; i < c.second.Len; i++) std::cout << (int)c.second.Bits[i];
    std::cout << "\n";
  }
  // Coding input data to output file
  unsigned char BitAccum = 0;
  int BitPos = 7;
  infile.close();
  infile.open(filename);
  while ((ch = infile.get()) != EOF) {
    for (int k = 0; k < NewCodes[ch].Len; k++) {
      BitAccum |= NewCodes[ch].Bits[k] << BitPos--;
      // Writing byte
      if (BitPos < 0) {
        size2++;
        outfile << BitAccum;
        BitAccum = 0;
        BitPos = 7;
      }
    }
  }
  if (BitPos < 7) outfile << BitAccum, size2++;
  std::cout << "Input size: " << size1
            << "\nPressed size(pure input data): " << size2 << "\n";

  infile.close();
  outfile.close();
  return true;
}

// Decompress function
bool Depress() {
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
  long size = 0;
  infile >> cnt;
  ElemMap Freq;
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
    Freq.insert({ch, num});
    size += num;
  }
  // Sort frequencies
  Tree *T, *Start;
  ElemArr CurFreq(Freq.begin(), Freq.end());
  std::qsort(CurFreq.data(), CurFreq.size(), sizeof(CurFreq[0]),
             (int (*)(const void *, const void *))comp);
  // Building code tree
  T = BuildCodeTree(CurFreq);
  Start = T;
  int ch;
  unsigned char BitAccum;
  int BitPos = -1, res = 0;
  bool isfirst = true, isstart = true;
  // Reading coded data
  outfile.open("Files/decompressed.txt");
  long num = 0;
  while (1) {
    // Leaf -> symbol
    if (!isfirst && T->Left() == NULL) {
      if (isstart && !res)
        break;
      outfile << (unsigned char)T->GetNode()[0];
      num++;
      if (num == size)
        break;
      T = Start;
      isstart = true;
    }
    if (isfirst) isfirst = false;
    // Get new byte
    if (BitPos < 0) {
      ch = infile.get();
      if (ch == EOF) break;
      BitAccum = ch;
      BitPos = 7;
    }
    // 0 - go left, 1 - go right
    res = (BitAccum >> BitPos--) & 1;
    if (res && (T->Right() != nullptr)) {
      T = T->Right();
      isstart = false;
    } else if (T->Left() != nullptr) {
      isstart = false;
      T = T->Left();
    }
  }
  infile.close();
  outfile.close();

  return true;
}