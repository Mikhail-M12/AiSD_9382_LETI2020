#include <cmath>
#include "fanohuffman.h"

Tree *buildCodeTreeFano(ElemArr curFreq, bool output, std::ofstream &info) {
  if (output) {
    std::cout << "Symbols: ";
    info << "Symbols: ";
  }
  // Quit recursion
  if (curFreq.size() == 0) {
    if (output) {
      std::cout << "No symbol -> empty node\n";
      info << "No symbol -> empty node\n";
    }
    return nullptr;
  }
  // Symbol leaf case
  if (curFreq.size() == 1) {
    std::string s;
    s.push_back(curFreq.begin()->first);
    if (output) {
      std::cout << s << " One symbol -> node {" << s << ", nullptr, nullptr}" << "\n";
      info << s << " One symbol -> node {" << s << ", nullptr, nullptr}" << "\n";
    }
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
  if (output) {
    std::cout << "/" << nodestr << "/ Sum: " << sum << " Average: " << avg << "\n";
    info << "/" << nodestr << "/ Sum: " << sum << " Average: " << avg << "\n";
  }
  // Splitting current array by frequency
  long cursum = 0, last = sum;
  auto iter = curFreq.begin();
  int strcnt = 0;
  while (last > fabs(cursum + (iter->second) - avg)) {
    cursum += iter->second;
    last = abs(cursum - avg);
    iter++;
    strcnt++;
  }
  if (output) {
    std::cout << "  left: " << nodestr.substr(0, strcnt) << "(" << cursum << ")\n"
              << "  right: " << nodestr.substr(strcnt) << "(" << sum - cursum << ")\n";
    info << "  left: " << nodestr.substr(0, strcnt) << "(" << cursum << ")\n"
         << "  right: " << nodestr.substr(strcnt) << "(" << sum - cursum << ")\n";
  }
  // Building left and right subtree
  ElemArr left(curFreq.begin(), iter);
  ElemArr right(iter, curFreq.end());
  return new Tree(new Tree::node({nodestr, cursum}, buildCodeTreeFano(left, output, info),
                                 buildCodeTreeFano(right, output, info)));
}

typedef std::vector<Tree *> Forest;

void HuffmanIter(Forest &forest, bool output, std::ofstream &info) {
  // Printing forest
  if (output) {
    std::cout << "Current forest:\n  ";
    info << "Current forest:\n  ";
    for (auto &e : forest) {
      std::cout << e->getNode().first << "(" << e->getNode().second << ") ";
      info << e->getNode().first << "(" << e->getNode().second << ") ";
    }
    info << "\n";
    std::cout << "\n";
  }

  long size = forest.size();

  // Initialize new node data
  Tree *last = forest[size - 1], *prelast = forest[size - 2];
  long sum = last->getNode().second + prelast->getNode().second;
  std::string nodestr = last->getNode().first + prelast->getNode().first;

  // Printing new node
  if (output) {
    std::cout << "  Sum nodes: " << prelast->getNode().first << "("
              << prelast->getNode().second << ") and " << last->getNode().first
              << "(" << last->getNode().second << ")\n";
    std::cout << "  Result: " << nodestr << "(" << sum << ")\n";
    info << "  Sum nodes: " << prelast->getNode().first << "("
              << prelast->getNode().second << ") and " << last->getNode().first
              << "(" << last->getNode().second << ")\n";
    info << "  Result: " << nodestr << "(" << sum << ")\n";
  }

  // Creating new node
  Tree::node *newNode = new Tree::node({nodestr, sum}, prelast, last);
  forest.pop_back(), forest.pop_back();
  if (forest.size() == 0) {
    forest.push_back(new Tree(newNode));
    return;
  }
  auto iter = forest.end();
  iter--;
  
  while ((*iter)->getNode().second <= newNode->info.second) {
    if (iter == forest.begin()) break;
    iter--;
  }
  if ((*(forest.begin()))->getNode().second > newNode->info.second) iter++;

  // Inserting new node in forest
  forest.insert(iter, new Tree(newNode));
}

// Building code tree function
Tree *buildCodeTreeHuffman(ElemArr curFreq, bool output, std::ofstream &info) {
  Forest forest;

  for (auto &e : curFreq) {
    std::string nodestr;
    char c = e.first;
    nodestr.push_back(c);
    Tree *t = new Tree(new Tree::node({nodestr, e.second}, nullptr, nullptr));
    forest.push_back(t);
  }
  while (forest.size() > 1)
    HuffmanIter(forest, output, info);
  return forest[0];
}
