#include <iostream>
#include <fstream>

//количество отступов для вывода рекурсивных функций
static int k = 0;
//для вывода промежуточных значений 
static std::ofstream fout;

//recursive function
long f(long n) {
    //начало функции f(n)
    fout << "startf: f(" << n << ")::\\";
    fout << "\n";
    long sumFunctionValues = 0;
    if (n == 1) {//f(1)=1
        fout << "\n";
        for (int i = 0; i < k; i++) {
            fout << "\t";
        }
        fout << "/endf f(" << n << ")::" << 1;
        fout << "\n";

        return 1;
    }
    if (n >= 2) {
        for (long i = 2; i <= n; i++) {
            //вывод отступов
            k++;
            for (int i = 0; i < k; i++) {
                fout << "\t";
            }
            // сумма значений функции
            sumFunctionValues += f(n / i);

            k--;
            fout << "\n";
        }
        //вывод отступов
        for (int i = 1; i <= k; i++) {
            fout << "\t";
        }
        //конец функции f(n)
        fout << "/endf /f(" << n << ")::" << sumFunctionValues;
        fout << "\n";

        return sumFunctionValues;
    }
    return 0;
}

//функция вывода рекурсивной функции от значений на промежутке [a,b]
//либо в файл, либо в консоль
void print_result(int a, int b) {
    long n = 0;
    int type = 0;
    std::cout << "Print to console - 1\n";
    std::cout << "Print to file - 2\n";
    std::cin >> type;

    std::ofstream file;
    std::string name_f;
    if (type == 2) {
        std::cout << "Enter file name\n";
        std::cin >> name_f;
        file.open(name_f);
    }
    for (int i = a; i < b; ++i) {
        fout << "f(" << i << ") : " << "\n";
        fout << "-------------------------------------------------------------------" << "\n";
        n = f(i);
        if (type == 1) {
            std::cout << "f(" << i << ") : " << n << "\n";
        } else {

            if (file.is_open()) {
                file << "f(" << i << ") : " << n << "\n";
            }else{
                std::cout<<"fileIsClose";
            }
        }
    }
}

//type_selection
void type_selection() {
    //тип вызова рекурсивной функции
    int type = 0;
    // значение для вызова рекурсивной функции
    int value = 0;

    std::ifstream file;
    std::string name_f;

    std::cout << "select type:\n 1-one value from console,2 - from 15 to 30,3 - one value from file\n";
    std::cin >> type;//ввод типа
    switch (type) {
        case 1:
            std::cout << "enter value\n";
            std::cin >> value;
            if (value < 1) {//проверка на ошибку
                std::cout << "Incorrect elem";
                break;
            }
            //вызов функции которая выведет на экран значение рекурсивной функции от value
            print_result(value, value + 1);
            break;
        case 2:
            //вызов функции которая выведет на экран значения рекурсивной функции от промежутка от [15,30]
            print_result(15, 31);
            break;
        case 3:
            std::cout << "Enter file name\n";
            std::cin >> name_f;
            file.open(name_f);
            file>>value;
            if(file.is_open()){
            print_result(value,value+1);
            } else{
                std::cout<<"fileIsClose";
            }
            file.close();
            break;
        default:
            std::cout << "error: wrong type";
    }
    std::cout << "intermediate values are written to the file intermediateResults.txt";
}

int main() {
    //открытие файла для промежуточных значений
    fout.open("intermediateResults.txt");
    //выбор типа для вызова функции
    type_selection();
    //закрытие файла для промежуточных значений
    fout.close();
    return 0;
}
