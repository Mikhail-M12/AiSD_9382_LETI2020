#include <iostream>

#include <bits/stdc++.h>

#define INF 1215752192
using namespace std;
template < typename T >
  void mergesort(int n, T inp[]) {
    T first[n]; //первая шина
    T second[n]; //вторая шина
    int cf = 0; //счетчик первой шины
    int cs = 0; //счетчик второй шины
    bool tape = true; //счетчик,показывающий,и какую шину используем
    int subarray = 0; //счетчик конца отсортированных под массивов
    queue < int > qfirst; //очередь концов отсортированных подмассивов первой шины
    queue < int > qsecond; //очередь концов отсортированных подмассивов второй шины
    int a = 0, b = 0;
    do {
      for (int i = 0; i < n; i++) {
        first[i] = INF; //заполняем шины большими числами
        second[i] = INF;
      }
      for (int i = 0; i < n; i++) //проходимся помассиву ищем все отсортированные подмассивы
      {
        if (tape) //записываем подмассивы, меняя шины
        {
          first[cf] = inp[i];
          cf++;
        } else {
          second[cs] = inp[i];
          cs++;
        }
        if (i != n - 1) {
          if (inp[i + 1] < inp[i]) {
            if (tape) {
              qfirst.push(cf - 1); //запоминаем концы подмассивов

            } else {

              qsecond.push(cs - 1); //запоминаем концы подмассивов

            }
            tape = !tape; //меняем шину
          }
        } else {
          if (tape) {
            qfirst.push(cf - 1);
          } else {
            qsecond.push(cs - 1);
          }
        }
      }
      if (second[0] != INF) //если массив еще не отсортирован
      {
        for (int i = 0; i < n; i++) {
          if (subarray == 0) {
            inp[i] = min(first[a], second[b]); //заполняем массив,выби рая минимальный изд вух сравниваемых
            if (inp[i] == first[a]) {
              a++;
              if (qfirst.empty() || qfirst.front() == a - 1) //если закончился подмассив напервой шине
              {
                subarray = 1;
                qfirst.pop();
              }
            } else {
              b++;
              if (qsecond.empty() || qsecond.front() == b - 1) //если закончился подмассив на второй шине
              {
                subarray = 2;
                qsecond.pop();
              }
            }
          } else {
            if (subarray == 1) //если закончился подмассив на первой шине
            {
              inp[i] = second[b];
              b++;
              if (qsecond.empty() || qsecond.front() == b - 1) {
                subarray = 0;
                qsecond.pop();
              }
            }
            if (subarray == 2) //если закончился подмассив на второй шине
            {
              inp[i] = first[a];
              a++;
              if (qfirst.empty() || qfirst.front() == a - 1) {
                subarray = 0;
                qfirst.pop();
              }
            }
          }
        }
      }
      tape = true; //обнуляем переменные
      subarray = 0;
      a = 0;
      b = 0;
      cf = 0;
      cs = 0;
    }
    while (second[0] != INF); //повторяем, пока массив не будет отсортирован
  }

int main() {
  ifstream fin("test.txt");
  int n;
  while (fin >> n) {
    if(n < 0){
      cout<<"Размер массива не может быть отрицательным\n";
      return 0;
    }
    else{
    int inp[n];
    for (int i = 0; i < n; i++) {
      fin >> inp[i]; //считываем массив
    }
    cout << "Your array: ";
    for (int i = 0; i < n; i++) {
      cout << inp[i] << " ";
    }
    cout << "\n";
    mergesort(n, inp);
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
      cout << inp[i] << " ";
    }
    cout << "\n\n";
    fin >> n;
  }
  }
  
  fin.close();
  return 0;
}
