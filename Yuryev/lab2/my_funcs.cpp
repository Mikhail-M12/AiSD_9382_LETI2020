#include "headers.h"
using namespace std;

void print_depth(int depth) // просто печатает пробелы в количестве глубины
{
    for (int j = 0; j < depth; j++)
        cout << "    ";
    return;
}

void free_cin(){do{}while(getchar() != '\n');} // очищает cin до \n

int is_atom_in_Main(const lisp s, base atom, int depth, int loc)  // пустой / из 1 атома -> обработает; остальное -> передаст в след. ф.
{
    /*print_depth(depth);
    cout << "Now in MAIN function" << endl;*/
    print_depth(depth);
    if(loc == 1)
        cout << "It is HEAD of Lisp" << endl;
    else if(loc == 2)
        cout << "It is TAIL of Lisp" << endl;
    
    if (isNull(s)) // пустой список
    {   
        print_depth(depth);
        write_lisp(s);
        cout << endl;
        print_depth(depth);
        cout << "Lisp is empty" << endl;
        return 0;
    }
    if (isAtom(s)) // весь список - один атом
    {
        print_depth(depth);
        cout << "\'" << getAtom(s) << "\'" << endl;

        if (getAtom(s) == atom)
        {
            print_depth(depth);
            cout << "It is needed atom!!!" << endl;
            return 1;
        }
        else 
        {
            print_depth(depth);
            cout << "It is not needed atom" << endl;
            return 0;
        }
    }
    else // непустой список из > 1 атома
    {
        if (is_atom_in_Add(s, atom, depth + 1))
        {
            print_depth(depth);
            write_lisp(s);
            cout << "\n";

            print_depth(depth);
            cout << "Needed atom is here!!!" << endl;
            return 1;
        }
        else
        {
            print_depth(depth);
            write_lisp(s);
            cout << "\n";

            print_depth(depth);
            cout << "There are no needed atom here" << endl;
            return 0;
        };
    };
}

int is_atom_in_Add(const lisp s, base atom, int depth) // отдельно передает в главную функцию голову и хвост
{
    /*print_depth(depth);
    cout << "Now in ADD function" << endl;*/

    if (is_atom_in_Main(head(s), atom, depth + 1, 1)) // передаем первую значащую часть
        return 1;
    if (isNull(tail (s))) // без этого сообщение о пустом списке выводилось бы дважды 
        return 0;
    else if (is_atom_in_Main(tail (s), atom, depth + 1, 2)) // передаем оставшуюся значащую часть
        return 1;
    else
        return 0;
};

