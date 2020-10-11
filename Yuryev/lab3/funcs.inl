
template<typename T>
bool is_nullptr(BTree<T>* a) // проврка указателя на nullptr
{return a == nullptr;}

template<typename T>
BTree<T>* ConsBT(const T x, BTree<T>* lst,  BTree<T>* rst) // объединение корня и 2 деревьев в 1
{	
    BTree<T>* p = nullptr;
	p = new BTree<T>;

	if (!is_nullptr(p))	
    { 	
		p->m_BTroot = x;
		p->m_l_tree = lst;
		p->m_r_tree = rst;
		return p;
	}
	else 
    {
        cerr << "Memory error!\n"; 
        exit(1);
    }
}

template<typename T>
void destroy (BTree<T>* b) // рекурсивная очистка дерева
{
    if (!is_nullptr(b))
    {
		destroy (b->m_l_tree);  // рекурсивно удалим оба поддерева
		destroy (b->m_r_tree);
		delete b;               // и очистим память для самого дерева
		b = nullptr;
	}
}

template<typename T>
BTree<T>* readBT() // считывает дерево заданное с помощью '/'
{	
	T ch;
	BTree<T> *p, *q;
	cin >> ch;

	if (ch == '/') 
		return nullptr;
	else 
	{
		p = readBT<T>(); // будущее левое дерево
		q = readBT<T>(); // будущее правое дерево
		return ConsBT(ch, p, q);
	}
}

template<typename T>
void writeBT(BTree<T> *b) 
{	
	if (!is_nullptr(b)) 
    {
		cout << b->get_BTroot();
		writeBT(b->get_left());
		writeBT(b->get_right());
	}
	else cout << '/';
}


