/*#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW*/
#include "Header.h"


int main() {
    std::fstream fin(".//Tests//6.txt");//файл для считывания выражений
    if (!fin.is_open())
        std::cout << "File is not open\n";
    else {
        char *f = new char[50]();
        f[0] = fin.get();
        if (f[0] == '(') {
            node *head = createList(fin); //создание иерархического списка
            while ((f[0] = fin.get()) != ' ') {
            }
            f[0] = fin.get();//переменная, относительно которой производится дифференцирование
            fin.close();
            differentiateList(head, f[0]); //дифференциование списка
            char* str1 = new char[50]();
            str1 = simplifyEnd(simplify(str1, head, f[0]));//упрощение списка
            std::cout << str1 << " end after simplify\n";//вывод результата на экран
            delete[] str1;
            delete head;
        } else {
            if (!fin) {
                std::cout << "Empty string!";
                return 0;
            } else {
                int i = 0;
                while (f[i] != ' ') {
                    i++;
                    f[i] = fin.get();
                }
                f[i] = '\0';
                char x = fin.get();
                std::cout << diff(f, x) << " end after simplify\n";//дифференцирование выражения с дальнейшим выводом на экран
            }
        }
        delete[] f;
    }
   /* if (_CrtDumpMemoryLeaks())
        printf("\nMemory leack deteckted\n");
    else
        printf("\nMemory is not leack deteckted\n");*/
    return 0;
}