#ifndef FANOHUFFMAN_H_
#define FANOHUFFMAN_H_

#include "def.h"

Tree *buildCodeTreeFano(ElemArr curFreq, bool output, std::ofstream &info);
Tree *buildCodeTreeHuffman(ElemArr curFreq, bool output, std::ofstream &info);

#endif //FANOHUFFMAN_H_