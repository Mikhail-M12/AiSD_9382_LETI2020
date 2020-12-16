#include <iostream>
#include <vector>
#include <forward_list>
#include <fstream>
#include <sstream>

bool sortFormat = false;

typedef std::vector<std::forward_list<std::string>> Piles;
typedef std::forward_list<std::string> Pile;

bool isNumber(const std::string &str) {
    char *ptr;
    strtol(str.c_str(), &ptr, 10);
    return *ptr == '\0';
}

bool compS(const std::string &a, const std::string &b) {
    return a >= b;
}

bool compI(const std::string &a, const std::string &b) {
    if (!isNumber(a))
        throw std::runtime_error("Найдено нецелочисленное значение < " + a + ">");
    if (!isNumber(b))
        throw std::runtime_error("Найдено нецелочисленное значение < " + b + ">");
    return strtol(a.c_str(), nullptr, 10) >= strtol(b.c_str(), nullptr, 10);
}

bool compare(const std::string &a, const std::string &b) {
    return sortFormat == 1 ? compI(a, b) : compS(a, b);
}

//Функция добавляет считанный элемент в массив списков
void pushInPiles(Piles &piles, const std::string &element) {
    if (piles.empty()) {
        Pile k;
        k.push_front(element);
        piles.push_back(k);
        return;
    }
    int beg = 0, end = piles.size() - 1;
    int temp1 = 0;
    int temp2 = 0;
    int mid;
    while (beg <= end) {
        mid = (end + beg) / 2;
        if (compare(piles.at(mid).front(), element)) {
            temp2 = mid;
            end = mid - 1;
        } else {
            temp1 = mid;
            beg = mid + 1;
        }
    }
    if (compare(piles.at(temp1).front(), element)) {
        piles.at(temp1).push_front(element);
        return;
    } else if (compare(piles.at(temp2).front(), element)) {
        piles.at(temp2).push_front(element);
        return;
    } else {
        Pile k;
        k.push_front(element);
        piles.push_back(k);
    }
}

//Функция считывает элементы из входного потока
template<typename StreamT>
void readPiles(StreamT &in, Piles &piles) {
    std::string element;
    std::string line;

    std::getline(in, line);
    if (line == "0")
        sortFormat = 0;
    else if (line == "1")
        sortFormat = 1;
    else throw std::runtime_error("Неверный тип сортировки");

    std::getline(in, line);
    std::istringstream str(line);
    while (getline(str, element, ' ')) {
        if (element != " ")
            pushInPiles(piles, element);
    }
}


//Функция выводит упорядоченный списк на экран
template<typename T>
void printPile(const T &pile) {
    for (auto &i:pile) {
        std::cout << i << " ";
    }
}

//Функция выводит массив списков
template<typename T>
void printPiles(const T &piles) {
    int k = 1;
    std::cout << "Вывод стопок" << std::endl;
    for (auto &i:piles) {
        std::cout << "Стопка" << k << " : ";
        printPile(i);
        k++;
        std::cout << std::endl;
    }
}

//Функция извлекает минимальную вершину
std::string popMin(Piles &piles, int &k) {

    std::string res = piles.front().front();
    int num = 0;
    for (int i = 0; i <= k && i<piles.size(); i++) {
        if (compare(res, piles.at(i).front())) {
            res = piles.at(i).front();
            num = i;
        }
    }
    piles.at(num).pop_front();
    k = num + 1;
    if (piles.at(num).empty()) {
        piles.erase(piles.begin() + num);
    }
    std::cout << "<min> = " << res << std::endl;
    return res;
}
//Функция сортирует считанные данные
std::vector<std::string> sort(Piles &piles) {
    std::vector<std::string> res;
    int k = 0;
    while (!piles.empty()) {
        res.push_back(popMin(piles, k));
        printPiles(piles);

        std::cout<<std::endl;
    }
    return res;
}
//Функция выводит массив
void printReasult(const std::vector<std::string>& result) {
    std::cout<<"result-->> ";
    for (auto &i : result)
        std::cout << i << " ";
}
//Функция считывает формат ввода и выполняет считывание входных данных
void launch() {
    Piles piles;
    int readFormat;

    std::cout << "0 - считать из файла, 1 - считать с консоли" << std::endl;
    std::cin >> readFormat;
    std::cin.ignore();
    switch (readFormat) {
        case 0: {
            std::cout << "Введите имя файла : ";
            std::ifstream in;
            std::string fileName;
            std::cin >> fileName;
            in.open(fileName);
            if (in) {
                readPiles(in, piles);
            } else
                throw std::runtime_error("Файл не найден!");
            in.close();
            break;
        }
        case 1: {
            std::cout
                    << "Введите тип сортировки 1 - сортировка целых чисел, 0 - сортировка строк в лексикографическом порядке"
                    << std::endl;
            std::cout << "Затем введите последовательность значений через пробел. Например: 1 2 3 4 5"
                      << std::endl;
            readPiles(std::cin, piles);
            break;
        }
        default: {
            throw std::runtime_error("Неверное действие");
        }
    }

    printPiles(piles);
    printReasult(sort(piles));
}

int main() {
    try {
        launch();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
