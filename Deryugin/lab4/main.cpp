#include <iostream>
#include <fstream>
using namespace std;

void cycleSort(int lengthOfArray, int *arr) {
    string circle = "(";
    int value, pos, extra;// value - buffer value; pos - current position; extra - extra variable for swap
    for (int cycleStart = 0; cycleStart < lengthOfArray; cycleStart++) {
        value = arr[cycleStart];
        pos = cycleStart;
        cout<<"Current value "<<value<<". Current position: "<<pos<<endl;
        for (int i = cycleStart + 1; i < lengthOfArray; i++)// search for number which less then value
            if (arr[i] < value) pos+= 1;
        if (pos == cycleStart) {// if current value on the position
            cout<<"This value on the position\n";
            continue;
        }
        while (value == arr[pos]) pos+= 1;// continue if value == next position
        cout<<"New position of this value is "<<pos<<endl;
        // swap variables
        circle+= to_string(value) + ", ";
        extra = arr[pos];
        circle+=to_string(extra) + ", ";
        arr[pos] = value;
        value = extra;
        //start circle
        while (pos != cycleStart) {
            cout<<"Current value "<<value<<". Current position: "<<pos<<endl;
            pos = cycleStart;
            for (int i = cycleStart + 1; i < lengthOfArray; i++) // search for number which less then value
                if (arr[i] < value) pos+= 1;
            while (value == arr[pos]) pos+= 1;// continue if value == next position
            cout<<"New position of this value is "<<pos<<endl;
            //swap variables
            extra = arr[pos];
            arr[pos] = value;
            value = extra;
            circle+= to_string(extra);
            if (pos != cycleStart) circle+= ", ";
        }
        cout<<"Circle is "<<circle<<")"<<endl<<endl;
        circle = "(";
    }

    for (int i = 0 ; i < lengthOfArray; i ++) {
        cout<<arr[i]<<" ";
    }
}


int main() {
    int lengthOfArray;// length of array
    int index = 0;// index of array
    string path = "input.txt";// path to input file
    int typeOfInput;// 1 if console
    do {//while length<0
        cout<<"Enter length of array"<<endl;
        cin>>lengthOfArray;
    } while (lengthOfArray < 0);

    int array[lengthOfArray];
    cout<<"Enter '1' if you wanna write down array in console otherwise write down any letter or number:\n";
    cin>>typeOfInput;
    //input from console
    if (typeOfInput == 1) {
        for (int i = 0; i < lengthOfArray; i++) {
                cin>>array[i];
        }
    }
    else {
        //open file
        ifstream fin;
        fin.open(path);
        //if cannot open file
        if (!fin.is_open()) {
            cout<<"Cannot open file";
            exit(1);
        }
        //reading file line by line
        while(!fin.eof()) {
            fin>>array[index];
            index++;
        }
        fin.close();//close file
    }
    cycleSort(lengthOfArray, array);//sort func
    return 0;
}
