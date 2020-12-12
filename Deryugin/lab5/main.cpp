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


RandomBinarySearchTree* searchLowest(RandomBinarySearchTree* randomBinarySearchTree, RandomBinarySearchTree* temp) {
    // if there is left subtree
    if (randomBinarySearchTree->left) searchLowest(randomBinarySearchTree->left, temp);
    // if subtree hasn't right subtree
    else if (!randomBinarySearchTree->right) {
        temp->data = randomBinarySearchTree->data;
        temp->count = randomBinarySearchTree->count;
        if (randomBinarySearchTree->parent->right->data == randomBinarySearchTree->data)
            randomBinarySearchTree->parent->right = nullptr;
        else if (randomBinarySearchTree->parent->left->data == randomBinarySearchTree->data)
            randomBinarySearchTree->parent->left = nullptr;
        return temp;
        //if left subtree has right subtree
    } else if (randomBinarySearchTree->right) {
        temp->data = randomBinarySearchTree->data;
        temp->count = randomBinarySearchTree->count;
        randomBinarySearchTree->data = randomBinarySearchTree->right->data;
        randomBinarySearchTree->count = randomBinarySearchTree->right->count;
        randomBinarySearchTree->left = randomBinarySearchTree->right->left;
        randomBinarySearchTree->right = randomBinarySearchTree->right->right;
        return temp;
    }
}

void removeElem(RandomBinarySearchTree* randomBinarySearchTree) {
    if (!randomBinarySearchTree->parent && !randomBinarySearchTree->left && !randomBinarySearchTree->right && randomBinarySearchTree->count ==1) {
        delete randomBinarySearchTree;
        cout<<"empty tree";
        exit(1);
    }
    // if there is more then 1 element with this value
    if (randomBinarySearchTree->count > 1) randomBinarySearchTree->count--;
    // remove leaf
    else if (!randomBinarySearchTree->left && !randomBinarySearchTree->right && randomBinarySearchTree->count == 1) {
        if (randomBinarySearchTree->parent->right->data == randomBinarySearchTree->data)
            randomBinarySearchTree->parent->right = nullptr;
        else if (randomBinarySearchTree->parent->left->data == randomBinarySearchTree->data)
            randomBinarySearchTree->parent->left = nullptr;
    }

    //if remove node has only left subtree
    else if (randomBinarySearchTree->left && !randomBinarySearchTree->right) {
        randomBinarySearchTree->data = randomBinarySearchTree->left->data;
        randomBinarySearchTree->count = randomBinarySearchTree->left->count;
        randomBinarySearchTree->left = randomBinarySearchTree->left->left;
        if (randomBinarySearchTree->left)
            randomBinarySearchTree->right = randomBinarySearchTree->left->right;
    }
    // if remove node has only right subtree
    else if (!randomBinarySearchTree->left && randomBinarySearchTree->right)  {
        randomBinarySearchTree->data = randomBinarySearchTree->right->data;
        randomBinarySearchTree->count = randomBinarySearchTree->right->count;
        randomBinarySearchTree->left = randomBinarySearchTree->right->left;
        randomBinarySearchTree->right = randomBinarySearchTree->right->right;
    }
    //if remove leaf has left and right subtree
    else if (randomBinarySearchTree->left && randomBinarySearchTree->right)  {
        RandomBinarySearchTree* temp = randomBinarySearchTree;
        randomBinarySearchTree = searchLowest(randomBinarySearchTree->right, temp);
    }

}

void search(char elem, RandomBinarySearchTree* randomBinarySearchTree) {
    // cannot find element in tree
    if (!randomBinarySearchTree) {
        cout<<"There no this element\n";
        return;
    }
    if (elem < randomBinarySearchTree->data) search(elem, randomBinarySearchTree->left);
    else if (elem > randomBinarySearchTree->data) search(elem, randomBinarySearchTree->right);
    else removeElem(randomBinarySearchTree);
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
            search(removeElem, randomBinarySearchTree);
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
                search(removeElem, randomBinarySearchTree);
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
