#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <conio.h>
#include <Windows.h>
using namespace std;

class TREE
{
private:


    int Key;
    int Count;
    TREE *duk; //Корень дерева.
    TREE *Left;
    TREE *Right;
public:
    TREE() { duk = nullptr; }
    ~TREE();
    TREE **GetDuk() { return &duk; }
    void Search(int num, int* count,int n);
    void Tree (int, TREE **,char side,int depth, int parrent,bool dataShow);
    void TreeFromFile (int n,TREE **p,ifstream& in,char side,int depth,int parrent,bool dataShow);
    void print1(TREE ** root, short x, short y, short a, char c);
    void printDepth(int depth);
    void Vyvod (TREE **, int);
};
void TREE::printDepth(int depth){
    for(int i =0; i < depth; ++i){
        cout << "/\\";
    }
}

TREE::~TREE(){
    if(duk->Left) duk->Left->~TREE();
    if(duk->Right) duk->Right->~TREE();
    delete duk;
}

void TREE::Search(int num,int* count,int n) {
    if(this->duk != nullptr){
        duk->Search(num,count,n);
    }else{
        TREE *l =this->Left, *r = this->Right;
        if(l != nullptr){
            l->Search(num, count,n);
        }
        if(r != nullptr){
            r->Search(num, count,n);
        }

        if(Key == num) {
            cout<<"\n\tFound!"<<"\n________________________________________\n";
            cout<<Key<<" == "<<num<<'\n';
            Vyvod(&duk,n);

            *count += 1;
            cout<<"Count = "<< *count<<".\n________________________________________\n";
        }else{
            Vyvod(&duk,n);
            cout<<Key<<" != "<<num<<'\n';
        }

    }
}


int main ()
{
    //system ("cls"); fflush (stdin);
    TREE A;
    int n=0, count=0, depth = 0;
    int choise, search, fileOrConsole;

    while(TRUE){
        cout << "0 - Exit. 1 - Create Tree. 2 - Print tree. 3 - Search.\n";
        fflush (stdin);
        cin >> choise;
        switch(choise){
            case 0:
                exit (0);
                break;
            case 1:
                cout<<"1 - Console. 2 - File\n";
                if(!(cin>>fileOrConsole)) {
                    cout<<"Eror you should input only digit\n";
                    cin.clear();
                }else {
                    if (fileOrConsole == 2) {
                        cout<<"Show logs?\n 1 - Yes. 0 - No\n";
                        bool logs;
                        if(!(cin>>logs)){
                            cout<<"Eror you should input only digit\n";
                            cin.clear();
                            break;
                        }
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
                            in >> n;
                            A.TreeFromFile(n, A.GetDuk(), in, 'k', depth, 0,logs);
                            in.close();
                            cout << "A draft of the received data:\n";
                            A.Vyvod(A.GetDuk(), n);
                        }

                    } else {
                        cout<<"Show logs?\n 1 - Yes. 0 - No\n";
                        bool logs;
                        if(!(cin>>logs)){
                            cout<<"Eror you should input only digit\n";
                            cin.clear();
                            break;
                        }
                        cout << "Enter the number of vertices -...\n";
                        if((cin >> n)){
                            if (n == 0) {
                                cout << "Empty array!\n";
                            } else {
                                cout << "Enter keys...\n";
                                A.Tree(n, A.GetDuk(), 'k', depth, 0,logs);
                                cout << "A draft of the received data:\n";
                                A.Vyvod(A.GetDuk(), n);

                            }
                        }else{
                            cout<<"Eror you should input only digit\n";
                            cin.clear();
                        }
                    }
                    system("pause");
                }
                break;
            case 2:
                system ("cls");
                if(n==0){
                    cout<<"None tree\n";
                }else {
                    cout << "Tree: \n";
                    A.print1(A.GetDuk(), 74, 2, 3, 'k');
                }
                cout<<"\n\n\n\n\n";

                system ("pause");
                break;
            case 3:
                cout << "Enter the item you are looking for - ...\n";
                if(!(cin >> search)){
                    cout<<"Eror input should be digit!";
                }else {
                    A.Search(search, &count,n);
                    cout << "Elemet : " << search << " amount " << count << '\n';
                    count = 0;
                }
                system ("pause");
                break;
            default:
                cout<<"Wrong enter!\n";
                break;
        }
        //system ("cls");
    }

}
void TREE::TreeFromFile (int n,TREE **p,ifstream& in,char side,int depth, int parrent,bool dataShow){
    TREE *now;
    int x,nl,nr;
    ++depth;
    now = *p;
    if  (n==0) *p = NULL;
    else
    {
        nl = n/2;
        nr = n - nl - 1;
        if(!(in>>x)){

            cout<<"Eror input should be digit!\n";
           in.close();
            return;
        }
        now = new TREE;
        (*now).Key = x;
        if(dataShow == 1){
            cout<<"\n___________________\n";
            printDepth(depth);

            if(side == 'l'){
                cout<<"Add Left children = "<< x<<";\n";
                printDepth(depth);
                cout<<"His parrent is = "<< parrent<<";\n";
                if(nl+nr==0){
                    printDepth(depth);
                    cout<<"reached the leaf = "<<x<<'\n';
                    cout<<"\t  "<<parrent<<"\n\t /\n\t"<<x<<"\n";
                    cout<<"       / \\\n";
                    cout<<"   "<<"null   null\n";
                }else {
                    printDepth(depth);
                    cout<<"Became a tree node...\n";
                    cout<<"\t  "<<parrent<<"\n\t /\n\t"<<x<<"\n";

                }
            }else if(side == 'r'){
                cout<<"Add Right children = "<< x<<" ;\n";
                printDepth(depth);
                cout<<"His parrent is = "<< parrent<<";\n";
                if(nl+nr==0){

                    printDepth(depth);
                    cout<<"reached the leaf = "<<x<<'\n';
                    cout<<"\t "<<parrent<<"\n\t  \\\n\t   "<<x<<"\n";
                    cout<<"\t  / \\\n";
                    cout<<"      "<<"null    null\n";
                }else {
                    printDepth(depth);
                    cout << "Became a tree node...\n";
                    cout<<"\t "<<parrent<<"\n\t  \\\n\t   "<<x<<"\n";

                }
            }else if(side == 'k'){
                cout<<"Add Root = "<< x<<" ;\n";
            }
            cout<<"\n___________________\n";
        }

        //else {
        //     cout<<"in a node "<<x<<" - "<<nl+nr<<" childrens\n";
        // }
        TreeFromFile (nl,&((*now).Left),in,'l',depth, x,dataShow);
        --depth;
        TreeFromFile (nr,&((*now).Right), in, 'r',depth,x,dataShow);
        *p = now;

    }
    --depth;
}

void TREE::Tree (int n,TREE **p,char side,int depth,int parrent,bool dataShow)
{

    TREE *now;
    int x, nl, nr;
    ++depth;
    now = *p;
    if (n == 0) *p = NULL;
    else {
        nl = n / 2;
        nr = n - nl - 1;
        if (!(cin >> x)) {

            cout << "Eror input should be digit!\n";
            cin.clear();
            return;
        } else {
            now = new TREE;
            (*now).Key = x;
            if (dataShow == 1) {
                printDepth(depth);
                if (side == 'l') {
                    cout << "Add Left children = " << x << " ;\n";
                    printDepth(depth);
                    cout << "His parrent is = " << parrent << ";\n";
                    if (nl + nr == 0) {
                        printDepth(depth);
                        cout << "reached the leaf = " << x << '\n';
                        cout << "\t  " << parrent << "\n\t /\n\t" << x << "\n";
                        cout << "       / \\\n";
                        cout << "   " << "null   null\n";
                    } else {
                        printDepth(depth);
                        cout << "Became a tree node...\n";
                        cout << "\t  " << parrent << "\n\t /\n\t" << x << "\n";

                    }
                } else if (side == 'r') {
                    cout << "Add Right children = " << x << " ;\n";
                    printDepth(depth);
                    cout << "His parrent is = " << parrent << ";\n";
                    if (nl + nr == 0) {

                        printDepth(depth);
                        cout << "reached the leaf = " << x << '\n';
                        cout << "\t " << parrent << "\n\t  \\\n\t   " << x << "\n";
                        cout << "\t  / \\\n";
                        cout << "      " << "null    null\n";
                    } else {
                        printDepth(depth);
                        cout << "Became a tree node...\n";
                        cout << "\t " << parrent << "\n\t  \\\n\t   " << x << "\n";

                    }
                } else if (side == 'k') {
                    cout << "Add Root = " << x << " ;\n";
                }
                cout << "\n___________________\n";
            }
                Tree(nl, &((*now).Left), 'l', depth, x, dataShow);
                Tree(nr, &((*now).Right), 'r', depth, x, dataShow);
                *p = now;
        }
    }
    --depth;
}






void TREE::Vyvod (TREE **w,int l)
// Изображение бинарного дерева, заданного
// указателем *w на экране дисплея.
{
    if  (*w!=NULL)
    {
        Vyvod (&((**w).Right),l+1);
        for  (int i=1; i<=l; i++) {
            cout<<"\t";
        }
        cout<<(**w).Key<<endl;
        Vyvod (&((**w).Left),l+1);
    }
}
void GoToXY (short x, short y)
{
    HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {x, y};
    SetConsoleCursorPosition(StdOut, coord);
}

void TREE::print1(TREE ** root, short x, short y, short a, char c) {
    if ((*root) != nullptr) {
        if (a > 0 && c != 'k') {
            if (c == 'l')
                x -= 10 * a;
            else
                x += 10 * a;
        } else if (c != 'k')
            if (c == 'l')
                x -= 4;
            else
                x += 4;

        GoToXY(x, y += 2);

        a--;

        cout << ((**root).Key);
        print1(&((*root)->Left), x, y, a, 'l');
        print1(&((*root)->Right), x, y, a, 'r');
    }
}