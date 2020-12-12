#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdio>
#include <typeinfo>


/*
 * функция сравнения двух чисел
 */
bool cmp(int a, int b){
    std::cout << "Compare " << a << " and " << b << std::endl;
    if (a > b){
        return true;
    }
    return false;
}

void shell(std::vector<int>& data)
{
    int step, i, j;
    unsigned int time1 = clock();

    for (step = data.size() / 2; step > 0; step /= 2)
    {
        std::cout << "Current step: " << step << '\n';
        // Перечисление элементов, которые сортируются на определённом шаге
        for (i = step; i < data.size(); i++) {
            // Перестановка элементов внутри подсписка, пока i-тый не будет отсортирован
            for (j = i - step; j >= 0  && cmp(data[j], data[j + step]); j -= step)
            {
                std::cout << "Change elem " << data[j] << " and " << data[j+step] << std::endl;
                std::swap(data[j], data[j + step]);
                std::cout << "Array after change: ";
                for (auto& k : data)
                {
                    std::cout << k << " ";
                }
                std::cout << std::endl;
            }
        }
        std::cout << "Array after step: ";
        for (auto& k : data)
        {
            std::cout << k << " ";
        }
        std::cout << std::endl << std::endl;
    }

    unsigned int time2 = clock();

    std::cout << "Time : " << (time2 - time1) / 1000.0 << "s\n"; // Подсчет длительности выполнения
}

/*
 * Функция проверки строки на число
 */
bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

//главная функция

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int n;
    std::cout << "Write f - if reading from file, any other - if console" << std::endl;
    std::vector<int> arrayForShell;
    std::vector<int> arrayForStdSort;
    char symbol;
    std::string  numb;
    std::cin >> symbol;
    /*
     * Считывания данных из файла
     */
    if (symbol == 'f'){
        std::cout << "Enter the path to the file:" << std::endl;
        std::string  input;
        std::cin >> input;
        std::ifstream fin;
        fin.open(input);
        if (!fin){
            std::cout << "file error" << std::endl;
            fin.close();
            system("pause");
            std::cout << "To continue the program, press any key ...";
            std::cin.get();
            exit(1);
        }
        fin >> numb;
        if (is_digits(numb)){
            n = std::atoi(numb.c_str());
        } else{
            std::cout << "Incorrect length" << std::endl;
            system("pause");
            std::cout << "To continue the program, press any key ...";
            std::cin.get();
            exit(1);
        }
        for (int i = 0; i < n; i++){
            fin >> numb;
            if (is_digits(numb)) {
                arrayForShell.push_back(std::atoi(numb.c_str()));
            } else{
                std::cout << "Data is incorrect" << std::endl;
                system("pause");
                std::cout << "To continue the program, press any key ...";
                std::cin.get();
                exit(1);
            }
        }
        std::cout << "Input array: ";
        for(auto i: arrayForShell){
            std::cout << i << " " ;
        }
        std::cout << std::endl;
        /*
         * Считывание данных из консоли
         */
    } else{
        std::cout<<"Array size > " ;
        std::cin >> numb;
        std::cout << std::endl;
        if (is_digits(numb)){
            n = std::atoi(numb.c_str());
        } else{
            std::cout << "Incorrect length" << std::endl;
            system("pause");
            std::cout << "To continue the program, press any key ...";
            std::cin.get();
            exit(1);
        }
        for (int i = 0; i < n; i++){
            std::cout<<i+1<<" item > " << std::endl;
            std::cin >> numb;
            if (is_digits(numb)) {
                arrayForShell.push_back(std::atoi(numb.c_str()));
            } else{
                std::cout << "Data is incorrect" << std::endl;
                system("pause");
                std::cout << "To continue the program, press any key ...";
                std::cin.get();
                exit(1);
            }
        }
    }
    /*
     * Занесение элементов в массив для стандартной сортировки
     */
    for (int i = 0; i < n; i++){
        arrayForStdSort.push_back(arrayForShell[i]);
    }

    std::cout << std::endl << "Shell sort call" << std::endl << std::endl;
    shell(arrayForShell); //Вызов сортировки Шелла

    /*
     * Вывод отсортированного массива
     */
    std::cout<<"Resulting array: ";
    for (int i=0; i<n; i++) {
        std::cout<<arrayForShell[i]<<" "; //вывод массива
    }
    std::cout << std::endl;
    std::cout << std::endl << "Calling the standard sort " << std::endl;
    std::sort(arrayForStdSort.begin(), arrayForStdSort.end()); //Вызов стандартной сортировки
    std::cout<<"Array after standard sort: ";
    for (int i=0; i<n; i++) {
        std::cout<<arrayForStdSort[i]<<" "; //вывод массива
    }
    std::cout << std::endl;
    system("pause");
   // std::cout << "To continue the program, press any key ...";
    std::cin.get();
    return 0;
}

