#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <conio.h>
using namespace std;
void printDep(int depth){
    for(int i = 0; i < depth; ++i){
        cout<<"/\\";
    }
}

template < typename T>
void BubleSort(T &array, size_t n){
    int i = 0;
    bool t = true;
    int depth = 0;
    while (t) {
        t = false;
        ++depth;
        for(int j = 0; j < n-i-1;++j){
            cout<<"Sort to "<<n-i-1<<" index\n";
            if (array[j] > array[j + 1]){
                printDep(depth);
                cout<<"array["<<j<<"] > array["<<j+1<<"]: "<< array[j] <<" > "<<array[j + 1]<<" True\n";
                printDep(depth);
                cout<<"array{";
                for(int out =0; out<n;++out){
                    cout<<array[out]<<", ";
                }
                cout<<"}\n";
                swap(array[j], array[j + 1]);
                printDep(depth);
                cout<<"swap: array["<<j<<"] -> array["<<j+1<<"]\n";
                printDep(depth);
                t = true;
                cout<<"new array{";
                for(int out =0; out<n;++out){
                    cout<<array[out]<<", ";
                }
                cout<<"}\n\n";
            }else {
                printDep(depth);
                cout<<"array["<<j<<"] > array["<<j+1<<"]: "<< array[j] <<" > "<<array[j + 1]<<" Lie\n";
                printDep(depth);
                cout<<"move on!\n\n";
            }
        }
        i = i + 1;
    }
    cout<<"Tumber of rounds->"<<depth<<'\n';
}


template < typename T>
void oddEvenSorting(T &array, size_t N) {
    cout<<"\nSorting start!\n______________________________________________________________\n";

    int depth = 0;
    for (size_t i = 0; i < N; i++) {
        ++depth;
        // (i % 2) ? 0 : 1 ?????????? 1, ???? i ??????, 0, ???? i ?? ??????

        bool split = (i % 2) ? 0 : 1;
        for (size_t j = (i % 2) ? 0 : 1; j + 1 < N; j += 2) {

            if (array[j] > array[j + 1]) {
                printDep(depth);
                if(!split){
                    cout<< "Split array into *even/odd* subgroups by index\n";
                }else {
                    cout<< "Split array into *odd/even* subgroups by index\n";
                }

                printDep(depth);
                cout<<"array["<<j<<"] > array["<<j+1<<"]: "<< array[j] <<" > "<<array[j + 1]<<" True\n";

                printDep(depth);
                cout<<"array{";
                for(int out =0; out<N;++out){
                    cout<<array[out]<<", ";
                }
                cout<<"}";
                cout<<'\n';
                std::swap(array[j], array[j + 1]);
                printDep(depth);
                cout<<"swap: array["<<j<<"] -> array["<<j+1<<"]\n";
                printDep(depth);
                cout<<"new array{";
                for(int out =0; out<N;++out){
                    cout<<array[out]<<", ";
                }
                cout<<"}";
                cout<<'\n';
                cout<<'\n';
            }else{
                printDep(depth);
                if(!split){
                    cout<< "Split array into *even/odd* subgroups by index\n";
                }else {
                    cout<< "Split array into *odd/even* subgroups by index\n";
                }
                printDep(depth);
                cout<<"array["<<j<<"] > array["<<j+1<<"]: "<< array[j] <<" > "<<array[j + 1]<<" Lie\n";
                printDep(depth);
                cout<<"move on!\n\n";
            }
        }
    }
    cout<<"Tumber of rounds->"<<depth<<'\n';
}

void writeToFile(string filename,int arg) {
    ofstream output;
    output.open(filename, ios::app);
    output << arg;
    output.close();
}
void writeToFile(string filename,string arg1) {
    ofstream output;
    output.open(filename, ios::app);
    output << arg1;
    output.close();
}

void CheckTheInput(int* arr, bool &Exit, bool choise, int len, bool choiseSort){
    if (len == 1 && arr[0] == '!') {
        Exit = false;
    } else if (len == 1) {
        cout << "In array one element : " << arr << "\n\n\n";
    } else if (len == 0) {
        cout << "\nAmount of elements: " << len << "\n";
        cout << "Empty array!\n\n\n";
    } else {
        if(choiseSort) {
            cout << "\nAmount of elements: " << len << '\n';
            cout << "What indexes can we go by:\n1) even/odd\n2) odd/even\n";
            oddEvenSorting(arr, len);
        }else BubleSort(arr,len);
        if(!choise) {
            writeToFile("output.txt","\nSorted array is: ");
            for(int i=0;i<len;++i) {
                writeToFile("output.txt", arr[i]);
                writeToFile("output.txt", " ");
            }
        }
        cout << "Sorted array is: ";
        for(int i =0; i < len; ++i)cout<< arr[i]<<' ';


    }
}
int comp (const int *i, const int *j)
{
    return *i - *j;
}

int main() {
    bool Exit = true;
    bool choiseFileOrConsole = true;
    bool choiseSort;
    int len=0;
    int* copyArray;
    cout<<"Choise the sort, 1 - odd/even \t 0 - Bubble sort optimized;\n";
    cin >> choiseSort;
    cout << "Enter : 0 - File Input, 1 - Console input: ";
    cin >> choiseFileOrConsole;
    cout <<'\n';
    if(!choiseFileOrConsole){
        string input_filename;
        const string output_filename = "output.txt";
        ifstream in;
        ofstream out;

        out.open(output_filename);
        out << "";
        out.close();

        cout << "Enter the input file name: \n\n";
        cin >> input_filename;
        in.open(input_filename);

        if (in.is_open()) {
            in >> len;
            int* some = new int[len];
            copyArray = new int[len];
            writeToFile("output.txt", "Initial array: ");
            for(int i = 0; i < len; ++i){
                in >> some[i];
                writeToFile("output.txt", some[i]);
                writeToFile("output.txt", " ");
                copyArray[i] = some[i];
            }
            CheckTheInput(some,Exit,choiseFileOrConsole,len, choiseSort);

        }
        else {
            cout << input_filename << " doesn't exist!\n";
        }

    }else {
        cout<<"Array length: ";
        cin>>len;
        int* elem = new int[len];
        copyArray = new int[len];
        cout << "\nInput data or \'!\' to quit: \n";
        for(int i=0; i < len; ++i){
            cout<<i<<" elem: ";
            std::cin >> elem[i];
            copyArray[i] = elem[i];
            cout<<'\n';
        }
        CheckTheInput(elem, Exit,choiseFileOrConsole, len,choiseSort);


    }
    qsort(copyArray, len, sizeof(int),(int(*) (const void *, const void *)) comp);
    cout<<"\nSorted by qsort:";
    for(int i = 0; i <len; ++i)cout<<copyArray[i]<<" ";
    cout << "\n____________________________________________\n\n";
    getch();
    return 0;
}
