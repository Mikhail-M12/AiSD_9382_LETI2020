#include <iostream>
#include <fstream>
using namespace std;

struct RandomBinarySearchTree {
    RandomBinarySearchTree* left;// left subtree
    RandomBinarySearchTree* right;// right subtree
    RandomBinarySearchTree* parent;// parent of tree
    int count;// count of char
    char data;// value
};

RandomBinarySearchTree* createTree(char data, RandomBinarySearchTree* randomBinarySearchTree, RandomBinarySearchTree* parent) {
    //create new element of tree
    if (randomBinarySearchTree == nullptr) {
        cout<<"Create new leaf with data: "<<data<<endl;
        randomBinarySearchTree = new RandomBinarySearchTree;
        randomBinarySearchTree->data = data;
        randomBinarySearchTree->count = 1;
        randomBinarySearchTree->left = nullptr;
        randomBinarySearchTree->right = nullptr;
        randomBinarySearchTree->parent = parent;
    }
    else if (data < randomBinarySearchTree->data) {
        cout<<data<<" < "<< randomBinarySearchTree->data<<" move to left tree\n";
        randomBinarySearchTree->left = createTree(data, randomBinarySearchTree->left, randomBinarySearchTree);
    }
    else if (data == randomBinarySearchTree->data) {
        cout<<data<<" = "<< randomBinarySearchTree->data<<" move there\n";
        randomBinarySearchTree->count++;
    }
    else {
        cout<<data<<" > "<< randomBinarySearchTree->data<<" move to right tree\n";
        randomBinarySearchTree->right = createTree(data, randomBinarySearchTree->right, randomBinarySearchTree);
    }
    return randomBinarySearchTree;
}

RandomBinarySearchTree* findMax(RandomBinarySearchTree* root) {

    if(root == nullptr) return nullptr;

    while(root->right) {
        root = root->right;
    }
    return root;
}
RandomBinarySearchTree* deleteNode(RandomBinarySearchTree* root, char data, bool replaced) {
    //cannot find tree
    if(root == nullptr) {
        cout<<"There no element\n";
        return root;
    }
    else if(data < root->data)
        root->left = deleteNode(root->left, data, replaced);
    else if (data > root->data)
        root->right = deleteNode(root->right, data, replaced);
    else {
        //there no subtree
        if (root->count > 1 && replaced) root->count--;
        else if (!root->parent && !root->left && !root->right) {
            cout<<"empty tree";
            exit(1);
        }
        else if(root->right == nullptr && root->left == nullptr){
            delete root;
            root = nullptr;
        }
            //has right subtree
        else if(root->right == nullptr) {
            root = root->left;
        }
        // has left subtree
        else if(root->left == nullptr) {
            root= root->right;
        }
            // has two subtrees
        else {
            RandomBinarySearchTree* temp = findMax(root->left);
            root->data = temp->data;
            root->count = temp->count;
            root->left = deleteNode(root->left, temp->data, false);
        }
    }
    return root;
}

void printLKP(RandomBinarySearchTree* randomBinarySearchTree) {
    if (randomBinarySearchTree->left) printLKP(randomBinarySearchTree->left);
    cout<<randomBinarySearchTree->data<<"["<<randomBinarySearchTree->count<<"]";
    if (randomBinarySearchTree->right) printLKP(randomBinarySearchTree->right);
}

void removeElement(RandomBinarySearchTree* randomBinarySearchTree, int mode) {
    char removeElem;// remove element
    string tmp;// rubbish
    if (mode) {
        do {
            cout<<"If you want to stop press '+'\nEnter remove element:\n";
            cin>>removeElem;
            randomBinarySearchTree = deleteNode(randomBinarySearchTree, removeElem, true);
            cout<<"LKP of tree:\n";
            printLKP(randomBinarySearchTree);
            cout<<"\n";//
        } while (removeElem != '+');
    } else {
        ifstream fin;
        fin.open("input.txt");
        //if cannot open file
        if (!fin.is_open()) {
            cout<<"Cannot open file";
            exit(1);
        }
        getline(fin, tmp);
        do {
            //reading file char by char
            fin>>removeElem;
            if (!fin.eof()) {
                randomBinarySearchTree = deleteNode(randomBinarySearchTree, removeElem, true);
                cout<<"LKP of tree:\n";
                printLKP(randomBinarySearchTree);
                cout<<"\n";
            }

        } while (!fin.eof());

        fin.close();//close file
    }


}

void enterTree() {
    auto* randomBinarySearchTree = new RandomBinarySearchTree;// create tree
    string rawTree;    // string of tree
    string path = "input.txt";  // path to input file
    int typeOfInput;// 1 if console
    cout<<"Enter '1' if you wanna write down binary tree in console otherwise write down any letter or number:\n";
    cin>>typeOfInput;
    //input from console
    if (typeOfInput == 1){
        cout<<"Enter tree:\n";
        cin>>rawTree;
        //if tree empty
        if (rawTree.empty()) {
            cout<<"empty tree";
            exit(1);
        }

    }
    else {
        //open file
        ifstream fin;
        fin.open(path);
        //if cannot open file
        if (!fin.is_open()) {
            cout<<"Cannot open file";
            exit(1);
        }
        //reading file line by line
        getline(fin, rawTree);
        if (rawTree.empty()) {
            cout<<"empty tree";
            exit(1);
        }
        fin.close();//close file
    }
    //create main node
    randomBinarySearchTree->data = rawTree[0];
    randomBinarySearchTree->count = 1;
    randomBinarySearchTree->left = nullptr;
    randomBinarySearchTree->right = nullptr;
    randomBinarySearchTree->parent = nullptr;
    // loop for adding element in tree
    for (int i = 1; i < rawTree.length(); i++) {
       randomBinarySearchTree = createTree(rawTree[i], randomBinarySearchTree, randomBinarySearchTree);
    }
    if (typeOfInput == 1)
        removeElement(randomBinarySearchTree, 1);
    else removeElement(randomBinarySearchTree, 0);
}
int main() {
    enterTree();
    return 0;
}
