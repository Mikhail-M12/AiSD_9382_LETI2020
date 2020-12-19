#ifndef FANOHUFFMAN_H_
#define FANOHUFFMAN_H_

#include "def.h"

Tree *buildCodeTreeFano(ElemArr curFreq, bool output);
Tree *buildCodeTreeHuffman(ElemArr curFreq, bool output);

#endif //FANOHUFFMAN_H_