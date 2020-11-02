#ifndef WEAK_HEAP_H
#define WEAK_HEAP_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
using namespace std;

//вычисляет логарифм от b по основанию a
double log(int a, int b)
{
    return log(b) / log(a);
}
//структура для записи элементов массива типа число-бит
typedef struct couple{
    int data;
    int bit;

} couple;

//класс слабой кучи
class WeakHeap {
    couple *heap;
    int frnt=0, rear=0;
    int queue_size;
  public :
    
    WeakHeap (int) ;
    ~WeakHeap();
    void push (couple f) ;
    void pop();
    void print_heap();

} ;



//Конструктор
WeakHeap::WeakHeap(int size) {
    queue_size=size;
    heap = new couple[queue_size];
}
WeakHeap::~WeakHeap(){
    delete[] heap;
}
void WeakHeap::print_heap(){
    cout<<heap[0].data;
    cout<<"\n";
    int depth=(int)log(2, queue_size);//вычисляем глубину дерева
    int k=0;
    for (int i=0;i<depth;i++){

        for (int j=0;j<pow(2,i);j++){
            
            cout<<heap[k+1].data<<"  ";
            k++;
        }
        cout<<"\n";    
    }

}

//Помещение элемента в куча
void WeakHeap::push (couple f) {
   
        heap[rear].data=f.data;
        heap[rear].bit=f.bit;
        rear++;
}
// Извлечение элемента из кучи
void WeakHeap::pop() {
    if ( frnt == rear ) {
        cout << "куча пуста" <<endl ;
        return;
    }
    frnt++;

    }

#endif