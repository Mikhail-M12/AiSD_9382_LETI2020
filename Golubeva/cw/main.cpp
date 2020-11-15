#include "Weak_heap.h"

int main()
{
    std::cout<<"Выберите способ ввода массива для сортировки\n";
    std::cout<<"Введите 1 для ввода с консоли или 0 для ввода из файла\n";

    char s;

    std::cin>>s;
    WeakHeap* wh=nullptr;
    int flag=0;
    while (!flag){
        switch (s)
        {
        case '0':
            std::cout<<"Вы выбрали ввод из файла\n";
            wh=wh->fileInputHeap();
            flag=1;
            break; 
        case '1':
            std::cout<<"Вы выбрали ввод с консоли\n";
            wh=wh->consoleInputHeap();
            flag=1;
            break;
        default:
            std::cout<<"Нет такой команды: \n"<<s<<"\n";
            std::cout<<"Введите команду\n";
            std::cin>>s;
            break;
        }
    }
  
    std::cout<<"\x1b[34mСиним\x1b[0m будут подсвечиваться проверяемые в куче элементы\n";
    std::cout<<"\x1b[32mЗелёным\x1b[0m будут подсвечиваться элементы, которые в результате сравнения поменяли местами\n";
    std::cout<<"\x1b[33mЖёлтым\x1b[0m будут подсвечиваться отсортированные элементы\n\n";

    wh->weakHeapSort();
    if (wh->size>0){
        std::cout<<"Отсортированный массив: ";
        wh->displayArray();
    }
    wh->~WeakHeap();
    return 0;
}