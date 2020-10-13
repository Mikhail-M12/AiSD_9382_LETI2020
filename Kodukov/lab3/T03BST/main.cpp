/* ������� ��������� 9382, �. 18�
 *
 * �������� ������ ���������� �������� ������� ������,
 * ���� ��� ������� ��� ���� �����������
 * : ��� �������� ������� ��������� ������ ����� ����,
 *   � ��� �������� ������ ��������� � ������ ����� ����.�������� ������
 *       ���������� ���������,
 *   ���� ��� ������� ��� ���� �����������
 * : �������� ���� �������� ����� ���� �� ������,
 *   ��� �������� ����.��� ��������� ��������� ������ � �������� �����
 *       ��������� ����������,
 *   �������� �� ��� �������� ������� ������ � �������� �� ��� ���������.
 */
#include "tree.h"

template <typename Elem>
Tree<Elem> *Read(std::ifstream &f) {
  char ch;
  Elem e = 0;
  Tree<Elem> *p, *q;

  f >> ch;
  int d = 0;
  while (ch >= '0' && ch <= '9') {
    e = e * pow(10, d++) + ch - '0';
    f >> ch;
  }
  if (ch == '/')
    return NULL;
  else {
    p = Read<Elem>(f);
    q = Read<Elem>(f);
    typename Tree<Elem>::node *N = new typename Tree<Elem>::node(e, p, q);
    return new Tree<Elem>(N);
  }
}

template <typename Elem>
void Print(Tree<Elem> *q, long n) {
  long i;
  if (q != nullptr) {
    Print<Elem>(q->Right(), n + 5);
    for (i = 0; i < n; i++) 
      std::cout << " ";
    std::cout << q->GetNode() << "\n";
    Print<Elem>(q->Left(), n + 5);
  }
}

int main() {
  Tree<int> *t;
  std::ifstream f("input.txt");
  t = Read<int>(f);
  if (t != nullptr) {
    f.close();
    Print(t, 0);
    std::cout << "Check search:\n";
    bool Search = t->CheckSearchTree(-INFINITY, INFINITY, 1);
    std::cout << "Search: " << (Search ? "true" : "false") << "\n\n";
    std::cout << "Check pyramid:\n";
    bool Pyramid = t->CheckPyramidTree();
    std::cout << "Pyramid: " << (Pyramid ? "true" : "false") << "\n";
    t->Clear();
  } else
    std::cout << "Wrong input";
}