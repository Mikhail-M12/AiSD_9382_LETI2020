#include "declaration.h"

using namespace std;
using namespace h_list;

	int main(){   	
	lisp s1;
	lisp s2;
	
	ifstream temp("t.txt");
	
	read_lisp (s1, temp);
	cout << "Ввёдён list1: " << endl;
	write_lisp (s1);
	cout << endl;
	
	read_lisp (s2, temp);
	cout << "Введён list2: " << endl;
	write_lisp (s2);
	cout << endl;

	temp.close();

	cout<<"\n";

	if (isAtom(s1)&&isAtom(s2)){
	    cout<<"Структурная идентичность списков: true\n";
	    destroy_2(s1, s2);
	    return 0;
	}    

	list_match1(s1, s2);
	
	destroy_2(s1, s2);
	
	return 0;
}
