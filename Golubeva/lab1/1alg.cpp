#include "name.hpp"

void change_elements(int& a, int& b){//меняем местами элементы
	int c;
	c=a;
	a=b;
	b=c;
}

bool my_isdigit(string s){//проверка строки, состоит ли она из цифр
	for (int i=0;i<s.length();i++){
		if (!isdigit(s[i]))
		return false;	
	}
	return true;
}

void my_permutation(string s, int* array, int numer, int count){//функция генерации номеров перестановок и вывод по значению
	
	cout<<' ';
	if (numer == count){
		cout<<' ';
		/*for (int i=0;i<numer;i++){
			cout<<' ';
	
		
		}*/
		cout<<" Numer of digits: ";
		
		
		for (int i=0;i<count;i++){// вывод перестановки массива с номерами на экран и запись в файл
			cout<<*(array+i)<<' ';
			
		}
		cout<<"Permutation: ";
		
		for (int i=0;i<count;i++){//вывод перестановки на экран и запись в файл
			cout<<s[*(array+i)];
	
		}
		cout<<'\n';
	
	}		
	else{
		for (int j=numer; j<count; j++){
			change_elements(*(array+numer), *(array+j));
			
			my_permutation(s, array, numer+1, count);//вызов рекурсивной функции
			change_elements(*(array+numer), *(array+j));
		}
	}
}

int main(){

	string n;
	cout<<"Введите количество перестановок, которые нужно считать из файла: ";
	cin>>n;
	cout<<'\n';

	while(!my_isdigit(n)){
		cout<<"Incorrect value of n. Try again\n";//проверка на корректность введённых значений

		cin>>n;
		cout<<'\n';
	
		
		}

	int p=stoi(n);
	ifstream temp("test.txt");

	string s; 
	//int n=0;
	int j=0;
	if (temp.is_open()){//открываем файлы для записи и чтения
		while(temp>>s && j<p){//извлечение данных из файла
			cout<<"Current sequence is: "<<s<<'\n';
			int count=s.length();
			int *array= new int(count);//массив для номеров элементов строки
		
			for (int i=0; i<count;i++)
				array[i]=i;
			my_permutation(s, array, 0, count);//генерируем перестановки для искомой строки из файла
			j+=1;
			delete[] array;
			cout<<'\n';
		}
	}
	else{
		cout<<"Problem with opening test.txt";
	}
	
	temp.close();
	
	return 0;
}


