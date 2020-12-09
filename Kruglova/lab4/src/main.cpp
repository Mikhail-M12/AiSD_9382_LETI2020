#include "headers.h"

void printDepth(int depth) // выведет "  " указанное кол-во раз
{
    for (int j = 0; j < depth; j++)
        std::cout << "[]";
    return;
}

int main()
{
    using namespace std;

    vector<int> inputElements, sortedVector;
    
    { // считывание количества элементов и самих элементов

    int count_of_elements = 0;
    int element = 0;
    char ch;
    while(true) // считывание, сколько будет введено элементов
    {
        cout << "Enter how many symbols will be entered, OR enter 'q' for exit:" << endl;

        ch = cin.peek();   // записываем следующий знак из cin в переменную, не изменяя cin
        if (ch == 'q')     // проверка на ввод 'q'
        {
            cout << "\'q\' was entered. Finishing program..." << endl;
            return 0;      // выход из программы
        }

        cin >> count_of_elements; // пытаемся считать значение в int

        if (cin.fail()) // если это не 'q' и не число или же это слишком большое число
        {
            cin.clear();            // переводим cin в обычный режим работы
            cin.ignore(32767,'\n'); // очищаем cin
            cout << "Input is invalid.  Please, try again.\n" << endl;
        }
        else
        {
            std::cin.ignore(32767,'\n'); // очищаем cin

            if (count_of_elements > 30) // проверяем значение на адекватные размеры
                cout << "Sorry, count of elements can`t be more than 30. Please, try again.\n" << endl;
            else if (count_of_elements <= 0)
                cout << "Sorry, count of elements can`t be <= 0. Please, try again.\n" << endl;
            else // если все хорошо
                break;
        }
    }

    for (int i = 0; i < count_of_elements; ) // считывание самих элементов
    {
        if (i == 0)
            cout << "Enter all your elements, OR enter 'q' for exit:" << endl;
        
        ch = cin.peek();   // записываем следующий знак из cin в переменную, не изменяя cin
        if (ch == 'q')     // проверка на ввод 'q'
        {
            cout << "\'q\' was entered. Finishing program..." << endl;
            return 0;      // выход из программы
        }

        cin >> element;    // пытаемся получить число

        if (cin.fail())    // ошибка при получении числа
        {
            cin.clear();
            cin.ignore(32767,'\n');

            cout << "Element №" << i << " is invalid.  Please, try again.\n" << endl; 
            if (i > 0)
                cout << "Enter remaining elements, OR enter 'q' for exit:" << endl;
            continue;
        }
        else // записываем элементы в вектор
        {
            inputElements.push_back(element);
            i += 1;
        }
    }
    
    cout << endl;
    }

    sortedVector = inputElements;

    bingoSort(&sortedVector);

    cout << "\nArray before sorting:" << endl;
    printVector(&inputElements);

    cout << "\nArray after sorting:" << endl;
    printVector(&sortedVector);

    return 0;
}

