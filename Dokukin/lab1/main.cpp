#include <iostream>
#include <string>
#include <fstream>

bool isUnsignedInt(std::string str, int depth = 0){ //Проверяем, является ли целым беззнаковым ( РЕКУРСИВНАЯ: целое_беззнаковое := цифра || цифра целое_беззнаковое )
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

bool isSignedInt(std::string str){ //Проверяем, является ли целым знаковым ( целое := целое_беззнаковое || +целое_беззнаковое || -целое_беззнаковое )
	if ( (str[0] == '+' || str[1] == '-') && str.length() == 1 ) return false; 										// Если в строке только "+" или "-" - неверный формат.
	if ( (int)str[0] > 47 && (int)str[0] < 58 && str.length() == 1 ) return true; 										  								
	if ( (str[0] == '+' || str[1] == '-') && str.length() > 1 ) return isUnsignedInt(str.substr(1, str.length() - 1)); // Если в строке "+" или "-"
	if ( (int)str[0] > 47 && (int)str[0] < 58 )  return isUnsignedInt(str.substr(1, str.length() - 1));				   // или цифра на 1 позиции, передаём строку без первого символа в isUnsignedInt
}

bool isReal(std::string str){ // Проверяем, является ли вещественным ( Вещественное := целое.целое_беззнаковое || целое.целое_беззнаковоеЕцелое || целоеЕцелое )
	int dotpos = str.find("."), epos = str.find("E");
	std::string str1, str2, str3;
	int npos = std::string::npos;
	std::cout<<"dotpos = "<<dotpos<<' '<<"epos = "<<epos<<'\n';
	if ( dotpos > epos && epos != npos ) return false; 							// Если есть и точка, и Е, и точка идёт после Е - неверный формат.
	if ( dotpos == 0 && epos == 0) 		 return false; 							// Если точка или Е в самом начале - неверный формат.
	if ( dotpos + 1 == epos ) 			 return false; 							// Если между точкой и Е ничего нет - неверный формат.
	if ( dotpos == str.length() - 1 || epos == str.length() - 1 ) return false; // Если после точки или Е идёт конец строки - неверный формат.
	//Разбиваем на подстроки
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
	int a = 0; // Выбор опции ввода
	
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
