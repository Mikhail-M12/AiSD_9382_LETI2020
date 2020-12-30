#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

class Node{
	public:
		int iLeft;
		int iRight;
		char key;
		Node(){
			this->iLeft = -1;
			this->iRight = -1;
			this->key = '#';
		}
};

class BinTree{
	public:
		Node* nodes;
		int height;
		
		void print(){
			for(int i = 0; i < std::pow(2, height) - 1; i++){
				std::cout<<nodes[i].key<<" ";
			}
			std::cout<<'\n';
		}
		void expand(){
			Node* tmp = new Node[(int)(std::pow(2, this->height + 1) - 1)];
			for (int i = 0; i < std::pow(2, this->height) - 1; i++){
				tmp[i].key = this->nodes[i].key;
				(tmp+i)->iLeft = 2*i + 1;
				(tmp+i)->iRight = 2*i + 2;
			}
			delete[] nodes;
			this->nodes = tmp;
			this->height++;
		}
		BinTree(std::string keys){
		    int height = 0;
		    while (std::pow(2, height) - 1 < keys.length()){
		        height++;
		    }
			Node* tmp = new Node[(int)(std::pow(2, height) - 1)];
			for (int i = 0; i < std::pow(2, height) - 1; i++){
				if (i < keys.length()){
					if (isspace(keys[i])) tmp[i].key = '#';
					else tmp[i].key = keys[i];
				}
				(tmp+i)->iLeft = 2*i + 1;
				(tmp+i)->iRight = 2*i + 2;
			}
			this->nodes = tmp;
			this->height = height;
		}
		bool isCorrectSearchTree(){
		    for (int i = 0; i < std::pow(2, this->height - 1) - 1; i++){
		        if (this->nodes[i].key == '#' && (this->nodes[2*i + 1].key != '#' || this->nodes[2*i + 2].key != '#')) return false;
		        if (this->nodes[this->nodes[i].iLeft].key != '#' && this->nodes[this->nodes[i].iLeft].key >= this->nodes[i].key) return false;
		        if (this->nodes[this->nodes[i].iRight].key != '#' && this->nodes[this->nodes[i].iRight].key < this->nodes[i].key) return false;
		    }
		    return true;
		}
		~BinTree(){
			delete[] nodes;
		}
};

int count(BinTree* b, int i = 0){
    int c = 0;
    int iLeft = b->nodes[i].iLeft;
    int iRight = b->nodes[i].iRight;
    if ((iLeft >= pow(2, b->height) - 1) || (iRight >= pow(2, b->height) - 1)) b->expand();
    if (b->nodes[i].key == '#') return 0;
    else{
        if (b->nodes[iLeft].key != '#') c = c + count(b, b->nodes[i].iLeft);
        if (b->nodes[iRight].key != '#') c = c + count(b, b->nodes[i].iRight);
        std::cout<<b->nodes[i].key<<" node children count: "<<c<<'\n';
        return c + 1;
    }
}

int height(BinTree* b, int i = 0){
    int h1 = 0, h2 = 0;
    int iLeft = b->nodes[i].iLeft;
    int iRight = b->nodes[i].iRight;
    if ((iLeft >= pow(2, b->height) - 1) || (iRight >= pow(2, b->height) - 1)) b->expand();
    if (b->nodes[i].key == '#') return 0;
    else{
        if (b->nodes[iLeft].key != '#') h1 = height(b, b->nodes[i].iLeft);
        if (b->nodes[iRight].key != '#') h2 = height(b, b->nodes[i].iRight);
        std::cout<<b->nodes[i].key<<" node height: "<<std::max(h1, h2)<<'\n';
        return std::max(h1, h2) + 1;
    }
}

bool isBalanced(BinTree* b, int i = 0){
    int iLeft = b->nodes[i].iLeft;
    int iRight = b->nodes[i].iRight;
    int cleft = 0, cright = 0;
    if (b->nodes[iLeft].key == '#' && b->nodes[iRight].key == '#') return true;
    if (b->nodes[iLeft].key != '#') cleft = count(b, iLeft);
    if (b->nodes[iRight].key != '#') cright = count(b, iRight);
    return isBalanced(b, iLeft) && isBalanced(b, iRight) && (std::abs(cleft - cright) < 2);
}

bool isAVL(BinTree* b, int i = 0){
	int iLeft = b->nodes[i].iLeft;
    int iRight = b->nodes[i].iRight;
    int hleft = 0, hright = 0;
    if (b->nodes[iLeft].key == '#' && b->nodes[iRight].key == '#') return true;
    if (b->nodes[iLeft].key != '#') hleft = height(b, iLeft);
    if (b->nodes[iRight].key != '#') hright = height(b, iRight);
    return isAVL(b, iLeft) && isAVL(b, iRight) && (std::abs(hleft - hright) < 2);
}

int process(std::string str){
	BinTree b(str);
	std::cout<<"The tree you've inserted:\n";
	b.print();

	if (!b.isCorrectSearchTree()){
	    std::cout<<"Incorrect tree format.\n";
	    std::cout<<"--------------------------------\n";
		return 1;
    }
    std::cout<<"Tree height: "<<height(&b)<<'\n';
    bool tmp = isBalanced(&b);
    if (tmp == 1) std::cout<<"This tree is a balanced tree.\n";
    else std::cout<<"This tree isn't a balanced tree.\n";
    tmp = isAVL(&b);
    if (tmp == 1) std::cout<<"This tree is an AVL-tree.\n";
    else std::cout<<"This tree isn't an AVL-tree.\n";
    std::cout<<"--------------------------------\n";
    return 0;
}

int func(){
	int a;
	std::string str;

	std::cout<<"Choose input option (0 - file input, 1 - console input):\n";
	std::cin>>a;
	if(a){
		std::cin>>str;
		process(str);
		return 0;
	}

    std::ifstream f("tests.txt");
	if(!f){
	    std::cout<<"Couldn't open file!\n";
	    return 1;
	}
	int testn = 1;
	while(!f.eof()){
		std::cout<<"Test #"<<testn<<'\n';
		f>>str;
		process(str);
		testn++;
	}
    return 0;
}

int main(){
    try{
		func();
    }
    catch(...){
		std::cout<<"An unexpected error occurred.\n";
	}
	return 0;
}
