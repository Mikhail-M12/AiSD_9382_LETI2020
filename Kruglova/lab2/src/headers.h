#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <fstream>

typedef char base; // базовый тип элементов (атомов)

struct s_expr;
 
struct two_ptr // содержит голову и хвост
{
    s_expr *head; 
    s_expr *tale;
};

struct s_expr // голова и хвост хранят либо атом, либо пару (рекурсия) и соответствующее значение в tag
{
    bool tag; // true: atom, false: pair
    int no_brackets = 0; // добавлено, чтобы при желании можно было не выводить скобки
    union
    {
        base atom; // 1 символ
        two_ptr pair; // голова и хвост
    } node;
}; 
typedef s_expr *lisp;

// объявления основных функций
lisp head (const lisp s);
lisp tail (const lisp s);
lisp cons (const lisp h, const lisp t);
lisp make_atom (const base x);
lisp copy_lisp (const lisp x);
void destroy (lisp s);

// объявления предикатов
bool isAtom (const lisp s); 
bool isNull (const lisp s);

// объявления функций вывода
void write_lisp (const lisp x); // основная
void write_seq (const lisp x);

// объявления функций считывания
void read_lisp (lisp& y); // основная
void read_s_expr (base prev, lisp& y);
void read_seq (lisp& y);

base getAtom (const lisp s);


void print_depth(int depth);

void free_cin(); // чтобы в cin ничего не оставалось при неправильном вводе.

int del_needed_atoms(lisp s, base atom, int depth);

int del_atoms_Add(lisp s, base atom, int depth, int loc);


#endif
