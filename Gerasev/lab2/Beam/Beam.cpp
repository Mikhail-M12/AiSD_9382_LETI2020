#include "Beam.h"

bool isBracketValid(int bracket)
{
    return bracket != string::npos;
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

    cout << "Error: Invalid findMiddleSpace call\n";
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
    string insides = inputString.substr(1, inputString.size() -2); // .substr(1, inputString.size() -1) on StackOverflow. Is not working for some reason.

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

Beam::~Beam()
{
    delete (beamUnion.pointers.Left);
    delete (beamUnion.pointers.Right);
}

void Beam::view()
{
    if (beamUnion.pointers.Left != nullptr && beamUnion.pointers.Right != nullptr)
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

int main()
{
    Beam beam("((1, 2) (((1, 2) (1, 2)) (1, 2)))");
    beam.view();
    
    return 0;
}