#pragma once

#include <iostream>
#include <string.h>
#include <csignal>

using namespace std;

int RECURSION_DEEPNESS = 0;

class Beam
{
private:
    struct Values { int mass = -1, lever = -1; };

    struct Pointers
    {
        Beam* Left = nullptr;
        Beam* Right = nullptr;
    };

    struct BeamUnion
    {
        Values values;
        Pointers pointers;
        // No way to make structure like this : (Values || Pointers)
        // Union is too low-level, and there is no way to tell the difference
        // between Values and Pointers
    };

    BeamUnion beamUnion;

    void isContainsListHandler(Beam second, string* result_ptr, string* currentlyAt);

public:
    Beam(string inputString = "(0, 0)");
    Beam(const Beam & beam);
    ~Beam();
    void view();
    bool isEqual(Beam second);
    bool isContains(Beam second);
    string* isContainsList(Beam second);
};



bool isPointerNull(Beam* p);
bool isPointersNulls(Beam* p1, Beam* p2);
bool isBracketValid(int bracket);