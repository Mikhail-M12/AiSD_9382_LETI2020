#include <iostream>
#include <fstream>

using namespace std;

enum Errors{
    INCORRECT_FIRST_SYMBOL,
    NO_CLOSE_BRACKET,
    UNFINISHED_EXPRESSION,
    NO_OPEN_BRACKET,
    INCORRECT_LENGTH,
    CANNOT_OPEN_FILE,
    EXTRA_SYMBOLS
};

struct binaryRocker; //binaryRocker struct declaration

struct shoulder {
    bool isBinaryRocker; // true: binaryRocker, false: weight
    int length;
    int weight;
    binaryRocker* binaryRockerPtr;
}; //end shoulder

struct binaryRocker {
    shoulder *left;
    shoulder *right;
}; //end binaryRocker

// Functions prototypes
void error(Errors error);
shoulder* makeLength (char character);
void makeWidth(char character, shoulder* shoulder);
binaryRocker* readBinaryRocker( binaryRocker* binRock, char character, ifstream& fin);
shoulder * readShoulder(char prev, binaryRocker* binRock, ifstream& fin);
void printResult(const binaryRocker* binRock, int side, int tab);
unsigned int numbers(unsigned int count, const binaryRocker* binRock, int tab);
void destroy(binaryRocker binRock);


void error(Errors error) {
    if (error == INCORRECT_FIRST_SYMBOL) cout<<"Incorrect first symbol\n";
    if (error == NO_CLOSE_BRACKET) cout<<"No close bracket\n";
    if (error == UNFINISHED_EXPRESSION) cout<<"Something went wrong\n";
    if (error == NO_OPEN_BRACKET) cout<<"Shoulder must start with '('\n";
    if (error == INCORRECT_LENGTH) cout<<"Length of shoulder must be number\n";
    if (error == CANNOT_OPEN_FILE) cout<<"Cannot open file\n";
    if (error == EXTRA_SYMBOLS) cout<<"Extra symbols\n";
}// end error func


shoulder* makeLength(char character) {
    auto *sh = new shoulder;
    sh->length = character - 48; // char to int
    return sh;
}// end makeLength func


void makeWeight(char character, shoulder* shoulder) {
    // set weight in shoulder
    shoulder->weight = character - 48;// char to int
    shoulder->isBinaryRocker = false;
    shoulder->binaryRockerPtr = nullptr;
}// end makeWeight func


binaryRocker* readBinaryRocker(binaryRocker* binRock, char character, ifstream& fin) {
    if (character == '(') {
        // Create left and right shoulder for binary rocker
        binRock->left = readShoulder(character, binRock, fin);
        binRock->right = readShoulder(character, binRock, fin);
    }
    // If first symbol isn't '('
    else {
        error(INCORRECT_FIRST_SYMBOL);
        exit(1);
    }
    fin>>character;
    // if close symbol isn't ')'
    if (character != ')') {
        error(NO_CLOSE_BRACKET);
        exit(1);
    }
    return binRock;
} //end readBinaryRocker func


shoulder* readShoulder(char prev, binaryRocker* binRock, ifstream& fin) { //prev - previous character
        auto* sh = new shoulder;

        //if there are unfinished expressions
        if (!(fin>>prev)) {
            error(UNFINISHED_EXPRESSION);
            exit(1);
        }
        if (prev != '(') {
            error(NO_OPEN_BRACKET);
            exit(1);
        }
        fin>>prev;
        // set length if it's a number otherwise throw an error
        if (isdigit(prev)) sh = makeLength(prev);
        else{
            error(INCORRECT_LENGTH);
            exit(1);
        }
        fin>>prev;
        // if shoulder is weight, set weight, otherwise create binary rocker
        if (isdigit(prev)){
            makeWeight(prev, sh);
        }
        else{
            auto* br = new binaryRocker;
            sh->binaryRockerPtr = readBinaryRocker(br, prev, fin);
            sh->isBinaryRocker = true;
            sh->weight = 0;
        }
        fin>>prev;
        if (prev != ')') {
            error(NO_CLOSE_BRACKET);
            exit(1);
        }
        return sh;

}// end readShoulder func


void printResult(const binaryRocker* binRock, int side, int tab) {//side 1 - left, side 2 - right
    if (side == 1) {
        if (!binRock->left->isBinaryRocker) {
            for (int i = 0; i < tab; i++) cout<<"\t";
            cout<<"Left shoulder ("<<binRock->left->length<<" "<<binRock->left->weight<<")\n";
        }
        else {
            for (int i = 0; i < tab; i++) cout<<"\t";
            cout<<"Left shoulder ("<<binRock->left->length<<" (  ))\n";
        }
    }
    else {
        if (!binRock->right->isBinaryRocker) {
            for (int i = 0; i < tab; i++) cout<<"\t";
            cout<<"Right shoulder ("<<binRock->right->length<<" "<<binRock->right->weight<<")\n";
        }
        else {
            for (int i = 0; i < tab; i++) cout<<"\t";
            cout<<"Right shoulder ("<<binRock->right->length<<" (  ))\n";
        }
    }
}


unsigned int numbers(unsigned int count, const binaryRocker* binRock, int tab) {
    //check left shoulder
    if (binRock->left->isBinaryRocker) {
        printResult(binRock, 1, tab);
        count = numbers(count, binRock->left->binaryRockerPtr, tab +1);
    }
    else {
        printResult(binRock, 1, tab);
        count++;
    }
    //check right shoulder
    if (binRock->right->isBinaryRocker) {
        printResult(binRock, 2, tab);
        count = numbers(count, binRock->right->binaryRockerPtr, tab + 1);
    }
    else {
        printResult(binRock, 2, tab);
        count++;
    }

    return count;
}// end numbers func




void destroy(binaryRocker* binRock) {
    if (binRock->left->weight == 0) destroy(binRock->left->binaryRockerPtr);
    else delete binRock->left;
    if (binRock->right->weight == 0) destroy(binRock->right->binaryRockerPtr);
    else delete binRock->right;
    delete binRock;
}// end destroy func


int main ( ) {
    char character;// previous character
    string path = "input.txt";// path to input file
    unsigned int result;//answer on question
    int typeOfInput;// 1 if console
    string consoleBinRock;
    cout<<"Enter '1' if you wanna write down binary rocker in console otherwise write down any letter or number:\n";
    cin>>typeOfInput;
    //input from console
    if (typeOfInput == 1){
        cout<<"Enter binary rocker:\n";
        cin>>consoleBinRock;
        ofstream fin(path);
        fin<<consoleBinRock;
        fin.close();

    }
    //open file
    ifstream fin;
    fin.open(path);
    if (!fin.is_open()){
        error(CANNOT_OPEN_FILE);
        exit(1);
    }
    auto* binRock = new binaryRocker;
    fin>>character;
    readBinaryRocker(binRock, character,  fin);
    if (fin>>character){
        error(EXTRA_SYMBOLS);
        exit(1);
    }
    //print intermediate and final result
    cout<<"Intermediate results:\n";
    result = numbers(0, binRock, 0);
    cout<<"Count of weights: "<<result;//write answer
    destroy(binRock);
    fin.close();//close file
    return 0;
}// end main func
