#include "headers.h"

int main()
{
    vector<BTree<char>*> queue;   // очередь указателей на деревья
    vector<char> for_print; // очередь, куда будут записываться элементы в порядке их вывода
    int depth = 1;
    BTree<char> *a;

    setlocale(LC_ALL, "rus"); // подключен русский язык

    queue.reserve(8);      // изменили емкость векторов, чтобы уменьшить время работы программы
    for_print.reserve(15); // будет меньше вызовов методов, перевыделяющих память (для любых 4-уровневых деревьев (и меньше) перевыделения вообще не будет)

    cout << "Enter Binary Tree with \'/\': " << endl;
    a = readBT<char>(); // явно указываем тип, т.к. нет никаких аргументов, по которым компилятор мог бы вычислить тип сам
    cout << endl;

    cout << "Entered Binary Tree:\n";
    writeBT(a); // а здесь компилятор уже сам видит тип
    cout << "\n\n";

    if(!is_nullptr(a)) // заносим в очередь указатель на основное дерево и nullptr, чтобы отделить первый уровень
    {
        queue.push_back(a);
        queue.push_back(nullptr);
    }

    cout << "   START running main function" << endl;
    write_tree_in_vector(&queue, &for_print, 1);
    cout << "   STOP running main function\n" << endl;


    cout << "All elements of binary tree by layers: " << endl;
    print_tree_by_layers(&for_print);

    for_print.clear();
    destroy (a);

    return 0;
}


