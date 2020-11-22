#include <iostream>
#include <fstream>
using namespace std;


template <class Item>
void read(Item arr[], int n) {    //считывание массива
	for (int i = 0; i < n; i++)
		cin >> arr[i];
}


template <class Item>
void print(Item arr[], int n) {    //печать массива
	for (int i = 0; i < n; i++)
		cout << arr[i] << ' ';
	cout << "\n";
}


template <class Item>
void printArray(Item arr[], int l, int r) {
	for (int i = l; i <= r; i++)
		cout << arr[i] << ' ';
	cout << "\n\n";
}


template <class Item>
void exch(Item& a, Item& b) {   //перестановка элементов
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}


template <class Item>
void insertionSort(Item arr[], int l, int r, int lenght) {
	bool check = false;
	for (int i = l + 1; i < r + 1; i++) {
		int j = i;
		while (j > l && arr[j - 1] > arr[j]) {
			cout << "Changing elements: " << arr[j - 1] << ", " << arr[j] << endl;
			exch(arr[j - 1], arr[j]);
			j--;
			cout << "Intermediate value (insertion): ";
			print(arr, lenght + 1);
			cout << "\n";
			check = true;
		}
	}
	if (!check)
		cout << "No need to use insertion sorting; Array is already sorted\n\n";
}


template <class Item>
void quickSort(Item arr[], int l, int r, int M, int lenght) {
	if (r - l <= M) {
		cout << "Beginning of the insertion sorting:\n";
		cout << "Unsorted subarray: ";
		printArray(arr, l, r);
		insertionSort(arr, l, r, lenght);
		return;
	}
	int z = arr[l + (r - l) / 2];  //средний элемент
	cout << "Middle element is " << z << "\n\n";
	int ll = l, rr = r; //первый и последний элементы
	while (ll < rr) {
		while (arr[ll] < z) {
			cout << "Element " << arr[ll] << " stays in place, because it less than middle element " << z << "\n\n";
			ll++;
		}
		while (arr[rr] > z) {
			cout << "Element " << arr[rr] << " stays in place, because it bigger than middle element " << z << "\n\n";
			rr--;
		}
		if (ll < rr) {
			cout << "Changing elements: " << arr[ll] << ", " << arr[rr] << endl;
			exch(arr[ll], arr[rr]);
			ll++;
			rr--;
			cout << "Intermediate value(quick sort): ";
			print(arr, lenght + 1);
			cout << "\n";
		}
		else if (ll == rr)
		{
			ll++;
			rr--;
		}
	}
	if (l < rr) quickSort(arr, l, rr + 1, M, lenght);
	if (ll < r) quickSort(arr, ll, r, M, lenght);
}

int main(int argc, char** argv) {
	int n, M;
	int* arr = nullptr;
	if (argc == 2)
	{
		char* file = argv[1];
		ifstream fin(file);// окрываем файл для чтения
		if (fin.is_open())
		{
			fin >> n;
			if (n < 0)
				n = 0;
			fin >> M;
			if (M < 0)
				M = 0;
			arr = new int[n];
			for (int i = 0; i < n; i++)
				fin >> arr[i];
		}
		else
		{
			std::cout << "Can`t open file" << std::endl;
			return 0;
		}
		fin.close();
	}
	else
	{
		cout << "Enter capacity of array:\n";
		cin >> n;
		if (n < 0)
			n = 0;
		cout << "Enter capacity of small subarray:\n";
		cin >> M;

		if (M < 0)
			M = 0;
		cout << "Enter array:\n";
		arr = new int[n];
		read(arr, n);
	}
	cout << "Entered array:\n";
	print(arr, n);
	cout << "\n";
	quickSort(arr, 0, n - 1, M, n - 1);
	cout << "\nSorted array:\n";
	print(arr, n);
	delete[] arr;
	return 0;
}