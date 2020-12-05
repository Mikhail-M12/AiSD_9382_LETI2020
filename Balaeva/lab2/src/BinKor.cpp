#include "BinKor.h"

using namespace std;
Weight::~Weight()
{
    delete binKor;
}

int WeightFunc(BinKor* binKor)
{
    int sumWeight = 0;
    if (!binKor->leftEdge->weight->isBinKor)
    {
        sumWeight+= binKor->leftEdge->weight->weight;
    }
    else
    {

        sumWeight += WeightFunc(binKor->leftEdge->weight->binKor);
    }

    if (!binKor->rightEdge->weight->isBinKor)
    {
        sumWeight += binKor->rightEdge->weight->weight;
    }
    else
    {

        sumWeight += WeightFunc(binKor->rightEdge->weight->binKor);
    }

    return sumWeight;
}

bool Balanced(const BinKor* binKor, int count)
{
    if(count == 0) {
      cout << endl;
      cout << "Вход в Balanced" << endl;
    }
    cout << "Глубина: " << count << endl;
    bool balancedRight = true;
    bool balancedLeft = true;
    int torqueLeft = 0;
    int torqueRight = 0;
    if (!binKor->leftEdge->weight->isBinKor)
    {
        torqueLeft = binKor->leftEdge->length * binKor->leftEdge->weight->weight;
        cout << "Вес левого сына(Глубина:" << count+1 <<  "): " << torqueLeft << endl;
    }
    else
    {   
        cout << "Вход в левого потомка" << endl;
        balancedLeft = Balanced(binKor->leftEdge->weight->binKor, 1+count);
        torqueLeft = binKor->leftEdge->length*WeightFunc(binKor->leftEdge->weight->binKor);
        cout << "Полный вес левого потомка(Глубина:" << count+1 <<  "): " << torqueLeft << endl;
    }
    if (!binKor->rightEdge->weight->isBinKor)
    {
        torqueRight = binKor->rightEdge->length * binKor->rightEdge->weight->weight;
        cout << "Вес правого сына(Глубина:" << count+1 <<  "): " << torqueLeft << endl;
    }
    else
    {   
        cout << "Вход в правого потомка" << endl;
        balancedRight = Balanced(binKor->rightEdge->weight->binKor, 1+count);
        torqueRight = binKor->rightEdge->length * WeightFunc(binKor->rightEdge->weight->binKor);
        cout << "Полный вес правого потомка(Глубина:" << count+1 <<  "): " << torqueLeft << endl;
    }
    return torqueLeft == torqueRight && balancedLeft && balancedRight;
}

bool Parser(string inputString, int& curPosition, BinKor* binKor)
{
    if (BinKorParse(inputString, curPosition, binKor))
        return true;
    else
        return false;
}

bool BinKorParse(string inputString, int& curPosition, BinKor* binKor)
{   
    cout << "Вход в BinKorParse: curPos = " << curPosition << endl;
    bool isBinkor = false;
    if (inputString[curPosition]== '('&& curPosition< inputString.length() -2)
    {
        curPosition++;
        binKor->leftEdge = new Edge();
        if(EdgeParse(inputString, curPosition, binKor->leftEdge))
        {
            if (inputString[curPosition] == ' ' && curPosition < inputString.length() - 2)
            {
                curPosition++;
                binKor->rightEdge = new Edge();
                if (EdgeParse(inputString, curPosition, binKor->rightEdge) && inputString[curPosition] == ')' && curPosition < inputString.length())
                {
                    curPosition++; 
                    isBinkor = true;
                }

            }
        }
    }
    return isBinkor;
}

bool EdgeParse(string inputString, int& curPosition, Edge* edge)
{
    bool isEdge = false;
    string stringValue;
    if (inputString[curPosition] == '(' && curPosition < inputString.length() - 2)
    {
        curPosition++;
        while (curPosition < inputString.length() - 1 && inputString[curPosition] != ' ')
        {
            stringValue += inputString[curPosition]; curPosition++;
        }
        int val = Value(stringValue);
        if (val <= 0)
            return false;
        else edge->length = val;

        if (inputString[curPosition] == ' ' && curPosition < inputString.length() - 2)
        {
            curPosition++;
            edge->weight = new Weight();
            if(WeightParser(inputString, curPosition,edge->weight))
             {
                 if(inputString[curPosition]== ')'&& curPosition< inputString.length() -1)
                 {
                     curPosition++;
                     isEdge = true;
                 }
             }
        }
    }
    return isEdge;
}

bool WeightParser(string inputString, int& curPosition, Weight* weight)
{
    bool isWeight = false;
    if (inputString[curPosition] == '(')
    {
        weight->isBinKor = true;
        weight->binKor = new BinKor();
        isWeight = BinKorParse(inputString, curPosition, weight->binKor);
    }
    else if (curPosition < inputString.length() - 2)
    {
        string stringValue;
        while (curPosition < inputString.length() - 1 && inputString[curPosition] != ')')
        {
            stringValue += inputString[curPosition];
            curPosition++;
        }
        int val = Value(stringValue);
        if (val >= 1)
        {
            isWeight = true;
            weight->weight = val;
            weight->isBinKor = false;
        }
    }
    return isWeight;
}

int Value(string stringValue)
{
    int value;
    try
    {
        value = stoi(stringValue);
    }

    catch (const std::invalid_argument& error)
    {
        cerr << "Invalid argument: " << error.what() << '\n';
        return -1;
    }
    if (to_string(value).length() == stringValue.length())
    {
        return value;
    }
    else
    {
        return-1;
    }
}


