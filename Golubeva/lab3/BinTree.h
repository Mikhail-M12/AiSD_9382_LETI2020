#pragma once
#include <fstream>
#include <cstdlib>

#include <iostream>
#include <cstdlib>
#include "limits.h"

using namespace std;

typedef unsigned int unInt;
//typedef char base;
ifstream infile ("./tests/KLP3.txt");

template <class T>

class BinTree{
    T info;

	BinTree *lt; //левое поддерево
	BinTree *rt; //правое поддерево

    BinTree* left (BinTree* b)       
        {   if (b == nullptr) { 
                cerr << "Error: Left(null) \n"; 
                exit(1); 
            }
            else 
                return b ->lt;//возвращаем левое поддерево, если b не нулевое
        }
//-------------------------------------    
    BinTree* right (BinTree* b)        
    {    if (b == nullptr) { 
            cerr << "Error: Right(null) \n"; 
            exit(1); 
            }
        else 
            return b->rt;//возвращаем правое поддерево, если b не нулевое
    }
//-------------------------------------        
    BinTree* consBT(const T &x, BinTree *lst,  BinTree *rst)
    {    BinTree *p=new BinTree;
       
        if ( p != NULL)    {     
            p ->info = x;
            p ->lt = lst;
            p ->rt = rst;
            return p;//создаём новое дерево, путём склеивания его из двух и добавления корня
        }
        else {
            cerr << "Memory not enough\n"; 
            exit(1);
            }
    }
//-------------------------------------            
    void destroy (BinTree* b)
    {    if (b != NULL){//проверяем, что дерево не нулевое и рекурсивно очищаем правое и левое поддеревья
            destroy (b->lt);
            destroy (b->rt);
            delete b;
            b = NULL;
        }
    }

public: 

//---------------------------------------
    BinTree* enterBT ()
    {    
        T ch;
        BinTree* p;
        BinTree* q;
        if (!infile){
            cout<<"Неправильно введён список\n";
            exit(1);
        }

        infile >> ch;//считываем очередной символ из файла
        if (ch=='/') 
            return nullptr;
        else {
            p = enterBT(); 
            q = enterBT(); 
            return consBT(ch, p, q);
        }
    }

 //---------------------------------------
    BinTree(){
        //конструктор по умолчанию
        lt=nullptr;
        rt=nullptr;
    }

//---------------------------------------
    ~BinTree(){
        //декструктор. Вызывает метод для очистки памяти дерева
        this->destroy(this);
    }

//---------------------------------------
    void outBT(BinTree* b)
    {       
        //выводит на экран запись введённого дерева
        if (b!=nullptr) {
            cout << rootBT(b);
            outBT(left(b));
            outBT(right(b));
        }
        else {
            cout<<"/";
        };
    }

//---------------------------------------
    void displayBT (BinTree* b, int n)
    {
        //выводит на экран запись введённого дерева с указание уровня
        if (b!=NULL) {

            cout << ' ' << rootBT(b)<< n;
            
            if(!isNull(right(b))){
                    cout << endl;
                    for (int i=1;i<=n;i++) 
                        cout << " ";
                    displayBT (right(b),n+1);
                }
            else    
                cout << endl;
            if(!isNull(left(b))){
                for (int i=1;i<=n;i++) 
                    cout << " "; 
                displayBT (left(b),n+1);}
        }
        else {
            
        };
    }

//---------------------------------------
void find_elem (BinTree* b, int n, T elem, int &count, int &track)
    {
    	cout<<" ";
        if (b!=NULL) {
            if (elem==rootBT(b)){
                count+=1;
                if (n<track)
                    track=n;
                cout<<"Совпадение с искомым элементом на уровне "<<n<<"\n";
            }
            else
                cout <<"Искомый элемент не совпадает с "<< rootBT(b)<<" на уровне "<< n<<"\n";
                
                if(!isNull(right(b))) {
                        cout << endl;
                        for (int i=1;i<=n;i++) 
                            cout << " ";
                        find_elem (right(b),n+1, elem, count, track);
                    }
                else 
                    cout << endl;
                if(!isNull(left(b))) {
                    for (int i=1;i<=n;i++) 
                        cout << " "; 
                    find_elem (left(b),n+1, elem, count, track);}
                    
        }
        else {};
    }
//-------------------------------------
     BinTree* create()
    {    
        return nullptr;
    }
//-------------------------------------
    bool isNull(BinTree* b)
    {    
        return (b == nullptr);
    }
//-------------------------------------
    T rootBT (BinTree* b)          
    {    if (b == nullptr) { 
            cerr << "Error: RootBT(null) \n"; 
            exit(1); 
        }
        else 
            return b->info;//возвращает значение поля информации
    }
};
