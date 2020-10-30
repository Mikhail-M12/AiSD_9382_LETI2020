#include "headers.h"

int InnerWayAndCount::getCount(){return m_count;};
int InnerWayAndCount::getInnerWay(){return m_innerWay;};
void InnerWayAndCount::addCount(int k){m_count += k;};
void InnerWayAndCount::addInnerWay(int k){m_innerWay += k;};

InnerWayAndCount::InnerWayAndCount(): m_count{1}, m_innerWay{0} // конструктор создания со списком инициализации
{}; 
