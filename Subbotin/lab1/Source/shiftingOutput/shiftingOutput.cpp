#include <iostream>
#include "shiftingOutput.h"

void shifting(int numberOfSpaces)
{
    for (int i = 0; i < numberOfSpaces; i++)
    {
        std::cout << " ";
    }
}

void printPattern(std::string pattern, int currentIdx, int &shift)
{
    shifting(shift);
    std::cout << pattern << "[" << currentIdx << "]\n";
    shift += 3;
}

void printPatternResult(std::string pattern, std::string sequence, bool check, int &shift){
    shift-=3;
    shifting(shift);
    std::cout << pattern << "[" << sequence << "] - " << std::boolalpha << check << "\n";
}

