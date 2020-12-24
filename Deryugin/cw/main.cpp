#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>

#define MAX_NUMBER 1000
#define MAX_COUNT_OF_TREES 10
#define MAX_NUMBER_WORST_CASE 8
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
    int* countOfTrees;// count of trees
    int** countOfNumbersInTree;// array with counts of numbers in trees
    int** depth;// depth of trees
    double** averageIterationsOfInsert;// average count of iteration
    double** averageIterationsOfDeletion;// average count of deletion
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

void generateInsertElements(RandomBinarySearchTree** randomBinarySearchTree, int countOfTrees, Results* results, int index) {
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
        results->depth[index][i] = depth;
        for (int j = 0; j < countOfInsert; j++) {
            iteration = searchAndInsert(randomElements[j], randomBinarySearchTree[i], randomBinarySearchTree[i]);
            sumOfIteration+= iteration;
            if (mode) {
                cout<<"Element: "<<randomElements[j]<<" will be insert. ";
                cout<<"Count of iterations(height): "<<iteration<<".\n";
            }
        }
        results->averageIterationsOfInsert[index][i] = static_cast<double>(sumOfIteration)/countOfInsert;
        sumOfIteration = 0;
        if (mode) cout<<endl;
    }

}

void generateRemoveElements(RandomBinarySearchTree** randomBinarySearchTree, int countOfTrees, Results* results, int index) {
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
                tmp+= countOfDeletion - j;
                break;
            }
        }
        results->averageIterationsOfDeletion[index][i]  = countOfDeletion == tmp? static_cast<double>(sumOfIterations)/countOfDeletion: static_cast<double>(sumOfIterations)/(countOfDeletion - tmp);
        sumOfIterations = 0;
        tmp = 0;
        if (mode) cout<<endl;
    }
}

void printResults(Results* results, int index) {
    double averageInsert = 0, averageDeletion = 0, averageDepth = 0, averageCountOfNumbers = 0;
    cout<<endl;
    cout<<"Count of trees: "<< results->countOfTrees[index]<<".\n";
    for (int i = 0; i < results->countOfTrees[index]; i++) {
        if (mode) {
            cout<<i<<" tree has "<<results->countOfNumbersInTree[index][i]<<" count of numbers in start.\n";
            cout<<"Average count to insert is: "<<results->averageIterationsOfInsert[index][i]<<". "<<
            "Average count to deletion is: "<<results->averageIterationsOfDeletion[index][i]<<". Max height of tree: "<<
            results->depth[index][i]<<endl;
        }
        averageInsert+= results->averageIterationsOfInsert[index][i];
        averageDeletion+= results->averageIterationsOfDeletion[index][i];
        averageDepth+= results->depth[index][i];
        averageCountOfNumbers+= results->countOfNumbersInTree[index][i];
    }

    cout<<endl;

    cout<<"Average iteration to insert of all trees: "<<averageInsert/results->countOfTrees[index]<<endl;
    cout<<"Average iteration to deletion of all trees: "<<averageDeletion/results->countOfTrees[index]<<endl;
    cout<<"Average n: "<<averageCountOfNumbers/results->countOfTrees[index]<<endl;
}



void makeTrees() {
    //results
    auto* results = new Results;
    // count of trees
    int countOfTreesWorstCase= rand() % MAX_COUNT_OF_TREES + 10;
    int countOfTreesAverageCase = rand() % MAX_COUNT_OF_TREES + 10;
    int startWith;

    //create struct of results
    results->countOfTrees = new int[2];
    results->countOfTrees[0] = countOfTreesAverageCase;
    results->countOfTrees[1] = countOfTreesWorstCase;

    results->countOfNumbersInTree = new int*[2];
    results->countOfNumbersInTree[0] = new int[countOfTreesAverageCase];
    results->countOfNumbersInTree[1] = new int[countOfTreesWorstCase];

    results->averageIterationsOfInsert = new double*[2];
    results->averageIterationsOfInsert[0] = new double[countOfTreesAverageCase];
    results->averageIterationsOfInsert[1] = new double[countOfTreesWorstCase];

    results->averageIterationsOfDeletion = new double*[2];
    results->averageIterationsOfDeletion[0] = new double[countOfTreesAverageCase];
    results->averageIterationsOfDeletion[1] = new double[countOfTreesWorstCase];

    results->depth = new int*[2];
    results->depth[0] = new int[countOfTreesAverageCase];
    results->depth[1] = new int[countOfTreesWorstCase];

    //array of count of integer in lines
    int countInLineAverageCase[countOfTreesAverageCase], countInLineWorstCase[countOfTreesWorstCase];

    cout<<"Built "<<countOfTreesAverageCase<<" trees in average case\n";
    cout<<"Built "<<countOfTreesWorstCase<<" trees in worst case\n";

    //write count of numbers in trees
    for (int i = 0; i < countOfTreesAverageCase; i++) {
        countInLineAverageCase[i] = rand() % 100000 + 30000;
        results->countOfNumbersInTree[0][i] = countInLineAverageCase[i];
    }

    for (int i = 0; i < countOfTreesWorstCase; i++) {
        countInLineWorstCase[i] = rand() %  MAX_NUMBER_WORST_CASE + 10;
        results->countOfNumbersInTree[1][i] = countInLineWorstCase[i];
    }

    // array of array of lines
    int **arrayOfLinesAverageCase = new int*[countOfTreesAverageCase];
    int **arrayOfLinesWorstCase = new int*[countOfTreesWorstCase];

    for (int i = 0; i < countOfTreesAverageCase; i++) arrayOfLinesAverageCase[i] = new int[countInLineAverageCase[i]];
    for (int i = 0; i < countOfTreesWorstCase; i++) arrayOfLinesWorstCase[i] = new int[countInLineWorstCase[i]];

    // create and print lines
    for (int i = 0; i < countOfTreesAverageCase; i++) {
        for (int j = 0; j < countInLineAverageCase[i]; j++) {
            arrayOfLinesAverageCase[i][j] = (rand() % MAX_NUMBER);
        }
    }

    for (int i = 0; i < countOfTreesWorstCase; i++) {
        startWith = rand() % 100;
        for (int j = 0; j < countInLineWorstCase[i]; j++) {
            arrayOfLinesWorstCase[i][j] = startWith++;
        }
    }

    cout<<endl;
    //create trees
    auto** arrayOfTreesAverageCase = new RandomBinarySearchTree*[countOfTreesAverageCase];
    auto** arrayOfTreesWorstCase = new RandomBinarySearchTree*[countOfTreesWorstCase];

    for (int i = 0; i < countOfTreesAverageCase; i++) arrayOfTreesAverageCase[i] = new RandomBinarySearchTree;
    for (int i = 0; i < countOfTreesWorstCase; i++) arrayOfTreesWorstCase[i] = new RandomBinarySearchTree;

    // fill trees
    for (int i = 0; i < countOfTreesAverageCase; i++) {
        enterTree(arrayOfLinesAverageCase[i], countInLineAverageCase[i], arrayOfTreesAverageCase[i]);
    }

    for (int i = 0; i < countOfTreesWorstCase; i++) {
        enterTree(arrayOfLinesWorstCase[i], countInLineWorstCase[i], arrayOfTreesWorstCase[i]);
    }

    generateInsertElements(arrayOfTreesAverageCase,countOfTreesAverageCase, results, 0);
    generateInsertElements(arrayOfTreesWorstCase,countOfTreesWorstCase, results, 1);

    //remove from trees
    generateRemoveElements(arrayOfTreesAverageCase, countOfTreesAverageCase, results, 0);
    generateRemoveElements(arrayOfTreesWorstCase, countOfTreesWorstCase, results, 1);


    cout<<"Average Case:\n";
    printResults(results, 0);
    cout<<"Worst Case:\n";
    printResults(results, 1);
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
