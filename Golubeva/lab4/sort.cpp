#include "sort.h"
#include <algorithm>
#include <iostream>

void swap_elements(int& a, int& b){
	int c=a;
	a=b;
	b=c;
} 
    
void comb_sorting(int* array, int array_len){
    int gap=array_len; 
    int i=0;
    while (gap >1){
        gap = std::max(1, int(gap / 1.25));  // minimum gap is 1
        std::cout<<"Текущий фактор уменьшения : "<<gap<<"\n";
        for (i=0;i<array_len-gap;i++){
            int j = i + gap;
            std::cout<<"Сравниваемые элементы: "<<array[i]<< " под номером "<<i<< " и "<<array[j]<<" под номером "<<j;
            if (array[i] > array[j]){
            	swap_elements(array[i], array[j]);
            	std::cout<<" (поменяли)";
            }
        std::cout<<"\n";      
        }   
        std::cout<<"Массив после прохода с фактором уменьшения: "<<gap<<"\n";    
        for (int i=0;i<array_len;i++)
		std::cout<<array[i]<<' '; 
        std::cout<<"\n\n";  
    } 
}   


