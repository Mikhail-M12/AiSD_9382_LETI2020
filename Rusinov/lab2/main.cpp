#include "string"
#include "iostream"
#include <fstream>


class List {
    List* next = nullptr;
    List* child = nullptr;
    char value = 0;

public:
    List() = default;
    ~List();
    explicit List(char atom);
    void addNextElement(List* element);
    void addChild(List* element);
    bool isAtom() const;
    void viewList(std::string format = std::string());
    char getAtom() const;
};


class Expression {
    std::string expression;
    // Метод для проверки корректности выражения
    void checkExpression(int* index);
    // Метод для поиска оператора в выражении
    char findOperator(const int* index);
    // Метод для установки смещения в выражении после оператора
    // Возвращает количество аргументов, которое приинмает оператор
    int setOffset(char op, int* index);
public:
    bool correctness = true;
    explicit Expression(std::string string);
    // Метод для создания иерархического списка из выражения
    List* createList(int* index);
    // Переопределенный оператор, ну, просто для красоты
    void operator *();
};


// добавление в список след элемента
void List::addNextElement(List *element) {
    List* current = this;
    while (current->next) current = current->next;
    current->next = element;
}

// добавление в список child
void List::addChild(List *element) {
    child = element;
}

// проверка является ли атомом элемент
bool List::isAtom() const {
    if (value) return true;
    return false;
}

// конструктор
List::List(char atom) : value(atom) {}

List::~List() {
    delete next;
    delete child;
}

// визуализация списка
void List::viewList(std::string format) {
    List* current = this;
    int counter = 1;
    // пока есть элементы, будем их отображать
    while(current) {
        // если элемент не атом, значит у него есть child
        // отобразим child
        if (!current->isAtom()) {
            if (format.length()) current->child->viewList(format + '.' + std::to_string(counter));
            else current->child->viewList(std::to_string(counter));
        } // если атом, то отобразим его значение
        else {
            if (format.length()) std::cout << format + "." + std::to_string(counter) << " - " << current->value << std::endl;
            else std::cout << counter << " - " << current->value << std::endl;
        }
        counter++;
        current = current->next;
    }
}

char List::getAtom() const {
    return value;
}


Expression::Expression(std::string string) : expression(string) {
    // Если длина выражения равна нулю, то оно заведомо неверное
    std::cout << "----------СИНТАКСИЧЕСКИЙ АНАЛИЗАТОР----------" << std::endl;
    if (expression.length() == 0) {
        std::cout << "Длина выражения меньше единицы!" << std::endl;
        correctness = false;
        return;
    }

    // Если длина выражения равна единице, и этот символ в [a..z], то выражение верное и не нуждается
    // в дополнительной проверке
    if ((97 <= expression[0]) && (expression[0] <= 122) && expression.length() == 1) {
        std::cout << "Длина выражения 1 и этот символ [a..z]. Выражение верное" << std::endl;
        return;
    }

    // Если длина выражения больше единицы, и первый символ [a..z], то выражение заведомо неверное
    if ((97 <= expression[0]) && (expression[0] <= 122) && expression.length() > 1) {
        std::cout << "Длина выражения > 1, и первый символ [a..z], выражение неверное" << std::endl;
        correctness = false;
        return;
    }

    // Основная синтаксическая проверка выражения находится здесь
    int index = 0;
    checkExpression(&index);


    // Если выражение было проверено и оно все еще корректное
    // Проверим, что индекс находится на конце выражения
    if (correctness) {
        if (index != expression.length()) {
            correctness = false;
            std::cout << "Не удалось дойти до конца выражения! Есть лишние символы" << std::endl;
        }
    }
}

void Expression::checkExpression(int* index) {
    // Если мы вышли за границы выражения, то оно неверное
    if (*index >= expression.length()) {
        std::cout << "Текущий индекс - " << *index << std::endl;
        std::cout << "Длина выражения - " << expression.length() << ". Выход за границу" << std::endl;
        correctness = false;
        return;
    }

    // Если символ под индексом [a..z], то выражение верное
    if ((97 <= expression[*index]) && (expression[*index] <= 122)) {
        std::cout << "Под индексом - " << *index << " найден символ " << expression[*index] << std::endl;
        *index += 1;
    }
        // Если встречен символ '(', то была встречена операция
    else if (expression[*index] == '(') {
        std::cout << "Под индексом - " << *index << " найдено начало операции" << std::endl;
        *index += 1;
        // Пытаемся найти оператор
        char op = findOperator(index);
        // Если не нашелся оператор, то выражение неверное
        if (!op) {
            std::cout << "В операции не найден оператор!" << std::endl;
            correctness = false;
            return;
        }

        std::cout << "Найден оператор - " << op << std::endl;

        // Устанавливаем смещение индекса и получаем количество операндов для оператора
        int countOperands = setOffset(op, index);
        std::cout << "Количество операндов для оператора - " << countOperands << std::endl;

        // Если вышли за границы выражения после установки смещения,
        // то выражение неверное
        if (*index >= expression.length()) {
            std::cout << "Текущий индекс - " << *index << std::endl;
            std::cout << "Длина выражения - " << expression.length() << ". Выход за границу" << std::endl;
            correctness = false;
            return;
        }

        // Циклически проверяем операнды операции
        for (int i = 0; i < countOperands; ++i){
            // Если встречен пробел, значит все впорядке и можно проверять операнд
            if (expression[*index] == ' ') {
                *index += 1;
                std::cout << "Проверка операнда" << std::endl;
                checkExpression(index);
                if (!correctness) return;
                // если после проверки операнда вышли за границы выражения
                // то выражение некорректно
                if (*index >= expression.length()) {
                    std::cout << "Текущий индекс - " << *index << std::endl;
                    std::cout << "Длина выражения - " << expression.length() << ". Выход за границу" << std::endl;
                    correctness = false;
                    return;
                }
                // пробел не встречен, значит выражение некорректное
            } else {
                std::cout << "После оператора/первого операнда не был встречен пробел" << std::endl;
                correctness = false;
                return;
            }
        }

        // если последний символ операции не закрывающая скобка
        // значит выражение неверное
        if (expression[*index] != ')') {
            std::cout << "Последний символ операции не закрывающая скобка" << std::endl;
            correctness = false;
            return;
        } else {
            *index += 1;
            std::cout << "Операция синтаксически корректная" << std::endl;
        }

    }
        // если был встречен символ не [a..z] и не '(', то выражение неверное
    else {
        std::cout << "Не было встречено символа [a..z] или символа начала операции" << std::endl;
        correctness = false;
        return;
    }
}

char Expression::findOperator(const int* index) {
    // ищем оператор NOT
    int found = expression.find("NOT", *index);
    if (found != std::string::npos && found == *index) return '!';

    // ищем оператор AND
    found = expression.find("AND", *index);
    if (found != std::string::npos && found == *index) return '&';

    // ищем оператор OR
    found = expression.find("OR", *index);
    if (found != std::string::npos && found == *index) return '|';

    // ищем оператор NAND
    found = expression.find("NAND", *index);
    if (found != std::string::npos && found == *index) return '~';

    // операторы не найдены, возвращаем 0
    return 0;
}

int Expression::setOffset(char op, int* index) {
    int countOperands;
    // если оператор NOT или AND
    // то смещение - 3 символа
    // количество аргументов 1, если NOT
    // 2, если AND
    if (op == '!' || op == '&') {
        *index += 3;
        if (op == '!') countOperands = 1;
        else countOperands = 2;
    }
        // если оператор OR, смещение - 2, кол-во аргументов - 2
    else if (op == '|') {
        *index += 2;
        countOperands = 2;
    }
        // в другом случае NAND, смещение - 4, кол-во аргументов - 2
    else {
        *index += 4;
        countOperands = 2;
    }
    return countOperands;
}

List* Expression::createList(int* index) {
    // создание списка уже заведомо верного выражения
    // поэтому можно избежать различных проверок на корректность выражения

    if ((97 <= expression[*index]) && (expression[*index] <= 122)) {
        // если символ [a..z], то создаем из него элемент списка и возвращаем
        List* list = new List(expression[*index]);
        *index += 1;
        return list;
    } else {
        // тогда символ '(' и это операция
        *index += 1;

        // находим оператор
        char op = findOperator(index);
        // создаем элемент списка из оператора
        List* list = new List(op);
        // кол-во аргументов для оператора и смещение
        int countOperands = setOffset(op, index);

        // считывание операндов в цикле
        for (int i = 0; i < countOperands; ++i){
            *index += 1;
            // создаем элемент списка из операнда
            List* operand = createList(index);
            // если оказалось, что первым элементом списка операнда является оператор
            // значит это child
            if (operand->getAtom() == '!' ||
                operand->getAtom() == '~' ||
                operand->getAtom() == '&' ||
                operand->getAtom() == '|') {
                // создаем новый элемент списка
                List* nextEl = new List();
                // добавляем к нему child
                nextEl->addChild(operand);
                // к списку с оператором добавляем элемент с child
                list->addNextElement(nextEl);
            } // иначе это просто следующий элемент
            else list->addNextElement(operand);
        }
        *index += 1;
        return list;
    }
}

void Expression::operator*() {
    // оператор вывода результата
    if (!correctness) {
        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "Дорогой друг, вероятно, в вашем выражении ошибка!";
    } else {
        int index = 0;
        List* list = createList(&index);
        std::cout << "------------ИЕРАРХИЧЕСКИЙ СПИСОК-------------" << std::endl;
        list->viewList();
        std::cout << "---------------------------------------------" << std::endl;
        delete list;
    }
}


int main() {
    std::string string;

    std::ifstream in("../file.txt");
    if (!in.is_open()) {
        std::cout << "Не удалось открыть файл!" << std::endl;
        in.close();
        return 0;
    }

    std::getline(in, string, '\n');
    in.close();

    *Expression(string);
    return 0;
}
