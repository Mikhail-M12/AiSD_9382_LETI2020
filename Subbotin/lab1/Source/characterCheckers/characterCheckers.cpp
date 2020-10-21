
#include "characterCheckers.h"

bool isDigit(std::string sequence, int &currentIdx)
{
    if (currentIdx >= size(sequence))
    {
        return false;
    }
    if (isdigit(sequence[currentIdx]))
    {
        currentIdx++;
        return true;
    }
    else
    {
        return false;
    }
}

bool isLetter(std::string sequence, int &currentIdx)
{
    if (currentIdx >= size(sequence))
    {
        return false;
    }
    if (isalpha(sequence[currentIdx]))
    {
        currentIdx++;
        return true;
    }
    else
    {
        return false;
    }
}

bool checkChar(std::string str, int& currentIdx, char ch)
{
    if(size(str) <= currentIdx )
    {
        return false;
    }
    if(str[currentIdx] != ch)
    {
        return false;
    }
    currentIdx++;
    return true;
}
