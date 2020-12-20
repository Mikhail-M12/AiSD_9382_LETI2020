#include <Windows.h>
#include <cmath>
#include "fanohuffman.h"

Tree *buildCodeTreeFano(ElemArr curFreq, bool output) {
  // Quit recursion
  if (curFreq.size() == 0) {
    if (output)
      std::cout << "No symbol -> empty node\n";
    return nullptr;
  }
  // Symbol -> leaf case
  if (curFreq.size() == 1) {
    std::string s;
    s.push_back(curFreq.begin()->first);
    if (output)
      std::cout << s << " One symbol -> node {" << s << ", nullptr, nullptr}" << "\n";
    // Creating node from symbo
    return new Tree(new Tree::node({s, curFreq[0].second}, nullptr, nullptr));
  }
  // Count average frequency
  long sum = 0;
  std::string nodestr;
  for (auto &f : curFreq) {
    nodestr.push_back(f.first);
    sum += f.second;
  }
  long avg = sum / 2;
  // Splitting current array by frequency
  long cursum = 0, last = sum;
  auto iter = curFreq.begin();
  int strcnt = 0;
  while (last > std::abs(cursum + (iter->second) - avg)) {
    cursum += iter->second;
    last = std::abs(cursum - avg);
    iter++;
    strcnt++;
  }
  // Print demo output
  if (output) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "/";
    SetConsoleTextAttribute(h, WORD(1 << 4 | 12));
    std::cout << nodestr.substr(0, strcnt);
    SetConsoleTextAttribute(h, WORD(1 << 4 | 10));
    std::cout << nodestr.substr(strcnt);
    SetConsoleTextAttribute(h, WORD(1 << 4 | 14));
    std::cout << "/ Sum: " << sum << " Average: " << avg << "\n";
    std::cout << "  left: ";
    SetConsoleTextAttribute(h, WORD(1 << 4 | 12));
    std::cout << nodestr.substr(0, strcnt);
    SetConsoleTextAttribute(h, WORD(1 << 4 | 14));
    std::cout << "(" << cursum << ")\n" << "  right: ";
    SetConsoleTextAttribute(h, WORD(1 << 4 | 10));
    std::cout << nodestr.substr(strcnt);
    SetConsoleTextAttribute(h, WORD(1 << 4 | 14));
    std:: cout << "(" << sum - cursum << ")\n";
  }
  // Building left and right subtree
  ElemArr left(curFreq.begin(), iter);
  ElemArr right(iter, curFreq.end());
  return new Tree(new Tree::node({nodestr, cursum}, buildCodeTreeFano(left, output),
                                 buildCodeTreeFano(right, output)));
}

typedef std::vector<Tree *> Forest;

std::string prev;

void HuffmanIter(Forest &forest, bool output) {
  // Printing forest
  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
  if (output) {
    std::cout << "Current forest:\n  ";
    for (int i = 0; i < forest.size(); i++) {
      if (forest[i]->getNode().first == prev) 
        SetConsoleTextAttribute(h, WORD(1 << 4 | 12));
      else if (i >= forest.size() - 2)
        SetConsoleTextAttribute(h, WORD(1 << 4 | 10));
      std::cout << forest[i]->getNode().first << "(" << forest[i]->getNode().second << ") ";
      SetConsoleTextAttribute(h, WORD(1 << 4 | 14));
    }
    std::cout << "\n";
  }

  long size = forest.size();

  // Initialize new node data
  Tree *last = forest[size - 1], *prelast = forest[size - 2];
  long sum = last->getNode().second + prelast->getNode().second;
  std::string nodestr = last->getNode().first + prelast->getNode().first;

  // Printing new node
  if (output) {
    std::cout << "  Sum nodes: ";
    SetConsoleTextAttribute(h, WORD(1 << 4 | 10));
    std::cout << prelast->getNode().first << "(" << prelast->getNode().second << ")";
    SetConsoleTextAttribute(h, WORD(1 << 4 | 14));
    std::cout << " and ";
    SetConsoleTextAttribute(h, WORD(1 << 4 | 10));
    std::cout << last->getNode().first << "(" << last->getNode().second << ")\n";
    SetConsoleTextAttribute(h, WORD(1 << 4 | 14));
    std::cout << "  Result: ";
    SetConsoleTextAttribute(h, WORD(1 << 4 | 12));
    std::cout << nodestr << "(" << sum << ")\n";
    SetConsoleTextAttribute(h, WORD(1 << 4 | 14));
  }

  // Creating new node
  Tree::node *newNode = new Tree::node({nodestr, sum}, prelast, last);
  forest.pop_back(), forest.pop_back();
  if (forest.size() == 0) {
    forest.push_back(new Tree(newNode));
    return;
  }

  // Finding index for new element
  auto iter = forest.end();
  iter--;
  
  while ((*iter)->getNode().second <= newNode->info.second) {
    if (iter == forest.begin()) break;
    iter--;
  }
  if ((*(forest.begin()))->getNode().second > newNode->info.second) iter++;

  // Inserting new node in forest
  forest.insert(iter, new Tree(newNode));
  prev = newNode->info.first;
}

// Building code tree function
Tree *buildCodeTreeHuffman(ElemArr curFreq, bool output) {
  prev = "";
  Forest forest;

  // Creating forest from element array
  for (auto &e : curFreq) {
    std::string nodestr;
    char c = e.first;
    nodestr.push_back(c);
    Tree *t = new Tree(new Tree::node({nodestr, e.second}, nullptr, nullptr));
    forest.push_back(t);
  }
  // Merging last two elements while it is possible
  while (forest.size() > 1)
    HuffmanIter(forest, output);
  if (output) std::cout << "Result node: " << forest[0]->getNode().first << "\n";
  return forest[0];
}
