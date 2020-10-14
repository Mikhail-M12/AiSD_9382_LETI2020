#include <iostream>
#include <string.h>
#include <fstream>
#include <cctype>
using namespace std;


void Error(int numberOfError){
    if (numberOfError == 1) cout<<"\nCannot open file\n";
    if (numberOfError == 2) cout<<"\nIncorrect first symbol\n";
    if (numberOfError == 3) cout<<"\nempty string\n";
    if (numberOfError == 4) cout<<"\nExtra symbols\n";
    if (numberOfError == 5) cout<<"\nIncorrect operation or operation is empty\n";
    if (numberOfError == 6) cout<<"\nIncorrect first simple expression\n";
    if (numberOfError == 7) cout<<"\nIncorrect second simple expression\n";
    if (numberOfError == 8) cout<<"\nNo symbol ')'\n";
    if (numberOfError == 9) cout<<"\nEmpty simple expression\n";
    if (numberOfError == 10) cout<<"\nNo '(' symbol\n";
}


bool Operation(ifstream &file, char ch){
    return ch == '+' || ch == '-' || ch == '*';
}


bool Simple(ifstream &file, char ch){
    bool flag;

    if(isalpha(ch)) return true;
    else if (ch == '('){
       if (file>>ch){
           cout<<ch;
           flag = Simple(file, ch);
           if (flag){
               if (file>>ch){
                   cout<<ch;
                   flag = Operation(file, ch);
                   if (flag){
                       if (file>>ch){
                           cout<<ch;
                           flag = Simple(file, ch);
                       }
                   }
                   else {
                       Error(5);
                       return false;
                   }
               }
           }
           else {
               Error(6);
               return false;
           }
           if (flag) {
               if (file>>ch){
                   cout<<ch;
                   return (ch == ')');
               }
               else{
                   Error(8);
                   return false;
               }
           }
           else{
               Error(7);
               return false;
           }
       }
       else{
           Error(9);
           return false;
       }
    }
    else{
        Error(10);
        return false;
    }
}

bool Expression(ifstream &file){
    char ch;
    bool flag = false;

    if (file>>ch) {
        cout<<ch;
        if (ch == '(' || isalpha(ch)) flag = Simple(file, ch);
        else Error(2);
        file>>ch;
        if (flag && !file.eof()) Error(4);
        flag = (flag && file.eof());
    }
    else Error(3);
    return flag;
}


int main(){
    string fileName = "input.txt";

    ifstream fin;
    fin.open(fileName);
    if (!fin.is_open()){
        Error(1);
        return 0;
    }

    if(Expression(fin)) cout<<"\nIts a Simple Expression";
    else cout<<"\nIts not a Simple Expression";

    fin.close();
    return 0;
}