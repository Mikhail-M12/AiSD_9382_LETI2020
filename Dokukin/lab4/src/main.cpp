#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>

#define EPS 0.0000005

template<class T>
void swap(T& a, T& b){
	int tmp = a;
	a = b;
	b = tmp;
}

template<class T>
int partition(T* A, int left, int right){
	int pivot = left; //Опорным элементом выбираем первый
	std::cout<<"Bounds: left - "<<left<<", right - "<<right<<"\nPivot element: "<<A[pivot]<<'\n';
	
	for (int i = left + 1; i <= right; i++){
		if (A[i] < A[pivot]){ //Если элемент меньше опорного - меняем его местами с первым элементом больше опорного, а затем меняем его же местами с самим опорным (для соблюдения условий задачи)
			if (pivot + 1 != i) swap(A[pivot+1], A[i]);
			swap(A[pivot], A[pivot+1]);
			pivot++;
		}
		std::cout<<"pivot = "<<pivot<<", i = "<<i<<'\n';
		for(int j = left; j <= right; j++){ //Каждый шаг выводим текущее состояние массива на экран
			if (j == pivot) std::cout<<'|';
			std::cout<<A[j];
			if (j == i) std::cout<<'|';
			std::cout<<" ";
		}
		std::cout<<'\n';
	}
	
	return pivot;
}

template <class T>
void quickSort(T* A, int left, int right){
	if (left < right){
		int q = partition(A, left, right);
		quickSort(A, left, q-1);
		quickSort(A, q+1, right);
	}
}

int func(){ //Выбираем опцию ввода, вводим количество элементов в массиве и сами элементы или вводим из файла
	int a;
	int elemmode;
	std::cout<<"Choose input option(0 - file input, 1 - console input):\n";
	std::cin>>a;
	
	
	int n;
	

	if(a){
		std::cout<<"Choose array elements type(<=0 - int, 1 - char, >=2 - float):";
		std::cin>>elemmode;
		std::cout<<"Insert array size:\n";
		std::cin>>n;
		std::cout<<"Insert array elements:\n";
		
		if (elemmode <= 0){
			int* B;
			B = new int[n];
			for(int i = 0; i < n; i++){
				std::cin>>B[i];
			}
			quickSort(B, 0, n - 1);
			std::cout<<"Sorted array: ";
			for(int i = 0; i < n; i++){
				std::cout<<B[i]<<" ";
			}
			delete[] B;
		}
		else if (elemmode == 1){
			char* B;
			B = new char[n];
			for(int i = 0; i < n; i++){
				std::cin>>B[i];
			}
			quickSort(B, 0, n - 1);
			std::cout<<"Sorted array: ";
			for(int i = 0; i < n; i++){
				std::cout<<B[i]<<" ";
			}
			delete[] B;
		}
		else{
			float* B;
			B = new float[n];
			for(int i = 0; i < n; i++){
				std::cin>>B[i];
			}
			quickSort(B, 0, n - 1);
			std::cout<<"Sorted array: ";
			for(int i = 0; i < n; i++){
				std::cout<<B[i]<<" ";
			}
			delete[] B;
		}
		
		std::cout<<"\n--------------------------------\n";
		return 0;
	}
	
	std::ifstream f("tests.txt");
	if (!f){
		std::cout<<"Couldn't open file.\n";
	}
	while(!f.eof()){
		f>>n;
		f>>elemmode;
		
		if (elemmode <= 0){
			int* B;
			B = new int[n];
			for(int i = 0; i < n; i++){
				f>>B[i];
			}
			std::cout<<"Array:\n";
			for(int i = 0; i < n; i++){
				std::cout<<B[i]<<' ';
			}
			std::cout<<'\n';
			quickSort(B, 0, n - 1);
			std::cout<<"Sorted array: ";
			for(int i = 0; i < n; i++){
				std::cout<<B[i]<<" ";
			}
			delete[] B;
		}
		else if (elemmode == 1){
			char* B;
			B = new char[n];
			for(int i = 0; i < n; i++){
				f>>B[i];
			}
			std::cout<<"Array:\n";
			for(int i = 0; i < n; i++){
				std::cout<<B[i]<<' ';
			}
			std::cout<<'\n';
			quickSort(B, 0, n - 1);
			std::cout<<"Sorted array: ";
			for(int i = 0; i < n; i++){
				std::cout<<B[i]<<" ";
			}
			delete[] B;
		}
		else{
			float* B;
			B = new float[n];
			for(int i = 0; i < n; i++){
				f>>B[i];
			}
			std::cout<<"Array:\n";
			for(int i = 0; i < n; i++){
				std::cout<<B[i]<<' ';
			}
			std::cout<<'\n';
			quickSort(B, 0, n - 1);
			std::cout<<"Sorted array: ";
			for(int i = 0; i < n; i++){
				std::cout<<B[i]<<" ";
			}
			delete[] B;
		}
		
		std::cout<<"\n--------------------------------\n";
	}
	return 0;
}

int main(){
	try{
		func();
	}
	catch(...){
		std::cout<<"An unexpected error occurred.\n";
	}
	return 0;
} 
