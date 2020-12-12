#include <iostream>
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
    // Пояснения к хеш функции
    void howHash(T value) {
        int s = 0;
        std::cout << "In the loop we go through the element summing up its symbols from ASCII" << '\n';
        for(int i = 0 ; i < value.length(); i++) {
            s += value[i];
            std::cout << "Sum " << i + 1 << " symbol(s) "<< s << '\n';
        }
        std::cout << "Modulo division of the sum by the size of the table, and we get the key : ";
        std::cout << "\x1b[32m" << s % size << "\x1b[0m" << '\n';
        std::cout << '\n';
    }
    // Пояснения для вставки
    void howInsert(T value) {
        // Расчитываем ключ от значения
        int key = hashFunction(value);
        std::cout << "\nFor this we have to find its key using a hash function." << '\n';
        // Пояснения для ключа
        howHash(value);
        std::cout << "When we find the key we just need to insert the \""<< "\x1b[4;32m" << value << "\x1b[0m" << "\" into the " << "\x1b[32m" << key << "\x1b[0m" << " chain of the table." << "\n\n";
    }
    // Пояснения для удаления
    void howDelete(T value) {
        // Расчитываем ключ от значения
        int key = hashFunction(value);
        std::cout << "\nFor this we have to find its key using a hash function." << '\n';
        // Пояснения для ключа
        howHash(value);
        std::cout << "When we find the key we just need to delete the \""<< "\x1b[4;32m" << value << "\x1b[0m" << "\" from the " << "\x1b[32m" << key << "\x1b[0m" << " chain of the table." << '\n';
        std::cout << "To do this in the loop we go through the " << "\x1b[32m" << key << "\x1b[0m" << " chain in search of a \"" << "\x1b[4;32m" << value << "\x1b[0m" << "\" and if we meet it we delete it." << "\n\n";
    }
   // Удаление элемента
   void deleteElem(T value) {
       // получаем хеш-индекс ключа
       int key = hashFunction(value);
       // В цикле обходим цепочку с соответствующим ключом
       for (typename vector<T>::iterator i = begin(table[key]); i != end(table[key]); ++i) {
           // При нахождении elem удаляем его и прерываем цикл
           if (*i == value){
               table[key].erase(i);
               break;
           }
       }
   }
    void displayHash() {
        // Обходим всю таблицу
        cout << "\n";
        for (int i = 0; i < size; i++) {
            cout << "\x1b[36m" <<  i << "\x1b[0m";
            // Выводим элементы цепочки
            for (auto x : table[i]) {
                cout << "\x1b[35m --> \x1b[0m" << x;
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
    cout << "\x1b[35mYou entered: \x1b[0m" << iss.str() << "\n";
    std::cout << "For each of these elements, the key is calculated using a hash function and it is placed in the corresponding cell of the table." << '\n';
    // Выводим хэш таблицу
    cout << "\n\x1b[1mHash table\x1b[0m" << "\n";
    table.displayHash();

    string input;
    while(true) {
        cout << "\x1b[31mTo remove type : \"1\"\x1b[0m \n"
                "\x1b[32mTo insert type : \"2\"\x1b[0m \n"
                "\x1b[33mTo leave type :  \"3\"\x1b[0m \n\n";
        // Считываем значение введенное пользователем
        std::cout << "Your input : ";
        cin >> input;
        // Для удаления элеммента
        if (input == "1") {
            std::cout << "You want delete : ";
            cin >> input;
            table.howDelete(input);
            table.deleteElem(input);
            std::cout << "\x1b[1mHash table after delete\x1b[0m" << '\n';
            table.displayHash();
        }
        // Для добавления элемента
        else if (input == "2") {
            std::cout << "You want insert : ";
            cin >> input;
            table.howInsert(input);
            table.insertElem(input);
            std::cout << "\x1b[1mHash table after insert\x1b[0m" << '\n';
            table.displayHash();
        }
        // Для выхода
        else if (input == "3") {
            break;
        }
        // Иначе
        else {
            std::cout << "\nIncorrect input please try again." << '\n';
        }
    }
    std::cout << "\nProgram end !" << '\n';
    return 0;
}
