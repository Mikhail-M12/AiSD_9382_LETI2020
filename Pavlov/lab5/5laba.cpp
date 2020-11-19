#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

template <typename T> struct Pair {
	T x;
	T y;

	Pair(T x, T y) : x(x), y(y) {}
};

struct Node {
	Pair<int> p;
	Node* l, * r;

	Node(int x, int y) : p(Pair<int>(x, y)), l(nullptr), r(nullptr) {}
	Node(int x, int y, Node* l, Node* r) : p(Pair<int>(x, y)), l(l), r(r) {}
};

template <typename T>
void writeToFile(const string filename, const T arg) {
	ofstream output;
	output.open(filename, ios::app);
	output << arg;
	output.close();
}

void indent(int n) {
	for (int i = 0; i < n; i++) {
		cout << "\t";
	}
}

void dispose(Node* t) {
	if (t == nullptr) {
		return;
	}
	dispose(t->l);
	dispose(t->r);
	delete t;
}

bool isIn(Node* t, int k) {
	if (t != nullptr) {
		if (k > t->p.x) {
			return isIn(t->r, k);
		}
		else if (k < t->p.x) {
			return isIn(t->l, k);
		}
		return true;
	}
	return false;
}

Node* merge(Node* l, Node* r, int& depth) {
	if (!depth) {
		cout << "\nAttempting to merge trees\n";
	}
	if (l == nullptr) {
		return r;
	}
	if (r == nullptr) {
		return l;
	}

	if (l->p.y > r->p.y) {
		indent(depth);
		cout << "Merging with the right branch of  " << l->p.x << "  " << l->p.y << "\n";
		depth++;
		l->r = merge(l->r, r, depth);
		depth--;
		return l;
	}
	indent(depth);
	cout << "Merging with the left branch of  " << r->p.x << "  " << r->p.y << "\n";
	depth++;
	r->l = merge(l, r->l, depth);
	depth--;
	return r;
}

Pair<Node*> split(Node* t, int k, int& depth) {
	if (!depth) {
		cout << "\nAttempting to split the tree.\n";
	}
	if (t == nullptr) {
		return Pair<Node*>(nullptr, nullptr);
	}
	else if (k > t->p.x) {
		indent(depth);
		cout << "Descending to  the right branch of  " << t->p.x << "  " << t->p.y << "\n";
		depth++;
		Pair<Node*> nPair = split(t->r, k, depth);
		depth++;
		t->r = nPair.x;
		return Pair<Node*>(t, nPair.y);
	}
	else{
		indent(depth);
		cout << "Descending to  the left branch of  " << t->p.x << "  " << t->p.y << "\n";
		depth++;
		Pair<Node*> nPair = split(t->l, k, depth);
		depth--;
		t->l = nPair.y;
		return Pair<Node*>(nPair.x, t);
	}
	return Pair<Node*>(t, nullptr);
}

Node* add(Node* t, int k, int v) {
	int depth = 0;
	cout << "\n\nSplitting the treap by key " << k << "\n";
	Pair<Node*> p = split(t, k, depth);
	Node* n = new Node(k, v);
	return merge(merge(p.x, n, depth), p.y, depth);
}

Node* remove(Node* t, int k, int& depth) {
	if (!depth) {
		cout << "\nAttempting to remove existing element.\n";
	}
	if (t != nullptr) {
		indent(depth);
		cout << "Current element: " << t->p.x << "  " << t->p.y << "\n";
		if (t->p.x < k) {
			depth++;
			t->r = remove(t->r, k, depth);
			depth--;
			return t;
		}
		else if (t->p.x > k) {
			depth++;
			t->l = remove(t->l, k, depth);
			depth--;
			return t;
		}
		else {
			indent(depth);
			cout << "\nRequired element found: " << t->p.x << "  " << t->p.y << " , removing...\n";
			Node* l = t->l, * r = t->r;
			t->l = nullptr;
			t->r = nullptr;
			dispose(t);
			return merge(l, r, depth);
		}
	}
	return t;
}

void printTreap(Node* t, int& depth) {
	if (t != nullptr) {
		if (t->r != nullptr) {
			depth++;
			printTreap(t->r, depth);
			depth--;
		}
		indent(depth);
		cout << t->p.x << "  " << t->p.y << "\n";
		if (t->l != nullptr) {
			depth++;
			printTreap(t->l, depth);
			depth--;
		}
	}
}

void printAscendingToFile(Node* t, const string& filename) {
	if (t != nullptr) {
		if (t->l != nullptr) {
			printAscendingToFile(t->l, filename);
		}
		writeToFile(filename, t->p.x);
		writeToFile(filename, "  ");
		writeToFile(filename, t->p.y);
		writeToFile(filename,  '\n');
		if (t->r != nullptr) {
			printAscendingToFile(t->r, filename);
		}
	}
}

int main() {
	srand(time(nullptr));
	int command = 0;
	int key = 0, value = 0;
	int depth = 0;
	Node* treap = nullptr;
	cout << "Enter : 1 - Console input , 2 - File Input:\n\n";
	cin >> command;

	if (command == 2) {
		string input_filename;
		const string output_filename = "output.txt";
		ifstream in;
		ofstream out;

		out.open(output_filename);
		out << "";
		out.close();

		cout << "Enter the input file name: \n\n";
		cin >> input_filename;
		in.open(input_filename);

		if (in.is_open()) {
			while (!in.eof()) {
				if (!(in >> key) || !(in >> value)) {
					break;
				}
				if (isIn(treap, key)) {
					cout << "\n\nElement with key = " << key << " already exists. Replacing...";
					treap = remove(treap, key, depth);
				}
				cout << "\n\nAdding new element with key = " << key << " to the treap\n";
				treap = add(treap, key, value);
			}
			if (treap != nullptr) {
				printTreap(treap, depth);
				printAscendingToFile(treap, output_filename);
				cout << "\nCheck out the results in \"output.txt\"\n";
			}
			else {
				cout << "File is empty or contains inappropriate data.\n";
			}
		}
		else {
			cout << input_filename << " doesn't exist!\n";
		}
	}
	else if (command == 1) {
		cout << "Enter the pairs (key then value, both integer) or anything except that (to finish): \n\n";
		while ((cin >> key)) {
			if (!(cin >> value)) {
				break;
			}
			if (isIn(treap, key)) {
				cout << "\n\nElement with key = " << key << " already exists. Replacing...";
				treap = remove(treap, key, depth);
			}
			cout << "\n\nAdding new element with key = " << key << " to the treap\n";
			treap = add(treap, key, value);
		}
		if (treap != nullptr) {
			printTreap(treap, depth);
		}
		else {
			cout << "The treap is empty.\n";
		}
	}
	else {
		cout << "\nUnknown command, program finished\n";
	}

	return 0;
}