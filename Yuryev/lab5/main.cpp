#include "headers.h"

int main()
{
    using namespace std;

    Node *a = new Node;
    pushFirst(a); // вставили начальный NYT
    string line = "", newLine = "";
    char ch;

    cout << "Enter symbol line" << endl;

    ch = cin.peek();   // записываем следующий знак из cin в переменную, не изменяя cin
    if ((ch == '\n') || (ch == ' ') || (ch == '\t'))     // проверка на пустой ввод
    {
        cout << "Nothing was entered. Finishing program..." << endl;
        deleteAllNodes();
        return 0;      // выход из программы
    }

    cin >> line; // считывается строка
    cin.ignore(32767,'\n'); // cin очищается от остатков

    for (int i = 0; i < line.size(); i++) // и для каждого символа вызывается кодер
    {
        cout << '\n' << endl;
        string a = vitterCoder(line[i]);
        newLine.append(a);
    }

    cout << '\n' << endl;
    cout << "Final coded line:\n" << newLine << endl; // выводится итоговая закодированная строка

    deleteAllNodes(); // освобождает память выделенную под дерево хаффмана
    return 0;
}

