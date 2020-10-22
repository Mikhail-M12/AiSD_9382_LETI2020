#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

template <typename T>
void Shell(T* A, int n){ //сортировка Шелла
    int count, d;
    d=n/2; // Присвоение в d половины длины массива
    while (d>0){ // выполнение цикла пока d > 0
        for (int i=0; i<n-d; i++){
            std::cout << std::endl;
            std::cout << "Проход " << i+1  << ", d = " << d << std::endl;
            for (int j = i; j >= 0; j--){
                std::cout << "Сравнение элементов " << A[j] << " и " << A[j + d] << std::endl;
                if (A[j]>A[j+d]){ // сравнение двух элементов
                    /*
                     * Замена элементов если условие верно
                     */
                    std::cout << "Замена элементов " << A[j] << " и " << A[j + d] << std::endl;
                    count = A[j];
                    A[j] = A[j + d];
                    A[j + d] = count;
                    std::cout << "Массив после замены: ";
                    for (int k = 0; k < n; k++){
                        std::cout << A[k] << ' ';
                    }
                    std::cout << std::endl<<std::endl;
                }
                else{
                    std::cout  << A[j] << " и " << A[j + d] << " замена не требуется " << std::endl;
                }
                //std::cout << std::endl;
            }
        }
        d=d/2;
    }
}


//главная функция

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int n;
    bool file;
    std::cout << "Напишите f - если чтение из файла, любой другой - если консоль" << std::endl;
    char symbol;
    std::cin >> symbol;
    std::string input;
    /*
     * Считывание название файла из командной строки, после чего
     * Считывание размера массива из файла
     */
    if (symbol == 'f'){
        std::cout << "Введите путь до файла:" << std::endl;
        std::cin >> input;
        std::ifstream fin;
        fin.open(input);
        if (!fin){
            std::cout << "error";
            exit(1);
        }
        fin >> n;
    } else {
        /*
         * Считывание размера массива из консоли
         */
        std::cout<<"Размер массива > " ;
        std::cin>>n;
        std::cout << std::endl;
    }
    if (n <= 0){
        std::cout << "Некоректная длина";
        exit(1);
    }

    int* arrayForShell= new int[n]; //объявление динамического массива
    std::vector<int> arrayForStdSort; // создание вектора для стандартной сортировки

    /*
     * Считывание массива из файла
     */
    if (symbol == 'f'){
        std::ifstream fin;
        fin.open(input);
        fin >> n;
        for (int i=0; i<n; i++){
             fin>>arrayForShell[i];
        }
        std::cout << "Поданный массив: ";
        for (int i=0; i<n; i++){
            std::cout << arrayForShell[i] << ' ';
        }
        std::cout << std::endl;
    } else{
        /*
        * Считывание массива из консоли
        */
        for (int i=0; i<n; i++){
            std::cout<<i+1<<" элемент >"; std::cin>>arrayForShell[i];
        }

    }
    /*
     * Занесение элементов в массив для стандартной сортировки
     */
    for (int i = 0; i < n; i++){
        arrayForStdSort.push_back(arrayForShell[i]);
    }

    std::cout << std::endl << "Вызов сортировки Шелла" << std::endl << std::endl;
    Shell(arrayForShell, n); //Вызов сортировки Шелла

    /*
     * Вывод отсортированного массива
     */
    std::cout<<"Результирующий массив: ";
    for (int i=0; i<n; i++) {
        std::cout<<arrayForShell[i]<<" "; //вывод массива
    }
    std::cout << std::endl;
    std::cout << std::endl << "Вызов стандартной сортировки" << std::endl;
    std::sort(arrayForStdSort.begin(), arrayForStdSort.end()); //Вызов стандартной сортировки
    std::cout<<"Массив после стандартной сортировки: ";
    for (int i=0; i<n; i++) {
        std::cout<<arrayForStdSort[i]<<" "; //вывод массива
    }
    std::cout << std::endl;
    delete [] arrayForShell; //освобождение памяти
    system("pause");
    std::cout << "Для продолжения работы программы нажмите любую клавишу...";
    std::cin.get();
    return 0;
}

