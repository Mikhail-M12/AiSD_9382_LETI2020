#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

template <typename T>
void shell(T* A, int n){ //сортировка Шелла
    int count, d;
    d=n/2; // Присвоение в d половины длины массива
    while (d>0){ // выполнение цикла пока d > 0
        for (int i=0; i<n-d; i++){
            std::cout << std::endl;
            std::cout << "Passage " << i+1  << ", d = " << d << std::endl;
            for (int j = i; j >= 0; j--){
                std::cout << "Comparison of elements " << A[j] << " и " << A[j + d] << std::endl;
                if (A[j]>A[j+d]){ // сравнение двух элементов
                    /*
                     * Замена элементов если условие верно
                     */
                    std::cout << "Replacing elements " << A[j] << " и " << A[j + d] << std::endl;
                    count = A[j];
                    A[j] = A[j + d];
                    A[j + d] = count;
                    std::cout << "Array after replacement: ";
                    for (int k = 0; k < n; k++){
                        std::cout << A[k] << ' ';
                    }
                    std::cout << std::endl<<std::endl;
                }
                else{
                    std::cout  << A[j] << " и " << A[j + d] << " no replacement required " << std::endl;
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
    std::cout << "Write f - if reading from file, any other - if console" << std::endl;
    char symbol;
    std::cin >> symbol;
    std::string input;
    /*
     * Считывание название файла из командной строки, после чего
     * Считывание размера массива из файла
     */
    if (symbol == 'f'){
        std::cout << "Enter the path to the file:" << std::endl;
        std::cin >> input;
        std::ifstream fin;
        fin.open(input);
        if (!fin){
            std::cout << "error" << std::endl;
            system("pause");
            std::cout << "To continue the program, press any key ...";
            std::cin.get();
            exit(1);
        }
        fin >> n;
    } else {
        /*
         * Считывание размера массива из консоли
         */
        std::cout<<"Array size > " ;
        std::cin>>n;
        std::cout << std::endl;
    }
    if (n <= 0){
        std::cout << "Incorrect length" << std::endl;
        system("pause");
        std::cout << "To continue the program, press any key ...";
        std::cin.get();
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
        std::cout << "The array fed: ";
        for (int i=0; i<n; i++){
            std::cout << arrayForShell[i] << ' ';
        }
        std::cout << std::endl;
    } else{
        /*
        * Считывание массива из консоли
        */
        for (int i=0; i<n; i++){
            std::cout<<i+1<<" item > " << std::endl; std::cin>>arrayForShell[i];
        }

    }
    /*
     * Занесение элементов в массив для стандартной сортировки
     */
    for (int i = 0; i < n; i++){
        arrayForStdSort.push_back(arrayForShell[i]);
    }

    std::cout << std::endl << "Shell sort call" << std::endl << std::endl;
    shell(arrayForShell, n); //Вызов сортировки Шелла

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
    delete [] arrayForShell; //освобождение памяти
    system("pause");
    std::cout << "To continue the program, press any key ...";
    std::cin.get();
    return 0;
}
