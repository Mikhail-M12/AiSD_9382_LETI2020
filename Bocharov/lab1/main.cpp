#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int spaceCount = 0; // Счетчик количества пробелов, для вывода порядка рекурсивных вызовов

//функция считывания списка имен из файла
template<typename StreamT>
std::vector<std::string> getNames(StreamT &in) {
    std::cout << "введите сиписок имен через enter" << std::endl;
    std::vector<std::string> names;
    std::string line;

    while (std::getline(in, line) && !line.empty()) {
        names.push_back(line);
    }

    if (names.empty()) {
        throw std::runtime_error("Список имен пуст!");
    }
    return names;
}

//функция формирует матрицу смежности используя данные из файла
template<typename StreamT>
void getRelationsMatrix(StreamT &in, std::vector<std::vector<bool>> &relationTable) {
    std::string line;
    int temp;
    int parent;

    while (std::getline(in, line) && !line.empty()) {
        std::istringstream str(line);
        if (!(str >> parent))
            throw std::runtime_error("ошибка: неверный номер родителя!");
        else {
            if (parent >= relationTable.size() || parent < 0)
                throw std::runtime_error("ошибка: неверный номер родителя!");
            else {
                while (str >> temp) {
                    if (temp >= relationTable.size() || temp < 0) {
                        throw std::runtime_error("ошибка: неверные номер ребенка!");
                    }
                    relationTable[parent][temp] = true;
                    relationTable[temp][parent] = true;
                }
            }
        }
    }
}

//функция рекурсивно проверяет, являеются ли 2 элемента родственниками
bool isFamily(int a, int b, std::vector<std::vector<bool>> &arr) {
    if (a == b)
        return false;
    if (arr[a][b]) {
        return true;
    } else {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[a][i]) {
                arr[a][i] = false;
                arr[i][a] = false;
                if (isFamily(i, b, arr)) {
                    arr[a][i] = true;
                    arr[i][a] = true;
                    return true;
                }
                arr[a][i] = true;
                arr[i][a] = true;
            }
        }
    }
    return false;
}

//функция рекурсивно проверяет, являеются ли 2 элемента родственниками и выводит порядок вызовов
bool isFamilyWithDetails(int a, int b, std::vector<std::vector<bool>> &arr) {
    std::string sp(spaceCount, ' '); // строка с табами
    std::cout << sp << "isFamily(" << a << " and " << b << ")  ";
    if (a == b)
        return false;
    if (arr[a][b]) {
        std::cout << "(Родственники)" << std::endl;
        return true;
    } else {
        spaceCount++;
        std::cout<<"-"<<std::endl;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[a][i]) {
                arr[a][i] = false;
                arr[i][a] = false;
                if (isFamilyWithDetails(i, b, arr)) {
                    arr[a][i] = true;
                    arr[i][a] = true;
                    spaceCount--;
                    return true;
                }
                arr[a][i] = true;
                arr[i][a] = true;
            }
        }
    }
    spaceCount--;
    if (spaceCount == 0)
        std::cout << "(Не родственники)" << std::endl;
    return false;
}

//функция выводит имена и их номера в списке
void printNames(std::vector<std::string> names) {
    std::cout << "Вывод имен" << std::endl;
    for (int i = 0; i < names.size(); i++)
        std::cout << i << " : " << names[i] << std::endl;
}

std::vector<std::vector<bool>> createArray(int size) {
    std::vector<std::vector<bool>> res;
    res.resize(size);
    for (auto &v : res) {
        v.resize(size);
    }
    return res;
}

//функция выводит матрицу смежности
void printRelationsMatrix(std::vector<std::vector<bool>> &arr) {
    std::cout << "вывод матрицы смежности" << std::endl;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

//функция выводит пары родственников
void printPairs(std::vector<std::string> names, std::vector<std::vector<bool>> &arr) {
    std::cout << "вывод пар" << std::endl;
    for (int i = 0; i < arr.size() - 1; i++)
        for (int j = i + 1; j < arr.size(); j++)
            if (isFamily(i, j, arr))
                std::cout << names[i] << " <--> " << names[j] << std::endl;
}

void printPairsWithDetails(std::vector<std::string> names, std::vector<std::vector<bool>> &arr) {
    std::cout << "вывод пар" << std::endl;
    for (int i = 0; i < arr.size() - 1; i++)
        for (int j = i + 1; j < arr.size(); j++)
            if (isFamilyWithDetails(i, j, arr))
                std::cout << names[i] << " <--> " << names[j] << std::endl;
}

int main() {
    try {
        std::cout << "1 - read from file  2 - read from console" << std::endl;


        int readFormat = 0;
        std::cin >> readFormat;
        std::cin.ignore();

        std::ifstream in;
        std::vector<std::string> names;// массив имен жителей

        if (readFormat == 1) {
            std::cout << "Введите имя файла: ";
            std::string fileName;
            std::cin >> fileName;
            in.open(fileName);
            if (in) {
                names = getNames(in);
            } else {
                throw std::runtime_error("Файл не найден!");
            }
        } else if (readFormat == 2) {
            names = getNames(std::cin);
        } else
            throw std::runtime_error("Неправильный формат ввода");
        std::cout << "Количество жителей :" << names.size() << std::endl;

        std::vector<std::vector<bool>> relationsMatrix = createArray(names.size());

        if (readFormat == 1) {
            getRelationsMatrix(in, relationsMatrix);
        } else {
            getRelationsMatrix(std::cin, relationsMatrix);
        }

        std::cout << "Введите код выбраного действия" << std::endl;
        int printValue = 0;
        std::cout
                << " 1 - вывести пары\n"
                   " 2 - вывести пары с деталями поиска\n"
                   " 3 - вывести список имен\n"
                   " 4 - вывести матрицу смежности\n"
                   " 0 - выход из программы"
                << std::endl;

        while (std::cin >> printValue) {
            switch (printValue) {
                case 1: {
                    printPairs(names, relationsMatrix);
                    break;
                }
                case 2: {
                    printPairsWithDetails(names, relationsMatrix);
                    break;
                }
                case 3: {
                    printNames(names);
                    break;
                }
                case 4: {
                    printRelationsMatrix(relationsMatrix);
                    break;
                }
                case 0: {
                    return 0;
                }
                default: {
                    throw std::runtime_error("Ошибка: выбрано неправильное действие");
                }
            }
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
