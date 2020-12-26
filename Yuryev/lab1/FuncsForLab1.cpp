#include <iostream>
#include <fstream>
using namespace std;

#include "headers.h"

int find_needed_bracket (int start, int end, char* list_for_find, char bracket, char symbol)
{
    int j = 0;
    for (int k = start + 1; k <= end; k++) // идем от начала до указанного конца
    {
            // при встрече открывающих скобок добавляем 1, при закрывающих вычитаем
        if (list_for_find[k] == bracket)
            j += 1;
        else if (list_for_find[k] == symbol)
            j -= 1;
        if (j == -1)
            return k;
    }
    return -1; // не нашел нужную закрывающую скобку
}

int text_with_brackets(int l_st_number, int l_end_number, char* line, int depth)
{
    for (int j = 0; j < depth; j++)
            cout << "    ";
    cout << "Now in TwB function" << endl;
    if (element(l_st_number, l_end_number, line, depth + 1)) // пихаем в "элемент" все, что есть
    {
        for (int j = 0; j < depth; j++)
            cout << "    ";
        cout << "\"";
        for (int k = l_st_number; k <= l_end_number; k++)
            cout << line[k];
        cout << "\"\n";

        for (int j = 0; j < depth; j++)
            cout << "    ";
        cout << "All in this elem - true => It is text with brackets" << endl;
        return 1;
    }

    else if(l_st_number == l_end_number) // если не "элемент" и длина == 1, то не текст
    {
        for (int j = 0; j < depth; j++)
            cout << "    ";
        cout << "\"" << line[l_st_number] << "\"" << endl;
        for (int j = 0; j < depth; j++)
            cout << "    ";
        cout << "It is not element => It is not Text with brackets" << endl;

        return 0;
    }

    // если начинаются скобки - пытаемся отправить их в элемент
    else if ((line[l_st_number] == '(') || (line[l_st_number] == '[') || (line[l_st_number] == '{'))
    {
        char bracket = line[l_st_number], func_br = 'z';
        if (bracket == '(')
            func_br = ')';
        else if (bracket == '[')
            func_br = ']';
        else if (bracket == '{')
            func_br = '}';
        else 
            cout << "Strange things happen"<< endl;

        // ищем нужные закрывающие скобки
        int new_end_number = find_needed_bracket(l_st_number, l_end_number, line, bracket, func_br);

        if (new_end_number == l_end_number) // такой случай уже проверен при 1-й отправке в element()
        {
            return 0;
        }

        else if (new_end_number == -1) 
        {
            for (int j = 0; j < depth; j++)
                cout << "    ";
            cout << "\"";
            for (int k = l_st_number; k <= l_end_number; k++)
                cout << line[k];
            cout << "\"\n";

            for (int j = 0; j < depth; j++)
                cout << "    ";
            cout << "There are no needed ending brackets => It is not Text with brackets" << endl;
            return 0; // проверка на отсутствие закрывающих скобок
        }

        else if (new_end_number - l_st_number == 1)
        {
            for (int j = 0; j < depth; j++)
                cout << "    ";
            cout << "\"" << line[l_st_number]<< line [new_end_number] << "\"";

            for (int j = 0; j < depth; j++)
                cout << "    ";
            cout << "There are empty brackets => It is not Text with brackets" << endl;
            return 0; // проверка на "("пусто")"
        };

        if (element(l_st_number, new_end_number, line, depth + 1))
        { // если внутри скобок "элемент", то можно проверять оставшийся ТсС
            if (new_end_number == l_end_number)
            {
                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "\"";
                for (int k = l_st_number; k <= l_end_number; k++)
                    cout << line[k] << endl;
                cout << "\"\n";
                
                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "There are no text with brackets after Element => It is Text with brackets" << endl;
                return 1; // за ")" нет никакого ТсС
            }

            else if (text_with_brackets(new_end_number + 1, l_end_number, line, depth + 1))
            {
                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "\"";
                for (int k = l_st_number; k <= l_end_number; k++)
                    cout << line[k];
                cout << "\"\n";
                
                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "There are true Text with brackets after Element => It is Text with brackets" << endl;
                return 1;
            }
        }
    }

    else // смотрим не элемент ли первый символ
    {
        if (element(l_st_number, l_st_number, line, depth + 1))
        {
            if(text_with_brackets(l_st_number + 1, l_end_number, line, depth + 1)) // пихаем в TcC все кроме первого символа
            {
                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "\"" << line[l_st_number] << "\"" << " - true element and " << endl;
                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "\"";
                for (int k = l_st_number; k <= l_end_number; k++)
                    cout << line[k];
                cout << "\"";
                cout << " - true Text with brackets => It is Text with brackets" << endl;
                return 1;
            }
        }
        else
        {
            for (int j = 0; j < depth; j++)
                cout << "    ";

            cout << "\"";
            for (int k = l_st_number; k <= l_end_number; k++)
                cout << line[k];
            cout << "\"";

            cout << " - First char isn`t Element => It isn`t Text with brackets" << endl;
            return 0;
        }
    };
}

int element(int l_start_number, int l_end_number, char* line, int depth)
{
    for (int j = 0; j < depth; j++)
            cout << "    ";
    cout << "Now in Element function" << endl;
    if (l_start_number == l_end_number) // если 1 символ
    {
        if ((line[l_start_number] == 'A') || (line[l_start_number] == 'B'))
        {
            for (int j = 0; j < depth; j++)
                cout << "    ";
            cout << "\"" << line[l_start_number] << "\"" << endl;
            for (int j = 0; j < depth; j++)
                cout << "    ";
            cout << "It is Element" << endl;
            return 1;
        }
        else
        {
            for (int j = 0; j < depth; j++)
                cout << "    ";
            cout << "It is not Element" << endl;
            return 0;
        }
    }

    // если по краям стоят скобки
    else if( ((line[l_start_number]=='(') && (line[l_end_number]==')')) || ((line[l_start_number]=='{') && (line[l_end_number]=='}')) || ((line[l_start_number]=='[') && (line[l_end_number]==']')) )
        {
            if (l_end_number - l_start_number == 1) // если скобки пусты
            {
                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "\"" << line[l_start_number] << line[l_end_number] << "\"" << endl;

                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "It is not Element" << endl;
                return 0;
            }
            else if (text_with_brackets(l_start_number + 1, l_end_number - 1, line, depth + 1)) //убираем скобки
            {
                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "\"";
                for (int k = l_start_number; k <= l_end_number; k++)
                    cout << line[k];
                cout << "\"" << endl;

                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "It is Element" << endl;
                return 1;
            }
            else 
            {
                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "\"";
                for (int k = l_start_number; k <= l_end_number; k++)
                    cout << line[k];
                cout << "\"" << endl;

                for (int j = 0; j < depth; j++)
                    cout << "    ";
                cout << "It isn`t Text with brackets inside brackets => It isn`t Element" << endl;
                return 0;
            }
        }

    // если слишком много символов    
    else 
    {
        for (int j = 0; j < depth; j++)
            cout << "    ";
        cout << "\"";
            for (int k = l_start_number; k <= l_end_number; k++)
                cout << line[k];
        cout << "\"" << endl;

        for (int j = 0; j < depth; j++)
            cout << "    ";
        cout << "It is not Element" << endl;
        return 0;
    }
    return 0;
}

int reading_file(string FileName, char* Array)
{
    ifstream file(FileName); // окрываем файл для чтения (для записи ofstream)

    if (file.is_open())
    {
        file.getline(Array,400,' ');
        cout << "Input text is: \n" << Array << endl;
    }
    else
    {
        cout << "проблема с открытием файла" << endl;
        return 1;
    }
    file.close();     // закрываем файл
    return 0;

}
