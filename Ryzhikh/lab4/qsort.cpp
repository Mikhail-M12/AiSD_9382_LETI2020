#include <iostream>
using namespace std;


template <class Item>
void read(Item arr[], int n){    //считывание массива
	for(int i = 0; i < n; i++)
		cin >> arr[i];
}	

	
template <class Item>
void print(Item arr[], int n){    //печать массива
	for(int i = 0; i < n; i++)
		cout << arr[i] << ' ';
	cout << "\n";
}


template <class Item>
void exch(Item &a, Item &b){   //перестановка элементов
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}


template <class Item>
void comepxch(Item &a, Item &b){
	if(b < a)
		exch(a, b);
}


template <class Item>
void insertion(Item arr[], int l, int r){    //сортировка вставками
	for(int i = r; i > l; i--)
		comepxch(arr[i-1], arr[i]);
	cout << "Promezhutochniy vivod: \n"; 
	print(arr, r);
	for(int i = l + 2; i <= r; i++){
		int j = i;
		Item v = arr[i];
		while(v < arr[j-1]){
			arr[j] = arr[j-1]; 
			j--;
		}
		arr[j] = v;
	}
}


template <class Item>
int partition(Item arr[], int l, int r){    //разбиение
	int i = l - 1;
	int j = r;
	Item v = arr[r]; 
    for (;;)
	{
		while (arr[++i] < v);
		while (v < arr[--j])
			if (j == l)
				break;
		if (i >= j) 
			break;
		exch(arr[i], arr[j]);
    }
    exch(arr[i], arr[r]);
    return i;
}


template <class Item>
void quickSort(Item arr[], int l, int r, int M){   //быстрая сортировка
	if (r-l <= M) 
		return;
	exch(arr[(l+r)/2], arr[r-1]);
	comepxch(arr[l], arr[r-1]);
	comepxch(arr[l], arr[r]);
	comepxch(arr[r-1], arr[r]);
	cout << "Promezhutochiy vivod:\n"; 
	print(arr, r+1);
	int i = partition(arr, l+1, r-1);
	quickSort(arr,l, i-1, M);
	quickSort(arr, i+1, r, M);
}


template <class Item>
void hybridSort(Item arr[], int l, int r, int M){   //быстрая сортировка, совмещенная с сортировкой вставками
	quickSort(arr, l, r, M);
	insertion(arr, l, r); 
}


int main(){
	int n, M;
	cout << "Vvedite kolichestvo elementov v massive:\n";
	cin >> n;
	cout << "Vvedite razmen malogo podmassiva:\n";
	cin >> M;
	cout << "Vvedite massiv:\n";
	int *arr = new int[n];
	read(arr, n);
	cout << "Vvedenniy massiv:\n";
	print(arr, n);
	cout << "\n";
	hybridSort(arr, 0, n-1, M);
	cout << "\nOtsortirovanniy massiv:\n";
	print(arr, n);
	delete[] arr;
	return 0;
}
