#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>

#define MAX_NUMBER 1000
#define MAX_COUNT_OF_TREES 100
static bool mode;

using namespace std;

struct RandomBinarySearchTree {
    RandomBinarySearchTree* left;// left subtree
    RandomBinarySearchTree* right;// right subtree
    RandomBinarySearchTree* parent;// parent of tree
    int count;// count of char
    int data;// value
    int height;
};

struct Results {
    int countOfTrees;// count of trees
    int* countOfNumbersInTree;// array with counts of numbers in trees
    int* depth;// depth of trees
    double* averageIterationsOfInsert;// average count of iteration
    double* averageIterationsOfDeletion;// average count of deletion
};


RandomBinarySearchTree* createTree(int data, RandomBinarySearchTree* randomBinarySearchTree, RandomBinarySearchTree* parent) {
    //create new element of tree
    if (randomBinarySearchTree == nullptr) {
        randomBinarySearchTree = new RandomBinarySearchTree;
        randomBinarySearchTree->data = data;
        randomBinarySearchTree->count = 1;
        randomBinarySearchTree->left = nullptr;
        randomBinarySearchTree->right = nullptr;
        randomBinarySearchTree->parent = parent;
        randomBinarySearchTree->height = parent->height + 1;
    }
    else if (data < randomBinarySearchTree->data) {
        randomBinarySearchTree->left = createTree(data, randomBinarySearchTree->left, randomBinarySearchTree);
    }
    else if (data == randomBinarySearchTree->data) {
        randomBinarySearchTree->count++;
    }
    else {
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

RandomBinarySearchTree* deleteNode(RandomBinarySearchTree* root, int data, bool replaced, int& sumOfIteration, bool& empty) {
    //cannot find tree
    if(root == nullptr) {
        if (mode) cout<<"There no element: "<<data<<endl;
        empty = true;
        return root;
    }
    else if(data < root->data)
        root->left = deleteNode(root->left, data, replaced,  sumOfIteration, empty);
    else if (data > root->data)
        root->right = deleteNode(root->right, data, replaced, sumOfIteration, empty);
    else {
        //there no subtree
        if (root->count > 1 && replaced) {
            root->count--;
            if (mode) {
                cout<<"Element: "<<data<<" will be deleted. ";
                cout<<"Count of iterations: "<<root->height<<endl;
            }
            sumOfIteration+= root->height;
        }
        else if (!root->parent && !root->left && !root->right) {
            if (mode) {
                cout<<"empty tree";
            }
            return nullptr;
        }
        else if(root->right == nullptr && root->left == nullptr){
            if (mode) {
                cout<<"Element: "<<data<<" will be deleted. ";
                cout<<"Count of iterations: "<<root->height<<endl;
            }
            sumOfIteration+= root->height;
            delete root;
            root = nullptr;
        }
            //has right subtree
        else if(root->right == nullptr) {
            if (mode) {
                cout<<"Element: "<<data<<" will be deleted. ";
                cout<<"Count of iterations: "<<root->height<<endl;
            }
            sumOfIteration+= root->height;
            root = root->left;
        }
        // has left subtree
        else if(root->left == nullptr) {
            if (mode) {
                cout<<"Element: "<<data<<" will be deleted. ";
                cout<<"Count of iterations: "<<root->height<<endl;
            }

            sumOfIteration+= root->height;
            root= root->right;
        }
            // has two subtrees
        else {
            RandomBinarySearchTree* temp = findMax(root->left);
            if (mode) {
                cout<<"Element: "<<data<<" will be deleted. ";
                cout<<"Count of iterations: "<<root->height<<endl;
            }
            sumOfIteration+= root->height;
            root->data = temp->data;
            root->count = temp->count;
            root->left = deleteNode(root->left, temp->data, false, sumOfIteration, empty);
        }
    }
    return root;
}


void enterTree(int* rawTree, int numbersInLine, RandomBinarySearchTree* randomBinarySearchTree) {

    //create main node
    randomBinarySearchTree->data = rawTree[0];
    randomBinarySearchTree->count = 1;
    randomBinarySearchTree->left = nullptr;
    randomBinarySearchTree->right = nullptr;
    randomBinarySearchTree->parent = nullptr;
    randomBinarySearchTree->height = 1;
    // loop for adding element in tree
    for (int i = 1; i < numbersInLine; i++) {
       randomBinarySearchTree = createTree(rawTree[i], randomBinarySearchTree, randomBinarySearchTree);
    }
}

int height(RandomBinarySearchTree* randomBinarySearchTree) {
    if (!randomBinarySearchTree) return 0;
    if (height(randomBinarySearchTree->left) > height(randomBinarySearchTree->right)) return height(randomBinarySearchTree->left) + 1;
    else return height(randomBinarySearchTree->right) + 1;
}

bool searchIdeal(RandomBinarySearchTree* randomBinarySearchTree) {
    if (randomBinarySearchTree == nullptr) return true;
    return  (searchIdeal(randomBinarySearchTree->left) && searchIdeal(randomBinarySearchTree->right)
    && abs(height(randomBinarySearchTree->left) - height(randomBinarySearchTree->right)) <= 1);
}

int searchAndInsert(int data, RandomBinarySearchTree* randomBinarySearchTree, RandomBinarySearchTree* parent) {
    if (!randomBinarySearchTree) {
        randomBinarySearchTree = new RandomBinarySearchTree;
        randomBinarySearchTree->height = parent->height + 1;
        randomBinarySearchTree->left = nullptr;
        randomBinarySearchTree->right = nullptr;
        randomBinarySearchTree->parent = parent;
        randomBinarySearchTree->data = data;
        randomBinarySearchTree->count = 1;
        return randomBinarySearchTree->height;
    }
    else if (data < randomBinarySearchTree->data) return searchAndInsert(data, randomBinarySearchTree->left, randomBinarySearchTree);
    else if (data > randomBinarySearchTree->data) return searchAndInsert(data, randomBinarySearchTree->right, randomBinarySearchTree);
    else {
        randomBinarySearchTree->count++;
        return randomBinarySearchTree->height;
    }
}

int maxDepth(RandomBinarySearchTree* randomBinarySearchTree) {
    if (!randomBinarySearchTree) return 0;
    if (maxDepth(randomBinarySearchTree->left) <= maxDepth(randomBinarySearchTree->right)) return maxDepth(randomBinarySearchTree->right) + 1;
    else return maxDepth(randomBinarySearchTree->left) + 1;
}

void generateInsertElements(RandomBinarySearchTree** randomBinarySearchTree, int countOfTrees, Results* results) {
    int countOfInsert, iteration, sumOfIteration = 0, depth;
    cout<<"Enter count of element which will be insert\n";
    do cin>>countOfInsert; while(countOfInsert <= 0);

    int randomElements[countOfInsert];

    if (mode) cout<<"Random elements: ";
    for (int i = 0; i < countOfInsert; i++) {
        randomElements[i] = rand() % MAX_NUMBER;
        if (mode) cout<<randomElements[i]<<" ";
    }
   if (mode) cout<<endl;

    for (int i = 0; i < countOfTrees; i++) {
        if (mode) {
            if (i == 0) cout<<"1st Tree:\n";
            else if (i == 1) cout<<"2nd Tree:\n";
            else if (i == 2) cout<<"3rd Tree:\n";
            else cout<<i + 1<<"th Tree:\n";
            cout<<"Maximum height of this tree: "<<maxDepth(randomBinarySearchTree[i])<<endl;
        }

        depth = maxDepth(randomBinarySearchTree[i]);
        results->depth[i] = depth;
        for (int j = 0; j < countOfInsert; j++) {
            iteration = searchAndInsert(randomElements[j], randomBinarySearchTree[i], randomBinarySearchTree[i]);
            sumOfIteration+= iteration;
            if (mode) {
                cout<<"Element: "<<randomElements[j]<<" will be insert. ";
                cout<<"Count of iterations(height): "<<iteration<<".\n";
            }
        }
        results->averageIterationsOfInsert[i] = static_cast<double>(sumOfIteration)/countOfInsert;
        sumOfIteration = 0;
        if (mode) cout<<endl;
    }

}

void generateRemoveElements(RandomBinarySearchTree** randomBinarySearchTree, int countOfTrees, Results* results) {
    int countOfDeletion = 0, sumOfIterations = 0, tmp = 0;
    bool empty = false;
    cout<<"\nEnter count of element which will be delete\n";
    do cin>>countOfDeletion; while(countOfDeletion <= 0);

    int randomElements[countOfDeletion];

    if (mode) cout<<"Random elements: ";
    for (int i = 0; i < countOfDeletion; i++) {
        randomElements[i] = rand() % MAX_NUMBER;
        if (mode) cout<<randomElements[i]<<" ";
    }
    cout<<endl;

    for (int i = 0; i < countOfTrees; i++) {
        if (mode) {
            if (i == 0) cout<<"1st Tree:\n";
            else if (i == 1) cout<<"2nd Tree:\n";
            else if (i == 2) cout<<"3rd Tree:\n";
            else cout<<i + 1<<"th Tree:\n";
            cout<<"Maximum height of this tree: "<<maxDepth(randomBinarySearchTree[i])<<endl;
        }
        for (int j = 0; j < countOfDeletion; j++) {
            if (mode) cout<<j<<") ";
            randomBinarySearchTree[i] = deleteNode(randomBinarySearchTree[i], randomElements[j], true, sumOfIterations, empty);
            if (empty) tmp++;
            empty = false;
            if (!randomBinarySearchTree[i]) {
                break;
            }
        }
        results->averageIterationsOfDeletion[i]  = countOfDeletion == tmp? static_cast<double>(sumOfIterations)/countOfDeletion: static_cast<double>(sumOfIterations)/(countOfDeletion - tmp);
        sumOfIterations = 0;
        tmp = 0;
        if (mode) cout<<endl;
    }
}

void printResults(Results* results) {
    double averageInsert = 0, averageDeletion = 0, averageDepth = 0, averageCountOfNumbers = 0;
    cout<<endl<<endl<<endl<<endl;
    cout<<"Count of trees: "<< results->countOfTrees<<".\n";
    for (int i = 0; i < results->countOfTrees; i++) {
        if (mode) {
            cout<<i<<" tree has "<<results->countOfNumbersInTree[i]<<" count of numbers in start.\n";
            cout<<"Average count to insert is: "<<results->averageIterationsOfInsert[i]<<". "<<
            "Average count to deletion is: "<<results->averageIterationsOfDeletion[i]<<". Max height of tree: "<<
            results->depth[i]<<endl;
        }
        averageInsert+= results->averageIterationsOfInsert[i];
        averageDeletion+= results->averageIterationsOfDeletion[i];
        averageDepth+= results->depth[i];
        averageCountOfNumbers+= results->countOfNumbersInTree[i];
    }

    cout<<endl<<endl<<endl<<endl;

    cout<<"Average iteration to insert of all trees: "<<averageInsert/results->countOfTrees<<endl;
    cout<<"Average iteration to deletion of all trees: "<<averageDeletion/results->countOfTrees<<endl;
    cout<<"Average n: "<<averageCountOfNumbers/results->countOfTrees<<endl;
}

void removeIdeal(RandomBinarySearchTree** randomBinarySearchTree, int countOfTrees, Results* results, const int* countInLine) {

    int idealTrees = 0, j = 0;
    for (int i = 0; i < countOfTrees; i++) {
        if (searchIdeal(randomBinarySearchTree[i])) {
            idealTrees++;
            randomBinarySearchTree[i] = nullptr;
        }
    }


    if (idealTrees == 1) cout<<"It's "<< idealTrees<<" ideal tree. It will be delete to remove complexity of best case\n";
    else if (idealTrees > 1) cout<<"There is "<< idealTrees<<" ideal trees. They will be delete to remove complexity of best case\n";
    // array without ideal trees
    auto** treesWithoutIdeal = new RandomBinarySearchTree*[countOfTrees - idealTrees];

    results->countOfNumbersInTree = new int[countOfTrees - idealTrees];
    results->averageIterationsOfInsert = new double [countOfTrees - idealTrees];
    results->averageIterationsOfDeletion = new double[countOfTrees - idealTrees];
    results->depth = new int[countOfTrees - idealTrees];

    for (int i = 0 ; i < countOfTrees; i++) {
        if (randomBinarySearchTree[i]) {
            treesWithoutIdeal[j] = new RandomBinarySearchTree;
            treesWithoutIdeal[j] = randomBinarySearchTree[i];
            results->countOfNumbersInTree[j] = countInLine[i];
            j++;
        }
    }

    results->countOfTrees = countOfTrees - idealTrees;

    //insert in trees
    generateInsertElements(treesWithoutIdeal,countOfTrees - idealTrees, results);

    //remove from trees
    generateRemoveElements(treesWithoutIdeal, countOfTrees - idealTrees, results);


    printResults(results);
}

void makeTrees() {
    //results
    auto* results = new Results;
    // count of trees
    int countOfTrees= rand() % MAX_COUNT_OF_TREES + 10;

    //array of count of integer in lines
    int countInLine[countOfTrees];
    cout<<"Built "<<countOfTrees<<" trees\n";

    //write count of numbers in trees
    for (int i = 0; i < countOfTrees; i++) {
            countInLine[i] = rand() % MAX_NUMBER + 10;
    }
    // array of array of lines
    int **arrayOfLines = new int*[countOfTrees];
    for (int i = 0; i < countOfTrees; i++) arrayOfLines[i] = new int[countInLine[i]];
    // create and print lines
    for (int i = 0; i < countOfTrees; i++) {
        for (int j = 0; j < countInLine[i]; j++) {
            arrayOfLines[i][j] = (rand() % MAX_NUMBER);
        }
    }
    cout<<endl;
    //create trees
    auto** arrayOfTrees = new RandomBinarySearchTree*[countOfTrees];
    for (int i = 0; i < countOfTrees; i++) arrayOfTrees[i] = new RandomBinarySearchTree;

    // fill trees
    for (int i = 0; i < countOfTrees; i++) {
        enterTree(arrayOfLines[i], countInLine[i], arrayOfTrees[i]);
    }

    removeIdeal(arrayOfTrees, countOfTrees, results, countInLine);
}

int main() {
    char modes;
    srand(time(nullptr));
    cout<<"Press 'q' to show intermediate results, otherwise press any button\n";
    cin>>modes;
    mode = modes == 'q';
    makeTrees();
    return 0;
}
