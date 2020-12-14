#include<iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>

#define FILE "/home/indiora/C++/Aisd/read.txt"

using namespace std;

string readFile(const string& file_name) {
    ifstream f(file_name); // Экземпляр класса
    stringstream ss;
    ss << f.rdbuf(); // Возвращает указатель на потоковый буфер
    return ss.str(); // Возвращает строку
}


template <typename T=string>
class Hash {
private:
    vector<vector<T>> table;
    // размер таблицы
    int size=10;
public:
    // Конструктор
    Hash() {
        table.reserve(size);
    }
    // Хеш функция реализованная адаптивным методом
    int hashFunction(T value) {
        int s = 0;
        for(int i = 0 ; i < value.length(); i++)
            s += value[i];
        // возвращает ключ
        return s % size;
    }
    // Вставка elem
    void insertElem(T value) {
        // Расчитываем ключ от значения
        int key = hashFunction(value);
        // Добавляем в соответствующую ячейку таблицы
        table[key].push_back(value);
    }
    // Поиск elem
   int findElem(T value) {
       // Расчитываем ключ от значения
       int key = hashFunction(value);
       int count = 0;
       // В цикле обходим цепочку с соответствующим ключом
       for (typename vector<T>::iterator i = begin(table[key]); i != end(table[key]); ++i) {
           // При нахождении elem увеличиваем счетчик
           if (*i == value){
               count++;
           }
       }
       // Возвращаем количество элементов
       return count;
   }

    void displayHash() {
        // Обходим всю таблицу
        for (int i = 0; i < size; i++) {
            cout << i;
            // Выводим элементы цепочки
            for (auto x : table[i]) {
                cout << " --> " << x;
            }
            cout << "\n";
        }
        cout << "\n";
   }

};



int main(int argc, char const *argv[]) {
    // Создаем экземпляр класса Hash
    Hash table;
    // Создаем экземпляр класс is.. и передаем ему строку считанную из файла
    istringstream iss(readFile(FILE));
    // Разбиваем считанную строку на Elem
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
    // Заносим Elem в хэш табоицу
    for(int i = 0; i < tokens.size(); i++){
        table.insertElem(tokens[i]);
    }
    // Выводим строку считанную из файла
    cout << "You entered: ";
    cout << iss.str() << '\n';
    // Выводим хэш таблицу
    cout << "Hash table" << "\n\n";
    table.displayHash();

    string input;

    while( input != "!No"){
        cout << "Enter the element you want to find and add, to exit type !No" << "\n";
        // Считываем значение введенное пользователем
        cin >> input;
        if (input != "!No") {
            // Выводим количество elem в таблице
            cout << "Number of elements in the hash table: " << table.findElem(input) << "\n";
            cout << "Added " << input << " in hash table"<< "\n\n";
            // Вставляем elem в таблицу
            table.insertElem(input);
            // Выводим таблицу
            table.displayHash();
        }
    }

    return 0;
}
//cat sad I_am bob_nop round what
