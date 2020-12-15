#include "treap.h"

void Treap::insert(TreapElem*& root, TreapElem a){
	//создание нового элемента на месте некоторого пустого, выход из функции
	if (root == nullptr)
	{
		root = new TreapElem(a);
		return;
	}
	//сравнения с ключом текущего узла
	if (a.key < root->key){
		insert(root->left, a);
	}

	else if (a.key >= root->key) {
		insert(root->right, a);
	}

	//повороты (если требуется)
	if (root->left && root->left->prior > root->prior) {
		rotateRight(root);
	}

	if (root->right && root->right->prior > root->prior) {
		rotateLeft(root);
	}
}

void Treap::read(std::istream& is){
	std::vector<TreapElem> treapVector;
	while (1) {
		TreapElem a;
		is >> a;
		treapVector.push_back(a);
		char tmp = is.get();
		if (tmp == '\n' || tmp == EOF) break;
	}
	for (auto it : treapVector) insert(root, it);

}
void Treap::rotateLeft(TreapElem*& el) {

	
	TreapElem* newEl = el->right;
	el->right = newEl->left;
	newEl->left = el;
	el = newEl;
}
void Treap::rotateRight(TreapElem*& el) {
	
	TreapElem* newEl = el->left;
	el->left = newEl->right;
	newEl->right = el;
	el = newEl;
}
int Treap::find(TreapElem* root, TreapElem e) {

	if (root){
		if (root->key == e.key && root->prior == e.prior  && isLeaf(root)) {
			return 1;
		}

		else if (root->key == e.key && root->prior == e.prior && !isLeaf(root)) {

			return 1 + find(root->right, e);
		}

		else{
			if (e.key >= root->key) {
				return find(root->right, e);
			}
			else {
				return find(root->left, e);
			}
		}
	}
	else return 0;
	
}
bool isLeaf(TreapElem* e) {
	return (!e->left && !e->right);
}