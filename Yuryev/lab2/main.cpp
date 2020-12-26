#include "headers.h"
using namespace std;

// есть плюсики за: удобство, качество кода, комментарии и тестирование

// надо было сделать в коде: (готово)
// 1) Исправить вывод лишних сообщений о пустом списке при вводе вложенного пустого списка; -0.5 балла
// 2) Добавить вывод сообщений в какой из 2 функций находится программа и находится ли она в
//    хвосте или голове; плюсик за ясность

// надо было сделать в отчете: 
// 1) Добавить описание алгоритма; плюсик за алгоритм
// 2) Добавить описание функций и структур данных; плюсик за описание функций и структур данных
// 3) Добавить пример с рисунком; -1 балл

int main() 
{
    setlocale(LC_ALL, "rus"); // подключен русский язык
    
    lisp s;
    base atom;

    cout << "Please, enter the list:" << endl;
    read_lisp (s);
    cout << "Entered list is: " << endl;
    write_lisp (s);
    cout << endl;
    
    free_cin(); // чтобы не оставалось ничего лишнего в cin

    cout << "Please, enter the atom:" << endl;
    cin >> atom;
    cout << "Entered atom is:" << endl;
    cout << atom << endl;

    free_cin();

    if(is_atom_in_Main(s, atom, 1, 0))
        cout << "The atom is in this hierarchical list!!!" << endl;
    else
        cout << "There is no such atom in this hierarchical list" << endl;
    
    destroy(s); // рекурсивно отчищаем выделенную под список память
    return 0;
}
