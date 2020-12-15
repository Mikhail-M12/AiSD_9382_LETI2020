#include "Avl.h"

TREE* TREE::balance(TREE* p,int n) // балансировка узла p
{
     cout<<"\n\tStarting balancing !!!\n_____________________________________\n";
     cout<<"Correcting the height to the root ...\n";
    fixHeight(&p);
      if( balanceFactor(&p)==2 )
    {
        cout<<"Check if the tree is balanced.\nThere may be 3 cases:\n1) Difference between the heights of the right and left subtree = 2\n2) Difference between the heights of the right and left subtree = -2\n3) Balancing is not needed.\n\n";

        cout<<"1) "<<Height(&p->Right) <<"-"<< Height(&p->Left) <<" = "<< int(Height(&p->Right)) - Height(&p->Left)<<"\n\n";
         cout<<"The difference showed the right subtree was larger than the left. (= 2)\nNow let's see what kind of rotation we should do\n1) Right - if right minus left subtree  > 0 \\n2) Left - if the left minus right subtree <0 .\\n\\n\"";
        cout<<" R - L = "<< Height(&((*p).Right)->Right) <<"-"<< Height(&((*p).Right->Left)) <<" = "<< int(Height(&((*p).Right->Right)) - Height(&((*p).Right->Left)))<<"\n";
         if( balanceFactor(&((*p).Right)) < 0 )
            p->Right = rotateRight(p->Right,n);
        return rotateLeft(p,n);
    }
    if( balanceFactor(&p)==-2 )
    {
        cout<<"Check if the tree is balanced.\nThere may be 3 cases:\n1) Difference between the heights of the right and left subtree = 2\n2) Difference between the heights of the right and left subtree = -2\n3) Balancing is not needed.\n\n";

        cout<<"2) "<<Height(&p->Right) <<"-"<< Height(&p->Left) <<" = "<< int(Height(&p->Right)) - Height(&p->Left)<<"\n\n";
        cout<<"The difference showed the left subtree was larger than the right. (=-2)\nNow let's see what kind of rotation we should do\n1) Right - if right minus left subtree  > 0 \n2) Left - if the left minus right subtree <0 .\n\n";
        cout<<" R - L = " <<Height(&((*p).Left)->Right) <<"-"<< Height(&((*p).Left->Left)) <<" = "<< int(Height(&((*p).Left->Right)) - Height(&((*p).Left->Left)))<<"\n\n";
        if( balanceFactor(&((*p).Left)) > 0  )
            p->Left = rotateLeft(p->Left,n);
        return rotateRight(&(*p),n);
    }
    cout<<"3) Already balanced!\n###########################################################\n";
    return p; // балансировка не нужна
}

TREE* TREE::rotateRight(TREE * node,int n){
    cout<<"Right Rotate!\n";
    TREE* b = node->Left;
    node->Left = b->Right;
    b->Right = node;
    fixHeight(&node);
    fixHeight(&b);
    cout<<"New Tree: \n";
    Vyvod(&b,n);
    return b;
}
TREE* TREE::rotateLeft(TREE * node, int n){
    cout<<"Left Rotate!\n";
    TREE* b = node->Right;
    node->Right = b->Left;
    b->Left = node;
    fixHeight(&node);
    fixHeight(&b);
    return b;
}

TREE* TREE::popElem(int n ,TREE* p, int k){
    if( !p ) return 0;
    if( p->Left != nullptr)
        p->Left = popElem(n,p->Left,k);
    if( p->Right != nullptr)
        p->Right = popElem(n,p->Right,k);
    if(p->Key == k)//  k == p->key
    {
        cout<<"\n\n\tFound!!!\n_______________________\nRemove node...\nFound the lowest left leaf and make him new node;\n";
        // cout<<"Item is found!\n";
        TREE* q = p->Left;
        TREE* r = p->Right;
        // cout<<"We wrote the left child and the right child into temporary variables ...\n";
        p = nullptr;
        //cout<<"Zeroing the tree node...\n";
        if( !r ) return q;
        TREE* min = findmin(r);
        // cout<<"We go down to the left child. И делаем его новым узлом.\n";
        min->Right = removemin(r,n);
        min->Left = q;
        //cout<<"We balance the new result under the tree.\n____________________________________________________\n";
        cout<<"\n\n\n\t\tNext - balance this tree\n###########################################################\n";
        Vyvod(&min,n);
        return balance(min,n);
    }cout<<"\n\t\tNext - balance this tree\n###########################################################\n";
    Vyvod(&p,n);
    return balance(p,n);

}

TREE* TREE::Insert(int n,TREE** node, int newKey,int prevKey){

    if((*node) == nullptr){
        cout<<"Reached the leaf: "<< prevKey<<"\n";
        cout<<"Make new leaf or left child: "<< newKey<<"\n\t"<<prevKey<<'\n';
        cout<<"       / \\\n";
        cout<<"   "<<"null   null\n";
        cout<<"    "<<"||\n    "<<newKey<<'\n';
        TREE* b = new TREE(newKey);

        return b;
    }else{
        prevKey = (*node)->Key;
        (*node)->Left = Insert(n,&((*node)->Left),newKey,prevKey);
    }
    cout<<"\t\tNext - rebalance Tree.\n###########################################################\n";

   Vyvod(&(*node),n);
    return balance(*node,n);
}

void TREE::printDepth(int depth){
    for(int i =0; i < depth; ++i){
        cout << "/\\";
    }
}



void TREE::Search(int num,int* count) {
    if(this->duk != nullptr){
        duk->Search(num,count);
    }else{
        TREE *l =this->Left, *r = this->Right;
        if(l != nullptr){
            l->Search(num, count);
        }
        if(r != nullptr){
            r->Search(num, count);
        }

        if(Key == num) {
            cout<<"\n\tFound!"<<"\n________________________________________\n";
            cout<<Key<<" == "<<num<<'\n';

            *count += 1;
            cout<<"Count = "<< *count<<".\nHeight is - "<<this->height<<".\n________________________________________\n";
        }else{
            cout<<Key<<" != "<<num<<'\n';
        }

    }
}
void TREE::TreeFromFile (int n,TREE **p,ifstream& in,char side,int depth, int parrent){
    TREE *now;
    int x,nl,nr;
    ++depth;
    now = *p;
    if  (n==0) *p = NULL;
    else
    {
        nl = n/2;
        nr = n - nl - 1;
        in>>x;
        now = new TREE;
        (*now).Key = x;
        (*now).height = Height(&now);
        //(*now).height = balanceFactor(&now);
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
        TreeFromFile (nl,&((*now).Left),in,'l',depth, x);
        --depth;
        TreeFromFile (nr,&((*now).Right), in, 'r',depth,x);
        fixHeight(&now);
        *p = now;

    }
    --depth;
}

void TREE::Tree (int n,TREE **p,char side,int depth,int parrent){
// Построение идеально сбалансированного
//           дерева с n вершинами.
// *p - указатель на корень дерева.

    TREE *now;
    int x,nl,nr;
    ++depth;
    now = *p;
    if  (n==0) *p = NULL;
    else
    {
        nl = n/2;
        nr = n - nl - 1;
        if(!(cin>>x)){

            cout<<"Eror input should be digit!\n";
            cin.clear();
            exit(0);
        }
        else {
            now = new TREE;
            (*now).Key = x;
            (*now).height = Height(&now);
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
            Tree(nl, &((*now).Left), 'l', depth, x);
            Tree(nr, &((*now).Right), 'r', depth, x);
            fixHeight(&now);
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
        for  (int i=1; i<=l; i++) cout<<"    ";
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

void TREE::print1(TREE ** root, short x, short y, short a, char c)
{
    if ((*root) != nullptr)
    {
        if (a>0 && c!='k')
        {
            if (c=='l')
                x-=10*a;
            else
                x+=10*a;
        }
        else
        if (c!='k')
            if (c=='l')
                x-=4;
            else
                x+=4;

        GoToXY (x,y+=2);

        a--;

        cout<<((**root).Key);
        print1(&((*root)->Left), x, y, a, 'l');
        print1(&((*root)->Right), x, y, a, 'r');
    }
}

void TREE::Start(){
    TREE A;
    int n=0, count=0, depth = 0;
    int choise, search, fileOrConsole;
    int *arr;

    while(TRUE){
        cout << "0 - Exit. 1 - Create Tree. 2 - Print tree. 3 - Search. 4 - Insert. 5 - Remove elem.\n";
        fflush (stdin);
        cin >> choise;
        switch(choise){
            case 0:
                exit (0);
                break;
            case 1:
                cout<<"1 - Console. 2 - File";
                if(!(cin>>fileOrConsole)) {
                    cout<<"Eror you should input only digit\n";
                    cin.clear();
                }else {
                    if (fileOrConsole == 2) {
                        string input_filename;
                        const string output_filename = "output.txt";
                        ifstream in;
                        ofstream out;
                        out.open(output_filename);
                        out << "";
                        out.close();
                        cout << "Enter the input file name: \n\n";
                        cin >> input_filename;
                        if(input_filename == "1"){
                            in.open("input.txt");
                        }else{
                            in.open(input_filename);
                        }

                        if (in.is_open()) {
                            in >> n;
                            A.TreeFromFile(n, A.GetDuk(), in, 'k', depth, 0);
                            in.close();
                            cout << "A draft of the received data:\n";
                            A.Vyvod(A.GetDuk(), n);
                        }

                    } else {
                        cout << "Enter the number of vertices -...\n";
                        if((cin >> n)){
                            if (n == 0) {
                                cout << "Empty array!\n";
                            } else {
                                cout << "Enter keys...\n";
                                A.Tree(n, A.GetDuk(), 'k', depth, 0);
                                cout << "A draft of the received data:\n";
                                A.Vyvod(A.GetDuk(), n);

                            }
                        }else{
                            cout<<"Eror you should input only digit\n";
                            cin.clear();
                        }
                        cout<<"The number of characters in the tree -"<<n<<".\n Its height is - "<<A.Height(A.GetDuk())<<"\n";
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
                    A.print1(A.GetDuk(), 74, 10, 3, 'k');
                }
                cout<<"\n\n\n\n\n";

                system ("pause");
                break;
            case 3:
                cout << "Enter the item you are looking for - ...\n";
                if(!(cin >> search)){
                    cout<<"Eror input should be digit!\n";
                    cin.clear();
                }else {
                    cout<<"\tStart!O(n)\n";
                    A.Search(search, &count);
                    cout << "Elemet : " << search << " amount " << count << '\n';
                    count = 0;
                }
                system ("pause");
                break;
            case 4:
                int a;
                cout<<"Input an insert number: ";
                if(!(cin>>a)){
                    cout<<"\nEror input should be digit!\n";
                    cin.clear();
                }else {
                    A.duk = A.Insert(n, A.GetDuk(), a,99999);
                    ++n;
                }
                system ("pause");
                break;
            case 5:
                if(n<=1){
                    cout<<"Empty tree!\n";
                }else{
                    int a;
                    cout << "Enter the number you want to remove - ...\n";
                    if(!(cin>>a)){
                        cout<<"\nEror input should be digit!\n";
                        cin.clear();
                    }else {
                        A.duk = A.popElem(n,*A.GetDuk(),a);
                        --n;
                    }
                }

                break;
            default:
                cout<<"Wrong enter!\n";
                break;
        }
        //system ("cls");
    }

}
