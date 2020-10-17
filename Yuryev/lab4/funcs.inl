template <typename T>
void print_list(std::list<T> entered_list) // выведет все элементы list через пробел
{
    using namespace std;
    cout << "{ ";
    for (auto pos_begin = entered_list.begin(); pos_begin != entered_list.end(); ++pos_begin)
        cout << *pos_begin << " ";
    cout << '}';
    return;
}

template <typename T> 
std::list<T> strandSort(std::list<T> lst) // нитевидная сортировка
{
    using namespace std;

    if (lst.size() == 0) // если передан пустой массив
    {
        cerr << "Array is empty." << endl;
        return lst;
    }
    else if (lst.size() == 1) // если передан массив из одного элемента
    {
        cerr << "Only one element in array." << endl;
        return lst;
    }

    cout << "START sorting" << endl;

    list<T> result_list;    // для готового результата
    list<T> sub_list;       // для вычислений
    int depth_counter = 1;  // для вывода отладочной информации

    while (!lst.empty()) 
    {
        { // отладочная информация
        print_empty_depth(depth_counter);
        cout << "NEW ITERATION" << endl;

        print_empty_depth(depth_counter);
        cout << "Start list = ";
        print_list(lst);
        cout << endl;

        print_empty_depth(depth_counter);
        cout << "Move first: \'" << *(lst.begin()) << "\' in sub_list." << endl;
        }

        sub_list.push_back(lst.front());// выписываем первый элемент из начального списка
        lst.pop_front();                // удаляем первый элемент из начального списка
        
        {  // отладочная информация
            print_empty_depth(depth_counter);
            cout << "Now sub_list = ";
            print_list(sub_list);
            cout << endl;
            depth_counter += 1;
        }

        for (typename list<T>::iterator it = lst.begin(); it != lst.end(); ) // итератор будет увеличиваться внутри
        {
            if (sub_list.back() <= *it)  // если последний добавленный элемент <= элемента на котором находится итератор
            {
                { // отладочная информация
                print_empty_depth(depth_counter);
                cout << "\'" << *it << "\' >= \'" << sub_list.back() << "\' so move it in sub_list." << endl;
                }

                sub_list.push_back(*it); // то добавляем его в конец
                it = lst.erase(it);      // и удаляем этот элемент из начального массива

                {  // отладочная информация
                print_empty_depth(depth_counter);
                cout << "Now sub_list = ";
                print_list(sub_list);
                cout << endl;
                depth_counter += 1;
                }
            } 
            else
                it++;
        }
        result_list.merge(sub_list); // смержили sub_list с result_list и теперь sub_list пуст (merge объдиняет 2 сортированных списка в один)

        { // отладочная информация
        print_empty_depth(depth_counter);
        cout << "END of iteration." << endl;

        print_empty_depth(depth_counter);
        cout << "Merge sub_list with result_lisp." << endl;

        print_empty_depth(depth_counter);
        cout << "Now result_list = ";
        print_list(result_list);
        cout << endl;
        depth_counter += 1;
        }
    }

    cout << "STOP sorting\n\n" << endl;
    return result_list;
}

void print_empty_depth(int depth) // выведет "  " указанное кол-во раз
{
    for (int j = 0; j < depth; j++)
        std::cout << "   ";
    return;
}