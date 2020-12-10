#include "sort.h"
#include "fstream"
#include "iostream"

int main(){
	std::ifstream infile("test.txt");
	int array_len;
	infile>>array_len;
	int i=0;
	int* array = new int[array_len];
	while (i<array_len&&infile){
		infile>>array[i];
		i+=1;
	}
	if (!infile||i<array_len){
		std::cout<<"Too many elements in array or incorrect date\n";
		delete [] array;
		return 0;
	}
	
	/*for (int i=0;i<array_len;i++)
		std::cout<<array[i]<<' ';
	std::cout<<"\n";*/
	
	comb_sorting(array, array_len);
	
	/*for (int i=0;i<array_len;i++)
		std::cout<<array[i]<<' ';
	std::cout<<"\n";*/

	delete[] array;
	return 0;
};
