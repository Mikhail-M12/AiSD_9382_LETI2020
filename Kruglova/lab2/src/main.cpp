#include "headers.h"

using namespace std;

int main() 
{
    setlocale(LC_ALL, "rus"); // подключен русский язык
    
    lisp l;
    base atom;

    cout << "Введите список" << endl;
    read_lisp (l);
    cout << "Вы ввели: " << endl;
    write_lisp (l);
    cout << endl;
    
    free_cin(); // чтобы не оставалось ничего лишнего в cin

    cout << "Введите атом" << endl;
    cin >> atom;
    cout << "Вы ввели:" << endl;
    cout << atom << endl;

    free_cin();

    lisp old_lisp = copy_lisp(l); // чтобы вывести, что было изначально

    del_needed_atoms(l, atom, 0);
    
    cout << "Изначальный список:     ";
    write_lisp(old_lisp);
    cout << endl;
    cout << "Форматированный список:     ";
    write_lisp(l);
    cout << endl;

    destroy(l); // рекурсивно отчищаем выделенную под списки память
    destroy(old_lisp);

    cout << "Хорошая работа!" << endl;
    return 0;
}
