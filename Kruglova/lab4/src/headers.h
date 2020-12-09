#include <iostream>
#include <vector>

void printDepth(int depth);

template<typename type> void printVector(std::vector<type> *vec)
{
    using namespace std;

    for (int i = 0; i < vec->size(); i++)
        cout << vec->at(i) << ' ';
    cout << endl;
}

template<typename type> void bingoSort(std::vector<type> *vec)
{
    using namespace std;
    cout << "Start sorting." << endl;
    if(vec->size() == 1)
    {
        cout << "There is only one element.\nStop sorting." << endl;
        return;
    }

    // начало первого прохода (здесь мы ищем только nextMaxValue)
    int depth = 0;
    int indOfMax = vec->size() - 1; // просто записали индекс последнего элемента
    // indOfMax хранит индекс, куда записывается максимальный элемент (конец неотсортированной последовательности)
    int nextMaxValue = vec->at(indOfMax); // и инициализировали максимум для следующей итерации

    for (int i = indOfMax; i >= 0; i-- ) // идем от конца списка до начала
    {
        if(vec->at(i) > nextMaxValue) // если нынешнее значение > сохраненного max
        {
            nextMaxValue = vec->at(i); // записываем его в max
        }
    }

    while (indOfMax && vec->at(indOfMax) == nextMaxValue) // пока индекс не 0, и на этом месте и так лежит максимальное значение
    {
        indOfMax -= 1; // уменьшаем индекс на 1 
        // если в конце и так лежат максимальные значения, то нам незачем по ним ходить ещё раз на следующей итерации
    }
    // конец первого прохода 
    // на этот момент у нас есть индекс с которого мы начнем идти и максимальное значение, с которым будем сравнивать др. элементы
    
    { // промежуточная информация
    printDepth(depth);
    cout << " Index of the last unsorted element = " << indOfMax << endl;
    printDepth(depth);
    cout << " Max value for the next iteration = " << nextMaxValue << endl;
    depth += 1;
    }

    // последующие проходы
    while(indOfMax) // пока индекс конца неотсортированного массива != 0
    {
        int maxValue = nextMaxValue; // на прошлой итерации уже было найдено max значение для этой итерации
        nextMaxValue = vec->at(indOfMax); // присвоили значение последнего неотсортированного элемента

        for (int i = indOfMax; i >= 0; i--) // идем от конца неотсортированного массива до его начала
        {
            if(vec->at(i) == maxValue) // если значение элемента == максимальному на этой итерации
            {
                type sw = vec->at(i); // то меняем местами этот элемент с последним неотсортированным
                vec->at(i) = vec->at(indOfMax);
                vec->at(indOfMax) = sw;

                indOfMax -= 1; // и уменьшаем индекс правой границы неотсортированной последовательности
            }
            else if(vec->at(i) > nextMaxValue) // если этот элемент больше максимального значения для следующей итерации
            {
                nextMaxValue = vec->at(i); // то сохраняем его значение
            };
        };
        while (indOfMax && vec->at(indOfMax) == nextMaxValue) // пока индекс не 0, и на его позиции лежит максимальное значение следующей итерации
        {
            indOfMax -= 1; // уменьшаем индекс на 1 
        };

        { // промежуточная информация
            printDepth(depth);
            cout << " Index of the last unsorted element = " << indOfMax << endl;

            printDepth(depth);
            cout << " Max value for the next iteration = " << nextMaxValue << endl;
            
            printDepth(depth);
            cout << " Array after iteration: " << endl;

            printDepth(depth);
            cout << ' ';
            printVector(vec);
            
            depth += 1;
        }

    }
    cout << "End of sorting." << endl;
    return;
}
 
