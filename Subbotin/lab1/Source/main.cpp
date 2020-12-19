#include <iostream>
#include <string>
#include <fstream>
#include "syntaxAnalyzer/syntaxAnalyzer.h"

int main() {
    std::string sequence;
    char choice='a';
    while(choice!='f' && choice!='c'){
        std::cout << "Введите f/c для ввода данных с файла/консоли:";
        std::cin >> choice;
    }
    if(choice == 'f'){
        std::ifstream inputFile;
        inputFile.open("../in.txt");
        if(inputFile.is_open()){
            getline(inputFile, sequence);
        }
        inputFile.close();
    }
    else if (choice == 'c'){
        std::cout << "Введите последовательность: ";
        std::cin >> sequence;
    }
    std::cout << "Шаблон: \n"
                 "список_параметров::=параметр | параметр,список_параметров\n"
                 "параметр::=имя=цифра цифра | имя=(список_параметров)\n"
                 "имя::=буква буква буква\n\n";
    if(size(sequence) > 0){
        std::cout << "Последовательность для анализа: " << sequence << "\n";
        analyzeSyntax(sequence);
    }
    else {
        std::cout << "Последовательность пуста!";
    }

    return 0;
}