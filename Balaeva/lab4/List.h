#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <array>
#include <initializer_list>
#include <string>

using namespace std;

template<typename T>
class List{
public:
    class Node{
    public:
        T value;
        Node* nextNode = nullptr;
        Node* prevNode = nullptr;

        Node() = default;

        Node(T newValue){
            value = newValue;
        }

        ~Node(){
            if(prevNode){
                delete prevNode;
            }
            if(nextNode){
                delete nextNode;
            }
        }
    };
private:


    Node* front;
    Node* back;
    int size = 0;

    Node* getNode(int index){
        if(index > size){
            return nullptr;
        }
        if(index == 0){
            return front;
        }
        if(index == size - 1){
            return back;
        }
        Node* tmp = front;
        int tmpIndex = 0;
        while(tmpIndex != index && tmp){
            tmp = tmp->nextNode;
            tmpIndex++;
        }
        return tmp;
    }

public:
    List(){
        this->size = 0;
    }

    template<size_t L>
    List(array<T, L> newArray){
        for(auto it: newArray){
            add(it);
        }
    }

    List(T* newArr, int size){
        for(int i = 0; i < size; i++){
            add(newArr[i]);
        }
    }

    List(initializer_list<T> initList){
        for(auto it: initList){
            add(it);
        }
    }

    int getSize(){
        return size;
    }

    void add(T newValue){
        Node* tmp = new Node(newValue);

        if(size == 0){
            this->front = tmp;
            this->back = tmp;
        }
        else{
            back->nextNode = tmp;
            tmp->prevNode = back;
            back = tmp;
        }
        this->size++;
    }

    Node* operator[](int index){
        return getNode(index);
    }

    T at(int index){
        Node* tmp = getNode(index);
        if(tmp){
            return tmp->value;
        }
        throw std::invalid_argument("Index out of range: " + to_string(index));
    }

    void swap(Node* firstNode, Node* secondNode){
        T tmp = firstNode->value;
        firstNode->value = secondNode->value;
        secondNode->value = tmp;
    }

    void print(){
        if(size == 0){
            return;
        }
        Node* tmp = this->front;
        while(tmp){
            if(tmp == tmp->nextNode){
                return;
            }
            cout << tmp->value << ' ';
            tmp = tmp->nextNode;
        }
        cout << '\n';
    }

    Node* getFront(){
        return front;
    };

    Node* getBack(){
        return back;
    }
};

#endif
