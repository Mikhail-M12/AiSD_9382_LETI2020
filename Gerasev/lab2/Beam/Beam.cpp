#include "Beam.h"

bool isBracketValid(int bracket)
{
    return bracket != string::npos;
}

bool isPointerNull(Beam* p)
{
    return p == nullptr;
}

bool isPointersNulls(Beam* p1, Beam* p2)
{
    return (isPointerNull(p1) && isPointerNull(p2));
}

int findMiddleSpace(string input)
{
    int openCounter = 0;
    for (int i=0; i<input.length(); i++)
    {
        switch (input[i])
        {
            case '(': { openCounter++; break; }
            case ')': { openCounter--; break; }
            case ' ':
                {
                    if (openCounter == 1) return i;
                    break;
                }
        }
    }

    cout << "Error: Invalid findMiddleSpace call ";
    cout << "on string " << input << '\n';
    raise(SIGILL);
    return -1;
}

Beam::Beam(string inputString)
{
    int massInput = -1, leverInput = -1;
    sscanf(inputString.c_str(), "(%d, %d)", &massInput, &leverInput);
    if (!(massInput == -1 || leverInput == -1))
    {
        beamUnion.values.mass = massInput;
        beamUnion.values.lever = leverInput;
        return;
    }   

    int middleSpace = findMiddleSpace(inputString);
    string insides = inputString.substr(1, inputString.size() -2); // .substr(1, inputString.size() -1) on StackOverflow. It's not working for some reason.

    string leftString = insides.substr(0, middleSpace-1);
    string rightString = insides.substr(middleSpace);

    if (!(leftString.empty() || rightString.empty()))
    {
        beamUnion.pointers.Left = new Beam(leftString);
        beamUnion.pointers.Right = new Beam(rightString);
        return;
    }

    cout << "Error: Invalid Input\n";
    raise(SIGILL);
}

Beam::Beam(const Beam & beam) // Оператор копирования
{
    if (!isPointersNulls(beam.beamUnion.pointers.Left, beam.beamUnion.pointers.Right))
    {
        beamUnion.pointers.Left = new Beam(*beam.beamUnion.pointers.Left);
        beamUnion.pointers.Right = new Beam(*beam.beamUnion.pointers.Right);
    }

    beamUnion.values.mass = beam.beamUnion.values.mass;
    beamUnion.values.lever = beam.beamUnion.values.lever;
}

Beam::~Beam()
{
    if (!isPointerNull(beamUnion.pointers.Left))
    {
        delete (beamUnion.pointers.Left);
    }

    if (!isPointerNull(beamUnion.pointers.Right))
    {
        delete (beamUnion.pointers.Right);
    }
}

void Beam::view()
{
    if (!isPointersNulls(beamUnion.pointers.Left, beamUnion.pointers.Right))
    {
        RECURSION_DEEPNESS++;
        beamUnion.pointers.Left->view();
        beamUnion.pointers.Right->view();
        RECURSION_DEEPNESS--;
        return;
    }

    string recursionDeepnessSpaces(RECURSION_DEEPNESS*4, ' ');
    cout << recursionDeepnessSpaces << beamUnion.values.mass << ' ' << beamUnion.values.lever << '\n';
}

bool Beam::isEqual(Beam second)
{
    if (!isPointersNulls(beamUnion.pointers.Left, beamUnion.pointers.Right) &&
        !isPointersNulls(second.beamUnion.pointers.Left, second.beamUnion.pointers.Right))
    {
        bool isLeftEq = (*beamUnion.pointers.Left).isEqual(*second.beamUnion.pointers.Left);
        bool isRightEq = (*beamUnion.pointers.Right).isEqual(*second.beamUnion.pointers.Right);
        return (isLeftEq && isRightEq);
    }

    bool isMassEq = beamUnion.values.mass == second.beamUnion.values.mass;
    bool isLeverEq = beamUnion.values.lever == second.beamUnion.values.lever; 
    return (isMassEq && isLeverEq);
}

bool Beam::isContains(Beam second)
{
    if (this->isEqual(second))
    {
        return true;
    }

    if (!isPointersNulls(beamUnion.pointers.Left, beamUnion.pointers.Right))
    {
        bool isInLeft, isInRight;
        isInLeft = beamUnion.pointers.Left->isContains(second);
        isInRight = beamUnion.pointers.Right->isContains(second);
        return (isInLeft || isInRight);
    }
    return false;
}

void Beam::isContainsListHandler(Beam second, string* result_ptr, string* currentlyAt_ptr)
{
    if (this->isEqual(second))
    {
        result_ptr->append(*currentlyAt_ptr);
        result_ptr->append(" ");
        *currentlyAt_ptr = currentlyAt_ptr->substr(0, currentlyAt_ptr->size() -1);
        return;
    }

    if (!isPointersNulls(beamUnion.pointers.Left, beamUnion.pointers.Right))
    {
        if (beamUnion.pointers.Left->isContains(second))
        {
            
            currentlyAt_ptr->append("0");
            beamUnion.pointers.Left->isContainsListHandler(second, result_ptr, currentlyAt_ptr);
        }

        if (beamUnion.pointers.Right->isContains(second))
        {
            currentlyAt_ptr->append("1");
            beamUnion.pointers.Right->isContainsListHandler(second, result_ptr, currentlyAt_ptr);
        }
    }

    *currentlyAt_ptr = currentlyAt_ptr->substr(0, currentlyAt_ptr->size() -1);;
    return;
}

string* Beam::isContainsList(Beam second)
{
    auto result_ptr = new string;
    auto currentlyAt_ptr = new string;
    this->isContainsListHandler(second, result_ptr, currentlyAt_ptr);
    return result_ptr;
}



int main()
{
    Beam beam1("(1, 2)");
    Beam beam2("((1, 2) (((1, 2) (1, 2)) (1, 2)))");
    string result = *(beam2.isContainsList(beam1));
    cout << "THE ANSWER IS " << result << '\n';
    return 0;
}