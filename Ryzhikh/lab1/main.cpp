#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void printer(int x)
{
	for (int i = 0; i < x; i++)
		cout << "    ";
	return;
}

void func(string a, int x, string* answ)
{
	printer(x);
	cout << "Now working with string: " << a << endl;
	if (a.empty())
	{
		*answ = a;
		printer(x);
		cout << "Returning string: " << a << endl;
		return;
	}
	if (a.find('/') == string::npos)
	{
		*answ = a;
		printer(x);
		cout << "Returning string: " << a << endl;
		return;
	}
	string b;
	b.append(a, a.find('/')+1);
	a.erase(a.find('/'));
	func(b, x+1, answ);
	*answ += a;
	printer(x);
	cout << "Returning string: " << a << endl;
	return;
}

int main()
{
	string a, answ;
	int x = 0;
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	getline(fin,a);
	func(a, x, &answ);
	fout << "Answer is: " << answ << endl;
	fin.close();
	fout.close();
	return 0;
}