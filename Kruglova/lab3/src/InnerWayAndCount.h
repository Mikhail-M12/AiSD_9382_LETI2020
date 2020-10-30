class InnerWayAndCount
{ // здесь нет сложных данных, поэтому прописывать иные конструкторы нет нужды (копирование и так будет работать нормально)
private: 
    int m_count; // количество узлов в дереве
    int m_innerWay; // внутренний путь дерева
public:
    InnerWayAndCount(); // конструктор создания со списком инициализации

    int getCount();
    int getInnerWay();
    void addCount(int k);
    void addInnerWay(int k);
};
