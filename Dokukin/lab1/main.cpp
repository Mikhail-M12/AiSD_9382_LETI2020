#include <iostream>
#include <string>
#include <fstream>

bool isUnsignedInt(std::string str, int depth = 0){ //���������, �������� �� ����� ����������� ( �����������: �����_����������� := ����� || ����� �����_����������� )
	for (int i = 0; i < depth; i++){
		std::cout<<"  ";
	}
	std::cout<<"Recursion depth: "<<depth+1<<", symbol to check: "<<str[0]<<'\n';
	if ( (int)str[0] > 47 && (int)str[0] < 58 ){
	if ( str.length() == 1 ) return true;
	else return isUnsignedInt(str.substr(1, str.length() - 1), ++depth);
	}
	else return false;
}

bool isSignedInt(std::string str){ //���������, �������� �� ����� �������� ( ����� := �����_����������� || +�����_����������� || -�����_����������� )
	if ( (str[0] == '+' || str[1] == '-') && str.length() == 1 ) return false; 										// ���� � ������ ������ "+" ��� "-" - �������� ������.
	if ( (int)str[0] > 47 && (int)str[0] < 58 && str.length() == 1 ) return true; 										  								
	if ( (str[0] == '+' || str[1] == '-') && str.length() > 1 ) return isUnsignedInt(str.substr(1, str.length() - 1)); // ���� � ������ "+" ��� "-"
	if ( (int)str[0] > 47 && (int)str[0] < 58 )  return isUnsignedInt(str.substr(1, str.length() - 1));				   // ��� ����� �� 1 �������, ������� ������ ��� ������� ������� � isUnsignedInt
}

bool isReal(std::string str){ // ���������, �������� �� ������������ ( ������������ := �����.�����_����������� || �����.�����_����������������� || ����������� )
	int dotpos = str.find("."), epos = str.find("E");
	std::string str1, str2, str3;
	int npos = std::string::npos;
	std::cout<<"dotpos = "<<dotpos<<' '<<"epos = "<<epos<<'\n';
	if ( dotpos > epos && epos != npos ) return false; 							// ���� ���� � �����, � �, � ����� ��� ����� � - �������� ������.
	if ( dotpos == 0 && epos == 0) 		 return false; 							// ���� ����� ��� � � ����� ������ - �������� ������.
	if ( dotpos + 1 == epos ) 			 return false; 							// ���� ����� ������ � � ������ ��� - �������� ������.
	if ( dotpos == str.length() - 1 || epos == str.length() - 1 ) return false; // ���� ����� ����� ��� � ��� ����� ������ - �������� ������.
	//��������� �� ���������
	if ( dotpos == npos && epos == npos ) str1 = str;
	if ( dotpos == npos && epos != npos ) str1 = str.substr(0, epos);
	if ( dotpos != npos ) str1 = str.substr(0, dotpos);
	if ( dotpos == npos ) str2 = "0";
	if ( dotpos != npos && epos == npos ) str2 = str.substr(dotpos + 1, str.length() - dotpos - 1);
	if ( dotpos != npos && epos != npos ) str2 = str.substr(dotpos + 1, epos - dotpos - 1);
	if ( epos == npos ) str3 = "0";
	if ( epos != npos ) str3 = str.substr(epos + 1, str.length() - epos - 1);
	std::cout<<"str1 = "<<str1<<", str2 = "<<str2<<", str3 = "<<str3<<'\n';
	return isSignedInt(str1) & isUnsignedInt(str2) & isSignedInt(str3);
}


int main(){
	std::string str;
	int a = 0; // ����� ����� �����
	
	std::ifstream f("tests.txt");
	
	std::cout<<"Choose input option(0 - file input; 1 - console input)\n";
	std::cin>>a;
	if (a){
		std::cin>>str;
		if (isReal(str)){
			std::cout<<str<<" is a real number.\n";
		}
		else{
		std::cout<<str<<" is not a real number.\n";
		}
		return 0;
	}
	if (!f){
		std::cout<<"Couldn't open file!\n";
		return 0;
	}
	while(!f.eof()){
		getline(f, str);
		std::cout<<str<<'\n';
		if (isReal(str)){
			std::cout<<str<<" is a real number.\n";
		}
		else{
			std::cout<<str<<" is not a real number.\n";
		}
		std::cout<<"--------------------------------\n";
	}
	return 0;
}
