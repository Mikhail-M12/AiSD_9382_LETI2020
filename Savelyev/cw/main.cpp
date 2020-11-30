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

    // Пояснения для вставки
    void howInsert(T value) {
        // Расчитываем ключ от значения
        int key = hashFunction(value);
        std::cout << "For this we have to find its key using a hash function." << '\n';
        std::cout << "Using adaptive hash function we get the key: " << key << '\n';
        std::cout << "When we find the key we just need to insert the \"" << value << "\" into the " << key << " chain of the table." << '\n';
    }
    // Пояснения для удаления
    void howDelete(T value) {
        // Расчитываем ключ от значения
        int key = hashFunction(value);
        std::cout << "For this we have to find its key using a hash function." << '\n';
        std::cout << "Using adaptive hash function we get the key: " << key << '\n';
        std::cout << "When we find the key we just need to delete the \"" << value << "\" from the " << key << " chain of the table." << '\n';
        std::cout << "To do this in the loop we go through the " << key << " chain in search of a \"" << value << "\" and if we meet it we delete it." << '\n';
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
    cout << "Hash table" << "\n";
    table.displayHash();

    string input;

    cout << "To remove type :  \"!delete\" \n"
            "To insert type : \"!insert\" \n"
            "To exit type : \"!exit\" \n\n";

    while(true) {
        // Считываем значение введенное пользователем
        std::cout << "Your input : ";
        cin >> input;
        // Для удаления элеммента
        if (input == "!delete") {
            std::cout << "You want delete : ";
            cin >> input;
            table.howDelete(input);
            table.deleteElem(input);
            std::cout << "Hash table after delete" << '\n';
            table.displayHash();
        }
        // Для добавления элемента
        else if (input == "!insert") {
            std::cout << "You want insert : ";
            cin >> input;
            table.howInsert(input);
            table.insertElem(input);
            std::cout << "Hash table after insert" << '\n';
            table.displayHash();
        }
        // Для выхода
        else if (input == "!exit") {
            break;
        }
        // Иначе
        else {
            std::cout << "Incorrect input please try again." << '\n';
        }
    }
    std::cout << "Program end !" << '\n';
    return 0;
}
