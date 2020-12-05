#include <iostream>
#include <stdio.h>
#include "src/BinKor.h"

using namespace std;



int main()
{
    setlocale(0, "");
    ifstream infile;
    string inputString;
    while(true){ 
      system("clear");
      cout << "Выберите опцию:" << endl;
      cout << "1. Консоль" << endl;
      cout << "2. Файл" << endl;
      cout << "3. Выход" << endl;
      string a;
      getline(cin, a);
      system("clear");
      if(a == "1"){
        cout << "Введите бинарное коромысло:" << endl;
        getline(cin, inputString); 
      }
      else if(a == "2"){
        cout << "Введите название файла: ";
        string file;
        getline(cin, file);
        infile.open(file);
        if (!infile.is_open()){
          system("clear");
          cout << "Входной поток не открыт.\n"; 
          cout << "Press enter to continue ...";
          cin.get();
          continue;
        }
        getline(infile, inputString);
      }
      else if(a == "3"){
        cout << "До встречи" << endl;
        break;
      }
      else{
        cout << "Неверный ввод" << endl;
        cout << "Press enter to continue ...";
        cin.get();
        continue;
      }

      int curPosition = 0;
      BinKor* binKor = new BinKor(); 
      system("clear");
      cout << inputString << endl;
      if (Parser(inputString, curPosition, binKor)) {
          cout << "Это бинарное коромысло.\n";
          if (Balanced(binKor, 0)) {
              cout << "Коромысло сбалансировано.\n";

          } else {
              cout << "Коромысло несбалансировано.\n";

          }
          cout << "Press enter to continue ...";
          cin.get();
      }
      else
      {
        cout << "Это не бинарное коромысло\n";
        cout << "Press enter to continue ...";
        cin.get();
      }
      delete binKor; 
    }
    cout << "Press enter to continue ...";
    cin.get();
    return 0;
}
