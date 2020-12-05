#ifndef CODE_H_
#define CODE_H_

#include "def.h"

bool press(const char *filename,
           Tree *(*buildCodeTree)(ElemArr curFreq, bool output, std::ofstream &info));
bool depress(Tree *(*buildCodeTree)(ElemArr curFreq, bool output, std::ofstream &info));

#endif // CODE_H_