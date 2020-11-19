#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>

using namespace std;

template <typename T>
void printArray(vector<T> a, int start, int end) {
	cout << "{";
	for (int i = start; i < end; i++) {
		cout << a[i] << ", ";
	}
	cout << a[end] << "}";
}
template <typename T>
int divide(vector<T>& a, int start, int end) //функция перестановки элементов относительно некоторого опорного
{
	static int count = 0;
	T pivot = a[end]; //опорный элемент для последующих сравнений

	
	int pIndex = start; //вспомогательный индекс, который показывает положение опорного элемента

	cout << "Перестановка элементов подмассива: ";
	printArray(a, start, end);
	cout << " относительно " << pivot << "\n";

	for (int i = start; i < end; i++)
	{
		count++;
		cout << "Сравнение " << a[i] << " и " << pivot << "\n";
		if (a[i] <= pivot)
		{
			cout << a[i] << " <= " << pivot << ", поэтому элемент переходит в левую половину.\n";
			swap(a[i], a[pIndex]);
			
			pIndex++;
		}
		else {

			cout << a[i] << " > " << pivot << ", поэтому элемент переходит в правую половину.\n";
			
			
		}
		
	}

	// После выполнения всех сравнений элемент со вспомогательный индексом меняется местами с опорным элементом
	// В полученном подмассиве все элементы, стоящие до опорного меньше его, а после опорного больше.
	swap(a[pIndex], a[end]);
	cout << "Результат перестановки: ";
	printArray(a, start, end);
	cout << "\n\nИсходный массив: ";
	printArray(a, 0, a.size() - 1);
	cout << "\n";
	// Функция возвращает индекс опорного элемента.
	
	return pIndex;
}
template <typename T>
// Непосредственно функция сортировки
void iterativeQuickSort(vector<T>& a)
{
	
	//для хранения подмассивов используется стек. элементы в нем имеют тип пары, в которой хранится
	//начала и конец сортируемых подмассивов
	stack<pair<int, int>> stk;
	
	int start = 0; 
	int end = a.size() - 1;
	stk.push(make_pair(start, end));

	// цикл будет выполняться, пока стек не станет пустым
	while (!stk.empty())
	{
		
		// на каждой итерации обрабытвается верхний элемент стека
		start = stk.top().first;
		end = stk.top().second;
		stk.pop();

		// перестановка элементов подмассива и получение индекса опорного элемента
		int pivot = divide(a, start, end);
		if ( end - start <= 1){
			cout << "Часть ";
			printArray(a, start, end);
			cout << " отсортирована\n\n";
			}
		else {
			//если в сортируемом подмассиве до(или после) опорного элемента находятся
			//минимум два элемента - подмассив, содержащий их также кладется в стек
			bool c1 = pivot - start >= 2;
			bool c2 = end - pivot >= 2;


			if (c1) {
				stk.push(make_pair(start, pivot - 1));
				cout << "Часть ";
				printArray(a, start, pivot - 1);
				cout << " может быть не отсортирована\n";
			}
			else {
				cout << "Часть ";
				printArray(a, start, pivot);
				cout << " отсортирована\n";
			}
			//помещение в стек подмассива левее опорного

			if (c2) {
				cout << "Часть ";
				printArray(a, pivot + 1, end);
				cout << " может быть не отсортирована\n";
				stk.push(make_pair(pivot + 1, end));
			}
			else {
				cout << "Часть ";
				printArray(a, pivot, end);
				cout << " отсортирована\n\n";
			}
		}
			//правее опорного
		
		
	}
}
template <typename T>
void readVector(vector<T>& v, FILE* f = stdin) { //считывание массива
	stringstream ss;
	char c = fgetc(f);
	int spacecount = 1;
	while (c != '\n' && c != EOF) {
		ss << c;
		if (isspace(c))spacecount++;
		c = fgetc(f);
	}
	
	for (int i = 0; i < spacecount; i++) {
		T a;
		ss >> a;
		v.push_back(a);
	}

}

int main()
{
	vector<int> v;
	setlocale(LC_ALL, "Russian");
	char* a = new char[20];
	char* c = new char[300];
	while (strcmp(a, "1\n") && strcmp(a, "2\n")) {
		std::cout << "Сортировка массива. Введите 1 для ввода с консоли и 2 для ввода с файла.\n";
		fgets(a, 20, stdin);
	}
	if (strcmp(a, "1\n") == 0) {
		std::cout << "Введите элементы массива через пробел:";
		readVector<int>(v,  stdin);

	}
	else {
		FILE* f1 = fopen("test.txt", "r+");
		std::cout << "Содержимое файла: ";
		
		while (fgets(c, 300, f1)) std::cout << c;
		f1 = fopen("test.txt", "r+");
		readVector<int>(v, f1);
		std::cout << "\n";
		fclose(f1);

	}
	iterativeQuickSort(v);
	cout << "Отсортированный массив: ";
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << "\n";
	return 0;
}