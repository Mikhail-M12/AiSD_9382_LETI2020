#include <iostream>
#include <fstream>
#include <fstream>
#include <cstdlib>
#include "./src/binTree.h"
#include <string>

using namespace std;

void displayBT(binTree *tree, int b, int n)
{	// n  － уровень узла
	if (b != 0) {
		cout << ' ' << tree->RootBT(b);
		if (!tree->isNull(tree->Right(b))) { 
      displayBT(tree, tree->Right(b), n + 1); 
    }
		else 
      cout << endl; // вниз

		if (!tree->isNull(tree->Left(b))) {
			for (int i = 1; i <= n; i++) cout << "  "; // вправо
			displayBT(tree, tree->Left(b), n + 1);
		}
	}
	else {};
}

int build(binTree *tree, string &a, string &b, int x) {
  string sub_a, sub_b;
	if (a == "") return 0;

	if (a.length() == 1) {
    int p = tree->ConsBT(a[0]);
		return p;
	}
	if (x < 0) return 0;

	int flag = a.find(b[x]);
	if (flag < 0) return 0;

  int r = tree->ConsBT(b[x]);

  sub_a = a.substr(0, flag);
  sub_b = b.substr(x+1, flag);
	tree->arr[r].lt = build(tree, sub_a, sub_b, x);

  sub_a = a.substr(flag + 1);
  sub_b = b.substr(b.size() - sub_a.size());
	tree->arr[r].rt = build(tree, sub_a, sub_b, x);
  
	return r;
}

void lpk(binTree *tree, int b, string &str) {
  if(tree->isNull(b)) return;
  lpk(tree, tree->arr[b].lt, str);
  lpk(tree, tree->arr[b].rt, str);
  str += tree->arr[b].info;
}

int main() {
  binTree *MyTree = new binTree();
	ifstream fin("input.txt");
	if (!fin) { cout << "File not open for reading!\n"; return 1; }
	string str1, str2, str3;
	cout << "Считывается ЛКП запись..." << endl;
	getline(fin, str1, '\n');
  cout << str1 << endl;
	cout << "Считывается КЛП запись..." << endl;
	getline(fin, str2, '\n');
  cout << str2 << endl;
  if(str2.length() == 0 || str1.length() == 0){
    cout << "Одна из строк пустая" << endl;
    return 1;
  }
  if(str2.length() != str1.length()){
    cout << "Некорректная запись" << endl;
    return 2;
  }
	build(MyTree, str1, str2, 0);
  lpk(MyTree, 1, str3);
  cout << "ЛПК: " << str3 << endl;
  cout << "В виде дерева:" << endl;
  displayBT(MyTree, 1, 1);
	return 0;
}

