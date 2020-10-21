
#include "syntaxAnalyzer.h"
#include<iostream>

void analyzeSyntax(std::string sequence)
{
    int shift = 0;
    int currentIdx = 0;
    if (listOfParameters(sequence, currentIdx, shift))
    {
        //Проверим на соответствие количества символов в получившемся шаблоне и заданной
        //последовательности
        if (currentIdx == size(sequence))
        {
            std::cout << " \nПоследовательность соответствует шаблону! \n";
        }
        else
        {
            std::cout << "\nИзвините, но ваша последовательность длиннее чем получившийся шаблон! \n";
        }
    }
    else
    {
        std::cout << "\nИзвините, но ваша последовательность не подходит под шаблон! \n";
    }
    std::cout << "Длина последовательности = " << size(sequence)
              << " Длина получившегося шаблона = " << currentIdx;
}