

#include <iostream>
#include <cstdlib>
#include "l_intrfc.h"
using namespace std;


namespace h_list
{
    int recDepth = 0;
    int count =0;
    int getCount (){return count;}
    void print(const char *message){
        for (int i = 0; i < recDepth; ++i){
            cout<< '.';
        }
        cout<< message << '\n';
    }
    void print(const char *message, char z){
        for (int i = 0; i < recDepth; ++i){
            cout<< '.';
        }

        cout<< message << '\''<<z <<'\''<<'\n';
    }
//....................................
    lisp head (const lisp s)
    {// PreCondition: not null (s)
        if (s != NULL) if (!isAtom(s)) return s->node.pair.hd;
            else { cerr << "Error: Head(atom) \n";  return NULL; }
        else { cerr << "Error: Head(nil) \n";
            return NULL;
        }
    }
//.......................................
    bool isAtom (const lisp s)
    { if(s == NULL) return false;
        else return (s -> tag);
    }
//.......................................
    bool isNull (const lisp s)
    { return s==NULL;
    }
//.......................................
    lisp tail (const lisp s)
    {// PreCondition: not null (s)
        if (s != NULL) if (!isAtom(s)) return s->node.pair.tl;
            else { cerr << "Error: Tail(atom) \n"; exit(1); }
        else { cerr << "Error: Tail(nil) \n";
            exit(1);
        }
    }
//.......................................
    lisp cons (const lisp h, const lisp t)
// PreCondition: not isAtom (t)
    {

        lisp p;
        if (isAtom(t)) { cerr << "Error: Cons(*, atom)\n"; exit(1);}
        else {
            p = new s_expr;
            if ( p == NULL) {cerr << "Memory not enough\n"; exit(1); }
            else {
                p->tag = false;
                p->node.pair.hd = h;
                p->node.pair.tl = t;
                return p;
            }
        }
    }
//...........................
    lisp make_atom (const base x)
    { lisp s;
        s = new s_expr;
        s -> tag = true;
        s->node.atom = x;
        return s;
    }
//...........................
    void destroy (lisp s)
    {
        if ( s != NULL) {
            if (!isAtom(s)) {
                destroy ( head (s));
                destroy ( tail(s));
            }
            delete s;
// s = NULL;
        };
    }
//...........................
    base getAtom (const lisp s)
    {
        if (!isAtom(s)) { cerr << "Error: getAtom(s) for !isAtom(s) \n"; exit(1);}
        else return (s->node.atom);
    }
//...........................
// ввод списка с консоли
    void read_lisp ( lisp& y){
        base x;
        do cin >> x; while (x==' ');
        read_s_expr ( x, y);
    } //end read_lisp
//...........................
    void read_s_expr (base prev, lisp& y)
    { //prev － ранее прочитанный символ}
        ++recDepth;
        print("We went to \"read_s_expr\".");
        if ( prev == '(' ){print("Met an opening parenthesis!");}

        if ( prev == ')' ) {
            cerr << " ! List.Error 1 " << endl; exit(1);
        }
        else if ( prev != '(' ){
            ++count;
            print("Counter added met atom ",prev);
            y = make_atom (prev);
        }
        else {
            read_seq(y);
            --recDepth;
            print("Exited \"read_seq\"!");
        }
    } //end read_s_expr
//...........................
    void read_seq ( lisp& y)
    {
        ++recDepth;
        base x;
        print("We went to \"read_seq\"!");

        lisp p1, p2;
        if (!(cin >> x)) {cerr << " ! List.Error 2 " << endl; exit(1);}
        else {
            while ( x==' ' ) cin >> x;
            if ( x == ')' ) {
                --recDepth;
                print("Met a closing parenthesis!");
                y = NULL;
            }
            else {
                read_s_expr ( x, p1);
                read_seq ( p2);

                --recDepth;
                print("Exited \"read_s_expr\"!");
                --recDepth;
                print("Exited \"read_seq\"!");
                y = cons (p1, p2);
            }
        }
    } //end read_seq
//...........................
// Процедура вывода списка с обрамляющими его скобками － write_lisp,
// а без обрамляющих скобок － write_seq
    void write_lisp (const lisp x)
    {//пустой список выводится как ()
        if (isNull(x)) cout << " ()";
        else if (isAtom(x)) cout << ' ' << x->node.atom;
        else { //непустой список}
            cout << " (" ;
            write_seq(x);
            cout << " )";
        }
    } // end write_lisp

//...........................
    void write_seq (const lisp x)
    {//выводит последовательность элементов списка без обрамляющих его скобок

        if (!isNull(x)) {
            write_lisp(head (x));
            write_seq(tail (x));

        }

    }
//...........................
    lisp copy_lisp (const lisp x)
    { if (isNull(x)) return NULL;
        else if (isAtom(x)) return make_atom (x->node.atom);
        else return cons (copy_lisp (head (x)), copy_lisp (tail(x)));
    } //end copy-lisp
} // end of namespace h_list
