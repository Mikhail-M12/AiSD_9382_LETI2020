
void print_empty_depth(int depth) // просто печатает пробелы в количестве глубины
{
    for (int j = 0; j < depth; j++)
        cout << "   ";
    return;
}

template<typename T>
void write_tree_in_vector(vector<BTree<T>*> *queue, vector<T> *for_print, int depth) // используя очередь, записывает элементы в нужном порядке в вектор for_print
{
    if (queue->empty()) // если очередь подана пустой
    {
        print_empty_depth(depth);
        cout << "Queue is empty. Stop working..." << endl;

        return; // то выполнение останавливается
    }

    if (is_nullptr(queue->at(0))) // nullptr в очереди = отделить уровни
    {
        if(queue->size() == 1) // чтобы не было бесконечного цикла в конце
        {
            print_empty_depth(depth);
            cout << "It is the end of queue." << endl;

            queue->clear();

            print_empty_depth(depth);
            cout << "End of function." << endl;

            return;
        }
        
        print_empty_depth(depth);
        cout << "Adding \'\\n\' in vector" << endl;

        for_print->push_back('\n'); // записали перенос строки в вектор для вывода

        queue->erase(queue->begin()); // удалили nullptr из начала
        queue->push_back(nullptr); // записали в конец nullptr, чтобы отделить следующий уровень

        print_empty_depth(depth);
        cout << "Going to the next layer." << endl;

        write_tree_in_vector(queue, for_print, depth + 1); // вызвали эту же функцию
        return;
    } 

    if(!is_nullptr((queue->at(0))->get_left())) // если есть левое поддерево
    {
        print_empty_depth(depth);
        cout << "Left isn`t empty." << endl;

        queue->push_back((queue->at(0))->get_left()); // добавляем в конец очереди указатель на него
    }
    else
    {
        print_empty_depth(depth);
        cout << "Left is empty." << endl;
    }
    

    if(!is_nullptr((queue->at(0))->get_right())) // если есть правое поддерево
    {
        print_empty_depth(depth);
        cout << "Right isn`t empty." << endl;

        queue->push_back((queue->at(0))->get_right());// добавляем в конец очереди указатель на него
    }
    else
    {
        print_empty_depth(depth);
        cout << "Right is empty." << endl;
    }
    

    print_empty_depth(depth);
    cout << "Adding \'" << (queue->at(0))->get_BTroot() << "\' in vector" << endl;

    for_print->push_back((queue->at(0))->get_BTroot()); // записываем корень рассматриваемого дерева

    queue->erase(queue->begin()); // удаляем из очереди первый указатель

    write_tree_in_vector(queue, for_print , depth + 1); // вызываем эту же функцию

    print_empty_depth(depth);
    cout << "End of function." << endl;

    return;
}

template<typename T>
void print_tree_by_layers(vector<T> *for_print) // выписывает дерево по слоям из вектора for_print
{
    if (!for_print->size())
    {
        cout << endl;
        cout << "(binary tree is empty)" << endl;
        return;
    }

    unsigned short int depth = 2;

    cout << "[]"; // чтобы главный корень тоже выводился с отступом

    for (int i = 0; i < for_print->size(); i++)
    {       
        cout << " " << for_print->at(i); // выводим элемент из вектора

        if (for_print->at(i) == '\n') // если перенос строки - печатаем и глубину уровня
        {
            for (int j = 0; j < depth; j++)
                cout << "[]";
            depth += 1;
        }
    }
    cout << endl;
}

