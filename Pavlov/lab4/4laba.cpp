#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

//Шаблонный тип данных
template <typename T>
struct Content {
	T content;
};

//Отступ, соответствующий глубине рекурсии
inline void indent(int n) {
	for (int i = 0; i < n; i++) {
		cout << "\t";
	}
}


//Создание кучи, отсортированной по убыванию
template <typename T>
void maxHeap(T* arr, int n, int i, int& depth){
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l].content > arr[largest].content) {	//Если левое поддерево больше корня
		indent(depth);
		cout << "The left child " << arr[l].content << " is greater than " << arr[largest].content << "\n";
		largest = l;
	}
	if (r < n && arr[r].content > arr[largest].content) { //Если правое поддерево больше корня/левого поддерева
		indent(depth);
		cout << "The right child " << arr[r].content << " is greater than " << arr[largest].content << "\n";
		largest = r;
	}
	if (largest != i){		//Если корень меньше хотя бы одного из своих поддеревьев
		indent(depth);
		cout << "Swapping " << arr[largest].content << " and " << arr[i].content << ", " << arr[i].content << " is now the root\n";
		swap(arr[i], arr[largest]);		//Меняем местами наибольший элемент с корнем
		indent(depth);
		cout << "Checking the lower levels\n";
		maxHeap(arr, n, largest, ++depth);	//Проверяем то, что было корнем
	}
	else {				//Если корень больше или равен обоим своим поддеревьям
		indent(depth);
		cout << "The root " << arr[largest].content << " is the largest\n";
		indent(depth);
		cout << "Finished creating maxHeap\n";
		if (!depth) {
			cout << "\n";
		}
	}
	if (depth) {
		depth--;
	}
}

//Сортировка по возрастанию
template <typename T>
void heapSort(T* arr, int n, int& depth){
	cout << "\nSort started\n\nPre-sort (descending sort)\n";
	for (int i = n / 2 - 1; i >= 0; i--) {						//Проходим по куче с листьев, строим убывающую кучу
		cout << "Creating maxHeap from root " << arr[0].content << " to " << (n - 1) << " element " << arr[n - 1].content << " starting from " << i << " element " << arr[i].content << "\n";
		maxHeap(arr, n, i, depth);
	}
	cout << "Final sort :\n";
	for (int i = n - 1; i > 0; i--){							//Меняем первый и последний доступный элементы, строим убывающую кучу для первых i - 1 элементов (пока i > 0)
		cout << "Swapping the root " << arr[0].content << " and the last element of array " << arr[i].content << "\n";
		swap(arr[0], arr[i]);
		cout << "Creating maxHeap from root " << arr[0].content << " to " << (i - 1) << " element " << arr[i - 1].content << " starting from 0 element " << arr[0].content << "\n";
		maxHeap(arr, i, 0, depth);
	}
	cout << "Sort finished\n\n";
}

int main() {
	
	int command = 0;
	cout << "1 - console input, 2 - file input : \n\n";
	cin >> command;
	if (command != 1 && command != 2) {
		cout << "Unknown command\n";
	}
	else{
		int* arra;
		Content<int>* arr;
		int x, size, depth = 0;

		//Работа с консолью
		if (command == 1) {
			while (true) {
				cout << "Enter the array size (0 to quit): ";
				cin >> size;
				if (size < 0) {
					cout << "\nInvalid value\n\n";
					continue;
				}
				if (!size) {
					break;
				}

				//Создание, заполнение и сортировка массивов
				arr = new Content<int>[size];
				arra = new int[size];
				for (int i = 0; i < size; i++) {
					cout << i + 1 << " element : ";
					cin >> x;
					arr[i].content = x;
					arra[i] = x;
				}
				if (size == 1) {
					cout << "Sort isn't needed\n\n";
					continue;
				}
				heapSort(arr, size, depth);
				cout << "Initial array :\n";
				for (int i = 0; i < size; ++i) {
					cout << arra[i] << " ";
				}
				cout << "\n";
				sort(arra, arra + size);
				cout << "Heap sort result :\n";
				for (int i = 0; i < size; i++) {
					cout << arr[i].content << " ";
				}
				cout << "\n";
				cout << "std::sort result :\n";
				for (int i = 0; i < size; ++i) {
					cout << arra[i] << " ";
				}
				cout << "\n";
			}
		}

		//Работа с файлом
		else {
			ifstream input;
			ofstream output;
			const string outputFilename = "output.txt";
			string inputFilename = "";
			output.open(outputFilename);
			output << "";
			output.close();
			while (inputFilename != "!") {
				cout << "Enter the input file name (or \'!\' to quit) : ";
				cin >> inputFilename;
				cout << "\n";
				bool valid = true;
				input.open(inputFilename);
				if (input.is_open()) {
					input >> size;
					if (size < 1) {
						output.open(outputFilename, ios::app);
						output << "NA (Not Array)\n";
						output.close();
						cout << "Invalid size\n\n";
						input.close();
						continue;
					}

					//Создание, заполнение и сортировка массивов
					arr = new Content<int>[size];
					arra = new int[size];
					for (int i = 0; i < size; i++) {
						if (input >> x) {
							arr[i].content = x;
							arra[i] = x;
						}
						else {
							valid = false;
							break;
						}
					}
					input.close();
					if (size == 1) {
						output.open(outputFilename, ios::app);
						output << arr[0].content << "  ->  " << arr[0].content << "\n";
						output.close();
						cout << "Initial array : " << arr[0].content << "\n";
						cout << "Sort isn't needed\n\n";
						continue;
					}
					if (!valid) {
						cout << "\nNot enough elements to fill the array\n\n";
						continue;
					}
					output.open(outputFilename, ios::app);
					for (int i = 0; i < size; i++) {
						output << arr[i].content;
						if (i != size - 1) {
							output << ", ";
						}
					}
					output << "  ->  ";
					heapSort(arr, size, depth);
					cout << "Initial array :\n";
					for (int i = 0; i < size; ++i) {
						cout << arra[i] << " ";
					}
					for (int i = 0; i < size; i++) {
						output << arr[i].content;
						if (i != size - 1) {
							output << ", ";
						}
					}
					output << "\n";
					output.close();
					cout << "\n";
					sort(arra, arra + size);
					cout << "Heap sort result :\n";
					for (int i = 0; i < size; i++) {
						cout << arr[i].content << " ";
					}
					cout << "\n";
					cout << "std::sort result :\n";
					for (int i = 0; i < size; ++i) {
						cout << arra[i] << " ";
					}
					cout << "\n\n";
				}
				else if (inputFilename == "!") {
					break;
				}
				else if (inputFilename != "") {
					cout << inputFilename << " doesn't exist\n\n";
				}
			}
		}
		
	}
	return 0;
}