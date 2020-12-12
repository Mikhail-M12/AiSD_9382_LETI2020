#include "Weak_heap.h"

int main()
{
    std::string s;
    WeakHeap* wh=nullptr;
    int flag=0;
    while (!flag){
        std::cout<<"Выберите способ ввода массива для сортировки\n";
        std::cout<<"Введите Console/C/c для ввода с консоли, File/F/f для ввода из файла, Exit/E/e для окончания работы программы\n";
        std::cout<<"\x1b[34mСиним\x1b[0m будут подсвечиваться проверяемые в куче элементы\n";
        std::cout<<"\x1b[32mЗелёным\x1b[0m будут подсвечиваться элементы, которые в результате сравнения поменяли местами\n";
        std::cout<<"\x1b[33mЖёлтым\x1b[0m будут подсвечиваться отсортированные элементы\n\n";

        std::cout<<"Введите команду\n";
        std::cin>>s;
        
        
        if (s=="File"||s=="F"||s=="f"){
            std::cout<<"Вы выбрали ввод из файла\n";
            wh=wh->fileInputHeap();
            if (wh){
                wh->weakHeapSort();
 
                std::cout<<"Отсортированный массив: ";
                wh->displayArray();
                delete wh;
            }    

        }
        else if (s=="Console"||s=="C"||s=="c"){
            std::cout<<"Вы выбрали ввод с консоли\n";
            wh=wh->consoleInputHeap();
            if (wh){
                wh->weakHeapSort();
                std::cout<<"Отсортированный массив: ";
                wh->displayArray();
                delete wh;
            }
 
        }
        else if (s=="Exit"||s=="E"||s=="e"){ 
            std::cout<<"Вы завершили программу!\n";
            flag=1;

        }   
        else{
            std::cout<<"Нет такой команды: \n"<<s<<"\n";
            
        }    
        
    }
    
    return 0;
}
