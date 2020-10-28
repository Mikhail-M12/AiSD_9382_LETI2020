#include "string"
#include "iostream"
#include <fstream>

typedef unsigned long long int number;

number cnk(number m, number n)
{
    if ((m == 0 && n > 0) || (m == n && n >= 0))
    {
        std::cout << "cnk(" << m << " по " << n << ")= 1, т.к. либо (m = 0 и n > 0), либо (m = n >= 0)\n";
        return 1;
    }
    if (m > n && n >= 0) {
        std::cout << "cnk(" << m << " по " << n << ")= 0, т.к. m > n >= 0\n";
        return 0;
    }
    if (n > m) {
        number num = cnk(m - 1, n - 1) + cnk(m, n - 1);
        std::cout << "cnk(" << m << " по " << m <<") = " << num <<" по заданной формуле\n";
        return num;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::ifstream fin("../file.txt");
    if (!fin.is_open()) {
        std::cout << "Не удалось открыть файл!" << std::endl;
        fin.close();
        return 0;
    }
    number n, k;
    fin >> n >> k;
    cnk(n, k);
    return 0;
}
