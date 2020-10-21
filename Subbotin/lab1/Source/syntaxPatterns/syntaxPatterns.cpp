#include "../shiftingOutput/shiftingOutput.h"
#include "../characterCheckers/characterCheckers.h"
#include "syntaxPatterns.h"
#include <iostream>
//функция отвечает за понятие 'имя'
bool name(std::string sequence, int &currentIdx, int &shift)
{
    printPattern("name", currentIdx, shift);

    //сохраняем начальный индекс
    const int givenIdx = currentIdx;

    //условие понятия 'имя'
    bool isCorrectName = isLetter(sequence, currentIdx) && isLetter(sequence, currentIdx) &&
                         isLetter(sequence, currentIdx);
    if (!isCorrectName)
    {
        printPatternResult("name", sequence.substr(givenIdx, currentIdx - givenIdx), false, shift);
        return false;
    }

    printPatternResult("name", sequence.substr(givenIdx, currentIdx - givenIdx), true, shift);
    return true;
}

//функция отвечает за понятие 'параметр'
bool parameter(std::string sequence, int &currentIdx, int &shift)
{
    printPattern("parameter", currentIdx, shift);
    //сохраняем начальный индекс
    const int givenIdx = currentIdx;

    //второе условие понятия 'параметр'
    bool bracketsCondition =
        name(sequence, currentIdx, shift) && checkChar(sequence, currentIdx, '=') &&
        checkChar(sequence, currentIdx, '(') && listOfParameters(sequence, currentIdx, shift) &&
        checkChar(sequence, currentIdx, ')');
    if (bracketsCondition)
    {
        printPatternResult("parameter", sequence.substr(givenIdx, currentIdx - givenIdx), true,
                           shift);
        return true;
    }

    shifting(shift);
    std::cout << "not condition with brackets \n";
    //Если первое условие не подходит, то индекс будет указывать на символ, который не подошел
    //вернемся к исходному индексу, чтобы проверить другое условие
    currentIdx = givenIdx;

    //первое условие понятия 'параметр'
    bool twoDigitsCondition = name(sequence, currentIdx, shift) &&
                              checkChar(sequence, currentIdx, '=') &&
                              isDigit(sequence, currentIdx) && isDigit(sequence, currentIdx);
    if (twoDigitsCondition)
    {
        printPatternResult("parameter", sequence.substr(givenIdx, currentIdx - givenIdx), true,
                           shift);
        return true;
    }

    printPatternResult("parameter", sequence.substr(givenIdx, currentIdx - givenIdx), false, shift);
    return false;
}

//функция отвечает за понятие 'список_параметров'
bool listOfParameters(std::string sequence, int &currentIdx, int &shift)
{
    printPattern("listOfParameters", currentIdx, shift);
    //сохраняем начальный индекс
    const int givenIdx = currentIdx;

    //второе условие понятия 'список_параметров'
    bool commaCondition = parameter(sequence, currentIdx, shift) &&
                          checkChar(sequence, currentIdx, ',') &&
                          listOfParameters(sequence, currentIdx, shift);
    if(commaCondition)
    {
        printPatternResult("listOfParameters", sequence.substr(givenIdx, currentIdx - givenIdx), true, shift);
        return true;
    }

    shifting(shift);
    std::cout << "not condition with comma \n";
    //Если первое условие не подходит, то индекс будет указывать на символ, который не подошел
    //вернемся к исходному индексу, чтобы проверить другое условие
    currentIdx = givenIdx;

    // первое условие понятия 'список_параметров'
    if(parameter(sequence, currentIdx, shift))
    {
        printPatternResult("listOfParameters", sequence.substr(givenIdx, currentIdx - givenIdx), true, shift);
        return true;
    }

    printPatternResult("listOfParameters", sequence.substr(givenIdx, currentIdx - givenIdx), false, shift);
    return false;
}