#include "cw.h"


QString convertedString(const char* text);
const char* getFileText(const char* filename);
cw::cw(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);

	this->setMinimumSize(800, 600);

	//���� ��� ����� ��������
	input = new QLineEdit(this);
	input->setGeometry(QRect(400, 0, 100, 60));
	input->setFont(QFont("Tahoma", 13, 13));
	input->setFocus();

	//���������� ��������� ��� �������� ������������ �����
	elemRegExp = QRegExp("\\s*\\(\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*\\)\\s*");
	treapRegExp = QRegExp("(\\s*\\(\\s*(-?\\d+)\\s*,\\s*(-?\\d+)\\s*\\)\\s*)*");
	

	//���� ��� ������ ����������� �����
	fileTextLabel = new QLabel(this);
	fileTextLabel->setGeometry(QRect(0, 650, 800, 60));

	//��������� �����
	std::ifstream fs("treap.txt");
	if (!fs.fail()) {
		fs.close();
		QString treapElems(getFileText("treap.txt"));
		fileTextLabel->setText(convertedString("���������� �����: ") + treapElems);
		bool correctTreap = treapRegExp.exactMatch(treapElems);
		if (!correctTreap) {

			fileTextLabel->setText(fileTextLabel->text() + convertedString("\n������������ ���� ��������� ��������"));
			fileTextLabel->setText(fileTextLabel->text() + convertedString("\n��������� ������ ��������"));
		}
		else {
			std::ifstream ifs("treap.txt");
			fileTextLabel->setText(fileTextLabel->text() + convertedString("\n�������� ���������"));
			treap.read(ifs);
			ifs.close();
		}
	}
	else fileTextLabel->setText(convertedString("�� ������� ������� ����\n ��������� ������ ��������"));

	fileTextLabel->setFont(QFont("Tahoma", 13, 13));

	//���������� ��� �����
	inputLabel = new QLabel(this);
	inputLabel->setGeometry(QRect(0, 0, 500, 60));
	inputLabel->setText(convertedString("������� ������� � \n������� (����, ���������)"));
	inputLabel->setFont(QFont("Tahoma", 13, 13));

	//������������ �������� ��������
	actionLabel = new QLabel(this);	
	actionLabel->setGeometry(QRect(650, 40, 1300, 60));
	actionLabel->setAlignment(Qt::AlignTop);
	actionLabel->setFont(QFont("Tahoma", 13, 13));

	//����������� �������� �������
	statusLabel = new QLabel(this);
	statusLabel->setGeometry(QRect(650, 0, 1200, 60));
	statusLabel->setAlignment(Qt::AlignTop);
	statusLabel->setFont(QFont("Tahoma", 13, 13));
	
	//������ ��� ������� ��������
	insertButton = new QPushButton("INSERT", this);
	insertButton->setGeometry(QRect(0, 120, 100, 50));
	connect(insertButton, SIGNAL(clicked()), this, SLOT(insertButtonClicked()));
	insertButton->setFocusPolicy(Qt::ClickFocus);

	//������ ��� �������� ��������
	deleteButton = new QPushButton("DELETE", this);
	deleteButton->setGeometry(QRect(120, 120, 100, 50));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
	deleteButton->setFocusPolicy(Qt::ClickFocus);
}

//������� �������������� �������� ����������(������������ ��� �����������)
void cw::DelayMs(int ms) {
	QTime dieTime = QTime::currentTime().addMSecs(ms);
	while (QTime::currentTime() < dieTime) {
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}

//��������� ����������� �����, � �������� �������� ��������
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
//����������� ����������� ����� ����� ������
void connectElemes(QPainter* painter, TreapElem* e1, TreapElem* e2, QRect qr1, QRect qr2) {
	if (e1 && e2) {
		QPointF f1(qr1.center().x(), qr1.center().y() + 25);
		QPointF f2(qr2.center().x(), qr2.center().y() - 25);;

		painter->drawLine(f1, f2);
	}
}
//����������� ����������� �������� � ��� ��������
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

//�������, ���������� ������������ ��������
void cw::paintTreap(QPainter* painter, Treap treap){
	
	this->paintElem(painter, treap.root, new QRect(this->width()/2 , 200, 50, 50), 256);
}

//�������, ��� ������� �������������� ��������, ���������� �� ���� ���������� ��������
void cw::paintEvent(QPaintEvent *event){

	QPainter* painter = new QPainter(this);
	paintTreap(painter, treap);
}
//�������, ������������ ���������� ������������� �����
QString convertedString(const char* s){
	QTextCodec *codec1 = QTextCodec::codecForName("CP1251");
	QString text = codec1->toUnicode(s);
	return text;
}
//�������� �������� � ��� �������� � �����-�� ���� ����
void colorRecursively(QColor color, TreapElem*& e) {
	if (e) {
		e->color = color;
		colorRecursively(color, e->left);
		colorRecursively(color, e->right);
	}
	else return;
}
//���������������� ������� ������
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
 
//����������������� ������� �������
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
 //����������� �������� �������� �� ��������
void cw::visualisedInsert(TreapElem*& root, TreapElem a) {
	

	actionLabel->setText(convertedString("�������� �������� ����"));
	if (root == nullptr){
		actionLabel->setText(convertedString("�������� ������ ����. �������� �������� ") + QString(a)
		+ convertedString(" �� ��� �����"));
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

	//��������� ����� �������� �������� � ������ �������� ����
	if (a.key < root->key) {
		actionLabel->setText(convertedString("�������� ����� ������������ �������� ") + QString(a)
		+ convertedString(" ������ �������� ����� �������� �������� ") + QString(*root)
		+ convertedString("\n������� � ������ �������"));

		DelayMs(mDelay);
		root->color = Qt::white;
		update();
		visualisedInsert(root->left, a);
	}
	//���� ���� ������������ �������� ������ (��� �����) ����� �������� ��������
	else{
		actionLabel->setText(convertedString("�������� ����� ������������ �������� ") + QString(a)
		+ convertedString(" ������(��� �����) �������� ����� �������� �������� ") + QString(*root)
		+ convertedString("\n������� � ������� �������"));

		DelayMs(mDelay);
		root->color = Qt::white;
		update();
		visualisedInsert(root->right, a);
	}

	//�������� (���� ���������)
	if (root->left && root->left->prior > root->prior) {
		actionLabel->setText(convertedString("�������� ���������� ������ ������� ") + QString(*root->left)
		+ convertedString(" ������ ��� �������� ���������� �������� �������� ") + QString(*root)
		+ convertedString("\n�������������� ������� �������\n"));

		visualisedRotateRight(root);
		update();
	}

	if (root->right && root->right->prior > root->prior) {
		actionLabel->setText(convertedString("�������� ���������� ������� �������: ") + QString(*root->right) 
		+ convertedString(" ������ ��� �������� ���������� �������� �������� ") + QString(*root)
		+ convertedString("\n�������������� ������� ������\n"));
		
		visualisedRotateLeft(root);
		update();
	}
}

//���������������� �������� �������� �� ��������
void cw::visualisedDelete(TreapElem*& root, TreapElem a) {

	//���� �������� ��� � ��������
	if (root == nullptr){
		return;
	}
	root->color = Qt::green;
	update();
	actionLabel->setText(convertedString("�������� �������� ��������"));
	DelayMs(mDelay);
	root->color = Qt::white;
	if (a.key == root->key && a.prior == root->prior) {
		actionLabel->setText(convertedString("���������� ���������� � ������� ���������."));
		root->color = QColor(204, 102, 153);
		update();
		DelayMs(mDelay);
		//���� ������� �������� ������, �� �� ������ ���������
		if (isLeaf(root)) {
			actionLabel->setText(convertedString("������� �������� ������. �������������� ��������� ��������� �������� �� ���������"));
			actionLabel->setText(actionLabel->text() + convertedString("\n�������� ��������"));
			DelayMs(mDelay);
			root = nullptr;
		}
		//���� ������� ����� ���� ��������, �� ���������� ���������� ��������, ���� ���� ������� �� ������
		//���� ������, ���� ����� � ������ ����� ��������
		else if (root->left && root->right){
			actionLabel->setText(convertedString("������� ����� ���� ��������. ���������� ���������� ��������."));
			DelayMs(mDelay);

			// � ������, ���� � ������ ������� ��������� ����, ��� � �������, �������������� ������� �������
			if (root->left->prior < root->right->prior){

				actionLabel->setText(convertedString("������ ������� �������� ����� ������� ���������, ��� �����\n"));
				actionLabel->setText(actionLabel->text() + convertedString("�������������� ������� ������"));
				// ������� ������
				visualisedRotateLeft(root);

				// ������� ������� ������ �� ����� ������ �������, ��������� ��� ��������
				visualisedDelete(root->left, a);
			}
			//���� � ������� ������� ������� ���������, �� ����� �������� ������� ������
			else{
				actionLabel->setText(convertedString("����� ������� �������� ����� ������� ���������, ��� ������\n"));
				actionLabel->setText(actionLabel->text() + convertedString("�������������� ������� �������"));
				// ������� �����o
				visualisedRotateRight(root);

				// ������� ������� ������ �� ����� ������ �������, ��������� ��� ��������
				visualisedDelete(root->right, a);
			}
		}
		//�������� ���� � ����� ��������
		else{
			actionLabel->setText(convertedString("������� ����� ������ �������"));
			TreapElem* child = (root->left) ? root->left : root->right;
			colorRecursively(QColor(150, 150, 150), child);
			update();
			DelayMs(mDelay);
			root = child;
			actionLabel->setText(convertedString("������������ �������� �������� �������� ��� �������"));
			update();
			DelayMs(mDelay);
		}
		//�������� ��������, �������� �� ����� ����������, � ����� ����
		if (root) colorRecursively(Qt::white, root);
		return;
	}
	//���� ���������� �������� �������� � ������� ���, �� ����� � ����������� ��
	//���������� ������������ ����� ��������� �����
	if (a.key < root->key) {
		actionLabel->setText(convertedString("�������� ����� ������������ �������� - ") + QString(a)
			+ convertedString(" ������ �������� ����� �������� �������� - ") + QString(*root) +
			convertedString("\n������� � ������ �������"));
		DelayMs(mDelay);
		visualisedDelete(root->left, a);
	}
	else {
		actionLabel->setText(convertedString("�������� ����� ������������ �������� - ") + QString(a)
			+ convertedString(" ������ �������� ����� �������� �������� - ") + QString(*root) +
			convertedString("\n������� � ������� �������"));
		DelayMs(mDelay);
		visualisedDelete(root->right, a);
	}
}
//���������� ������� �� ������ ��������
void cw::deleteButtonClicked() {

	
	bool correct = elemRegExp.exactMatch(input->text());//�������� ����� ��� ������ ����������� ���������
	if (correct) { //���� ���� ���������, ����������� �������� ��������, ������ ��� �������� � ������� ���������� �����������
				   //��� � ���� ��� ����� ��������
		input->setDisabled(1);
		int h = elemRegExp.cap(2).toInt();
		int g = elemRegExp.cap(1).toInt();
		TreapElem ex(g, h);
		if (treap.find(treap.root, ex) != 0) {
			deleteButton->setDisabled(1);
			insertButton->setDisabled(1);
			statusLabel->setText(convertedString("�������� ��������") + QString(ex));
			visualisedDelete(treap.root, ex);
			actionLabel->setText(convertedString(""));
			statusLabel->setText(convertedString("�������� ���������"));
			update();
		}
		else statusLabel->setText(convertedString("������� �� ������������ � ��������"));
	}
	else statusLabel->setText(convertedString("������������ ����"));
	deleteButton->setDisabled(0);
	insertButton->setDisabled(0);
	input->setDisabled(0);
	input->setFocus();
}
//���������� ������� �� ������ �������
void cw::insertButtonClicked(){

	bool correct = elemRegExp.exactMatch(input->text()); //�������� ����� ��� ������ ����������� ���������
	if (correct) { //���� ���� ���������, ����������� �������� �������, ������ ��� �������� � ������� ���������� �����������
				   //��� � ���� ��� ����� ��������
		deleteButton->setDisabled(1); 
		insertButton->setDisabled(1);
		input->setDisabled(1);
		int h = elemRegExp.cap(2).toInt();
		int g = elemRegExp.cap(1).toInt();
		TreapElem ex(g, h);
		statusLabel->setText(convertedString("������� ��������") + QString(ex));
		visualisedInsert(treap.root, ex);
		actionLabel->setText(convertedString(""));
		statusLabel->setText(convertedString("������� ���������"));
		update();
	}		//����� ��������� ��������� �� ����
	else statusLabel->setText(convertedString("������������ ����"));

	deleteButton->setDisabled(0);
	insertButton->setDisabled(0);
	input->setDisabled(0);
	input->setFocus();
}