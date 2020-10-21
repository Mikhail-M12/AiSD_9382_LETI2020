#include <string>
#ifndef UNTITLED_SYNTAXPATTERNS_H
#define UNTITLED_SYNTAXPATTERNS_H

//функция отвечает за понятие 'параметр'
bool parameter(std::string sequence, int &currentIdx, int &shift);

//функция отвечает за понятие 'список_параметров'
bool listOfParameters(std::string sequence, int &currentIdx, int &shift);

//функция отвечает за понятие 'имя'
bool name (std::string sequence, int &currentIdx, int &shift);

#endif //UNTITLED_SYNTAXPATTERNS_H
