#include "BinTree.h"

int main ()
{
    int track= INT_MAX;
    int count=0;

    char elem;

    infile>>elem;//вводим искомый элемен  из файла

    cout<<"Элемент для поиска: "<<elem<<"\n\n";

    BinTree<char>* b;

    b=b->enterBT();//вводим дерево из файла

    cout<<"Вы ввели: ";

    b->outBT(b);

    cout<<"\n\n";
  
    b->find_elem(b, 1, elem, count, track);
    
    if (count==0){
        cout<<"Искомый элемент не обнаружен\n";
        cout<<"Количество вхождений в дерево 0\n";
        cout<<"Путь до элемента -1\n";
    }    
    else
    {
       cout<<"Искомый элемент обнаружен\n";
       cout<<"Количество вхождений в дерево "<<count<<"\n"; 
       cout<<"Минимальный путь до элемента "<< track<<"\n";
    }
 
    cout << endl;

    return  0;
}