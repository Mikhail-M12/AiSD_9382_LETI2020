// continue of namespace h_list
#include "declaration.h"


using namespace std;
namespace h_list
{

//....................................
	lisp head (const lisp s)
	{// PreCondition: not null (s)
		if (s != NULL) 
			if (!isAtom(s))	
				return s->node.pair.hd;
			else { 
				cerr << "Error: Head(atom) \n"; 
				exit(1); 
			}
		else { 
			cerr << "Error: Head(nil) \n";
			exit(1);
		}
	}
//.......................................
	bool isAtom (const lisp s){	
		if(s == NULL) //если список пустой то false
			return false;
		else 
			return (s -> tag);
	}
//.......................................
	bool isNull (const lisp s){ 
		return s==NULL;//возвращает сравнение с null
	}
//.......................................
	lisp tail (const lisp s)
{// PreCondition: not null (s)
		if (s != NULL) 
			if (!isAtom(s))//проверка на то, что это не атом
				return s->node.pair.tl;//возвращает хвост переданного списка
			else { 
				cerr << "Error: Tail(atom) \n"; 
				exit(1); 
			}
		else { 
			cerr << "Error: Tail(nil) \n";
			exit(1);
		}
	}
//.......................................
	lisp cons (const lisp h, const lisp t)
	// PreCondition: not isAtom (t)
	{lisp p;
	if (isAtom(t)) { 
		cerr << "Error: Tail(nil) \n"; 
		exit(1);
	}
	else {	
		p = new s_expr; 
		if ( p == NULL)	{
			cerr << "Memory not enough\n"; 
			exit(1); 
		} 	
		else {
			p->tag = false;
			p->node.pair.hd = h;
			p->node.pair.tl = t;
			return p;	
		}
	}
	}
//...........................
	lisp make_atom (const base x)
	{	lisp s;
		s = new s_expr;//выделяем память
		s -> tag = true;
		s->node.atom = x;//присваиваем переданное значение
		return s;
	}

//...........................
	void destroy (lisp s) 
	{
	if ( s != NULL) {
		if (!isAtom(s)) {
			destroy ( head (s));
			destroy ( tail(s));
		}
		delete s;
		// s = NULL;
		};
	}
//...........................

	void destroy_2(lisp x, lisp y){
		destroy (x);
		destroy (y);
		//совместили удаление двух списков, чтоб избежать излишнего дублирования в коде
	}	
	
	
//...........................
	base getAtom (const lisp s)
	{
		if (!isAtom(s)) { //проверка на то, атом ли это
			cerr << "Error: getAtom(s) for !isAtom(s) \n"; 
			exit(1);
		}
		else 
			return (s->node.atom);//выводит значения атома
	}

	
//...........................
// 
	void read_lisp ( lisp& y, ifstream& temp)
	{	base x;
		do 
			temp >> x; //читаем последовательность из файла
		while (x==' ');
			read_s_expr ( x, y, temp);
	} //end read_lisp
//...........................
	void read_s_expr (base prev, lisp& y, ifstream& temp)
	{ 
		if ( prev == ')' ) {
			cerr << " ! List.Error 1 " << endl; 
			exit(1); 
		} 
		else if ( prev != '(' ) 
			y = make_atom (prev);//создаём атом
		else 
			read_seq (y, temp);
	} //end read_s_expr
//...........................
	void read_seq ( lisp& y, ifstream& temp) 
	{	base x; 
		lisp p1, p2;


		if (!(temp >> x)) {//читаем последовательность из файла
			cerr << " ! List.Error 2 " << endl; 
			exit(1);
		}
		else {
			while  ( x==' ' ) 
				temp >> x;
			if ( x == ')' ) 
				y = NULL;
			else{
				read_s_expr ( x, p1, temp);
				read_seq ( p2, temp);
				y = cons (p1, p2);
			} 
		}
	} //end read_seq
//...........................

	void write_lisp (const lisp x)
	{ 
	if (isNull(x)) cout << " ()";
	else if (isAtom(x)) 
		cout << ' ' << x->node.atom;//выводим значение узла
		else  { 
			cout << " (" ;
			write_seq(x);//извлекаем данные из списка дальше
			cout << " )";
		}
	} // end write_lisp
//...........................
	void write_seq (const lisp x)  
	{
		if (!isNull(x)) {
			write_lisp(head (x)); 
			write_seq(tail (x));
		}
	}
//...........................
	void list_match1 (const lisp x, const lisp y){
		/*if (isNull(x)&&isNull(y)){
			cout << " ()\n";
			cout<<"Структурная идентичность списков: true\n";
			destroy_2(x, y);//очищаем память
			exit(1);
		}	
		else */if (isAtom(x)&&isAtom(y)) {
		
			
		}
			
			else  if (!(isAtom(x)||isAtom(y))){ 
		
				list_match2(x, y);//вызываем функцию для дальнейшей обработки списка
			
			}
			else {
				cout<<"Структурная идентичность списков: false\n";
				destroy_2(x,y);
				exit(1);
				
			}
			
} 
//...........................
	void list_match2 (const lisp x, const lisp y){		
		
		if ((isNull(x)&&!isNull(y))||((!isNull(x))&&isNull(y))){//проверка на то, закончилась ли проверка одного списка раньше другого
			cout<<"Структурная идентичность списков: false\n";
			destroy_2(x,y);
			exit(1);
		}	
			
		if ((isAtom(x)||isAtom(y))){//проверка на то, что в каком-то узле атом, а в каком-то список
			cout<<"Структурная идентичность списков: false\n";
			destroy_2(x,y);
			exit(1);	
		}
		
		if (isNull(x)&&isNull(y)){//если на данном этапе списки оба пустые, то они идентичны
			
			cout<<"Структурная идентичность списков: true\n";
			
			destroy_2(x,y);
			exit(1);
		}
			
		if (!isNull(x)&&!isNull(y)) {//рекурсивный вызов, если обработка не завершена
			list_match1(head (x), head(y)); 
			list_match2(tail (x), tail(y));
			
			
		}
	
	}


} // end of namespace h_list
