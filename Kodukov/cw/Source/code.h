#ifndef CODE_H_
#define CODE_H_

#include "def.h"

extern ElemArr curFreq;
extern Tree *T;
struct Code {
  bool bits[50];
  int len = 0;
};
extern std::map<unsigned char, Code> newCodes;
extern std::vector<bool> coded;
extern long long size;

void print(Tree *q, long n, char path_to);

bool press(std::istream &input,
           Tree *(*buildCodeTree)(ElemArr curFreq, bool output));
bool depress(Tree *(*buildCodeTree)(ElemArr curFreq, bool output));

#endif // CODE_H_