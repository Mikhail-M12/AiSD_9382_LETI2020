#include <iostream>
#include <string.h>
#include <fstream>
#include <cctype>
using namespace std;

/*Функция вывода ошибок*/
void printError(int numberOfError){
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

/*Функция проверки знака операции*/
bool isOperation(ifstream &file, char letter){
    return letter == '+' || letter == '-' || letter == '*';
}

/*Функция проверки простого выражения*/
bool isSimple(ifstream &file, char letter, int depth){
    bool flag;
    /*Является ли простое выражание латинской буквой*/
    if(isalpha(letter)){
        return true;
    }
    else if (letter == '('){
        /*Проверка первой части простого выражения*/
       if (file>>letter){
           if (letter == '(')  for (int i = 0; i < depth+1; i++) cout<<"\t";
           else  for (int i = 0; i < depth; i++) cout<<"\t";
           cout<<letter<<"\n";
           flag = isSimple(file, letter, depth+1);
           /*Проверка второй части(коррестность знака опериции) простого выражения*/
           if (flag){
               if (file>>letter){
                   for (int i = 0; i < depth; i++) cout<<"\t";
                   cout<<letter<<"\n";
                   flag = isOperation(file, letter);
                   /*Проверка третьей части простого вырожения*/
                   if (flag){
                       if (file>>letter){
                           if (letter == '(') {
                               for (int i = 0; i < depth+1; i++) cout<<"\t";
                               cout<<letter<<"\n";
                               flag = isSimple(file, letter, depth+1);
                           }
                           else {
                               for (int i = 0; i < depth; i++) cout<<"\t";
                               cout<<letter<<"\n";

                               flag = isSimple(file, letter, depth);
                           }

                       }
                   }
                   else {
                       printError(5);
                       return false;
                   }
               }
           }
           else {
               printError(6);
               return false;
           }
           /*Проверка на наличие закрывающей скобки*/
           if (flag) {
               if (file>>letter){
                   for (int i = 0; i < depth; i++) cout<<"\t";
                   cout<<letter<<"\n";
                   return (letter == ')');
               }
               else{
                   printError(8);
                   return false;
               }
           }
           else{
               printError(7);
               return false;
           }
       }
       else{
           printError(9);
           return false;
       }
    }
    else{
        printError(10);
        return false;
    }
}

/*Функция проверки первого сивмола, а также проверки на налчие лишних символов*/
bool isSimpleExpression(ifstream &file){
    char letter;
    bool flag = false;
    int depth = 0;

    if (file>>letter) {
        cout<<letter<<"\n";
        if (letter == '(' || isalpha(letter)) flag = isSimple(file, letter, depth);
        else printError(2);
        file>>letter;
        if (flag && !file.eof()) printError(4); // Вызов функции ошибок, если есть лишние символы или ошибки в самой строке
        flag = (flag && file.eof());
    }
    else printError(3);
    return flag;
}


int main(){
    string fileName = "input.txt";

    ifstream fin;
    fin.open(fileName);
    if (!fin.is_open()){
        printError(1);
        return 0;
    }

    if(isSimpleExpression(fin)) cout<<"\nIts a Simple Expression";
    else cout<<"\nIts not a Simple Expression";

    fin.close();
    return 0;
}
