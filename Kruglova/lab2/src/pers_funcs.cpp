#include "headers.h"

using namespace std;

void print_depth(int depth) // печать чтобы показать глубину
{
    for (int j = 0; j < depth; j++)
        cout << "[] ";
    return;
}

void free_cin() // чтобы очистить поток ввода
{
    do{}
    while(getchar() != '\n');
} 

int del_needed_atoms(lisp s, base atom, int depth)
{
    cout << "Program start---------------------------------------------------" << endl;

    if (isNull(s))      // если весь список = ( )
    {
        print_depth(depth);
        cout << "( )" << endl;

        print_depth(depth);
        cout << "It is empty Lisp." << endl;
        return 0;
    }
    
    else if (isAtom(s)) // если весь список состоит из одного атома
    {
        if (getAtom(s) == atom) // и это искомый атом
        {
            print_depth(depth);
            write_lisp(s);
            cout << endl;

            print_depth(depth);
            cout << "This lisp is needed atom." << endl;

            s->node.atom = '\0'; // просто удалить с пом. destroy и обнулить указатель нельзя, т.к.
                                 // сам указатель в main не изменится -> будет ошибка сегментирования
            return 1;
        }
        else // и это не тот атом
        {
            print_depth(depth);
            write_lisp(s);
            cout << endl;

            print_depth(depth);
            cout << "This lisp is a wrong atom." << endl;
            return 0;
        };
    }
    
    else                // список состоит из пары указателей head и tail
    {
        if (del_atoms_Add(s, atom, depth + 1,0))
            return 1;
        else
            return 0;
    }
}


int del_atoms_Add(lisp s, base atom, int depth, int loc)
{
    print_depth(depth);
    if (loc == 0)
        cout << "Now in second function" << endl;
    else if (loc == 1)
        cout << "Now in the HEAD of lisp" << endl;
    else if (loc == 2)
        cout << "Now in the TAIL of lisp" << endl;

    if (isNull(head(s)))     // у переданной пары голова = ()
    {
        print_depth(depth);
        write_lisp(s);
        cout << endl;

        print_depth(depth);
        cout << "HEAD = ()";

        if (isNull(tail(s)))      // а хвост пуст
        {
            cout << " and TAIL is empty." << endl;
            return 0;
        }
        
        else if (isAtom(tail(s))) // а хвост - это атом
        {
            if (getAtom(tail(s)) == atom) // который нужно удалить
            {
                destroy(tail(s)); // удалили хвост 
                s->node.pair.tale = NULL; // обнулили указатель

                cout << " and TAIL is needed atom." << endl;
                return 1;
            }
            else                          // который нам не подходит
            {
                cout << " and TAIL is a wrong atom." << endl;
                return 0;
            }
        }
        
        else                      // а хвост - пара указателей head и tail
        {
            cout << " and TAIL is a \'pair\'" << endl;
            del_atoms_Add(tail(s), atom, depth + 1, 2); // вызываем эту же функцию для хвоста
        }      
    }

    else if(isAtom(head(s))) // у переданной пары голова - атом
    {
        print_depth(depth);
        write_lisp(s);
        cout << endl;

        if (getAtom(head(s)) == atom) // причем тот, который нужно удалить
        {
            print_depth(depth);
            cout << "HEAD is needed atom";

            if (isNull(tail(s)))      // а хвост пустой
            {
                cout << " and TAIL is empty." << endl;

                destroy(head(s));         // удалили голову
                s->node.pair.head = NULL; // обнулили указатель в паре
                s->no_brackets = 1;       // сделали так, чтобы не выводились лишние скобки
                return 1;
            }
            
            else if (isAtom(tail(s))) // а хвост тоже атом
            {
                if (getAtom(tail(s)) == atom)   // и тоже тот, который нужно удалить
                {
                    cout << " and TAIL is needed atom too." << endl;

                    destroy(head(s));         // удалили голову
                    s->node.pair.head = NULL; // обнулили указатель

                    destroy(tail(s));         // удалили голову
                    s->node.pair.tale = NULL; // обнулили указатель

                    s->no_brackets = 1;       // чтобы не выводились лишние скобки
                    return 1;
                }
                else                            // но не тот, что нужен
                {
                    cout << " and TAIL is a wrong atom." << endl;
                    
                    s->node.pair.head = s->node.pair.tale; // теперь в голове - ненужный атом
                    s->node.pair.tale = NULL;              // а в хвосте - ничего
                    s->no_brackets = 1;                    // чтобы не воводились лишние скобки
                    return 1;                              // и весь список теперь = а
                }   
            }
            
            else                      // а хвост - пара указателей head и tail
            {
                cout << " and TAIL is a \'pair\'." << endl;

                s->node.pair.head = s->node.pair.tale; // теперь в голове - пара указателей из хвоста
                s->node.pair.tale = NULL;              // а в хвосте - ничего
                s->no_brackets = 1;                    // чтобы не выводились лишние скобки

                del_atoms_Add(head(s), atom, depth + 1, 1); // вызываем следующую функцию для head
            }    
        }
        
        else                          // но это не искомый атом
        {
            print_depth(depth);
            cout << "HEAD is a wrong atom";

            if (isNull(tail(s)))     // а хвост пустой
            {
                cout << " and TAIL is empty" << endl;

                return 0;
            }
            
            else if(isAtom(tail(s))) // а хвост - атом
            {
                if (getAtom(tail(s)) == atom) // причем тот, который нужно удалить
                {
                    cout << " and TAIL is needed atom." << endl;

                    destroy(tail(s));         // очистили хвост
                    s->node.pair.tale = NULL; // и обнулили указатель
                    return 1;
                }
                else                          // но он тоже неподходящий 
                {
                    cout << " and TAIL is a wrong atom too. " << endl;

                    return 0;
                }
            }
            
            else                     // а хвост - пара указателей head и tail
            {
                cout << " and TAIL is a \'pair\'." << endl;

                del_atoms_Add(tail(s), atom, depth + 1, 2);
            } 
        }
    }

    else                     // у переданной пары голова - пара указателей head и tail
    {
        print_depth(depth);
        write_lisp(s);
        cout << endl;

        print_depth(depth);
        cout << "HEAD is a \'pair\'";

        if(isNull(tail(s)))      // а хвост пустой
        {
            cout << " and TAIL is empty." << endl;

            del_atoms_Add(head(s), atom, depth + 1, 1);
        }
        
        else if(isAtom(tail(s))) // а хвост - атом
        {
            if (getAtom(tail(s)) == atom)   // причем тот, который нужно удалить
            {
                cout << " and TAIL is needed atom." << endl;

                destroy(tail(s));         // очищаем хвост
                s->node.pair.tale = NULL; // и обнуляем указатель

                del_atoms_Add(head(s), atom, depth + 1, 1); // вызываем для головы
            }
            else                            // но который не надо удалять
            {
                cout << " and TAIL is a wrong atom." << endl;

                del_atoms_Add(head(s), atom, depth + 1, 1);
            }            
        }
        
        else                     // и хвост тоже пара указателей
        {
            cout << " and TAIL is a \'pair\' too." << endl;

            del_atoms_Add(head(s), atom, depth + 1, 1);
            del_atoms_Add(tail(s), atom, depth + 1, 2);
        }
    }
}

