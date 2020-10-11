#include "headers.h"

using namespace std;

// Создание и удаление списка
lisp head (const lisp s) //возвращает именно указатель на голову из поданного списка, если подать атом -> будет ошибка (поэтому нужно проверять на атом)
{
    if (s != NULL)
    {
        if (!isAtom(s)) 
            return s->node.pair.head;
        else 
        {
            cerr << "Error: Head(atom) \n"; 
            exit(1);
        }
    }
    else 
    {
        cerr << "Error: Head(nil) \n"; 
        exit(1);
    }
}

lisp tail (const lisp s) // возвращает именно указатель на хвост из поданного списка, если подать атом -> ошибка
{
    if (s != NULL)
    {
        if (!isAtom(s)) 
            return s->node.pair.tale;
        else 
        {
            cerr << "Error: Tail(atom) \n"; 
            exit(1);
        };
    }
    else 
    { 
        cerr << "Error: Tail(nil) \n";
        exit(1);
    };
}

lisp cons (const lisp h, const lisp t) // создает и возвращает новый lisp из головы и хвоста
{
    lisp p;
    if (isAtom(t)) 
    { 
        cerr << "Error: cons(*, atom) \n"; 
        exit(1);
    }
    else 
    { 
        p = new s_expr;
        if ( p == NULL) // не удалось выделить память
        {
            cerr << "Memory ...\n"; 
            exit(1); 
        } 
        else 
        {
            p->tag = false; // сделали значение tag = пара и заполнили поля
            p->node.pair.head = h; 
            p->node.pair.tale = t;
            return p;
        };
    };
}

lisp make_atom (const base x) // из символа char делает lisp и возвращает
{ 
    lisp s;
    s = new s_expr;
    s -> tag = true; // перевели tag в значение атом и записали этот символ
    s->node.atom = x;
    return s; // возвращаем указатель
}

void destroy (lisp s) // рекурсивно все очищаем (и объект, и память выделенную внутри)
{
    if ( s != NULL) 
    {
        if (!isAtom(s)) // если это пара, то рекурсивно очищаем выделенную память для головы и хвоста
        {
            destroy ( head (s));
            destroy ( tail(s));
        };
        delete s; // очищаем память для самого объекта
    };
}


// Работа со списком
bool isAtom (const lisp s) // возвращает tag из поданого списка
{ 
    if(s == NULL) 
        return false;
    else 
        return (s -> tag);
}

bool isNull (const lisp s) {return s==NULL;} // проверка на пустоту списка

lisp copy_lisp (const lisp x) // делает и возвращает копию поданного списка
{ 
    if (isNull(x)) 
        return NULL;
    else if (isAtom(x))
        return make_atom (x->node.atom);
    else 
        return cons (copy_lisp (head (x)), copy_lisp (tail(x)));
}

base getAtom (const lisp s) // вернет значение атома (переведет из lisp в char), если не атом - exit(1)
{
    if (!isAtom(s)) 
    { 
        cerr << "Error: getAtom(s) for !isAtom(s) \n"; 
        exit(1);
    }
    else 
        return (s->node.atom);
}


//вывод списка на консоль
void write_lisp (const lisp x) // выведет пусто или атом и вызовет следующую функцию
{
    if (isNull(x))   //пустой список 
    {   
        cout << " ()";
    }
    else if (isAtom(x))  // весь список - атом
    {
        cout << ' ' << x->node.atom;
    }
    else //непустой список
    { 
        cout << " (" ;
        write_seq(x); // вызов следующей функции
        cout << " )";
    }
}

void write_seq (const lisp x)//выводит список без внешних скобок (их выведет прошлая функция)
{
    if (!isNull(x)) // эта проверка нужна для нормальной работы прямой рекурсии этой функции
    {
        if (isNull(head(x)) && isNull(tail(x))) // если хвост и голова пусты и не должно ничего выводиться
        {
            if (x->no_brackets == 1)
                return;
        }
        else if (isAtom(head(x)) && isNull(tail(x))) // если в голову перенесли атом
        {
            if (x->no_brackets == 1)
            {
                cout << ' ' << x->node.atom;
                return;
            }
        }
        else if (isNull(tail(x)))                    // если в голову перенесли пару
        {
            if (x->no_brackets == 1)
            {
                write_seq(head(x));
                return;
            }
        }

        write_lisp(head (x)); // если head будет NULL -  будет выведено - ()
        write_seq(tail (x));  // a если tail будет NULL - ничего не выведется
        
    };
}


// ввод списка с консоли
void read_lisp (lisp& y) // считывает символ и передает его со списком дальше
{ 
    base x;
    do cin >> x; while (x==' ');
    read_s_expr (x, y);
}

void read_s_expr (base prev, lisp& y)//'(' -> вызов следующей функции; иное -> записали как atom
{
    if ( prev == ')' ) // есть закрывающая скобка - нет открывающей (словит и обратное) -> exit(1)
    {
        cerr << " ! List.Error 1 :: no open bracket" << endl;
        exit(1); 
    }
    else if (prev != '(') 
        y = make_atom (prev);
    else 
        read_seq (y); // передали в следующую функцию
}

void read_seq (lisp& y)  // рекурсивное считывание всего, что внутри скобок и создание иерарх. списка в lisp y
{ 
    base x;
    lisp p1, p2;
    if (!(cin >> x)) // после открывающей скобки ничего -> exit(1)
    {
        cerr << " ! List.Error 2 :: nothing after open bracket" << endl; 
        exit(1);
    }
    else 
    {
        while (x==' ') // это пропускает пробелы
            cin >> x;
        if (x == ')') // пустые скобки
            y = NULL;
        else 
        {
            read_s_expr (x, p1);
            read_seq (p2);
            y = cons (p1, p2); // последовательное создание иерархического списка с самого глуокого вложения
        }
    };
}
