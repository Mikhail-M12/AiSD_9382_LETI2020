#include "headers.h"

int main()
{
    using namespace std;
    setlocale(LC_ALL, "rus");

    list<int> start_list;
    int element = 0;
    short int count_of_elements = 0;
    char ch;

    { // считывание количества элементов и самих элементов
    while(true) // считывание, сколько будет введено элементов
    {
        cout << "Enter how many symbols will be in the list, OR enter 'q' for exit:" << endl;

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
            cin.ignore(32767,'\n'); // очищаем cin от остатков
            cout << "Input is invalid.  Please, try again.\n" << endl;
        }
        else
        {
            std::cin.ignore(32767,'\n');// удаляем лишние значения

            if (count_of_elements > 50) // проверяем значение на адекватные размеры
                cout << "Sorry, count of elements can`t be more than 50. Please, try again.\n" << endl;
            else if (count_of_elements < 0)
                cout << "Sorry, count of elements can`t be < 0. Please, try again.\n" << endl;
            else
                break;
        }
    }

    for (int i = 0; i < count_of_elements; ) // считывание самих элементов
    {
        if (i == 0)
            cout << "Enter all elements, OR enter 'q' for exit:" << endl;
        
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
        else
        {
            start_list.push_back(element);
            i += 1;
        }

    }
    
    cout << endl;
    }

    list<int> strand_sorted_list = strandSort(start_list);

    cout << "List before strand sorting:\n";
    print_list(start_list);
    cout << '\n' << endl;

    cout << "List after strand sorting:\n";
    print_list(strand_sorted_list);
    cout << '\n' << endl;

    list<int> c = start_list;
    c.sort(); // стандартная сортировка std::list::sort

    cout << "List after std::list::sorting:\n";
    print_list(c);
    cout << '\n' << endl;
    
    cout << "END OF PROGRAM" << endl;
    return 0;

}