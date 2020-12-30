#include "string"
#include "iostream"
#include <fstream>


typedef long long int number;

number cnk(number m, number n, int count)
{
    if ((m == 0 && n > 0) || (m == n && n >= 0)){
        for(int i = 0; i < count; i++){
            std::cout<<" ";
        }
        std::cout << "cnk(" << n << " по " << m << ")= 1, т.к. либо (m = 0 и n > 0), либо (m = n >= 0)\n";
        return 1;
    }
    if (m > n && n >= 0) {
        for(int i = 0; i < count; i++){
            std::cout<<" ";
        }
        std::cout << "cnk(" << n << " по " << m << ")= 0, т.к. m > n >= 0\n";
        return 0;
    }
    if (n > m) {
        count++;
        std::cout<<"Я вхожу в рекурсивный цикл "<<count<<"\n";
        number num = cnk(m - 1, n - 1, count) + cnk(m, n - 1, count);
        for(int i = 0; i < count; i++){
            std::cout<<" ";
        }
        std::cout << "cnk(" << n << " по " << m <<") = " << num <<" по заданной формуле\n";
        std::cout<<"Я выхожу из рекурсивного цикла "<<count<<"\n";

        return num;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::ifstream fin("../file.txt");

    number n, k;
    char ans;

    std::cout<<"Ввод с консоли? Y/N\n";
    std::cin>>ans;
    if(ans=='Y'){
        std::cout<<"Введите числа:\n";
        std::cin >> n >> k;
        if (n < 0 || k < 0){
            std::cout << "Числа должны быть неотрицательнымия!";
            return 0;
        }
        cnk(k, n, 0);


    }
    else if(ans=='N') {
        if (!fin.is_open()) {
            std::cout << "Не удалось открыть файл!" << std::endl;
            fin.close();
            return 0;
        }
        fin >> n >> k;
        if (n < 0 || k < 0){
            std::cout << "Числа должны быть неотрицательными!";
            return 0;
        }
        cnk(k, n, 0);
    } else
        std::cout <<"Введите ответ корректно";
    return 0;
}
