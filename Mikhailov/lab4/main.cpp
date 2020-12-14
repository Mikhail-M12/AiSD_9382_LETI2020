#include <iostream>
#include<vector>
#include<string>
#include <fstream>
#include <sstream>

#define ERR_SYMBOL_B -1
#define ERR_SYMBOL_N -2
#define ERR_LENGTH -3

using namespace std;

struct dArr
{
    int length;
    int *base;
};

/**
 * Вычисляет количество элементов (чисел), разделенных пробелом, и проверяет корректность формата
 * @param input - входная строка
 */
int strCount(string &input) {
    unsigned int count = 0;
    bool num = false;
    if (input.empty())
        return 0;
    for (char i : input) {
        if (i == ' ') {
            if (num) {
                count++;
                num = false;
            }
        } else {
            if (!isdigit(i))
                return ERR_SYMBOL_B;
            num = true;
        }
    }
    if (num)
        count++;
    return static_cast<int>(count);
}

/**
 * Проверяет совпадение строк по количеству чисел в них, а также проверят корректность входных данных
 * Возвращает количество чисел
 * @param bolts болты
 * @param nuts гайки
 */
int checkStr(string &bolts, string &nuts) {
    int nB = strCount(bolts);
    if (nB == -1)
        return ERR_SYMBOL_B;
    int nN = strCount(nuts);
    if (nN == -1)
        return ERR_SYMBOL_N;
    if (nN == nB)
        return nN;
    return ERR_LENGTH;
}

/**
 * Создает динамический массив чисел из принятой строки
 * @param input входная строка
 * @param length длина массива
 */
dArr makeArray(string &input, int length) {
    dArr output{};
    output.base = new int[length];
    output.length = length;
    stringstream temp;
    temp << input;
    for (int i = 0; i < length; i++) {
        temp >> output.base[i];
    }
    return output;
}

/**
 * Возвращает строку, состоящую из элементов массива, разделенных пробелом
 * @param input
 */
string getStrFromArray(dArr &input) {
    string output;
    for (int i = 0; i < input.length; i++) {
        output += to_string(input.base[i]);
        output += " ";
    }
    return output;
}

/**
 * Возвращает строку, состоящую из двух массивов, в которых два элемента выделены фигурными скобками
 * @param bolts массив болтов
 * @param ptr1 позиция в массиве болтов
 * @param nuts массив гаек
 * @param ptr2 позиция в массиве гаек
 */
string getStrCmpAction(dArr &bolts, int ptr1, dArr &nuts, int ptr2) {
    string output;
    output += "--------------------------------------------------------------------------\n";
    output += "Сравниваем элементы:\nБолты:\n";
    for (int i = 0; i < bolts.length; i++) {
        if (i == ptr1)
            output += "{";
        output += to_string(bolts.base[i]);
        if (i == ptr1)
            output += "}";
        output += " ";
    }
    output += "\nГайки:\n";
    for (int i = 0; i < nuts.length; i++) {
        if (i == ptr2)
            output += "{";
        output += to_string(nuts.base[i]);
        if (i == ptr2)
            output += "}";
        output += " ";
    }
    return output;
}

/**
 * Возвращает строку, состоящую из элементов массива, среди которых два элемента выделены фигурными скобками
 * @param input массив элементов
 * @param ptr1 позиция первого элемента
 * @param ptr2 позиция второго элемента
 */
string getStrSwapAction(dArr &input, int ptr1, int ptr2) {
    string output;
    output += "Меняем элементы местами: ";
    for (int i = 0; i < input.length; i++) {
        if (i == ptr1 || i == ptr2)
            output += "{";
        output += to_string(input.base[i]);
        if (i == ptr1 || i == ptr2)
            output += "}";
        output += " ";
    }
    output += "\n";
    return output;
}

/**
 * Проверяет, совпадают ли в отсортированных массивах элементы с одинаковыми индексами (проверка пар)
 * @param bolts массив болтов
 * @param nuts массив гаек
 */
int checkPairs(dArr &bolts, dArr &nuts) {
    for (int i = 0; i < bolts.length; i++) {
        if (bolts.base[i] != nuts.base[i])
            return 0;
    }
    return 1;
}

/**
 * Возвращает строку, в которой содержатся все пары в формате (Bi , Ni), где Bi и Ni – элементы двух массивов с индексом i
 * @param bolts массив болтов
 * @param nuts массив гаек
 */
string getPairs(dArr &bolts, dArr &nuts) {
    string output;
    for (int i = 0; i < bolts.length; i++) {
        if (bolts.base[i] == nuts.base[i]) {
            output += "(";
            output += to_string(bolts.base[i]);
            output += ", ";
            output += to_string(nuts.base[i]);
            output += ") ";
        }
    }
    return output;
}

/**
 * Сортирует массивы на основе алгоритма QuickSort
 * @param bolts массив болтов
 * @param nuts массив гаек
 * @param start начальная позиция
 * @param length длина массива
 * @param n количество рекурсий
 */
int qsortNB(dArr &bolts, dArr &nuts, int start, int length, int &n) {
    int ret = 0;
    string output;
    bool equiv = false;
    int bigger = start;
    if (length - start > 1) {
        n++;
        int center = nuts.base[length - 1];
        int i = start;
        while (i < length - 1) {
            output = getStrCmpAction(bolts, i, nuts, length - 1);
            if (bolts.base[i] < center) {
                output += "Болт меньше, перемещаем в левую часть\n";
                output += getStrSwapAction(bolts, i, bigger);
                swap(bolts.base[i], bolts.base[bigger]);
                output += "Результат:\nБолты:\n";
                output += getStrFromArray(bolts);
                output += "\nГайки:\n";
                output += getStrFromArray(nuts);
                bigger++;
            }
            if (bolts.base[i] == center) {
                if (!equiv)
                    equiv = true;
                else {
                    cout << "Ошибка! Обнаружены одинаковые болты" << endl;
                    return 2;
                }
                output += "Болт имеет такой же размер, перемещаем в конец\n";
                output += getStrSwapAction(bolts, i, length - 1);
                swap(bolts.base[i], bolts.base[length - 1]);
                output += "Результат:\nБолты:\n";
                output += getStrFromArray(bolts);
                output += "\nГайки:\n";
                output += getStrFromArray(nuts);
                continue;
            }
            cout << output << endl;
            i++;
        }
        equiv = false;
        center = bolts.base[length - 1];
        bigger = start;
        i = start;
        while (i < length - 1) {
            output = getStrCmpAction(bolts, length - 1, nuts, i);
            if (nuts.base[i] < center) {
                output += "Гайка меньше, перемещаем в левую часть\n";
                output += getStrSwapAction(nuts, i, bigger);
                swap(nuts.base[i], nuts.base[bigger]);
                output += "Результат:\nБолты:\n";
                output += getStrFromArray(bolts);
                output += "\nГайки:\n";
                output += getStrFromArray(nuts);
                bigger++;
            }
            if (nuts.base[i] == center) {
                if (!equiv)
                    equiv = true;
                else {
                    cout << "Ошибка! Обнаружены одинаковые гайки" << endl;
                    return 2;
                }
                output += "Гайка имеет такой же размер, перемещаем в конец\n";
                output += getStrSwapAction(nuts, i, length - 1);
                swap(nuts.base[i], nuts.base[length - 1]);
                output += "Результат:\nБолты:\n";
                output += getStrFromArray(bolts);
                output += "\nГайки:\n";
                output += getStrFromArray(nuts);
                continue;
            }
            cout << output << endl;
            i++;
        }
        ret = qsortNB(bolts, nuts, start, bigger, n);
        if (ret)
            return ret;
        ret = qsortNB(bolts, nuts, bigger, length - 1, n);
    }
    return ret;
}

int sortBN(dArr &bolts, dArr &nuts, int &n) {
    return qsortNB(bolts, nuts, 0, bolts.length, n);
}

int main() {
    int load;
    string bolts;
    string nuts;
    dArr boltsArr{};
    dArr nutsArr{};
    int n;
    bool isError;
    cout << "\x1b[32m********************  Болты и гайки  ********************\x1b[0m" << endl;
    cout << "Пожалуйста, выберите способ ввода данных: 1 - из файла, 0 - из консоли, любое другое значение - выход из программы" << endl;
    cout << "Ваш выбор: ";
    cin >> load;
    if (load == 1) {
        string filePath = "input.txt";
        ifstream fin(filePath, ios::in);
        if (fin) {
            getline(fin, bolts);
            getline(fin, nuts);
        } else {
            cout << "Ошибка! Входной файл не найден" << endl;
            return 0;
        }
        fin.close();
    } else if (load == 0) {
        cout << "Введите массив болтов через пробел: " << endl;
        cin.ignore(1);
        getline(cin, bolts);
        cout << "Введите массив гаек через пробел: " << endl;
        getline(cin, nuts);
    } else
        return 0;
    int num = checkStr(bolts, nuts);
    switch (num) {
        case 0:
            cout << "Ошибка! Введен пустой массив" << endl;
            isError = true;
            break;
        case ERR_SYMBOL_B:
            cout << "Ошибка! Болты могут быть заданы только цифрами" << endl;
            isError = true;
            break;
        case ERR_SYMBOL_N:
            cout << "Ошибка! Гайки могут быть заданы только цифрами" << endl;
            isError = true;
            break;
        case ERR_LENGTH:
            cout << "Ошибка! Количество болтов и гаек не совпадает" << endl;
            isError = true;
            break;
        default:
            isError = false;
            break;
    }
    if (!isError) {
        boltsArr = makeArray(bolts, num);
        nutsArr = makeArray(nuts, num);
        if (!sortBN(boltsArr, nutsArr, n)) {
            if (!checkPairs(boltsArr, nutsArr))
                cout << "Обнаружены непарные болты и гайки" << endl;
            else {
                cout << "================================================================" << endl;
                cout << "Количество элементов в массивах гаек и болтов: " << num << endl;
                cout << "Глубина рекурсии: " << n << endl;
                cout << "Сортировка завершена" << endl;
                cout << "Болты:" << endl;
                cout << getStrFromArray(boltsArr) << endl;
                cout << "Гайки:" << endl;
                cout << getStrFromArray(nutsArr) << endl;
                cout << "Найденные пары болтов и гаек:" << endl;
                cout << "\x1b[31m" << getPairs(boltsArr, nutsArr) << "\x1b[0m" << endl;
                cout << "================================================================" << endl;
            }
        } else {
            cout << "Сортировка прервана\n";
        }
    }
    return 0;
}