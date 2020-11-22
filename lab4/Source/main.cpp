#include <iostream>
#include<string>
#include <fstream>
#include <conio.h>

using namespace std;
void printDep(int depth){
    for(int i = 0; i < depth; ++i){
        cout<<"/\\";
    }
}
/*
В этой сортировке мы делим данные на четные и нечетные индексы, а затем сравниваем их.
 Четные строго со следующим числом, т.е нечетным.
 После чего делаем сдвиг и сравниваем уже нечетные/четные.
*/
template < typename T>
void oddEvenSorting(T &array, size_t N) {
    cout<<"\nSorting start!\n______________________________________________________________\n";

    int depth = 0;
    for (size_t i = 0; i < N; i++) {
        ++depth;
        // (i % 2) ? 0 : 1 возвращает 1, если i четное, 0, если i не четное
        size_t j = (i % 2) ? 0 : 1;
        bool split = (i % 2) ? 0 : 1;
        for (; j + 1 < N; j += 2) {

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
}

void writeToFile(const string filename, const string arg) {
    ofstream output;
    output.open(filename, ios::app);
    output << arg;
    output.close();
}


bool CheckTheInput(string arr, bool &Exit, bool choise){
    if (arr.length() == 1 && arr[0] == '!') {
        Exit = false;
    } else if (arr.length() == 1) {
        cout << "In array one element : " << arr << "\n\n\n";
    } else if (arr.length() == 0) {
        cout << "\nAmount of elements: " << arr.length() << "\n";
        cout << "Empty array!\n\n\n";
    } else {
        cout << "\nAmount of elements: " << arr.length() << '\n';
        cout << "What indexes can we go by:\n1) even/odd\n2) odd/even\n";
        oddEvenSorting(arr, arr.length());
        if(!choise) {
            writeToFile("output.txt", "\nSorted array is: ");
            writeToFile("output.txt", arr);
        }
        cout << "Sorted array is: " << arr << "\n____________________________________________\n\n";
    }
}

int main() {
    bool Exit = true;
    bool choise = true;
    cout << "Enter : 0 - File Input, 1 - Console input: ";
    cin>>choise;
    cin.ignore();
    cout<<'\n';
    if(!choise){
         //-----Ввод с файла-----//
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
            string s = "";

            getline(in, s);
            writeToFile("output.txt", "Initial array: ");
            writeToFile("output.txt", s);
            CheckTheInput(s,Exit,choise);

        }
        else {
            cout << input_filename << " doesn't exist!\n";
        }

    }else {
        string arr = "";
        while (Exit) {
            cout << "Input data or \'!\' to quit: ";
            getline(cin, arr);
            CheckTheInput(arr, Exit,choise);
        }
    }
    getch();
    return 0;
}
