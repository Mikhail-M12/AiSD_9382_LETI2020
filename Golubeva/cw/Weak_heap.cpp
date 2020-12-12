#include "Weak_heap.h"
#include <limits>
#include <cstring>
#include <cctype>

#define GETFLAG(r, x) ((r[(x) >> 3] >> ((x) & 7)) & 1) //если в качестве "левого" потомка родителя

#define TOGGLEFLAG(r, x) (r[(x) >> 3] ^= 1 << ((x) & 7)) //Для потомка переопределяем, порядок его потомков
    //(кто "левый", а кто "правый")


WeakHeap::~WeakHeap(){
  if (!wheap.empty())
    wheap.clear();    
}

//вычисляет логарифм от b по основанию a
double log(int a, int b)
{
    return log(b) / log(a);
}

//проверяет, что строка состоит из цифр
bool str_is_digit(std::string s){

  int size=s.size();

  int j=0;

  if (s[0]=='-'){
      j+=1;
            
  }
 
  for (int i=j;i<size;i++){

      if (!isdigit(s[i])){

          return false;
          }
  }

  return true;
}


void WeakHeap::displayHeap(int i_1, int j_1, int col, int num){

    std::vector <int> heap1;
    heap1.push_back(wheap[0]);
    heap1.push_back(wheap[1]);
    for (int i=0;i<s;i++){//записываем элементы в кучу в порядке, удобном для вывода на экран 
        heap1.push_back(wheap[2*i+r[i]]);
        heap1.push_back(wheap[2*i+1-r[i]]);

    }
    if (col==0){
      if (i_1==0 || j_1==0)
        std::cout<<"\x1b[32m"<<wheap[0]<<"\x1b[0m";
      else  
        std::cout<<wheap[0];
    }
    else
    {
      if (i_1==0 || j_1==0)
        std::cout<<"\x1b[34m"<<wheap[0]<<"\x1b[0m";
      else  
        std::cout<<wheap[0];
    }
       
    std::cout<<"\n";
    int new_size=size-num;

    int depth=(int)log(2, new_size);//вычисляем глубину дерева
    if ((int)log(2, new_size)!=pow(2, depth))
        depth+=1;
    
    int k=0;
  

    for (int i=0;i<depth;i++){

      for (int j=0;j<pow(2,i);j++){
        if (k<new_size)
          if (col==0){//проверяем, какого цвета выводить элементы
              if (k+1==i_1 || k+1==j_1){
                std::cout<<"\x1b[32m"<<wheap[k+1]<<"\x1b[0m"<<"  ";
              
              }
              
              else{
                std::cout<<wheap[k+1]<<"  ";
                
              }
            }
          else
          {
          if (k+1==i_1 || k+1==j_1){
              std::cout<<"\x1b[34m"<<wheap[k+1]<<"\x1b[0m"<<"  ";
              
            }
            
            else{
              std::cout<<wheap[k+1]<<"  ";
              
            }
          }
          k++;
        }
        
        std::cout<<"\n";   
          
    }

  if (num>1){
    std::cout<<"\n";
    std::cout<<"Отсортированная часть массива: ";
    for (int i=1;i<num;i++)
        std::cout<<"\x1b[33m"<<wheap[new_size+i]<<"\x1b[0m"<<"  ";
    std::cout<<"\n";
  }

  if (col==0)
    std::cout<<"---------------------------------------------------------------\n";   
  else
    std::cout<<"\n";
 
}


void WeakHeap::displayHeap(){

  std::vector <int> heap1;
  heap1.push_back(wheap[0]);
  heap1.push_back(wheap[1]);
  for (int i=0;i<s;i++){//записываем элементы в кучу в порядке, удобном для вывода на экран 
      heap1.push_back(wheap[2*i+r[i]]);
      heap1.push_back(wheap[2*i+1-r[i]]);

  }
  std::cout<<wheap[0];
  std::cout<<"\n";
  
  int depth=(int)log(2, size);//вычисляем глубину дерева
  if ((int)log(2, size)!=pow(2, depth))
    depth+=1;
  
  int k=0;

  for (int i=0;i<depth;i++){
      
        for (int j=0;j<pow(2,i);j++){
            if (k<size-1)
                std::cout<<wheap[k+1]<<"  ";
            k++;   
        }
        std::cout<<"\n";     
  }
    std::cout<<"---------------------------------------------------------------\n";
}

void WeakHeap::weakHeapMerge(unsigned char *r, int i, int j, int num) {


    if (wheap[i] < wheap[j]) {//"Суперродитель" меньше потомка?
        //Для потомка переопределяем, порядок его потомков
        //(кто "левый", а кто "правый")

        TOGGLEFLAG(r, j);
        //Меняем значения "суперродителя" и потомка
        this->displayHeap(i, j, 1, num);
        std::cout<<"Суперродитель "<<wheap[i]<<" меньше потомка "<<wheap[j]<<", меняем их местами\n";
        
        std::swap(wheap[i], wheap[j]);
        this->displayHeap(i, j, 0, num);
    
    }
    else{
        this->displayHeap(i, j, 1, num);
        std::cout<<"---------------------------------------------------------------\n";
    }
}

void WeakHeap::weakHeapSort() {
    int n = size;
    int lef;
    int per;
    if(n > 1) {
		
        int i, j, x, y, Gparent;
        s = (n + 7) / 8;
        r = new unsigned char [s];
            
        //Массив для обозначения, какой у элемента 
        //потомок "левый", а какой "правый"
        for(i = 0; i < n / 8; ++i) 
        r[i] = 0;
            

        std::cout<<"Построение первоначальной слабой кучи\n";

        //Построение первоначальной слабой кучи
        for(i = n - 1; i > 0; --i) {
            j = i;
        //Поднимаемся на сколько возможно вверх, 
        //если в качестве "левого" потомка родителя
            lef=GETFLAG(r, j >> 1);
            while ((j & 1) == lef) {
                j = j>> 1;
                lef=GETFLAG(r, j >> 1);
            }  
        //И ещё на один уровень вверх как "правый" потомок родителя
            Gparent = j >> 1;
        //Слияние начального элемента, с которого 
        //начали восхождение до "суперродителя"
            weakHeapMerge(r, Gparent, i, 1);
    }

    //Перенос максимума из корня в конец -->
    //слабая просейка --> и всё по новой
    std::cout<<"Слабая куча построена\n";
    this->displayHeap();
    
    for(i = n - 1; i >= 2; --i) {
        std::cout<<"Переносим максимум из корня, применяем слабую просейку\n";
        //Максимум отправляем в конец неотсортированной части массива
        //Элемент из конца неотсортированной части попадает в корень
            this->displayHeap(0, i, 1, n-i);
        std::cout<<"Переместили корень "<<wheap[0]<<" и элемент из конца неотсортированной части "<<wheap[i]<<"\n";
        std::swap(wheap[0], wheap[i]);
        this->displayHeap(0, i, 0, n-i);
        x = 1;
        //Опускаемся жадно вниз по "левым" веткам
        lef=GETFLAG(r, x);
        while((y = 2 * x + lef) < i) {
            x = y;
            lef=GETFLAG(r, x);
        }  
        //Поднимаемся по "левой" ветке обратно до самого вверха
        //попутно по дороге делаем слияние каждого узла с корнем
        while(x > 0) {
            weakHeapMerge(r, 0, x, n-i);
            x >>= 1;
        }
    }
    //Последнее действие - меняем местами корень
    //и следующий за ним элемент
    this->displayHeap(0, 1, 1, n-1);
    std::cout<<"Меняем местами корень "<<wheap[0]<<" и следующий за ним элемент "<<wheap[1]<<"\n";
    std::swap(wheap[0], wheap[1]);
    this->displayHeap(0, 1, 0, n-1);
    delete[] r;
  }
}
void WeakHeap::displayArray()
{
    for (int i=0;i<size;i++)
        std::cout<<wheap[i]<<" ";
    std::cout<<"\n\n";
}

WeakHeap* WeakHeap::consoleInputHeap(){
    int count=0;
    int member;
    std::string str;


    while (count<=0){
        std::cout<<"Введите количество элементов в массиве или введите Quit/Q/q для выхода в главное меню\n";

        std::cin>>str;
        if (str=="Q"||str=="Quit"||str=="q"){
            return nullptr;
        }
        try{
          count = std::stoi(str);
        }catch(std::invalid_argument&){
          std::cout<<"Вы ввели строку\n";
          continue;
        }
            if (count<=0)
                std::cout<<"Количество элементов должно быть положительным\n";
            
    }
    WeakHeap* wh=new WeakHeap();
    
    
    while(wh->size!=count){
        std::cout<<"Введите элементы через пробел(осталось ввести "<<count-wh->size<<" элементов)\n";
        std::cout<<"Введите элемент или введите Quit/Q/q для выхода в главное меню\n";
        std::cin>>str;
        if (str=="Q"||str=="Quit"||str=="q"){
            delete wh;
            return nullptr;
        }
        try{
          member = std::stoi(str);
        }catch(std::invalid_argument&){
          std::cout<<"Некорректное значение элемента"<<str<<"\n";
          continue;
        }
            wh->wheap.push_back(member);
            wh->size+=1;
        
    }
   
    return wh;
}

WeakHeap* WeakHeap::fileInputHeap(){
    int count=0;
    std::string str;
    std::ifstream file("input.txt");
    while(file.fail())
    try{
      //открываем файл для чтения
      if (file.fail())
        file.close();
        throw "Не удалось открыть файл\n";
        
    }
    catch(const char* s){
      std::cout<<s;
      std::string r;
      std::ifstream file("input.txt");
      std::cout<<"Исправьте файл, чтобы он открывался и сообщите об этом программе, введя какое-нибудь сообщение или введите Quit/Q/q для выхода в главное меню\n";
      std::cin>>r;
      if (r=="Q"||r=="Quit"||r=="q"){
            return nullptr;
        }

    }
    file>>str;

    try{
          count = std::stoi(str);
          if (count<=0){
            std::cout<<"Количество элементов должно быть положительным, невозможно продолжить ввод из файла\n\n";
            file.close();
            return nullptr;
        }

        }catch(std::invalid_argument&){
          std::cout<<"Некорректное значение количества элементов, невозможно продолжить ввод из файла\n\n";
          file.close();
          return nullptr;
        }

    WeakHeap* wh= new WeakHeap();
    for (int i=0;i<count;i++){
        file>>str;

        try{
            wh->wheap.push_back(std::stoi(str));
            wh->size+=1;
        }catch(std::invalid_argument&){
            std::cout<<"Некорректное значение элемента "<<str<<", невозможно продолжить ввод из файла\n\n";
            file.close();
            delete wh;
            return nullptr;
        }
    }
    file.close();
    return wh;
}