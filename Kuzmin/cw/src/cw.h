#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_cw.h"
#include "QTimer"
#include "QLabel"
#include <QLineEdit>
#include "QPainter"
#include "treap.h"
#include <QTime>
#include <ctime>
#include <QTextCodec>
#include "QRegExp"
#include <regex>
#include <QPushButton>
#include <QRadioButton>
class cw : public QMainWindow
{
    Q_OBJECT

public:
    cw(QWidget *parent = Q_NULLPTR);
	Treap treap;
	QLabel* actionLabel;
	QLabel* statusLabel;
	QLabel* inputLabel;
	QLabel* fileTextLabel;
	QPushButton* insertButton;
	QPushButton* deleteButton;
	QPushButton* stopButton;
	QPushButton* continueButton;
	QPushButton* stepButton;
	QRadioButton* automodeButton;
	bool step = false;
	bool automode = false;

	QLineEdit* input;
	QRegExp elemRegExp;
	QRegExp treapRegExp;
	int mDelay = 5000;
	void paintElem(QPainter* painter, TreapElem* e, QRect* qr, float xcoef);
	void paintTreap(QPainter* painter, Treap treap);
	void DelayMs(int ms);

	void visualisedInsert(TreapElem*& root, TreapElem a);
	void visualisedRotateRight(TreapElem*& root);
	void visualisedRotateLeft(TreapElem*& root);
	void visualisedDelete(TreapElem*& root, TreapElem a);

public slots:
	void insertButtonClicked();
	void deleteButtonClicked();
	void stepButtonClicked();
	void automodeButtonClicked();

private:
    Ui::cwClass ui;

protected:
	void paintEvent(QPaintEvent *event);
	
};
