#include "Weak_heap.h"



int main() {
    int count;
    
    ifstream file("test.txt");//открываем файл для чтения
    file>>count;
    
    int count_of_bit=count/2;//вычисляем количество элементов, в которых введён не фиктивный дополнительный бит
    couple* array=new couple[count];

    for (int i=0;i<count;i++){
        file>>array[i].data>>array[i].bit;//читаем данные из файла
    }

    file.close();
    
    WeakHeap heap1(count);
    heap1.push(array[0]);
    heap1.push(array[1]);
    for (int i=1;i<count_of_bit;i++){//записываем элементы в кучу в порядке, удобном для вывода на экран 
        heap1.push(array[2*i+array[i].bit]);
        heap1.push(array[2*i+1-array[i].bit]);

    }

    heap1.print_heap();//выводим нашу слабую кучу на экран

  
    delete [] array;
    return 0;
}