#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdio>
#include <typeinfo>


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
            for (j = i - step; j >= 0 && data[j] > data[j + step]; j -= step)
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
        for (auto& k : data)
        {
            std::cout << k << " ";
        }
        std::cout << std::endl;
    }

    unsigned int time2 = clock();

    std::cout << "Time : " << (time2 - time1) / 1000.0 << "s\n"; // Подсчет длительности выполнения
}


//главная функция

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int n;
    std::cout << "Write f - if reading from file, any other - if console" << std::endl;
    char symbol;
    std::cin >> symbol;
    char input[200];
    /*
     * Считывание название файла из командной строки, после чего
     * Считывание размера массива из файла
     */
    if (symbol == 'f'){
        std::cout << "Enter the path to the file:" << std::endl;
        fflush(stdin);
        std::cin.getline (input, 200);
        //std::ifstream fin;
        FILE* fin;
        //fin.open(input);
        fin = fopen(input, "r");
        if (!fin){
            std::cout << "file error" << std::endl;
            fclose(fin);
            system("pause");
            std::cout << "To continue the program, press any key ...";
            std::cin.get();
            exit(1);
        }
        int error;
        fflush(fin);
        error = fscanf(fin, "%d", &n);
        if (error != 1){
            fclose(fin);
            std::cout << "Data is incorrect"<< std::endl;
            system("pause");
            std::cout << "To continue the program, press any key ...";
            std::cin.get();
            exit(1);
        }
        fclose(fin);

    } else {
        /*
         * Считывание размера массива из консоли
         */
        std::cout<<"Array size > " ;
        int error;
        error = scanf("%d", &n);
        if (error != 1){
            std::cout << "Data is incorrect" << std::endl;
            system("pause");
            std::cout << "To continue the program, press any key ...";
            std::cin.get();
            exit(1);
        }
        std::cout << std::endl;
    }
    if (n <= 0){
        std::cout << "Incorrect length" << std::endl;
        system("pause");
        std::cout << "To continue the program, press any key ...";
        std::cin.get();
        exit(1);
    }

    std::vector<int> arrayForShell; //объявление динамического массива
    std::vector<int> arrayForStdSort; // создание вектора для стандартной сортировки

    /*
     * Считывание массива из файла
     */
    if (symbol == 'f'){
        /*std::ifstream fin;
        fin.open(input);
        fin >> n;*/
        FILE* fin;
        //fin.open(input);
        fin = fopen(input, "r");
        if (!fin){
            std::cout << "file error" << std::endl;
            fclose(fin);
            system("pause");
            std::cout << "To continue the program, press any key ...";
            std::cin.get();
            exit(1);
        }
        int error;
        error = fscanf(fin, "%d", &n);
        if (error != 1){
            fclose(fin);
            std::cout << "Data is incorrect" << std::endl;
            system("pause");
            std::cout << "To continue the program, press any key ...";
            std::cin.get();
            exit(1);
        }
        int currentNumb;
        error = 0;
        for (int i=0; i<n; i++){
            error = fscanf(fin, "%d", &currentNumb);
            if (error != 1){
                fclose(fin);
                std::cout << "Data is incorrect" << std::endl;
                system("pause");
                std::cout << "To continue the program, press any key ...";
                std::cin.get();
                exit(1);
            }
            arrayForShell.push_back(currentNumb);
        }
        std::cout << "The array fed: ";
        for (int i=0; i<n; i++){
            std::cout << arrayForShell[i] << ' ';
        }
        fclose(fin);
        std::cout << std::endl;
    } else{
        /*
        * Считывание массива из консоли
        */
        int error;
        int currentNumb;
        for (int i=0; i<n; i++){
            std::cout<<i+1<<" item > " << std::endl;
            error = scanf("%d", &currentNumb);
            if (error != 1){
                std::cout << "Data is incorrect" << std::endl;
                system("pause");
                std::cout << "To continue the program, press any key ...";
                std::cin.get();
                exit(1);
            }
            arrayForShell.push_back(currentNumb);
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

