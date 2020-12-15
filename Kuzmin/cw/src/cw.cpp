#include "cw.h"


QString convertedString(const char* text);
const char* getFileText(const char* filename);
cw::cw(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);

	this->setMinimumSize(800, 600);

	//окно для ввода элемента
	input = new QLineEdit(this);
	input->setGeometry(QRect(400, 0, 100, 60));
	input->setFont(QFont("Tahoma", 13, 13));
	input->setFocus();

	//регулярные выражения для проверки корректности ввода
	elemRegExp = QRegExp("\\s*\\(\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*\\)\\s*");
	treapRegExp = QRegExp("(\\s*\\(\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*\\)\\s*)*");
	

	//окно для вывода содержимого файла
	fileTextLabel = new QLabel(this);
	fileTextLabel->setGeometry(QRect(0, 650, 800, 60));

	//обработка файла
	std::ifstream fs("treap.txt");
	if (!fs.fail()) {
		fs.close();
		QString treapElems(getFileText("treap.txt"));
		fileTextLabel->setText(convertedString("Содержимое файла: ") + treapElems);
		bool correctTreap = treapRegExp.exactMatch(treapElems);
		if (!correctTreap) {

			fileTextLabel->setText(fileTextLabel->text() + convertedString("\nНекорректный ввод элементов дерамиды"));
			fileTextLabel->setText(fileTextLabel->text() + convertedString("\nПостроена пустая дерамида"));
		}
		else {
			std::ifstream ifs("treap.txt");
			fileTextLabel->setText(fileTextLabel->text() + convertedString("\nДерамида построена"));
			treap.read(ifs);
			ifs.close();
		}
	}
	else fileTextLabel->setText(convertedString("Не удалось открыть файл\n Построена пустая дерамида"));

	fileTextLabel->setFont(QFont("Tahoma", 13, 13));

	//инструкция для ввода
	inputLabel = new QLabel(this);
	inputLabel->setGeometry(QRect(0, 0, 500, 60));
	inputLabel->setText(convertedString("Введите элемент в \nформате (ключ, приоритет)"));
	inputLabel->setFont(QFont("Tahoma", 13, 13));

	//отображаение текущего действия
	actionLabel = new QLabel(this);	
	actionLabel->setGeometry(QRect(650, 40, 1300, 60));
	actionLabel->setAlignment(Qt::AlignTop);
	actionLabel->setFont(QFont("Tahoma", 13, 13));

	//отображение текущего статуса
	statusLabel = new QLabel(this);
	statusLabel->setGeometry(QRect(650, 0, 1200, 60));
	statusLabel->setAlignment(Qt::AlignTop);
	statusLabel->setFont(QFont("Tahoma", 13, 13));
	
	//кнопка для вставки элемента
	insertButton = new QPushButton("INSERT", this);
	insertButton->setGeometry(QRect(0, 120, 100, 50));
	connect(insertButton, SIGNAL(clicked()), this, SLOT(insertButtonClicked()));
	insertButton->setFocusPolicy(Qt::ClickFocus);

	//кнопка для удаления элемента
	deleteButton = new QPushButton("DELETE", this);
	deleteButton->setGeometry(QRect(120, 120, 100, 50));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
	deleteButton->setFocusPolicy(Qt::ClickFocus);
}

//функция осуществляющая задержку приложения(используется при визулизации)
void cw::DelayMs(int ms) {
	QTime dieTime = QTime::currentTime().addMSecs(ms);
	while (QTime::currentTime() < dieTime) {
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}

//получение содержимого файла, с которого вводится дерамида
const char* getFileText(const char* filename){
	std::ifstream f(filename);
	char* tmp = new char[200];
	char d;
	int i = 0;
	while (f.get(d)) tmp[i++] = d;
	tmp[i] = '\0';
	f.close();
	return tmp;
}
//графическое изображение ребра между узлами
void connectElemes(QPainter* painter, TreapElem* e1, TreapElem* e2, QRect qr1, QRect qr2) {
	if (e1 && e2) {
		QPointF f1(qr1.center().x(), qr1.center().y() + 25);
		QPointF f2(qr2.center().x(), qr2.center().y() - 25);;

		painter->drawLine(f1, f2);
	}
}
//графическое изображение элемента и его потомков
void cw::paintElem(QPainter* painter, TreapElem* e, QRect* qr, float xcoef = 150){
	if (e){
		painter->setBrush(e->color);
		painter->setPen(Qt::black);
		painter->drawEllipse(*qr);
		painter->setBrush(Qt::white);
		painter->drawText(*qr, Qt::AlignCenter, *e);
		connectElemes(painter, e, e->left, *qr, QRect(qr->x() - xcoef, qr->y() + 100, qr->width(), qr->height()));
		paintElem(painter, e->left, new QRect(qr->x() - xcoef, qr->y() + 100, qr->width(), qr->height()), xcoef / 3 * 2);
		connectElemes(painter, e, e->right, *qr, QRect(qr->x() + xcoef, qr->y() + 100, qr->width(), qr->height()));
		paintElem(painter, e->right, new QRect(qr->x() + xcoef, qr->y() + 100, qr->width(), qr->height()), xcoef / 3 * 2);
	}
	else return;
}

//функция, графически изображающая дерамиду
void cw::paintTreap(QPainter* painter, Treap treap){
	
	this->paintElem(painter, treap.root, new QRect(this->width()/2 , 200, 50, 50), 256);
}

//событие, при котором отрисовывается дерамида, вызывается по мере выполнения операций
void cw::paintEvent(QPaintEvent *event){

	QPainter* painter = new QPainter(this);
	paintTreap(painter, treap);
}
//функция, возвращающая корректный кириллический текст
QString convertedString(const char* s){
	QTextCodec *codec1 = QTextCodec::codecForName("CP1251");
	QString text = codec1->toUnicode(s);
	return text;
}
//покраска элемента и его потомков в какой-то один цвет
void colorRecursively(QColor color, TreapElem*& e) {
	if (e) {
		e->color = color;
		colorRecursively(color, e->left);
		colorRecursively(color, e->right);
	}
	else return;
}
//визулизированный поворот налево
 void cw::visualisedRotateLeft(TreapElem*& el) {

	TreapElem* newEl = el->right;
	colorRecursively(Qt::yellow, newEl);
	colorRecursively(QColor(200, 200, 200), newEl->left);
	colorRecursively(QColor(100, 120, 33, 127), el->left);
	el->color = QColor(255, 0, 0, 127);
	update();
	DelayMs(mDelay);
	el->right = newEl->left;
	newEl->left = el;
	el = newEl;
	update();
	DelayMs(mDelay);
	colorRecursively(Qt::white, newEl);
	el->color = Qt::white;
	update();	
}
 
//визуализированный поворот направо
 void cw::visualisedRotateRight(TreapElem*& el) {
	
	TreapElem* newEl = el->left;
	colorRecursively(Qt::yellow, newEl);
	colorRecursively(QColor(200, 200, 200), newEl->right);
	colorRecursively(QColor(100, 120, 33, 127), el->right);
	el->color = QColor(255, 0, 0, 127);
	update();
	DelayMs(mDelay);
	el->left = newEl->right;
	newEl->right = el;
	el = newEl;
	update();
	DelayMs(mDelay);
	colorRecursively(Qt::white, newEl);
	el->color = Qt::white;
	update();

}
 //визулизация удаления элемента из дерамиды
void cw::visualisedInsert(TreapElem*& root, TreapElem a) {
	

	actionLabel->setText(convertedString("Просмотр текущего узла"));
	if (root == nullptr){
		actionLabel->setText(convertedString("Встречен пустой узел. Создание элемента ") + QString(a)
		+ convertedString(" на его месте"));
		root = new TreapElem(a);
		root->color = QColor(0, 0, 255, 127);
		update();
		DelayMs(mDelay);
		root->color = Qt::white;
		return;
	}
	root->color = Qt::green;
	update();
	DelayMs(mDelay);

	//сравнения ключа искомого элемента с ключом текущего узла
	if (a.key < root->key) {
		actionLabel->setText(convertedString("Значение ключа вставляемого элемента ") + QString(a)
		+ convertedString(" меньше значения ключа текущего элемента ") + QString(*root)
		+ convertedString("\nПереход к левому потомку"));

		DelayMs(mDelay);
		root->color = Qt::white;
		update();
		visualisedInsert(root->left, a);
	}
	//если ключ вставляемого элемента больше (или равен) ключа текущего элемента
	else{
		actionLabel->setText(convertedString("Значение ключа вставляемого элемента ") + QString(a)
		+ convertedString(" больше(или равно) значения ключа текущего элемента ") + QString(*root)
		+ convertedString("\nПереход к правому потомку"));

		DelayMs(mDelay);
		root->color = Qt::white;
		update();
		visualisedInsert(root->right, a);
	}

	//повороты (если требуется)
	if (root->left && root->left->prior > root->prior) {
		actionLabel->setText(convertedString("Значение приоритета левого потомка ") + QString(*root->left)
		+ convertedString(" больше чем значение приоритета текущего элемента ") + QString(*root)
		+ convertedString("\nОсуществляется поворот направо\n"));

		visualisedRotateRight(root);
		update();
	}

	if (root->right && root->right->prior > root->prior) {
		actionLabel->setText(convertedString("Значение приоритета правого потомка: ") + QString(*root->right) 
		+ convertedString(" больше чем значение приоритета текущего элемента ") + QString(*root)
		+ convertedString("\nОсуществляется поворот налево\n"));
		
		visualisedRotateLeft(root);
		update();
	}
}

//визулизированное удаление элемента из дерамиды
void cw::visualisedDelete(TreapElem*& root, TreapElem a) {

	//если элемента нет в дерамиде
	if (root == nullptr){
		return;
	}
	root->color = Qt::green;
	update();
	actionLabel->setText(convertedString("Просмотр текущего элемента"));
	DelayMs(mDelay);
	root->color = Qt::white;
	if (a.key == root->key && a.prior == root->prior) {
		actionLabel->setText(convertedString("Обнаружено совпадение с искомым элементом."));
		root->color = QColor(204, 102, 153);
		update();
		DelayMs(mDelay);
		//если элемент является листом, то он просто удаляется
		if (isLeaf(root)) {
			actionLabel->setText(convertedString("Элемент является листом. Дополнительных изменений структуры дерамиды не требуется"));
			actionLabel->setText(actionLabel->text() + convertedString("\nУдаление элемента"));
			DelayMs(mDelay);
			root = nullptr;
		}
		//если элемент имеет двух потомков, то необходимо произвести повороты, пока этот элемент не станет
		//либо листом, либо узлом с только одним потомком
		else if (root->left && root->right){
			actionLabel->setText(convertedString("Элемент имеет двух потомков. Необходимо произвести повороты."));
			DelayMs(mDelay);

			// в случае, если у левого потомка приоритет ниже, чем у правого, осуществляется поворот направо
			if (root->left->prior < root->right->prior){

				actionLabel->setText(convertedString("Правый потомок элемента имеет больший приоритет, чем левый\n"));
				actionLabel->setText(actionLabel->text() + convertedString("Осуществляется поворот налево"));
				// Поворот налево
				visualisedRotateLeft(root);

				// Прежний элемент теперь на месте левого потомка, выполняем его удаление
				visualisedDelete(root->left, a);
			}
			//если у правого потомка больший приоритет, то тогда делается поворот налево
			else{
				actionLabel->setText(convertedString("Левый потомок элемента имеет меньший приоритет, чем правый\n"));
				actionLabel->setText(actionLabel->text() + convertedString("Осуществляется поворот направо"));
				// Поворот налевo
				visualisedRotateRight(root);

				// Прежний элемент теперь на месте левого потомка, выполняем его удаление
				visualisedDelete(root->right, a);
			}
		}
		//удаление узла с одним потомком
		else{
			actionLabel->setText(convertedString("Элемент имеет одного потомка"));
			TreapElem* child = (root->left) ? root->left : root->right;
			colorRecursively(QColor(150, 150, 150), child);
			update();
			DelayMs(mDelay);
			root = child;
			actionLabel->setText(convertedString("Присваивание текущему элементу значение его потомка"));
			update();
			DelayMs(mDelay);
		}
		//покраска элемента, стоящего на месте удаленного, в белый цвет
		if (root) colorRecursively(Qt::white, root);
		return;
	}
	//если совпадения текущего элемента с искомым нет, то далее в зависимости от
	//приоритета производится обход следующих узлов
	if (a.key < root->key) {
		actionLabel->setText(convertedString("Значение ключа вставляемого элемента - ") + QString(a)
			+ convertedString(" меньше значения ключа текущего элемента - ") + QString(*root) +
			convertedString("\nПереход к левому потомку"));
		DelayMs(mDelay);
		visualisedDelete(root->left, a);
	}
	else {
		actionLabel->setText(convertedString("Значение ключа вставляемого элемента - ") + QString(a)
			+ convertedString(" больше значения ключа текущего элемента - ") + QString(*root) +
			convertedString("\nПереход к правому потомку"));
		DelayMs(mDelay);
		visualisedDelete(root->right, a);
	}
}
//обработчик нажатия на кнопку удаления
void cw::deleteButtonClicked() {

	
	bool correct = elemRegExp.exactMatch(input->text());//проверка ввода при помощи регулярного выражения
	if (correct) { //если ввод корректен, запускается алгоритм удаления, кнопки для удаления и вставка становятся неактивными
				   //как и окно для ввода элемента
		input->setDisabled(1);
		int h = elemRegExp.cap(2).toInt();
		int g = elemRegExp.cap(1).toInt();
		TreapElem ex(g, h);
		if (treap.find(treap.root, ex) != 0) {
			deleteButton->setDisabled(1);
			insertButton->setDisabled(1);
			statusLabel->setText(convertedString("Удаление элемента") + QString(ex));
			visualisedDelete(treap.root, ex);
			actionLabel->setText(convertedString(""));
			statusLabel->setText(convertedString("Удаление завершено"));
			update();
		}
		else statusLabel->setText(convertedString("Элемент не присутствует в дерамиде"));
	}
	else statusLabel->setText(convertedString("Некорректный ввод"));
	deleteButton->setDisabled(0);
	insertButton->setDisabled(0);
	input->setDisabled(0);
	input->setFocus();
}
//обработчик нажатия на кнопку вставки
void cw::insertButtonClicked(){

	bool correct = elemRegExp.exactMatch(input->text()); //проверка ввода при помощи регулярного выражения
	if (correct) { //если ввод корректен, запускается алгоритм вставки, кнопки для удаления и вставка становятся неактивными
				   //как и окно для ввода элемента
		deleteButton->setDisabled(1); 
		insertButton->setDisabled(1);
		input->setDisabled(1);
		int h = elemRegExp.cap(2).toInt();
		int g = elemRegExp.cap(1).toInt();
		TreapElem ex(g, h);
		statusLabel->setText(convertedString("Вставка элемента") + QString(ex));
		visualisedInsert(treap.root, ex);
		actionLabel->setText(convertedString(""));
		statusLabel->setText(convertedString("Вставка завершена"));
		update();
	}		//иначе выводится сообщение об этом
	else statusLabel->setText(convertedString("Некорректный ввод"));

	deleteButton->setDisabled(0);
	insertButton->setDisabled(0);
	input->setDisabled(0);
	input->setFocus();
}