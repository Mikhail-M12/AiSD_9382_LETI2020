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
        // No way to make (Values or pointers)
        // Union is too low-level
    };

    BeamUnion beamUnion;

public:
    Beam(string inputString);
    ~Beam();
    void view();
};
