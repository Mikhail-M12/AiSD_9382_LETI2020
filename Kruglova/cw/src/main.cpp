#include "headers.h"

unsigned int count = 187; // ( = 2*кол-во символов алфавита - 1) нужно для нумерования элементов дерева (94 печатных символа первой половины ascii)
std::vector<Node*> leafs; // здесь хранятся все адреса на узлы-листья + NYT (на нулевом месте)
std::vector<Node*> internalNodes; // здесь хранятся все адреса на внутренние узлы (корень на нулевом месте)

void printHufTree(Node* root) // визуализирует структуру дерева Хаффмана
{
    using namespace std;

    vector<Node*> vec;
    splitHafTree(root, &vec, 1); // запишет в вектор все узлы дерева по уровням (по порядку) ПОМНИ, ЧТО УРОВНИ РАЗДЕЛЕНЫ nullptr

    cout << '/' << std::string( 60, '*' ) << '/' << endl;

    auto iter = vec.begin();
    while(iter != vec.end())
    {
        if((*iter) == nullptr) // если встретили разделитель уровня
        {
            iter++;
            continue;
        }

        cout << "/* № " << (*iter)->m_number << ":  Par = [";

        if ( ((*iter)->m_parent) != nullptr)
        {
            cout << (*iter)->m_parent->m_number;
            if( ((*iter)->m_parent->m_left) == (*iter) )
                cout << 'L';
            else
                cout << 'R';
        }
        else
        {
            cout << "Null";
        }
        cout << "]\tW = " << (*iter)->m_weight;

        if((*iter)->m_isLeaf) // если это лист
        {
            cout << "\tType = Leaf\tSymbol = " << (*iter)->m_symbol << endl;
        }
        else if((*iter)->m_isNYT) // если это NYT
        {
            cout << "\tType = NYT" << endl;
        }
        else // если это внутренний узел
        {
            cout << "\tType = Internal" << endl;
        }
        
        iter ++;
    }
    cout << '/' << std::string( 60, '*' ) << '/' << '\n' << endl;
}

void pushFirst(Node* a)
{
    leafs.push_back(a);
};

Node* findSymbol(char symbol, std::vector<Node*> *leafs) // ищет в переданном векторе из уникальных листьев тот, что содержит нужный символ
{
    if (symbol == '\0') // \0 - обозначение для внутренних узлов, поэтому нет уникального элемента с таким символом
        return nullptr;

    int lastInd = leafs->size(); 
    for (int i = 1; i < lastInd; i++) // идем по списку листьев и проверяем значения символа внутри
    {
        if(((leafs->at(i))->m_symbol) == symbol) // если переданный символ встречался раньше
        {
            return leafs->at(i);
        }
    }
    return leafs->at(0); // если же это новый символ, то вернем NYT
};

void swapNodes(Node *a, Node *b) // меняет 2 узла/листа местами с помощью замены их собвственных указателей и указателей их родителей
{
    if (a->m_parent == nullptr || b->m_parent == nullptr) // если одно из значений - корень
    {
        std::cout << "You can`t swap root." << std::endl;
        return;
    }

    if (a == b)
    {
        std::cout << "You can`t swap one element with itself." << std::endl;
        return;
    }


    if ((a->m_parent) == (b->m_parent)) // если у элементов один родитель
    {
        Node* parent = a->m_parent;
        if(a->m_parent->m_left == a) // если а - левый ребенок, а b - правый
        {
            a->m_parent->m_left = b;
            a->m_parent->m_right = a;
        }
        else // если же а - правый ребенок, а b - левый
        {
            a->m_parent->m_left = a;
            a->m_parent->m_right = b;
        }
        // менять указатели на родителей переданным элементам не нужно
    }
    else // если у элементов разные родители
    {
        // меняем указатели на детей в их родителях

        Node *tempVal; // временное место хранения значения

        tempVal = a->m_parent;
        if( (tempVal)->m_right == a) // если a - правый ребенок, то меняем указатель родителя на правого ребенка
            (tempVal)->m_right = b;
        else // иначе меняем указатель на левого ребенка
            (tempVal)->m_left = b;


        tempVal = b->m_parent; // ошибка!!! У родителя b сейчас оба ребенка = b ПОПРАВЬ!
        if( (tempVal)->m_right == b) // аналогично поступаем с родителем второго узла
            (tempVal)->m_right = a;
        else
            (tempVal)->m_left = a;


        // меняем указатели на родителей в детях

        b->m_parent = a->m_parent;
        a->m_parent = tempVal;
    };

    if(b->m_isLeaf && a->m_isLeaf) // если это 2 листа, то можно спокойно поменять у них номера на друг друга
    {
        unsigned int k = a->m_number;
        a->m_number = b->m_number;
        b->m_number = k;
    }
};

Node* findBlockLeader(std::vector<Node*> *vec, unsigned int weight) // находит лидера блока (лидер блока: тот же вес, тот же тип (лист/вн.узел), максимальный номер)
{ // после вызова сделай проверку на то, не является ли тот же элемент и лидером (для лист-лист) и на nullptr (надо ли вообще делать swap)
    Node* p = nullptr;
    unsigned int number = 0;

    for (int i = 0; i < vec->size(); i++) // проходимся по всем элементам
    {
        if((vec->at(i))->m_weight == weight) // если вес элемента == нужному весу
        {
            if(p == nullptr) // первый подходящий элемент
            {
                p = vec->at(i);
                number = p->m_number;
            }
            else if( (vec->at(i))->m_number > number) // если у элемента номер больше
            {
                p = vec->at(i);
                number = p->m_number;
            }
        }
    }
    return p;
};

void encodeSymbol(std::string* emptyStr, Node* p) // записывает в переданную строку путь до листа/NYT
{
    Node* prevNode = p; // от этого узла будем подниматься наверх

    while(prevNode->m_parent != nullptr) // пока не находимся в корне
    {
        if(prevNode->m_parent->m_left == prevNode) // если это левый ребенок
        {
            emptyStr->insert(0,"0"); // вставляем в начало 0
            prevNode = prevNode->m_parent;
        }
        else if(prevNode->m_parent->m_right == prevNode) // если это правый ребенок
        {
            emptyStr->insert(0,"1"); // вставляем в начало 1
            prevNode = prevNode->m_parent;
        }
        else
        {
            std::cerr << "There is strange error in encodeSymbol()." << std::endl;
            return;
            // если это вывелось, значит где-то ошибка в создании дерева (указатель на ребенка пуст)
        }
        
    }
};

void splitHafTree(Node* root, std::vector<Node*> *vec, short int level) // запишет все листы и узлы в вектор по порядку КПЛ
{
    if (level == 1) // если это самый первый проход
    {
        vec->push_back(root); // то просто создаем первый блок
        vec->push_back(nullptr); // nullptr служат для разделения блоков (уровней дерева)
    }
    else
    {
        short int countOfNulls = 0; // для подсчета уровней
        auto k = vec->begin();
        while (k != vec->end()) // проходимся по всему вектору
        {
            if ((*k) == nullptr) // если встретили разделитель
            {
                countOfNulls += 1;
                if (countOfNulls == level) // если количество разделителей = уровню функции
                {
                    vec->insert(k, root); // то записываем значение в конец нужного блока
                    break; // и останавливаем итерацию
                }
            }
            k++;
        }
        if(countOfNulls < level) // если в векторе меньше блоков, чем уровень у функции, то добавим еще один блок
        {
            vec->push_back(root); 
            vec->push_back(nullptr);
        }
    }

    if ((root->m_left) != nullptr) // если узел внутренний, то делаем рекурсивный вызов функции для детей узла
    {
        splitHafTree(root->m_right, vec, level + 1);
        splitHafTree(root->m_left, vec, level + 1);
    }
    return;
};

void remakeNumeration(Node* p) // передаем этой функции указатель на корень и она расставит номера по КПЛ
{
    std::vector<Node*> vec;
    splitHafTree(p, &vec, 1); // теперь в vec упорядоченно лежат все узлы и листья дерева
    unsigned int count = 187;

    auto iter = vec.begin();
    while(iter != vec.end()) // проходимся по всем узлам и выставляем там соответствующие номера
    {
        if (*iter != nullptr) // пропускаем все разделители
        {
            (*iter)->m_number = count;
            count -= 1;
        }
        iter++;
    }

};

void deleteAllNodes()
{
    std::vector<Node*> *allLeafs = &leafs;
    std::vector<Node*> *allIntNodes = &internalNodes;

    auto l = allLeafs->begin();
    auto iN = allIntNodes->begin();

    while(l != allLeafs->end())
    {
        delete *l;
        l++;
    }
    while(iN != allIntNodes->end())
    {
        delete *iN;
        iN++;
    }
};

void fillSymbolCode(char symbol, std::string *str) // записывает ascii-номер символа в строку (длина = 8)
{
    int c = (int)symbol;
    str->push_back('0');
    for(int j = 64; j > 1; j = j/2)
    {
        if(c >= j)
        {
            c -= j;
            str->push_back('1');
        }
        else
        {
            str->push_back('0');
        }
    }
    if(c == 1)
        str->push_back('1');
    else
        str->push_back('0');
};

Node* slideAndIncrement(Node* p)
{
    if(!(p->m_isLeaf)) // если это внутренний узел
    {
        Node* previousP = p->m_parent;
        
        // сдвигаем p в дереве выше, чем узлы-листья с весом w+1
        Node* a = findBlockLeader(&leafs, (p->m_weight) + 1);
        if(a != nullptr) // если такие листья есть
        {
            swapNodes(a, p); // т.к. здесь swap листа с внутренним узлом, то swap не поменяет автоматически внутреннюю нумерацию
            Node* p = internalNodes.at(0); // на первом месте в списке внутренних узлов стоит корень
            remakeNumeration(p); // пересоздаем нумерацию искуственно, начиная с корня
        }
        p->m_weight += 1;
        return previousP;
    }
    else // если же это лист
    {
        // сдвигаем p в дереве выше, чем внутренние узлы с весом w
        Node* b = findBlockLeader(&internalNodes, p->m_weight);
        if (b != nullptr)
        {
            swapNodes(p, b);
            remakeNumeration(internalNodes.at(0));
        }
        p->m_weight += 1;
        return p->m_parent;
    }
};



void writeTreeForTask(Node* root, std::string *tree) // в переданную строку записывает дерево в настоящий момент в виде: 3/2/1w/1o...
{
    std::vector<Node*> vec;
    splitHafTree(root, &vec, 1); // теперь в vec упорядоченно лежат все узлы и листья дерева (они лежат по обходу в ширину СПРАВА-НАЛЕВО)

    auto iter = vec.begin();
    while(iter != vec.end()) // проходимся по всем узлам
    {
        if ((*iter) != nullptr) // пропускаем все разделители уровней
        {
            tree->append(std::to_string((*iter)->m_weight)); // записываем вес узла
            if((*iter)->m_isNYT)
                tree->push_back('*');
            else if((*iter)->m_isLeaf)                   // и если этот узел - лист
            {
                tree->push_back((*iter)->m_symbol); // то записываем и его символ
                tree->push_back('/');                   // символ разделения узлов
            }
            else
                tree->push_back('/'); 
        }
        iter++;
    }
}



std::string vitterCoder(char symbol, std::string *step) // step - строка, которая показывает результат шага (нужна для проверки заданий)
{
    std::string code;
    Node* nodeForIncrease = nullptr;
    Node* p = findSymbol(symbol, &leafs); // смотрим не встречался ли нам такой символ раньше
    
    { // записали в начало строки шага обрабатываемый символ
    step->push_back(symbol); 
    }

    if (p->m_isNYT) // если этот символ встретился впервые
    {
        // Кодирование символа:
        encodeSymbol(&code, p); // записывает в строку путь до NYT
        
        { // добавляет в строку шага часть с |...|
            step->push_back('|');
            step->append(code);
            step->push_back(symbol);
            step->push_back('|');
        }


        { // кавычки здесь, чтобы не держать в памяти symbolCode (переменная будет уничтожена при выходе из них)
        std::string symbolCode = "";
        fillSymbolCode(symbol, &symbolCode);    // получаем ascii-код символа
        code.append(symbolCode);                // добавляем его в код
        }

        // Перестройка дерева:
        p->m_left = new Node(p); // создаем новый NYT
        p->m_right = new Node(p, symbol); // и создаем новый лист
        p->m_isNYT = false; // в узле, где мы находимся, указываем, что он больше не NYT
        nodeForIncrease = p->m_right; // указываем, что лист был только что создан, и его вес нужно увеличить

        leafs.push_back(p->m_right); // записываем новосозданный лист в конец вектора листьев
        leafs.at(0) = p->m_left; // меняем указатель на новый NYT в векторе

        internalNodes.push_back(p); // так как старый NYT стал внутренним узлом сохраним его в соответствующий вектор
    }
    else // если же символ встречался ранее
    {   
        // Кодирование символа:

        encodeSymbol(&code, p); // записывает в строку путь до листа (что и является кодом символа)
        
        { // добавляет в строку шага часть с |...|
            step->push_back('|');
            step->append(code);
            step->push_back('|');
        }

        // Перестройка дерева:

        // swap лист с тем же элементов с листом-лидером блока (блок - один тип, один вес)
        Node* k = findBlockLeader(&leafs, p->m_weight);
        if (k != p) // на nullptr проверка здесь не нужна т.к. гарантированно есть хотя бы 1 элемент такого веса (сам p)
            swapNodes(p, k);
        if ( p->m_parent->m_left->m_isNYT ) // если p после перемещения все равно брат NYT (это нужно во избежания пары проблем с slideAndIncrement() )
        {
            nodeForIncrease = p; // лист будет увеличен в конце отдельно 
            p = p->m_parent;    // а цикличное увеличение начнется с его родителя
        }
    }

    while (p != nullptr) // увеличиваем вес и делаем необходимые сдвиги в дереве от p до корня
    {
        p = slideAndIncrement(p);
    };

    if (nodeForIncrease != nullptr) // делаем еще одно увеличение и сдвиг в дереве, если это необходимо
    {
        slideAndIncrement(nodeForIncrease);
    };

    writeTreeForTask(::internalNodes.at(0), step); // записываем в строку-шаг полученное в результате кодирования дерево (СПРАВА-НАЛЕВО)

    return code; // возвращаем строку по значению
};



char identifySymbol(std::string ascii) // принимает на вход строку с ascii-кодом символа и возвращает опознанный символ
{
    int num = 0;
    char symbol = 0;
    for (int i = 0; i < ascii.size(); i++) // идем по всем символам строки 
    {
        if (ascii[i] == '0')
        {
            continue;
        }
        else if(ascii[i] == '1')
        {
            num = 1;
            for (int k = 7 - i; k > 0; k--)
            {
                num *= 2;
            }
            symbol += num;
        }
    }
    return symbol;
};

Node* findNextLeaf(std::string remainCode, int *count, Node* root) // проходит по дереву, ориентируясь по значению символов строки, и возвращает узел, где он остановился
{
    Node* currentNode = root;
    int k = 0;
    
    while( !(currentNode->m_isLeaf) && !(currentNode->m_isNYT))
    {
        if(remainCode[k] == '0')
        {
            currentNode = currentNode->m_left;
        }
        else if(remainCode[k] == '1')
        {
            currentNode = currentNode->m_right;
        }
        k += 1;
    }
    *count = k; // сообщает наружу, сколько символов занимает путь до листа
    
    return currentNode;
};

std::string vitterDecoder(std::string *code) // декодирует код в сообщение
{
    setlocale(LC_ALL, "rus");
    Node* root = new Node;          // использован конструктор для создания первого NYT
    std::string startCode = *code;  // переданный код, который будем раскодировывать
    std::string message = "";       // сюда будут добавляться друг за другом раскодированные символы
    std::string temporaryStr = "";  // строка для временного хранения значений
    int count = 0;
    char symbol;

    ::leafs.push_back(root);   // сохраняем корень в список листьев, т.к. он пока NYT

    // Первыми всегда идут 8 цифр кода символа
    temporaryStr.assign(startCode, 0, 8);   // сохраняем 8 цифр кода во временной переменной
    startCode.erase(0,8);                   // удаляем код символа из общей строки кода
    symbol = identifySymbol(temporaryStr);  // распознаем этот символ
    message.push_back(symbol);              // записываем этот символ в конец декодированного сообщения

    // начальная перестройка дерева
    root->m_left = new Node(root);          // создаем новый NYT
    root->m_right = new Node(root, symbol); // и создаем новый лист
    root->m_isNYT = false;                  // в узле, где мы находимся(бывший NYT), указываем, что он больше не NYT

    ::leafs.at(0) = root->m_left;           // обновили NYT в списке
    ::leafs.push_back(root->m_right);       // записали новый лист в список листьев
    ::internalNodes.push_back(root);        // записали корень в список внутренних узлов (он занял 0 позицию и с нее не уйдет)

    root->m_weight = 1;                     // это простейший случай, поэтому прописали веса вручную
    root->m_right->m_weight = 1;

    while(startCode != "")      // пока не проанализируем строку до конца
    {
        Node* nextLeaf = findNextLeaf(startCode, &count, root); // находит к какому листу ведет последовательность (в count записывается количество символов, кодирующих путь до листа)
        Node* nodeToIncrease = nullptr;                         // лист для увеличения (нужен для отделения узлов, вес которых нужно увеличивать в самом конце)

        std::string temp;
        temp.assign(startCode, 0 , count); // код, который ведет до листа

        if(nextLeaf->m_isNYT) // если последовательность привела к NYT -> встретился новый символ
        {
            startCode.erase(0, count);              // удалили путь до NYT из общей строки кода
            temporaryStr.assign(startCode, 0, 8);   // сохранили во временное хранилище 8 символов (код нововстреченного символа)
            startCode.erase(0,8);                   // удалили код нововстреченного символа из общей строки кода
            symbol = identifySymbol(temporaryStr);  // идентифицируем символ по его коду
            message.push_back(symbol);              // записываем идентифицированный символ в строку раскодированного сообщения

            // перестройка дерева
            nextLeaf->m_left = new Node(nextLeaf);          // создаем новый NYT
            nextLeaf->m_right = new Node(nextLeaf, symbol); // и создаем новый лист
            nextLeaf->m_isNYT = false;                      // в узле, где мы находимся, указываем, что он больше не NYT

            ::leafs.at(0) = nextLeaf->m_left;       // обновили NYT
            ::leafs.push_back(nextLeaf->m_right);   // указали новосозданный лист в списке листьев
            ::internalNodes.push_back(nextLeaf);    // старый NYT записали в список внутренних узлов

            nodeToIncrease = nextLeaf->m_right;
        }
        else // если же последовательность привела к конкретному листу -> символ из этого листа встречается повторно
        {
            // раскодирование символа
            startCode.erase(0, count);      // удалили путь до листа из общей строки кода
            symbol = nextLeaf->m_symbol;    // узнали, что за символ был встречени из значения листа
            message.push_back(symbol);      // записали этот символ в конец раскодироваемого сообщения

            Node* k = findBlockLeader(&::leafs, nextLeaf->m_weight);    // находим лидера блока
            if (k != nextLeaf)  // если лидер блока != листу, содержащему анализируемый символ
            {
                swapNodes(nextLeaf, k); // то меняем местами эти 2 листа (swapNodes уже имеет внутри изменение нумерации дерева для лист swap лист)
            }
            
            if ( nextLeaf->m_parent->m_left->m_isNYT ) // если p после перемещения все равно брат NYT (это нужно во избежания пары проблем с slideAndIncrement() )
            {
                nodeToIncrease = nextLeaf;          // лист будет увеличен в конце отдельно 
                nextLeaf = nextLeaf->m_parent;      // а цикличное увеличение начнется с его родителя
            }
        }

        while(nextLeaf != nullptr) // цикличное увеличение веса узлов снизу вверх
        {
            nextLeaf = slideAndIncrement(nextLeaf);
        };

        if(nodeToIncrease != nullptr) // увеличение веса узла, специально вынесенного последним на увеличение
        {
            slideAndIncrement(nodeToIncrease);
        };
    }

    return message;
};




int readingFile(std::string fileName, std::vector<std::string> *arrayOfLines) // считывает из файла массив строк
{
    using namespace std;
    char ch;
    int count;
    std::string a;
    ifstream file(fileName, ios::in | ios::binary); // окрываем файл для чтения
    if (!file)
    {
        cout << "Проблема с открытием файла.\nЗавершение программы..." << endl;
        return -1;
    }

    file >> count; // считали количество вариантов заданий
    if(file.fail()) // если количество вариантов заданий не было введено
    {
        cout << "Не указано количество вариантов заданий.\nЗавершение программы..." << endl;
        return -2;
    }
    getline(file, a, '\n'); // считываем остаток строки, где находилось число вариантов, для перехода к данным

    for(int k = 0; k < count; k++) // циклично считываем строки из файла (если указано большее количество вариантов, чем их есть на деле, то эта разница будет заполнена копиями последней строки)
    {
        getline(file, a, '\n'); // пустые строки будут считаться отдельными строками
        arrayOfLines->push_back(a);
        //cout << "string nom " << k + 1 << ": " << a << endl; // просто для проверки
    }

    file.close();     // закрываем файл
    return 0;
}

int writingTasks(std::string fileName, std::string *str, std::vector<std::string> *arrayOfLines) // создает файл с заданием
{
    using namespace std;
    ofstream out(fileName); // открываем файл для записи
    if (!out) // если не удалось его открыть
    {
        cout << "Не получается открыть файл для создания заданий.\n";
        return -1;
    }
    
    out << *str << "\n"; // в str содержится текст задания
    for(int i = 0; i < 50; i++) // отделяем задание от вариантов заданий с помощью "---------"
        out << '-';
    out << "\n\n";

    for (int i = 0; i < arrayOfLines->size(); i++)
    {
        out << "Var " << i + 1 << ": " << arrayOfLines->at(i) << "\n";
    }

    out.close();
    return 0;
}

int writingCoderAnswers(std::string fileName, std::string *str, std::vector<std::string> *arrayOfLines)
{
    using namespace std;
    ofstream out(fileName); // открываем файл для записи
    if (!out) // если не удалось его открыть
    {
        cout << "Не получается открыть файл для создания ответов.\n";
        return -1;
    }
    string newLine = "", step = "";
    int counter = 0;

    out << *str << "\n";        // в str содержится уточнение, к какому заданию эти ответы
    for(int i = 0; i < 50; i++) // отделяем уточнение от непосредственно решений с помощью "---------"
        out << '-';
    out << "\n\n\n";
    cout << "\n\n" << endl;

    auto iter = arrayOfLines->begin();
    while(iter != arrayOfLines->end()) // проходимся по всем введенным строкам
    {
        counter += 1;
        out << "\t\tVar " << counter << ":\n\n";
        cout << "\tРешаем " << counter << " вар.\n" << endl;
        cout << "  Текст: " << (*iter) << "\n" << endl;

        ::leafs.clear();
        ::internalNodes.clear();
        Node *root = new Node;  // был вызван конструктор для корневого NYT
        pushFirst(root);        // вставили начальный NYT в список листьев

        for (int i = 0; i < (*iter).size(); i++) // для каждого символа строки вызывается кодер
        {
            string a = vitterCoder((*iter).at(i), &step);   // в a - код символа, в step - строка-шаг, которую должен изобразить ученик
            newLine.append(a);                              // добавили его в общий код строки
            out << "Шаг " << i + 1 << ": " << step << "\n";
            cout << "Шаг " << i + 1 << " = " << step << "\n" << endl;
            step = "";
        }
        out << "\n\n\n";
        cout << "\tРешение варианта завершено.\n\n" << endl;
        deleteAllNodes();
        iter++;
    }
    out.close();
    return 0;
}


int main()
{
    using namespace std;
    setlocale(LC_ALL, "rus");

    string inputFile = "./text.txt";
    string tasks1 = "./tasks1.txt", answers1 = "./answers1.txt";    // задания и ответы по кодирования
    string task1Statement = "", task2Statement = "";                // здесь будут храниться формулировки заданий
    string ans1Statement = "" , ans2Statement = "";                 // здесь будут храниться
    std::vector<std::string> arrayOfLines, arrayOfCodes;            // здесь будут храниться переданные строки, и их полученные коды
    { // формулировка заданий и уточнения к файлу ответов
        task1Statement = "\t\tЗадание на динамическое кодирование Хаффмена\n\nДля заданного текста (последовательности символов) схематически изобразить процесс работы кодировщика по методу динамического кодирования по Хаффмену (алгоритм Виттера).\nДля этого на каждом шагу указать очередной обработанный символ входной последовательности и его код, а также полученное после обработки этого символа кодовое дерево.\n\n\tПожалуйста, обратите внимание на следущие пункты: \n1) В задании проверяется алгоритм Виттера, а не алгоритм ФГК. Методы построения деревьев в этих алгоритмах несколько отличаются.\n2) При указании ответов необходимо приложить кодировку символов, которой вы пользовались.\n3) В указанных решениях структура дерева должна описываться обходом в ширину СПРАВА-НАЛЕВО.\n4) Узел NYT в решениях должен обозначаться при помощи \"0*\".";
        ans1Statement = "\t\tОтветы к заданиям на динамическое кодирование Хаффмена\n\n\tПожалуйста, обратите внимание на следущие пункты: \n1) В задании проверяется алгоритм Виттера, а не алгоритм ФГК. Методы построения деревьев в этих алгоритмах несколько отличаются.\n2) Ответы не привязаны к конкретным кодировкам, а даны в общем виде для удобства проверяющего.\n3) В указанных решениях структура дерева описывается обходом в ширину СПРАВА-НАЛЕВО.\n4) Узел NYT в решениях обозначается при помощи \"0*\".";
    }

    cout << "Начинается считывание строк..." << endl;
    if(readingFile(inputFile, &arrayOfLines) < 0) // считали строки из файла в вектор (если что-то не так пошло с файлом - закругляемся)
        return 0;
    cout << "Считывание строк закончилось успешно." << endl;

    writingTasks(tasks1, &task1Statement, &arrayOfLines); // создали файл с заданиями на кодирование
    cout << "Создание файла с заданиями." << endl;

    cout << "Начинается запись решений к заданиям." << endl;
    writingCoderAnswers(answers1, &ans1Statement, &arrayOfLines); //  ,кодировщик вызывается изнутри этой функции
    cout << "Создание файла с решениями успешно." << endl;

    return 0;
}

