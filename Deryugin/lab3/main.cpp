#include <iostream>
#include <fstream>

using namespace std;
//enum for errors
enum Errors {
    CANNOT_OPEN_FILE,
    INCORRECT_DATA
};

void error(Errors error) {
    if (error == CANNOT_OPEN_FILE) cout<<"Cannot open file\n";
    if (error == INCORRECT_DATA) cout<<"Incorrect data\n";
}// end error func

template <typename Elem>
class BinaryTree {
    struct Node {
        Elem data;// root data
        Node* left;//left subtree
        Node* right;// right subtree
    };

    Node* createBinaryTree(string lkp, string lpk) {
        // if hasn't right leaf
        if (lkp.size() == 0 && lpk.size() == 0) return nullptr;
        //create new leaf
        if (lkp == lpk && lkp.size() == 1) {
            Node* tree = new Node;
            tree->data = lpk[0];
            tree->left = nullptr;
            tree->right = nullptr;
            return tree;
        }
        Node* tree = new Node;// create tree
        int indexOfRoot;// index of current root
        tree->data = lpk[lpk.size() - 1];// last symbol is root
        indexOfRoot = lkp.find(tree->data);
        if (indexOfRoot < 0) {
            error(INCORRECT_DATA);
            exit(1);
        }
        cout<<"Root is "<<tree->data<<endl<<"Left subtree LKP: "<<lkp.substr(0, indexOfRoot)<<endl;
        cout<<"Left subtree LPK: "<<lpk.substr(0, indexOfRoot)<<endl<<"Right subtree LKP: "<<lkp.substr(indexOfRoot + 1, lkp.size() - indexOfRoot - 1)<<endl;
        cout<<"Right subtree LPK: "<<lpk.substr(indexOfRoot, lkp.size() - indexOfRoot - 1)<<endl<<endl;
        // if hasn't right leaf
        if (indexOfRoot == 0) tree->left = nullptr;
        else tree->left = createBinaryTree(lkp.substr(0, indexOfRoot), lpk.substr(0, indexOfRoot));
        tree->right = createBinaryTree(lkp.substr(indexOfRoot + 1, lkp.size() - indexOfRoot - 1), lpk.substr(indexOfRoot, lkp.size() - indexOfRoot - 1));
        return tree;
    }

public:
    Node* tree;
    BinaryTree(string lkp, string lpk) {
        cout<<"You entered:\nLKP: "<<lkp<<";\nLPK: "<<lpk<<endl<<endl;
        //if lkp size != lpk size
        if (lkp.size() != lpk.size()) {
            error(INCORRECT_DATA);
            exit(1);
        }
        int indexOfRoot;// index of current root
        tree = new Node;// create tree
        tree->data = lpk[lpk.size() - 1];//last symbol is root
        indexOfRoot = lkp.find(tree->data);// find index of root
        if (indexOfRoot < 0) {
            error(INCORRECT_DATA);
            exit(1);
        }
        cout<<"Root is "<<tree->data<<endl<<"Left subtree LKP: "<<lkp.substr(0, indexOfRoot)<<endl;
        cout<<"Left subtree LPK: "<<lpk.substr(0, indexOfRoot)<<endl<<"Right subtree LKP: "<<lkp.substr(indexOfRoot + 1, lkp.size() - indexOfRoot - 1)<<endl;
        cout<<"Right subtree LPK: "<<lpk.substr(indexOfRoot, lkp.size() - indexOfRoot - 1)<<endl<<endl;
        // create left subtree
        if (indexOfRoot == 0) tree->left = nullptr;
        else tree->left = createBinaryTree(lkp.substr(0, indexOfRoot), lpk.substr(0, indexOfRoot));
        //create right subtree
        tree->right = createBinaryTree(lkp.substr(indexOfRoot + 1, lkp.size() - indexOfRoot - 1), lpk.substr(indexOfRoot, lkp.size() - indexOfRoot - 1));
    }

    void printKLP(Node* binTree) {
        //print root-left-right tree
        cout<<binTree->data;
        if (binTree->left) printKLP(binTree->left);
        if (binTree->right) printKLP(binTree->right);
    }

    void printTree(Node* binTree, int space) {
        if (!binTree) {
            for(int i = 0; i < space; i++) cout<<"\t";
            cout<<"#"<<endl;
            return;
        }
        printTree(binTree->right,space+1);
        for(int i = 0 ; i < space; i++) cout<<"\t";
        cout<<binTree->data<<endl;
        printTree(binTree->left,space+1);

    }

};


int main() {
    string path = "input.txt";// path to input file
    int typeOfInput;// 1 if console
    string lkp, lpk;
    cout<<"Enter '1' if you wanna write down binary tree in console otherwise write down any letter or number:\n";
    cin>>typeOfInput;
    //input from console
    if (typeOfInput == 1){
        cout<<"Enter binary tree(LKP):\n";
        cin>>lkp;
        cout<<"Enter binary tree(LPK):\n";
        cin>>lpk;
    }
    else {
        //open file
        ifstream fin;
        fin.open(path);
        //if cannot open file
        if (!fin.is_open()) {
            error(CANNOT_OPEN_FILE);
            exit(1);
        }
        //reading file line by line
        getline(fin, lkp);
        getline(fin, lpk);
        fin.close();//close file
    }
    //print result
    BinaryTree<char> binTree(lkp, lpk);
    cout<<"KLP is: ";
    binTree.printKLP(binTree.tree);
    cout<<endl;
    cout<<"Tree:"<<endl;
    //print tree
    binTree.printTree(binTree.tree, 0);
    return 0;
}
