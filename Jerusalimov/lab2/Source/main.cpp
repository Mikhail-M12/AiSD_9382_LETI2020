#include <iostream>
#include <cstdlib>
#include "l_intrfc.h"
#include <windows.h>
#include <conio.h>
using namespace std;
using namespace h_list;

lisp concat (const lisp y, const lisp z);
lisp flatten(const lisp s);
void counter(lisp s, lisp *linery);
void print2(const char *message);
void print2();
int depth = 0;
int main ( )
{ SetConsoleCP(1251); // для вывода кирилицы
    SetConsoleOutputCP(1251); // для вывода кирилицы
    lisp s1, s2;
    cout<<"Enter the list:"<<endl;
    counter(s1,&s2);
    write_lisp(s2);

    getch();
    return 0;
}
void print2(const char *message){
    for (int i = 0; i < depth; ++i){
        cout<< '.';
    }
    cout<< message << '\n';
}
void print2(){
    for (int i = 0; i < depth; ++i){
        cout<< '.';
    }
}
void counter(lisp s, lisp *linery){
    read_lisp (s);
    cout<<"\n__________________________________________\n*Forming a linear list*\n\n";
    *linery = flatten(s);
    cout<<"____________________________________________\n";
   cout<<"There are "<< getCount() <<" atoms in the list." << endl;

}
//...........................
lisp concat (const lisp y, const lisp z)
{
    ++depth;
    print2("We went into the \"concat\" function!");
    if (isNull(y)) return copy_lisp(z);
    else {
        ++depth;
        print2("Entered the \"cons\" function!");
        print2("Allocated memory for a new node");
        lisp temp = cons (copy_lisp(head (y)), concat (tail (y), z));

        --depth;
        print2("Exited \"cons\" function");
        --depth;
        print2("Exited \"concat\" function");
        return temp;
    }
} // end concat
//........................
lisp flatten(const lisp s)
{
    ++depth;
    print2("We went into the \"flatten\" function!");
    if (isNull(s)) return NULL;
    else if(isAtom(s)) return cons(make_atom(getAtom(s)),NULL);
    else if (isAtom(head(s))) {//s ? непустой список
        ++depth;
        print2("entered the \"cons\" function!");
        lisp temp =cons( make_atom(getAtom(head(s))),flatten(tail(s)));

        --depth;
        print2("Exited \"cons\" function");
        --depth;
        print2("Exited \"flatten\" function");

        return temp;
    }
    else {//Not Atom(Head(s))
        lisp temp =concat(flatten(head(s)), flatten(tail(s)));
        --depth;
        print2("Exited \"flatten\" function");
        --depth;
        print2("Exited \"flatten\" function");
        --depth;
        print2("Exited \"concat\" function");
        return temp;
    }

} // end flatten
